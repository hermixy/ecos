#ifndef CYGONCE_HAL_CACHE_H
#define CYGONCE_HAL_CACHE_H

//=============================================================================
//
//      hal_cache.h
//
//      HAL cache control API
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
// Author(s):   nickg, gthomas
// Contributors:        nickg, gthomas
// Date:        1998-09-28
// Purpose:     Cache control API
// Description: The macros defined here provide the HAL APIs for handling
//              cache control operations.
// Usage:
//              #include <cyg/hal/hal_cache.h>
//              ...
//              
//
//####DESCRIPTIONEND####
//
//=============================================================================

#include <cyg/infra/cyg_type.h>
#include <cyg/hal/hal_io.h>

//-----------------------------------------------------------------------------
// Cache dimensions - one unified cache

#define HAL_CACHE_UNIFIED

#define HAL_UCACHE_SIZE                 0x800    // Size of cache in bytes
#define HAL_UCACHE_LINE_SIZE            4        // Size of a cache line
#define HAL_UCACHE_WAYS                 4        // Associativity of the cache

#define HAL_UCACHE_SETS (HAL_UCACHE_SIZE/(HAL_UCACHE_LINE_SIZE*HAL_UCACHE_WAYS))

// Cache & SRAM control
#define CYG_DEVICE_CCR          0xFFFFA400
#define CYG_DEVICE_LSCR         0xFFFFA404
#define CYG_DEVICE_CACHE_MEM    0x60000800

#define CCR_E                   0x01      // Cache enabled
#define CCR_S                   0x02      // SRAM mode enabled
#define CCR_F                   0x04      // Flush mode enabled
#define CCR_I                   0x08      // Invalidate mode

#define LCSR_E                  0x01      // Local SRAM enabled
#define LCSR_L                  0x02      // Local SRAM mapped to high memory

//-----------------------------------------------------------------------------
// Global control of cache

// Enable the cache
#define HAL_UCACHE_ENABLE()                                     \
{                                                               \
    HAL_WRITE_UINT8(CYG_DEVICE_CCR, CCR_E);                     \
}

// Disable the cache
#define HAL_UCACHE_DISABLE()                                    \
{                                                               \
    HAL_WRITE_UINT8(CYG_DEVICE_CCR, 0);                         \
}

// Invalidate the entire cache
#define HAL_UCACHE_INVALIDATE_ALL()             \
{                                               \
    register cyg_uint8 old_ccr;                 \
    HAL_READ_UINT8(CYG_DEVICE_CCR, old_ccr);    \
    HAL_WRITE_UINT8(CYG_DEVICE_CCR, CCR_I);     \
    HAL_WRITE_UINT8(CYG_DEVICE_CCR, old_ccr);   \
}

// Synchronize the contents of the cache with memory.
#define HAL_UCACHE_SYNC()                                               \
{                                                                       \
    register volatile cyg_uint32 *cache_SRAM =                          \
                     (volatile cyg_uint32*) CYG_DEVICE_CACHE_MEM;       \
    register int i;                                                     \
    register cyg_uint8 old_ccr;                                         \
    HAL_READ_UINT8(CYG_DEVICE_CCR, old_ccr);                            \
    HAL_WRITE_UINT8(CYG_DEVICE_CCR, CCR_F);                             \
    for (i = 0;  i < HAL_DCACHE_SETS;  i++) {                           \
        cyg_uint32 tmp = *cache_SRAM++;                                 \
    }                                                                   \
    HAL_WRITE_UINT8(CYG_DEVICE_CCR, CCR_I);                             \
    HAL_WRITE_UINT8(CYG_DEVICE_CCR, old_ccr);                           \
}

// Query the state of the cache
#define HAL_UCACHE_IS_ENABLED(_state_)          \
{                                               \
    cyg_uint8 __ccr;                            \
    HAL_READ_UINT8(CYG_DEVICE_CCR, __ccr);      \
    (_state_) = (CCR_E == __ccr) ? 1 : 0;       \
}

// Purge contents of cache
#define HAL_UCACHE_PURGE_ALL()  HAL_UCACHE_INVALIDATE_ALL()

// Set the cache refill burst size
//#define HAL_UCACHE_BURST_SIZE(_size_)

// Set the cache write mode
//#define HAL_UCACHE_WRITE_MODE( _mode_ )

//#define HAL_UCACHE_WRITETHRU_MODE       0
//#define HAL_UCACHE_WRITEBACK_MODE       1

// Load the contents of the given address range into the cache
// and then lock the cache so that it stays there.
//#define HAL_UCACHE_LOCK(_base_, _size_)

// Undo a previous lock operation
//#define HAL_UCACHE_UNLOCK(_base_, _size_)

// Unlock entire cache
//#define HAL_UCACHE_UNLOCK_ALL()

//-----------------------------------------------------------------------------
// Cache line control

// Allocate cache lines for the given address range without reading its
// contents from memory.
//#define HAL_UCACHE_ALLOCATE( _base_ , _size_ )

// Write dirty cache lines to memory and invalidate the cache entries
// for the given address range.
//#define HAL_UCACHE_FLUSH( _base_ , _size_ )

// Invalidate cache lines in the given range without writing to memory.
//#define HAL_UCACHE_INVALIDATE( _base_ , _size_ )

// Write dirty cache lines to memory for the given address range.
//#define HAL_UCACHE_STORE( _base_ , _size_ )

// Preread the given range into the cache with the intention of reading
// from it later.
//#define HAL_UCACHE_READ_HINT( _base_ , _size_ )

// Preread the given range into the cache with the intention of writing
// to it later.
//#define HAL_UCACHE_WRITE_HINT( _base_ , _size_ )

// Allocate and zero the cache lines associated with the given range.
//#define HAL_UCACHE_ZERO( _base_ , _size_ )

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Data and instruction cache macros map onto the both-cache macros

//-----------------------------------------------------------------------------
// Global control of data cache

#define HAL_DCACHE_SIZE                 HAL_UCACHE_SIZE
#define HAL_DCACHE_LINE_SIZE            HAL_UCACHE_LINE_SIZE
#define HAL_DCACHE_WAYS                 HAL_UCACHE_WAYS
#define HAL_DCACHE_SETS                 HAL_UCACHE_SETS

// Enable the data cache
#define HAL_DCACHE_ENABLE()             HAL_UCACHE_ENABLE()

// Disable the data cache
#define HAL_DCACHE_DISABLE()            HAL_UCACHE_DISABLE()

// Invalidate the entire cache
#define HAL_DCACHE_INVALIDATE_ALL()     HAL_UCACHE_INVALIDATE_ALL()

// Synchronize the contents of the cache with memory.
#define HAL_DCACHE_SYNC()               HAL_UCACHE_SYNC()

// Query the state of the data cache
#define HAL_DCACHE_IS_ENABLED(_state_)  HAL_UCACHE_IS_ENABLED(_state_)

// Set the data cache refill burst size
//#define HAL_DCACHE_BURST_SIZE(_size_)

// Set the data cache write mode
//#define HAL_DCACHE_WRITE_MODE( _mode_ )

//#define HAL_DCACHE_WRITETHRU_MODE       0
//#define HAL_DCACHE_WRITEBACK_MODE       1

// Load the contents of the given address range into the data cache
// and then lock the cache so that it stays there.
//#define HAL_DCACHE_LOCK(_base_, _size_)

// Undo a previous lock operation
//#define HAL_DCACHE_UNLOCK(_base_, _size_)

// Unlock entire cache
//#define HAL_DCACHE_UNLOCK_ALL()

//-----------------------------------------------------------------------------
// Data cache line control

// Allocate cache lines for the given address range without reading its
// contents from memory.
//#define HAL_DCACHE_ALLOCATE( _base_ , _size_ )

// Write dirty cache lines to memory and invalidate the cache entries
// for the given address range.
//#define HAL_DCACHE_FLUSH( _base_ , _size_ )

// Invalidate cache lines in the given range without writing to memory.
//#define HAL_DCACHE_INVALIDATE( _base_ , _size_ )

// Write dirty cache lines to memory for the given address range.
//#define HAL_DCACHE_STORE( _base_ , _size_ )

// Preread the given range into the cache with the intention of reading
// from it later.
//#define HAL_DCACHE_READ_HINT( _base_ , _size_ )

// Preread the given range into the cache with the intention of writing
// to it later.
//#define HAL_DCACHE_WRITE_HINT( _base_ , _size_ )

// Allocate and zero the cache lines associated with the given range.
//#define HAL_DCACHE_ZERO( _base_ , _size_ )

//-----------------------------------------------------------------------------
// Global control of Instruction cache

#define HAL_ICACHE_SIZE                 HAL_UCACHE_SIZE
#define HAL_ICACHE_LINE_SIZE            HAL_UCACHE_LINE_SIZE
#define HAL_ICACHE_WAYS                 HAL_UCACHE_WAYS
#define HAL_ICACHE_SETS                 HAL_UCACHE_SETS

// Enable the instruction cache
#define HAL_ICACHE_ENABLE()             HAL_UCACHE_ENABLE()

// Disable the instruction cache
#define HAL_ICACHE_DISABLE()            HAL_UCACHE_DISABLE()

// Invalidate the entire cache
#define HAL_ICACHE_INVALIDATE_ALL()     HAL_UCACHE_INVALIDATE_ALL()


// Synchronize the contents of the cache with memory.
#define HAL_ICACHE_SYNC()               HAL_UCACHE_SYNC()

// Query the state of the instruction cache
#define HAL_ICACHE_IS_ENABLED(_state_)  HAL_UCACHE_IS_ENABLED(_state_)

// Set the instruction cache refill burst size
//#define HAL_ICACHE_BURST_SIZE(_size_)

// Load the contents of the given address range into the instruction cache
// and then lock the cache so that it stays there.

//#define HAL_ICACHE_LOCK(_base_, _size_)

// Undo a previous lock operation
//#define HAL_ICACHE_UNLOCK(_base_, _size_)

// Unlock entire cache
//#define HAL_ICACHE_UNLOCK_ALL()

//-----------------------------------------------------------------------------
// Instruction cache line control

// Invalidate cache lines in the given range without writing to memory.
//#define HAL_ICACHE_INVALIDATE( _base_ , _size_ )

#endif // ifndef CYGONCE_HAL_CACHE_H
// End of hal_cache.h
