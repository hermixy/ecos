#ifndef CYGONCE_ASSABET_H
#define CYGONCE_ASSABET_H

/*=============================================================================
//
//      assabet.h
//
//      Platform specific support (register layout, etc)
//
//=============================================================================
// ####ECOSGPLCOPYRIGHTBEGIN####                                            
// -------------------------------------------                              
// This file is part of eCos, the Embedded Configurable Operating System.   
// Copyright (C) 1998, 1999, 2000, 2001, 2002 Free Software Foundation, Inc.
//
// eCos is free software; you can redistribute it and/or modify it under    
// the terms of the GNU General Public License as published by the Free     
// Software Foundation; either version 2 or (at your option) any later      
// version.                                                                 
//
// eCos is distributed in the hope that it will be useful, but WITHOUT      
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or    
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License    
// for more details.                                                        
//
// You should have received a copy of the GNU General Public License        
// along with eCos; if not, write to the Free Software Foundation, Inc.,    
// 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.            
//
// As a special exception, if other files instantiate templates or use      
// macros or inline functions from this file, or you compile this file      
// and link it with other works to produce a work based on this file,       
// this file does not by itself cause the resulting work to be covered by   
// the GNU General Public License. However the source code for this file    
// must still be made available in accordance with section (3) of the GNU   
// General Public License v2.                                               
//
// This exception does not invalidate any other reasons why a work based    
// on this file might be covered by the GNU General Public License.         
// -------------------------------------------                              
// ####ECOSGPLCOPYRIGHTEND####                                              
//=============================================================================
//#####DESCRIPTIONBEGIN####
//
// Author(s):    gthomas
// Contributors: gthomas
// Date:         2000-05-08
// Purpose:      Intel SA1110/Assabet platform specific support routines
// Description: 
// Usage:        #include <cyg/hal/assabet.h>
//
//####DESCRIPTIONEND####
//
//===========================================================================*/


#ifndef __ASSEMBLER__
//
// Board Control Register
// Note: This register is write-only.  Thus a shadow copy is provided so that
// it may be safely updated/shared by multiple threads.
//
extern unsigned long _assabet_BCR;  // Shadow copy

extern void assabet_BCR(unsigned long mask, unsigned long value);

//
// Board Configuration data - read at RESET
//
extern unsigned long _assabet_CFG;
#endif

// 
// Signal assertion levels
//
#define SA1110_LOGIC_ONE(m)  (m & 0xFFFFFFFF)
#define SA1110_LOGIC_ZERO(m) (m & 0x00000000)

//
// SA1110/Assabet Board Control Register
//
#define SA1110_BOARD_CONTROL        REG32_PTR(0x12000000)
#define SA1110_BCR_MIN              0x00A014E4     // Reset state

#define SA1110_BCR_CF_POWER         0x00000001     // 1 = CompactFlash power on
#define SA1110_BCR_CF_POWER_ON      SA1110_LOGIC_ONE(SA1110_BCR_CF_POWER)
#define SA1110_BCR_CF_POWER_OFF     SA1110_LOGIC_ZERO(SA1110_BCR_CF_POWER)
#define SA1110_BCR_CF_RESET         0x00000002     // 1 = CompactFlash reset
#define SA1110_BCR_CF_RESET_ENABLE  SA1110_LOGIC_ONE(SA1110_BCR_CF_RESET)
#define SA1110_BCR_CF_RESET_DISABLE SA1110_LOGIC_ZERO(SA1110_BCR_CF_RESET)
#define SA1110_BCR_SOFT_RESET       0x00000004     // 0 = resets UCB1300, ADI7171, UDA1341
#define SA1110_BCR_IRDA_FREQ        0x00000008     // 0 = SIR, 1 = MIR/FIR
#define SA1110_BCR_IRDA_MD          0x00000030     // IrDA Mode & range
#define SA1110_BCR_IRDA_MD_MAX      0x00000000     // Max range and power
#define SA1110_BCR_IRDA_MD_OFF      0x00000010     // Shutdown
#define SA1110_BCR_IRDA_MD_23       0x00000020     // 2/3 power
#define SA1110_BCR_IRDA_MD_13       0x00000030     // 1/3 power
#define SA1110_BCR_STEREO_LB        0x00000040     // 1 = Stereo loopback on
#define SA1110_BCR_CF_BUS           0x00000080     // 0 = CompactFlash bus on
#define SA1110_BCR_CF_BUS_ON        SA1110_LOGIC_ZERO(SA1110_BCR_CF_BUS)
#define SA1110_BCR_CF_BUS_OFF       SA1110_LOGIC_ONE(SA1110_BCR_CF_BUS)
#define SA1110_BCR_AUDIO_ON         0x00000100     // 1 = UDA1341, MIC, DAA power on
#define SA1110_BCR_BACKLIGHT        0x00000200     // 1 = LCD backlight on
#define SA1110_BCR_LCD_BPP          0x00000400     // 1 = 16 RGB, 0 = 12 RGB
#define SA1110_BCR_LCD_16BPP        SA1110_LOGIC_ONE(SA1110_BCR_LCD_BPP)
#define SA1110_BCR_LCD_12BPP        SA1110_LOGIC_ZERO(SA1110_BCR_LCD_BPP)
#define SA1110_BCR_LCD              0x00000800     // 1 = LCD panel and controller on
#define SA1110_BCR_LCD_ON           SA1110_LOGIC_ONE(SA1110_BCR_LCD)
#define SA1110_BCR_LCD_OFF          SA1110_LOGIC_ZERO(SA1110_BCR_LCD)
#define SA1110_BCR_RS232_ENABLE     0x00001000     // 1 = Enable RD232 signals
#define SA1110_BCR_RED_LED          0x00002000     // 0 = Red LED on
#define SA1110_BCR_RED_LED_ON       SA1110_LOGIC_ZERO(SA1110_BCR_RED_LED)
#define SA1110_BCR_RED_LED_OFF      SA1110_LOGIC_ONE(SA1110_BCR_RED_LED)
#define SA1110_BCR_GREEN_LED        0x00004000     // 0 = Green LED on
#define SA1110_BCR_GREEN_LED_ON     SA1110_LOGIC_ZERO(SA1110_BCR_GREEN_LED)
#define SA1110_BCR_GREEN_LED_OFF    SA1110_LOGIC_ONE(SA1110_BCR_GREEN_LED)
#define SA1110_BCR_MOTOR            0x00008000     // 1 = Vibrator motor on
#define SA1110_BCR_MOTOR_ON         SA1110_LOGIC_ONE(SA1110_BCR_MOTOR)
#define SA1110_BCR_MOTOR_OFF        SA1110_LOGIC_ZERO(SA1110_BCR_MOTOR)
#define SA1110_BCR_COM_DTR          0x00010000     // COM port Data Terminal Ready
#define SA1110_BCR_COM_RTS          0x00020000     // COM port Request To Send
#define SA1110_BCR_RADIO_WAKE       0x00040000     // 1 = Wake up CPU with radio
#define SA1110_BCR_MUTE             0x00200000     // 1 = Audio muted

//
// Special purpose GPIO interrupt mappings
//
#define SA1110_CF_IRQ               CYGNUM_HAL_INTERRUPT_GPIO21
#define SA1110_CF_DETECT            CYGNUM_HAL_INTERRUPT_GPIO22

//
// GPIO layout
//
#define SA1110_GPIO_CF_DETECT       0x00400000     // 0 = Compact Flash detect
#define SA1110_GPIO_CF_PRESENT      SA1110_LOGIC_ZERO(SA1110_GPIO_CF_DETECT)
#define SA1110_GPIO_CF_ABSENT       SA1110_LOGIC_ONE(SA1110_GPIO_CF_DETECT)

//
// LCD Controller
//
#define SA1110_LCCR0                SA11X0_REGISTER(0x30100000)
#define SA1110_LCSR                 SA11X0_REGISTER(0x30100004)
#define SA1110_DBAR1                SA11X0_REGISTER(0x30100010)
#define SA1110_DCAR1                SA11X0_REGISTER(0x30100014)
#define SA1110_DBAR2                SA11X0_REGISTER(0x30100018)
#define SA1110_DCAR2                SA11X0_REGISTER(0x3010001C)
#define SA1110_LCCR1                SA11X0_REGISTER(0x30100020)
#define SA1110_LCCR2                SA11X0_REGISTER(0x30100024)
#define SA1110_LCCR3                SA11X0_REGISTER(0x30100028)

/*---------------------------------------------------------------------------*/
/* end of assabet.h                                                          */
#endif /* CYGONCE_ASSABET_H */
