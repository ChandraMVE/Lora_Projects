/*!
 * @file      main_ping_pong.c
 *
 * @brief     Ping-pong example for LR11xx chip
 *
 * The Clear BSD License
 * Copyright Semtech Corporation 2022. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted (subject to the limitations in the disclaimer
 * below) provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Semtech corporation nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY
 * THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT
 * NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SEMTECH CORPORATION BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
// Transmitter code.
/*
 * -----------------------------------------------------------------------------
 * --- DEPENDENCIES ------------------------------------------------------------
 */

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
#include "lis2de12_reg.h"
/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE MACROS-----------------------------------------------------------
 */

/**
 * @brief Size of ping-pong message prefix
 *
 * Expressed in bytes
 */
#define PING_PONG_PREFIX_SIZE 4

/**
 * @brief Threshold:number of exchanges before informing user on UART that the board pair is still not synchronized
 *
 * Expressed in number of packet exchanged
 */
#define SYNC_PACKET_THRESHOLD 64

/**
 * @brief Number of exchanges are stored in the payload of the packet exchanged during this PING-PONG communication
 *        this constant indicates where in the packet the two bytes used to count are located
 *
 * Expressed in bytes
 */

#define ITERATION_INDEX ( PING_PONG_PREFIX_SIZE + 1 )

/**
 * @brief Duration of the wait before packet transmission to assure reception status is ready on the other side
 *
 * Expressed in milliseconds
 */
#define DELAY_BEFORE_TX_MS 20

/**
 * @brief Duration of the wait between each ping-pong activity, can be used to adjust ping-pong speed
 *
 * Expressed in milliseconds
 */
#define DELAY_PING_PONG_PACE_MS 200

/**
 * @brief LR11xx interrupt mask used by the application
 */
#define IRQ_MASK                                                                          \
    ( LR11XX_SYSTEM_IRQ_TX_DONE | LR11XX_SYSTEM_IRQ_RX_DONE | LR11XX_SYSTEM_IRQ_TIMEOUT | \
      LR11XX_SYSTEM_IRQ_HEADER_ERROR | LR11XX_SYSTEM_IRQ_CRC_ERROR | LR11XX_SYSTEM_IRQ_FSK_LEN_ERROR )

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE CONSTANTS -------------------------------------------------------
 */

#define APP_PARTIAL_SLEEP true

/*
 * -----------------------------------------------------------------------------
 * --- GLOBAL VARIABLES -------------------------------------------------------
 */
//uint8_t acceleration_mg[3];

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE TYPES -----------------------------------------------------------
 */
union acceleration_data
{
	float 	aceeleration[3];
	uint8_t buffer_tx[PAYLOAD_LENGTH];

};

union acceleration_data tx,rx;

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE VARIABLES -------------------------------------------------------
 */

static lr11xx_hal_context_t* context;

//static uint8_t buffer_tx[PAYLOAD_LENGTH];

static bool    is_master = true;

//static const uint8_t ping_msg[PING_PONG_PREFIX_SIZE] = "PING";
//static const uint8_t pong_msg[PING_PONG_PREFIX_SIZE] = "PONG";

static uint8_t  iteration       = 0;
static uint16_t packets_to_sync = 0;

uint8_t buffer_rx[PAYLOAD_LENGTH];
uint8_t size;
uint8_t receive_buffer[PAYLOAD_LENGTH];

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE FUNCTIONS DECLARATION -------------------------------------------
 */

/**
 * @brief Handle reception failure for ping-pong example
 */
static void ping_pong_reception_failure_handling( void );

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC FUNCTIONS DEFINITION ---------------------------------------------
 */

/**
 * @brief Main application entry point.
 */
//int main( void )
//{
//    smtc_hal_mcu_init( );
//    apps_common_shield_init( );
//    uart_init();
//
//    HAL_DBG_TRACE_INFO( " ===== LR11xx Transmitter example =====\n\r" );
//    lis2de12_filter_hp_rst_on_int();
//    apps_common_print_sdk_driver_version( );
//
//    context = apps_common_lr11xx_get_context( );
//
//    apps_common_lr11xx_system_init( ( void* ) context );
//    apps_common_lr11xx_fetch_and_print_version( ( void* ) context );
//    apps_common_lr11xx_radio_init( ( void* ) context );
//
//    ASSERT_LR11XX_RC( lr11xx_system_set_dio_irq_params( context, IRQ_MASK, 0 ) );
//    ASSERT_LR11XX_RC( lr11xx_system_clear_irq_status( context, LR11XX_SYSTEM_IRQ_ALL_MASK ) );
//
//    /* Intializes random number generator */
//
//    srand( 10 );
//
//    for ( int i=0; i < 3; i++)
//    {
//    	tx.aceeleration[i] = acceleration_mg[i];
//    }
//
////    memcpy( buffer_tx, (uint8_t *)acceleration_mg, PAYLOAD_LENGTH );
//
//    ASSERT_LR11XX_RC( lr11xx_regmem_write_buffer8( context, tx.buffer_tx, PAYLOAD_LENGTH ) );
//
//    apps_common_lr11xx_handle_pre_tx( );
//
//    ASSERT_LR11XX_RC( lr11xx_radio_set_tx( context, 0 ) );
//
//    while( 1 )
//    {
//        apps_common_lr11xx_irq_process( context, IRQ_MASK );
//    }
//
//}
int main(void)
{
    smtc_hal_mcu_init();
    apps_common_shield_init();
    uart_init();

    HAL_DBG_TRACE_INFO(" ===== LR11xx Transmitter example =====\n\r");

    // Declare and initialize device context
    stmdev_ctx_t dev_ctx;
    uint8_t whoamI;

    /* Initialize mems driver interface */
    dev_ctx.write_reg = platform_write;
    dev_ctx.read_reg = platform_read;
    dev_ctx.mdelay = platform_delay;
    dev_ctx.handle = &SENSOR_BUS;

    // Initialize and configure accelerometer
    lis2de12_init_and_configure();

    apps_common_print_sdk_driver_version();

    context = apps_common_lr11xx_get_context();

    apps_common_lr11xx_system_init((void*)context);
    apps_common_lr11xx_fetch_and_print_version((void*)context);
    apps_common_lr11xx_radio_init((void*)context);

    ASSERT_LR11XX_RC(lr11xx_system_set_dio_irq_params(context, IRQ_MASK, 0));
    ASSERT_LR11XX_RC(lr11xx_system_clear_irq_status(context, LR11XX_SYSTEM_IRQ_ALL_MASK));

    // Initialize random number generator
    srand(10);

    while (1)
    {
        int16_t data_raw_acceleration[3];
        uint8_t reg_byte;

        // Read output only if new value is available
        lis2de12_xl_data_ready_get(&dev_ctx, &reg_byte);

        if (reg_byte)
        {
            lis2de12_acceleration_raw_get(&dev_ctx, data_raw_acceleration);

            tx.aceeleration[0] = lis2de12_from_fs2_to_mg(data_raw_acceleration[0]);
            tx.aceeleration[1] = lis2de12_from_fs2_to_mg(data_raw_acceleration[1]);
            tx.aceeleration[2] = lis2de12_from_fs2_to_mg(data_raw_acceleration[2]);

            // Copy data to buffer for transmission
            memcpy(tx.buffer_tx, (uint8_t*)&tx, PAYLOAD_LENGTH);

            if ((GPIOA->IDR & LL_GPIO_PIN_9) != 0x00u)
           {
            // Prepare for transmission
            ASSERT_LR11XX_RC(lr11xx_regmem_write_buffer8(context, tx.buffer_tx, PAYLOAD_LENGTH));
            apps_common_lr11xx_handle_pre_tx();

            // Transmit data
            ASSERT_LR11XX_RC(lr11xx_radio_set_tx(context, 0));

            // Process interrupts and errors
            apps_common_lr11xx_irq_process(context, IRQ_MASK);
           }
            //HAL_DBG_TRACE_INFO("AccX: %08.4f AccY: %08.4f AccZ: %08.4f\n\r", tx.aceeleration[0], tx.aceeleration[1], tx.aceeleration[2]);
        }

        // Wait before next read
        LL_mDelay(DELAY_PING_PONG_PACE_MS);
    }
}



void on_tx_done( void )
{
    apps_common_lr11xx_handle_post_tx( );
    HAL_DBG_TRACE_INFO( "Transmitted message of X axis %f, Transmitted message of Y axis %f, Transmitted message of Z axis %f"
    		"\n\r", tx.aceeleration[0], tx.aceeleration[1] , tx.aceeleration[2]  );

    LL_mDelay( DELAY_PING_PONG_PACE_MS );

    // lis2de12_filter_hp_rst_on_int();

    ASSERT_LR11XX_RC( lr11xx_regmem_write_buffer8( context, tx.buffer_tx, PAYLOAD_LENGTH ) );

    apps_common_lr11xx_handle_pre_tx( );

    ASSERT_LR11XX_RC( lr11xx_radio_set_tx( context, 0 ) );
}

void on_rx_timeout( void )
{
    packets_to_sync++;
    if( packets_to_sync > SYNC_PACKET_THRESHOLD )
    {
        HAL_DBG_TRACE_WARNING(
            "It looks like synchronisation is still not done, consider resetting one of the board\n\r" );
    }
    ping_pong_reception_failure_handling( );
}

void on_rx_crc_error( void )
{
    ping_pong_reception_failure_handling( );
}

void on_fsk_len_error( void )
{
    ping_pong_reception_failure_handling( );
}

static void ping_pong_reception_failure_handling( void )
{
    apps_common_lr11xx_handle_post_rx( );

    is_master = true;
    iteration = 0;

    tx.buffer_tx[ITERATION_INDEX] = iteration;

    ASSERT_LR11XX_RC( lr11xx_regmem_write_buffer8( context, tx.buffer_tx, PAYLOAD_LENGTH ) );

    apps_common_lr11xx_handle_pre_tx( );
    ASSERT_LR11XX_RC( lr11xx_radio_set_tx( context, 0 ) );
}
