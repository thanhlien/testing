/*****************************************************************************
 *   truly_g240320ltsw.c:  Driver for 3.2 inch QVGA display from truly
 *                         TFT-G240320LTSW-118W-E
 *
 *   Copyright(C) 2010, Embedded Artists AB
 *   All rights reserved.
 *
 ******************************************************************************/


/******************************************************************************
 * Includes
 *****************************************************************************/

#include "lpc_types.h"
#include "ssp.h"
#include "lcd_params.h"
#include "lcd_driver.h"
#include "truly_display.h"
#include "timer.h"

/******************************************************************************
 * Defines and typedefs
 *****************************************************************************/

#define CS_ON    (LPC_GPIO0->CLR |= (1<<16)) // p0.16 -> low
#define CS_OFF   (LPC_GPIO0->SET |= (1<<16)) // p0.16 -> high
#define DC_CMD   (LPC_GPIO0->CLR |= (1<<19)) // p0.19 -> low
#define DC_DATA  (LPC_GPIO0->SET |= (1<<19)) // p0.19 -> high

#define SSP_PORT (LPC_SSP0)
#define SSP_CLOCK 3000000

/******************************************************************************
 * Local Functions
 *****************************************************************************/

static void pinConfig(void)
{
  LPC_IOCON->P0_4 |= 7; /* LCD_VD_0 @ P0.4 */
  LPC_IOCON->P0_5 |= 7; /* LCD_VD_1 @ P0.5 */
  LPC_IOCON->P0_6 |= 7; /* LCD_VD_8 @ P0.6 */
  LPC_IOCON->P0_7 |= 7; /* LCD_VD_9 @ P0.7 */
  LPC_IOCON->P0_8 |= 7; /* LCD_VD_16 @ P0.8 */
  LPC_IOCON->P0_9 |= 7; /* LCD_VD_17 @ P0.9 */

  LPC_IOCON->P1_20 |= 7; /* LCD_VD_10 @ P1.20 */
  LPC_IOCON->P1_21 |= 7; /* LCD_VD_11 @ P1.21 */
  LPC_IOCON->P1_22 |= 7; /* LCD_VD_12 @ P1.22 */
  LPC_IOCON->P1_23 |= 7; /* LCD_VD_13 @ P1.23 */
  LPC_IOCON->P1_24 |= 7; /* LCD_VD_14 @ P1.24 */
  LPC_IOCON->P1_25 |= 7; /* LCD_VD_15 @ P1.25 */
  LPC_IOCON->P1_26 |= 7; /* LCD_VD_20 @ P1.26 */
  LPC_IOCON->P1_27 |= 7; /* LCD_VD_21 @ P1.27 */
  LPC_IOCON->P1_28 |= 7; /* LCD_VD_22 @ P1.28 */
  LPC_IOCON->P1_29 |= 7; /* LCD_VD_23 @ P1.29 */

  LPC_IOCON->P2_0 |= 7; /* LCD_PWR @ P2.0 */
  LPC_IOCON->P2_1 |= 7; /* LCD_LE  @ P2.1 */
  LPC_IOCON->P2_2 |= 7; /* LCD_DCLK @ P2.2 */
  LPC_IOCON->P2_3 |= 7; /* LCD_FP @ P2.3 */
  LPC_IOCON->P2_4 |= 7; /* LCD_ENAB_M @ P2.4 */
  LPC_IOCON->P2_5 |= 7; /* LCD_LP @ P2.5 */
  LPC_IOCON->P2_6 |= 7; /* LCD_VD_4 @ P2.6 */
  LPC_IOCON->P2_7 |= 7; /* LCD_VD_5 @ P2.7 */
  LPC_IOCON->P2_8 |= 7; /* LCD_VD_6 @ P2.8 */
  LPC_IOCON->P2_9 |= 7; /* LCD_VD_7 @ P2.9 */
  
  LPC_IOCON->P2_11 |= 7; /* LCD_CLKIN @ P2.11 */
  LPC_IOCON->P2_12 |= 7; /* LCD_VD_18 @ P2.12 */
  LPC_IOCON->P2_13 |= 7; /* LCD_VD_19 @ P2.13 */

  LPC_IOCON->P4_28 |= 7; /* LCD_VD_2 @ P4.28 */
  LPC_IOCON->P4_29 |= 7; /* LCD_VD_3 @ P4.29 */

  /* p1.18 (backlight) pin as output p2.0 */
  LPC_GPIO1->DIR |= (1<<18); 

  /* p0.16 pin as output (CS) */
  LPC_GPIO0->DIR |= (1<<16);

  /* p0.19 pin as output (DC) */
  LPC_GPIO0->DIR |= (1<<19);

  // PIN config SSP
  LPC_IOCON->P0_15 = (LPC_IOCON->P0_15&(~0xFFF)) | 0x00000002;
  LPC_IOCON->P0_16 = (LPC_IOCON->P0_16&(~0xFFF)) | 0x00000002;
  LPC_IOCON->P0_17 = (LPC_IOCON->P0_17&(~0xFFF)) | 0x00000002;
  LPC_IOCON->P0_18 = (LPC_IOCON->P0_18&(~0xFFF)) | 0x00000002;
}

static void
writeToReg(uint16_t addr, uint16_t data)
{
  uint8_t buf[2];
  SSP_DATA_SETUP_Type sspCfg;
  DC_CMD;
  CS_ON;

  buf[0] = 0;
  buf[1] = (addr & 0xff);

  sspCfg.tx_data = buf;
  sspCfg.rx_data = NULL;
  sspCfg.length  = 2; 

  SSP_ReadWrite (SSP_PORT, &sspCfg, SSP_TRANSFER_POLLING);

  CS_OFF;  

  DC_DATA;
  CS_ON;
  buf[0] = (data >> 8);
  buf[1] = (data & 0xff);
  SSP_ReadWrite (SSP_PORT, &sspCfg, SSP_TRANSFER_POLLING);
  CS_OFF; 

  DC_CMD;
  CS_ON;

  buf[0] = (0);
  buf[1] = (0x22);
  SSP_ReadWrite (SSP_PORT, &sspCfg, SSP_TRANSFER_POLLING);
  CS_OFF; 
}

static void ssd1289_init(void)
{
  writeToReg (0x00,0x0001);
  delayMs(0, 15);
  writeToReg (0x03,0xAEAC);
  writeToReg (0x0C,0x0007);
  writeToReg (0x0D,0x000F);
  writeToReg (0x0E,0x2900);
  writeToReg (0x1E,0x00B3);
  delayMs(0, 15);
  writeToReg (0x01,0x2B3F);
  writeToReg (0x02,0x0600);
  writeToReg (0x10,0x0000);
  writeToReg (0x11,0x65b0);
  delayMs(0, 20);
  writeToReg (0x05,0x0000);
  writeToReg (0x06,0x0000);
  writeToReg (0x16,0xEF1C);
  writeToReg (0x17,0x0003);
  writeToReg (0x07,0x0233);
  writeToReg (0x0B,0x5312);
  writeToReg (0x0F,0x0000);
  writeToReg (0x1E,0x00AE);
  delayMs(0, 20);
  writeToReg (0x41,0x0000);
  writeToReg (0x42,0x0000);
  writeToReg (0x48,0x0000);
  writeToReg (0x49,0x013F);
  writeToReg (0x44,0xEF00);
  writeToReg (0x45,0x0000);
  writeToReg (0x46,0x013F);
  writeToReg (0x4A,0x0000);
  writeToReg (0x4B,0x0000);
  delayMs(0, 20);
  writeToReg (0x30,0x0707);
  writeToReg (0x31,0x0704);
  writeToReg (0x32,0x0204);
  writeToReg (0x33,0x0201);
  writeToReg (0x34,0x0203);
  writeToReg (0x35,0x0204);
  writeToReg (0x36,0x0204);
  writeToReg (0x37,0x0502);
  writeToReg (0x3A,0x0302);
  writeToReg (0x3B,0x0500);
  delayMs(0, 20);
  writeToReg (0x22,0x0000);
}

/******************************************************************************
 * Public Functions
 *****************************************************************************/

/******************************************************************************
 *
 * Description:
 *    Initialize the display
 *
 *****************************************************************************/
int32_t truly_lcd_open (int32_t framebuf)
{
  int32_t dev = 0;
  SSP_CFG_Type SSP_ConfigStruct;

  pinConfig();

  // initialize SSP configuration structure to default
  SSP_ConfigStructInit(&SSP_ConfigStruct);

  // set clock rate
  SSP_ConfigStruct.ClockRate = SSP_CLOCK;

  // Initialize SSP peripheral with parameter given in structure above
  SSP_Init(SSP_PORT, &SSP_ConfigStruct);

  // Enable SSP peripheral
  SSP_Cmd(SSP_PORT, ENABLE);

  /* turn on backlight -> active low */
  LPC_GPIO1->SET |= (1 << 18);


  dev = lcd_open((int32_t)&truly_g240320ltsw);

  lcd_ioctl(dev, LCD_PWR_ON, 1);
  lcd_ioctl(dev, LCD_SET_BUFFER, framebuf);

  delayMs(0, 200);

  /* initialize LCD controller */
  ssd1289_init();

  SSP_Cmd(SSP_PORT, DISABLE);
  SSP_DeInit(SSP_PORT);

  return dev;
}

int32_t truly_lcd_close (int32_t devid)
{
  /* turn off backlight  */
  LPC_GPIO1->CLR |= (1 << 18);

  return lcd_close(devid);
}

