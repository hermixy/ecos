#ifndef CYGONCE_HAL_PLATFORM_INTS_H
#define CYGONCE_HAL_PLATFORM_INTS_H
//==========================================================================
//
//      hal_platform_ints.h
//
//      HAL Interrupt and clock support
//
//==========================================================================
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
//==========================================================================
//#####DESCRIPTIONBEGIN####
//
// Author(s):    gthomas
// Contributors: gthomas
// Date:         1999-04-21
// Purpose:      Define Interrupt support
// Description:  The interrupt details for the CMA230 are defined here.
// Usage:
//               #include <cyg/hal/hal_platform_ints.h>
//               ...
//              
//
//####DESCRIPTIONEND####
//
//==========================================================================

#define CYGNUM_HAL_INTERRUPT_unused     0
#define CYGNUM_HAL_INTERRUPT_ABORT      1
#define CYGNUM_HAL_INTERRUPT_SERIAL_B   2
#define CYGNUM_HAL_INTERRUPT_SERIAL_A   3
#define CYGNUM_HAL_INTERRUPT_TIMER      4
#define CYGNUM_HAL_INTERRUPT_ETHER_PP   5  // Ethernet or Parallel port
#define CYGNUM_HAL_INTERRUPT_SLOT1      6
#define CYGNUM_HAL_INTERRUPT_SLOT2      7
#define CYGNUM_HAL_INTERRUPT_SLOT3      8

#define CYGNUM_HAL_ISR_MIN              0
#define CYGNUM_HAL_ISR_MAX              8
#define CYGNUM_HAL_ISR_COUNT            (CYGNUM_HAL_ISR_MAX+1)

// The vector used by the Real time clock
#define CYGNUM_HAL_INTERRUPT_RTC        CYGNUM_HAL_INTERRUPT_TIMER


//----------------------------------------------------------------------------
// Reset.
#define HAL_PLATFORM_RESET()             CYG_EMPTY_STATEMENT

#define HAL_PLATFORM_RESET_ENTRY 0xe000000

#endif // CYGONCE_HAL_PLATFORM_INTS_H
