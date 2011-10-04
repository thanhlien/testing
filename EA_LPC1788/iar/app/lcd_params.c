/*****************************************************************************
 *   lcd_params.c:  LCD module file for NXP LPC177x_8x Family Microprocessors
 *
 *   Copyright(C) 2009, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2009.05.26  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#include "lcd_params.h"

const LCD_PARAM_T sharp_lq064 =
{
  89,       /* Horizontal back porch */
  50,       /* Horizontal front porch */
  14,       /* HSYNC pulse width */
  640,      /* Pixels per line */
  18,       /* Vertical back porch */
  94,       /* Vertical front porch */
  17,       /* VSYNC pulse width */
  480,      /* Lines per panel */
  0,        /* Invert output enable */
  0,        /* Do not invert panel clock */
  1,        /* Invert HSYNC */
  1,        /* Invert VSYNC */
  1,        /* AC bias frequency (not used) */
  18,       /* Bits per pixel */
  25180000, /* Optimal clock rate (Hz) */
  TFT,      /* LCD panel type */
  0,        /* Single panel display */
};

/* Sharp LM057QB STN display */
const LCD_PARAM_T sharp_lm057qb =
{
  5,          /* Horizontal back porch */
  5,          /* Horizontal front porch */
  3,          /* HSYNC pulse width */
  320,        /* Pixels per line */
  1,          /* Vertical back porch */
  1,          /* Vertical front porch */
  1,          /* VSYNC pulse width */
  240,        /* Lines per panel */
  0,          /* Do not invert output enable (NA) */
  0,          /* Do not invert panel clock */
  0,          /* Do not invert HSYNC */
  0,          /* Do not invert VSYNC */
  1,          /* AC bias frequency */
  4,          /* Bits per pixel */
  4500000,    /* Optimal clock rate (Hz) */
  MONO_4BIT,  /* LCD panel type */
  0,          /* Dual panel display */
//  0,          /* HRTFT CLS enable flag (NA) */
//  0,          /* HRTFT SPS enable flag (NA) */
//  0,          /* HRTFT LP to PS delay (NA) */
//  0,          /* HRTFT polarity delay (NA) */
//  0,          /* HRTFT LP delay (NA) */
//  0,          /* HRTFT SPL delay (NA) */
//  0           /* HRTFT SPL to CLKS delay (NA) */
};

/* Sharp LM057QC STN display */
const LCD_PARAM_T sharp_lm057qc =
{
  5,          /* Horizontal back porch */
  5,          /* Horizontal front porch */
  3,          /* HSYNC pulse width */
  320,        /* Pixels per line */    
  0,          /* Vertical back porch */
  0,          /* Vertical front porch */
  1,          /* VSYNC pulse width */
  240,        /* Lines per panel */      
  0,          /* Do not invert output enable (NA) */
  0,          /* Do not invert panel clock */
  0,          /* Do not invert HSYNC */
  0,          /* Do not invert VSYNC */
  0,          /* AC bias frequency */  
  8,          /* Bits per pixel */
  2500000,    /* Optimal clock rate (Hz) */  
  CSTN,       /* LCD panel type */
  0,          /* Dual panel display */
};

/* Truly G240320LTSW display */
const LCD_PARAM_T truly_g240320ltsw =
{
  28,       /* Horizontal back porch */
  10,       /* Horizontal front porch */
  2,        /* HSYNC pulse width */
  240,      /* Pixels per line */
  2,        /* Vertical back porch */
  1,        /* Vertical front porch */
  2,        /* VSYNC pulse width */
  320,      /* Lines per panel */
  0,        /* Invert output enable */
  1,        /* Do not invert panel clock */
  1,        /* Invert HSYNC */
  1,        /* Invert VSYNC */
  1,        /* AC bias frequency (not used) */
  16,       /* Bits per pixel */
  8200000,  /* Optimal clock rate (Hz) */
  ADTFT,    /* LCD panel type */
  0,        /* Single panel display */
};

#if 0
// not implemented yet
/* HannStar HSD043I9W1-A01-0299 display */
const LCD_PARAM_T hannstar_hsd043i9w1 =
{
   40,       /* Horizontal back porch */
    5,       /* Horizontal front porch */
    2,       /* HSYNC pulse width */
  480,       /* Pixels per line */
    8,       /* Vertical back porch */
    8,       /* Vertical front porch */
    2,       /* VSYNC pulse width */
  272,       /* Lines per panel */
    0,        /* Invert output enable */
    0,        /* Do not invert panel clock */
    1,        /* Invert HSYNC */
    1,        /* Invert VSYNC */
    1,        /* AC bias frequency (not used) */
   16,        /* Bits per pixel */
  9000000,    /* Optimal clock rate (Hz) between 1-8.22 MHz according to SSD1289 datasheet */
  TFT,        /* LCD panel type */
    0,        /* Single panel display */
}; 
#endif
