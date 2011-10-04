/**********************************************************************
 * $Id:: lcd_colorbars.c 1260 2008-10-28 23:20:43Z wellsk             $
 *
 * Project: NXP EA2478 LCD example
 *
 * Description:
 *     Draws color bars on the LCD. Requires RGB565 mode.
 *
 **********************************************************************
 * Software that is described herein is for illustrative purposes only  
 * which provides customers with programming information regarding the  
 * products. This software is supplied "AS IS" without any warranties.  
 * NXP Semiconductors assumes no responsibility or liability for the 
 * use of the software, conveys no license or title under any patent, 
 * copyright, or mask work right to the product. NXP Semiconductors 
 * reserves the right to make changes in the software without 
 * notification. NXP Semiconductors also make no representation or 
 * warranty that such application will be suitable for the specified 
 * use without further testing or modification. 
 *********************************************************************/
#include "string.h"// memset

#include "ex_sdram.h"
#include "lpc_types.h"
#include "lpc_swim.h"
#include "lpc_swim_font.h"
#include "lpc_swim.h"
#include "lpc_rom8x16.h"
#include "lpc_winfreesystem14x16.h"
#include "lpc_x6x13.h"

#include "lcd_params.h"      /* LCD panel parameters */
#include "LPC177x_8x.h"
#include "system_LPC177x_8x.h"
#include "type.h"
#include "timer.h"
#include "lcd_type.h"
#include "truly_display.h"

extern long dev_lcd ;

#define FONT  font_x6x13 // font_rom8x16 font_rom8x16 font_winfreesys14x16

/***********************************************************************
 *
 * Function: make_number_str
 *
 * Purpose: Convert a number to a positive decimal string
 *
 * Processing:
 *     Using successive division, compute the base10 value of a number
 *     into a string and return the string value to the caller.
 *
 * Parameters:
 *     str      : Where to place the generated strinjg
 *     iteration: Number to generate a string from
 *
 * Outputs: None
 *
 * Returns: Nothing
 *
 * Notes: None
 *
 **********************************************************************/
void make_number_str(CHAR *str,
                     INT_32 iteration)
{
    UNS_8 tmp[32];
    INT_32 dvv1, dvv2;
    INT_32 cnt = 0;

    /* Number 0 in string */
    str[cnt] = '0';

    /* Main loop */
    while (iteration > 0)
    {
        dvv1 = iteration / 10;
        dvv2 = dvv1 * 10;
        dvv1 = iteration - dvv2;

        tmp[cnt] = dvv1;
        iteration = iteration / 10;
        cnt++;
    }

    if (cnt > 0)
    {
        for (dvv1 = 0; dvv1 < cnt; dvv1++)
        {
            str[dvv1] = (CHAR) ('0' + tmp[cnt - (dvv1 + 1)]);
        }
    }
    
    str[cnt + 1] = '\0';
}

/**********************************************************************
 *
 * Function: lcd_colorbars
 *
 * Purpose: Draw colorbars on LCD panel
 *
 * Processing:
 *     See function.
 *
 * Parameters: None
 *
 * Outputs: None
 *
 * Returns: Nothing
 *
 * Notes: None
 *
 *********************************************************************/
void lcd_colorbars(void)
{
  SWIM_WINDOW_T win1;
  COLOR_T clr, *fblog;
  int idx;
  UNS_16 xgs, ygs, curx, cury, curym, xidx;
  int32_t framebuf = (int32_t)(SDRAM_BASE+0x10000);
  CHAR str[32];
  int tick = timer0_counter;
  int lasttick;

  /* Clear the framebuffer */
  memset((void*)(framebuf), 0x00, 240*320*2);

  fblog = (COLOR_T*)framebuf;

  /* Create a SWIM window */
  swim_window_open(&win1, DISPLAY_WIDTH, DISPLAY_HEIGHT, fblog, 0, 0, 
    DISPLAY_WIDTH-1, DISPLAY_HEIGHT-1, 1, WHITE, BLACK, BLACK);

  /* Compute vertical size for bars */
  ygs = DISPLAY_HEIGHT / 3;

  /* Draw Red bars */
  cury = 0;
  curx = 0;
  curym = ygs - 1;
  xgs = DISPLAY_WIDTH / RED_COLORS;
  clr = BLACK;
  for (xidx = 0; xidx < RED_COLORS; xidx++)
  {
      swim_set_pen_color(&win1, clr);
      for (idx = 0; idx <= xgs; idx++)
      {
          swim_put_line(&win1, curx, cury, curx, curym);
          curx++;
      }
      clr = clr + 0x0800;
  }

  /* Draw green bars */
  cury = cury + ygs;
  curx = 0;
  curym = cury + (ygs - 1);
  xgs = DISPLAY_WIDTH / GREEN_COLORS;
  clr = BLACK;
  for (xidx = 0; xidx < GREEN_COLORS; xidx++)
  {
      swim_set_pen_color(&win1, clr);
      for (idx = 0; idx <= xgs; idx++)
      {
          swim_put_line(&win1, curx, cury, curx, curym);
          curx++;
      }
      clr = clr + 0x0020;
  }

  /* Draw blue bars */
  cury = cury + ygs;
  curx = 0;
  curym = cury + (ygs - 1);
  xgs = DISPLAY_WIDTH / BLUE_COLORS;
  clr = BLACK;
  for (xidx = 0; xidx < BLUE_COLORS; xidx++)
  {
      swim_set_pen_color(&win1, clr);
      for (idx = 0; idx <= xgs; idx++)
      {
          swim_put_line(&win1, curx, cury, curx, curym);
          curx++;
      }
      clr = clr + 0x0001;
  }

  /* Draw the title bar */
  swim_set_font(&win1, (FONT_T *)&FONT );
  swim_set_pen_color(&win1, WHITE);
  swim_set_title(&win1, "NXP SWIM Graphics Library", BLACK);
  
  /* Reconfigure and enable timer 0 */
  init_timer(0, SystemCoreClock / (LPC_SC->PCLKSEL&0x1F) / 60);
  enable_timer(0);
  disable_timer(0);
  enable_timer(0);

  /* Constantly render the tick counter for timer 0 */
  swim_set_pen_color(&win1, LIGHTGRAY);
  while(1) 
  {
    tick = timer0_counter;
    if (lasttick != tick)
	{
      swim_set_xy(&win1, 0, 0);
      swim_put_text(&win1, "Tick #");
      make_number_str(str, tick);
      swim_put_text(&win1, str);
      swim_put_text(&win1, "\n");
	  lasttick = tick;
	}
  }	    
}
