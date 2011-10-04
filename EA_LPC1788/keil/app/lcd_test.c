/*****************************************************************************
 *   lcd_test.c:  LCD module file for NXP LPC177x_8x Family Microprocessors
 *
 *   Copyright(C) 2009, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2009.05.26  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#include "string.h"  // memset

#include "LPC177x_8x.h"
#include "system_LPC177x_8x.h"
#include "type.h"
#include "ex_sdram.h"
#include "lcd_params.h"
#include "lcd_driver.h"
#include "lpc_swim.h"
#include "lcd_type.h"
#include "timer.h"
#include "truly_display.h"

extern void lcd_colorbars(void);

/***********************************************************************
 *
 * Function: main
 *
 * Purpose: Function entry point from the startup code.
 *
 * Processing:
 *
 * Parameters: 	None
 *
 * Outputs: None
 *
 * Returns: None
 *
 **********************************************************************/
int main(void)
{
  int32_t framebuf = (int32_t)(SDRAM_BASE+0x10000);

  SystemInit();
  
  /* Initialise external SDRAM */
  EMCInit();

  /* Initialize timer 0 */
  init_timer(0, SystemCoreClock / (LPC_SC->PCLKSEL&0x1F) / 60);
  
  /* Clear the framebuffer (320x240 pixels * 16 bits) */
  memset((void*)(framebuf), 0x00, 240*320*2);

  /* Initialise the 3.2" LCD */
  truly_lcd_open(framebuf);

  /* Run the color bars test */
  lcd_colorbars();  

  /* You should never come back from colorbars */
  while(1) 
  {
  }
}
