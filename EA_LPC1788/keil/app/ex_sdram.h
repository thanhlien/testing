/*****************************************************************************
 *   ex_sdram.h:  Header file for NXP LPC177x_8x Family Microprocessors
 *
 *   Copyright(C) 2009, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2009.05.26  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#ifndef __EX_SDRAM_H 
#define __EX_SDRAM_H

/*
These timing parameters are based on the EMC clock
there is no way of ensuring what the EMC clock frequency is
without severely bloating the code
ENSURE THAT THE EMC clock is one of these values
*/
#define SDRAM_SPEED_48 0
#define SDRAM_SPEED_50 1
#define SDRAM_SPEED_60 2
#define SDRAM_SPEED_72 3

#define SDRAM_SPEED SDRAM_SPEED_60

#define SDRAM_CONFIG_32BIT
#define SDRAM_SIZE               0x2000000

#define SDRAM_BASE               0xA0000000 /*CS0*/
//#define SDRAM_BASE               0xB0000000
//#define SDRAM_BASE               0xC0000000
//#define SDRAM_BASE               0xD0000000 /*CS3*/

extern void EMCInit( void );

#endif /* end __EX_SDRAM_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
