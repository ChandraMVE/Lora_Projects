#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "apps_common.h"
#include "apps_utilities.h"
#include "lr11xx_radio.h"
#include "lr11xx_system.h"
#include "lr11xx_system_types.h"
#include "lr11xx_regmem.h"
#include "main_ping_pong.h"
#include "smtc_hal_dbg_trace.h"
#include "uart_init.h"
#include "stm32l4xx_ll_utils.h"
#include "lis2de12_drv.h"

#define PAYLOAD_LENGTH 32  // Define the length of the payload, adjust as necessary
#define ITERATION_INDEX (PING_PONG_PREFIX_SIZE + 1)
#define IRQ_MASK (LR11XX_SYSTEM_IRQ_RX_DONE | LR11XX_SYSTEM_IRQ_TIMEOUT | LR11XX_SYSTEM_IRQ_HEADER_ERROR | LR11XX_SYSTEM_IRQ_CRC_ERROR | LR11XX_SYSTEM_IRQ_FSK_LEN_ERROR)

static uint8_t received_data[PAYLOAD_LENGTH];
static lr11xx_hal_context_t* context;

static void init_receiver(void);
static void handle_rx_done(void);
static void handle_rx_timeout(void);
static void handle_rx_crc_error(void);
static void handle_fsk_len_error(void);

int main(void)
{
    smtc_hal_mcu_init();
    uart_init();
    HAL_DBG_TRACE_INFO(" ===== LR11xx Receiver example =====\n\r");

    context = apps_common_lr11xx_get_context();

    // Initialize the radio and system
    apps_common_lr11xx_system_init((void *)context);
    apps_common_lr11xx_radio_init((void *)context);

    ASSERT_LR11XX_RC(lr11xx_system_set_dio_irq_params(context, IRQ_MASK, 0));
    ASSERT_LR11XX_RC(lr11xx_system_clear_irq_status(context, LR11XX_SYSTEM_IRQ_ALL_MASK));

    // Initialize receiver
    init_receiver();

    while (1)
    {
        // Main loop: process IRQs
        apps_common_lr11xx_irq_process(context, IRQ_MASK);
    }
}

static void init_receiver(void)
{
    // Initialize the receiver
    apps_common_lr11xx_handle_pre_rx();
    ASSERT_LR11XX_RC(lr11xx_radio_set_rx(context, 0));
}

static void handle_rx_done(void)
{
    // Read received data
    lr11xx_status_t status = lr11xx_regmem_read_buffer8(context, received_data, 0, PAYLOAD_LENGTH);
    ASSERT_LR11XX_RC(status);

    // Process the received data
    HAL_DBG_TRACE_INFO("Received message of X axis %f, Y axis %f, Z axis %f\n\r",
        ((float *)received_data)[0], ((float *)received_data)[1], ((float *)received_data)[2]);

    // Reinitialize the receiver for the next message
    init_receiver();
}

static void handle_rx_timeout(void)
{
    // Print warning message
    HAL_DBG_TRACE_WARNING("Reception timeout occurred. Waiting for next packet...\n\r");

    // Reinitialize the receiver for the next message
    init_receiver();
}

static void handle_rx_crc_error(void)
{
    // Print error message
    HAL_DBG_TRACE_ERROR("CRC error occurred during reception.\n\r");

    // Reinitialize the receiver for the next message
    init_receiver();
}

static void handle_fsk_len_error(void)
{
    // Print error message
    HAL_DBG_TRACE_ERROR("FSK length error occurred during reception.\n\r");

    // Reinitialize the receiver for the next message
    init_receiver();
}

/**
 * @brief Handle the reception of data.
 */
void on_rx_done(void)
{
    handle_rx_done();
}

/**
 * @brief Handle reception timeout event.
 */
void on_rx_timeout(void)
{
    handle_rx_timeout();
}

/**
 * @brief Handle CRC error event during reception.
 */
void on_rx_crc_error(void)
{
    handle_rx_crc_error();
}

/**
 * @brief Handle FSK length error event during reception.
 */
void on_fsk_len_error(void)
{
    handle_fsk_len_error();
}
