/*
  Copyright (c) 2014-2015 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
/*
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * + Pin number |  ZERO Board pin  |  PIN   | Label/Name      | Comments (* is for default peripheral in use)
  * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            |     Serial       |        |                 |
 * | 0          | RX               |  PA14  |                 | EIC/EXTINT[11] ADC/AIN[19]           PTC/X[3] *SERCOM0/PAD[3]  SERCOM2/PAD[3]  TCC0/WO[3]  TCC1/WO[1]
 * | 1          | TX               |  PA15  |                 | EIC/EXTINT[10] ADC/AIN[18]           PTC/X[2] *SERCOM0/PAD[2]                  TCC0/WO[2]  TCC1/WO[0]
  * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | Digital Low      |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 2          | ~2               |  PA08  |                 | EIC/EXTINT[15]                                 SERCOM2/PAD[3]  SERCOM4/PAD[3] *TC3/WO[1]   TCC0/WO[5]
 * | 3          | ~3               |  PA09  |                 | EIC/NMI        ADC/AIN[16]           PTC/X[0]  SERCOM0/PAD[0]  SERCOM2/PAD[0] *TCC0/WO[0]  TCC1/WO[2]
 * | 4          | ~4               |  PA20  |                 | EIC/EXTINT[4]                        PTC/X[8]  SERCOM5/PAD[2]  SERCOM3/PAD[2]             *TCC0/WO[6]
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | Digital High     |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 5          | ~5               |  PA07  |                 | EIC/EXTINT[7]  ADC/AIN[7]  AC/AIN[3] PTC/Y[5]  SERCOM0/PAD[3]                 *TCC1/WO[1]
 * | 6          | ~6               |  PA18  |                 | EIC/EXTINT[2]                        PTC/X[6] +SERCOM1/PAD[2]  SERCOM3/PAD[2] *TC3/WO[0]    TCC0/WO[2]
 * | 7          | ~7               |  PA16  |                 | EIC/EXTINT[0]                        PTC/X[4] +SERCOM1/PAD[0]  SERCOM3/PAD[0] *TCC2/WO[0]   TCC0/WO[6]
 * | 8          | 8                |  PA19  |                 | EIC/EXTINT[3]                        PTC/X[7] +SERCOM1/PAD[3]  SERCOM3/PAD[3]  TC3/WO[1]   *TCC0/WO[3]
 * | 9          | 9                |  PA27  | BUTTON LED      | EIC/EXTINT[1]                        PTC/X[5] +SERCOM1/PAD[1]  SERCOM3/PAD[1] *TCC2/WO[1]   TCC0/WO[7]
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | Analog Connector |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 10         | A0               |  PA02  | A0              | EIC/EXTINT[2] *ADC/AIN[0]  DAC/VOUT  PTC/Y[0]
 * | 11         | A1               |  PA04  | A1              | EIC/EXTINT[4] *ADC/AIN[4]  AC/AIN[0] PTC/Y[2]  SERCOM0/PAD[0]                  TCC0/WO[0]
 * | 12         | A2               |  PA05  | A2              | EIC/EXTINT[5] *ADC/AIN[5]  AC/AIN[1] PTC/Y[5]  SERCOM0/PAD[1]                  TCC0/WO[1]
 * | 13         | A3               |  PA06  | A3              | EIC/EXTINT[6]  ADC/AIN[6]  AC/AIN[2] PTC/Y[4]  SERCOM0/PAD[2]                 *TCC1/WO[0]
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            |     Wire         |        |                 |
 * | 14         | SDA              |  PA08  | SDA             | EIC/EXTINT[6]                        PTC/X[10] *SERCOM3/PAD[0] SERCOM5/PAD[0] TC4/WO[0] TCC0/WO[4]
 * | 15         | SCL              |  PA09  | SCL             | EIC/EXTINT[7]                        PTC/X[11] *SERCOM3/PAD[1] SERCOM5/PAD[1] TC4/WO[1] TCC0/WO[5]
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            |SPI (Legacy ICSP) |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 16         | MISO             |  PA16  | MISO            | EIC/EXTINT[12] SERCOM2/PAD[0] *SERCOM4/PAD[0] TCC2/WO[0] TCC0/WO[6]
 * |            | 2                |        | 5V0             |
 * | 17         | MOSI             |  PA17  | MOSI            | EIC/EXTINT[10]                *SERCOM4/PAD[2] TC5/WO[0]  TCC0/WO[4]
 * | 18         | SCK              |  PA18  | SCK             | EIC/EXTINT[11]                *SERCOM4/PAD[3] TC5/WO[1]  TCC0/WO[5]
 * |            | 5                |        | RESET           |
 * |            | 6                |        | GND             |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | LEDs             |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 19         |                  |  PA28  | LED             |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | USB              |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 20         |                  |  PA23  | USB_HOST_ENABLE | EIC/EXTINT[8]
 * | 21         |                  |  PA24  | USB_NEGATIVE    | *USB/DM
 * | 22         |                  |  PA25  | USB_POSITIVE    | *USB/DP
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            |                  |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | GND              |        |                 |
 * | 23         | AREF             |  PA03  |                 | EIC/EXTINT[3] *[ADC|DAC]/VREFA ADC/AIN[1] PTC/Y[1]
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 24         |                  |  PA02  |                 | Alternate use of A0 (DAC output)
 * | 25         |                  |  PA30  |                 | SWCLK, alternate use EXTINT[10] TCC1/WO[0] SERCOM1/PAD[2]
 * | 26         |                  |  PA31  |                 | SWDIO, alternate use EXTINT[11] TCC1/WO[1] SERCOM1/PAD[3]
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            |32.768KHz Crystal |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            |                  |  PA00  | XIN32           | EIC/EXTINT[0] SERCOM1/PAD[0] TCC2/WO[0]
 * |            |                  |  PA01  | XOUT32          | EIC/EXTINT[1] SERCOM1/PAD[1] TCC2/WO[1]
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 */


#include "variant.h"

/*
 * Pins descriptions
 */
const PinDescription g_APinDescription[]=
{
  // ----------------------
  // 0/1 - SERCOM/UART (Serial1)
  { PORTA, 15, PIO_SERCOM, (PIN_ATTR_DIGITAL), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_6 }, // RX: SERCOM0/PAD[3]
  { PORTA, 16, PIO_SERCOM, (PIN_ATTR_DIGITAL), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_7 }, // TX: SERCOM0/PAD[2]

  // 2..9 - Digital pins
  // Digital Low
  //{ PORTA, 14, PIO_DIGITAL  , (PIN_ATTR_DIGITAL                                ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_14  },
  { PORTA,  8, PIO_TIMER    , (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER    ), No_ADC_Channel, PWM0_CH0  , TCC0_CH0    , EXTERNAL_INT_NMI }, // TCC0/WO[0]
  { PORTA,  9, PIO_TIMER    , (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER    ), No_ADC_Channel, PWM0_CH1  , TCC0_CH1    , EXTERNAL_INT_9   }, // TCC0/WO[1]
  { PORTA, 20, PIO_TIMER_ALT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER_ALT), No_ADC_Channel, PWM0_CH6  , TCC0_CH6    , EXTERNAL_INT_4   }, // TCC0/WO[6]
  
  // Digital High
  { PORTA,  7, PIO_TIMER    , (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER    ), No_ADC_Channel, PWM1_CH1  , TCC1_CH1    , EXTERNAL_INT_7    }, // TCC1/WO[1]
  { PORTA, 27, PIO_DIGITAL  , (PIN_ATTR_DIGITAL                                ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // used as output only

  // 10..13 - Analog pins
  // --------------------
  { PORTA,  2, PIO_ANALOG, (PIN_ATTR_ANALOG), ADC_Channel0, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2 }, // ADC/AIN[0]
  { PORTA,  4, PIO_ANALOG, (0              ), ADC_Channel4, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_4 }, // ADC/AIN[4]
  { PORTA,  5, PIO_ANALOG, (0              ), ADC_Channel5, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_5 }, // ADC/AIN[5]
  { PORTA,  6, PIO_ANALOG, (0              ), ADC_Channel6, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_6 }, // ADC/AIN[6]
  
  // 14..15 I2C pins (SDA/SCL)
  // ----------------------
  { PORTA, 8, PIO_SERCOM, (PIN_ATTR_DIGITAL), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_6 }, // SDA: SERCOM0/PAD[0]
  { PORTA, 9, PIO_SERCOM, (PIN_ATTR_DIGITAL), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_7 }, // SCL: SERCOM0/PAD[1]


  // 16..18 - SPI pins (ICSP:MISO,SCK,MOSI)
  // ----------------------
  { PORTA, 16, PIO_SERCOM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // MISO: SERCOM4/PAD[0]
  { PORTA, 17, PIO_SERCOM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // MOSI: SERCOM4/PAD[2]
  { PORTA, 18, PIO_SERCOM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // SCK: SERCOM4/PAD[3]


  // 19 - LEDS (PA28)
  // --------------------
  { PORTA, 28, PIO_OUTPUT, (PIN_ATTR_DIGITAL), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // used as output only
  
  // 20..22 - USB
  // --------------------
  { PORTA, 23, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // USB Host enable
  { PORTA, 24, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // USB/DM
  { PORTA, 25, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // USB/DP
  
  // 23 (AREF)
  { PORTA, 3, PIO_ANALOG, (PIN_ATTR_ANALOG), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // DAC/VREFP

  // ----------------------
  // 24..26 - Alternate use of A0 (DAC output), 44 SWCLK, 45, SWDIO
  { PORTA,  2, PIO_ANALOG, (PIN_ATTR_ANALOG            ), DAC_Channel0  , NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2  }, // DAC/VOUT
  { PORTA, 30, PIO_PWM   , (PIN_ATTR_DIGITAL|PIO_SERCOM), No_ADC_Channel, NOT_ON_PWM, TCC1_CH0    , EXTERNAL_INT_10 }, // SWCLK
  { PORTA, 31, PIO_PWM   , (PIN_ATTR_DIGITAL|PIO_SERCOM), No_ADC_Channel, NOT_ON_PWM, TCC1_CH1    , EXTERNAL_INT_11 }, // SWDIO
} ;

extern "C" {
    unsigned int PINCOUNT_fn() {
        return (sizeof(g_APinDescription) / sizeof(g_APinDescription[0]));
    }
}

const void* g_apTCInstances[TCC_INST_NUM+TC_INST_NUM]={ TCC0, TCC1, TCC2, TC3, TC4, TC5 } ;

// Multi-serial objects instantiation
SERCOM sercom0( SERCOM0 ) ;
SERCOM sercom1( SERCOM1 ) ;
SERCOM sercom2( SERCOM2 ) ;
SERCOM sercom3( SERCOM3 ) ;
//SERCOM sercom4( SERCOM4 ) ;
//SERCOM sercom5( SERCOM5 ) ;

Uart Serial1( &sercom0, PIN_SERIAL1_RX, PIN_SERIAL1_TX, PAD_SERIAL1_RX, PAD_SERIAL1_TX ) ;
//Uart Serial( &sercom5, PIN_SERIAL_RX, PIN_SERIAL_TX, PAD_SERIAL_RX, PAD_SERIAL_TX ) ;
void SERCOM0_Handler()
{
  Serial1.IrqHandler();
}

//void SERCOM3_Handler()
//{
//  Serial.IrqHandler();
//}

