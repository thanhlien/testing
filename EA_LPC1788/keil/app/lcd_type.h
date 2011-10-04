/***********************************************************************
 * $Id: lcd_type.h 3697 2010-06-10 22:57:10Z usb00423 $
 *
 * Project: LPC18xx Validation
 *
 * Description: Selection of LCD Type
 *
 * Copyright(C) 2010, NXP Semiconductor
 * All rights reserved.
 *
 ***********************************************************************
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
 **********************************************************************/
#ifndef __LCD_TYPE_H
#define __LCD_TYPE_H

// Enumerate LCD types
#define SHARP_LM057QC	0
#define SHARP_LM057QB	1
#define SHARP_LQ064		2	/* TFT 16-bit, 1:5:5:5 mode */
#define TRULY_G240320LTSW 3 /* TFT 18-bit, 1:6:6:6 mode */
#if 0
// not implemented yet
#define HANNSTAR_HSD043I9W1 4
#endif
// Define LCD under test
#define LCD_TYPE 		TRULY_G240320LTSW

#define LCD_FRAME_BUF 0xA0000000
#if (LCD_TYPE == SHARP_LM057QC)
	#define LCD_DISPLAY sharp_lm057qc 	
#elif (LCD_TYPE == SHARP_LM057QB)
	#define LCD_DISPLAY sharp_lm057qb	
#elif (LCD_TYPE == SHARP_LQ064)
	#define LCD_DISPLAY sharp_lq064
#elif (LCD_TYPE == TRULY_G240320LTSW)
	#define LCD_DISPLAY truly_g240320ltsw
#else
	#define LCD_DISPLAY hannstar_hsd043i9w1
#endif

#define DISPLAY_HEIGHT LCD_DISPLAY.lines_per_panel
#define DISPLAY_WIDTH LCD_DISPLAY.pixels_per_line

#endif /* __LCD_TYPE_H */
