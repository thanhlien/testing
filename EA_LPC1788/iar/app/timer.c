/*****************************************************************************
 *   timer.c:  Timer C file for NXP LPC177x_8x Family Microprocessors
 *
 *   Copyright(C) 2009, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2009.05.26  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#include "LPC177x_8x.h"
#include "system_LPC177x_8x.h"
#include "type.h"
#include "timer.h"

volatile uint32_t timer0_counter = 0;
volatile uint32_t timer1_counter = 0;
volatile uint32_t timer2_counter = 0;
volatile uint32_t timer3_counter = 0;

/*****************************************************************************
** Function name:		delayMs
**
** Descriptions:		Start the timer delay in milo seconds
**						until elapsed
**
** parameters:			timer number, Delay value in milo second			 
** 						
** Returned value:		None
** 
*****************************************************************************/
void delayMs(uint8_t timer_num, uint32_t delayInMs)
{
  if ( timer_num == 0 )
  {
	LPC_TIM0->TCR = 0x02;		/* reset timer */
	LPC_TIM0->PR  = 0x00;		/* set prescaler to zero */
	LPC_TIM0->MR0 = delayInMs * (SystemCoreClock / (LPC_SC->PCLKSEL&0x1F) / 1000 - 1);
	LPC_TIM0->IR  = 0xff;		/* reset all interrrupts */
	LPC_TIM0->MCR = 0x04;		/* stop timer on match */
	LPC_TIM0->TCR = 0x01;		/* start timer */
  
	/* wait until delay time has elapsed */
	while (LPC_TIM0->TCR & 0x01);
  }
  else if ( timer_num == 1 )
  {
	LPC_TIM1->TCR = 0x02;		/* reset timer */
	LPC_TIM1->PR  = 0x00;		/* set prescaler to zero */
	LPC_TIM1->MR0 = delayInMs * (SystemCoreClock / (LPC_SC->PCLKSEL&0x1F) / 1000 - 1);
	LPC_TIM1->IR  = 0xff;		/* reset all interrrupts */
	LPC_TIM1->MCR = 0x04;		/* stop timer on match */
	LPC_TIM1->TCR = 0x01;		/* start timer */
  
	/* wait until delay time has elapsed */
	while (LPC_TIM1->TCR & 0x01);
  }
  else if ( timer_num == 2 )
  {
	LPC_TIM2->TCR = 0x02;		/* reset timer */
	LPC_TIM2->PR  = 0x00;		/* set prescaler to zero */
	LPC_TIM2->MR0 = delayInMs * (SystemCoreClock / (LPC_SC->PCLKSEL&0x1F) / 1000 - 1);
	LPC_TIM2->IR  = 0xff;		/* reset all interrrupts */
	LPC_TIM2->MCR = 0x04;		/* stop timer on match */
	LPC_TIM2->TCR = 0x01;		/* start timer */
  
	/* wait until delay time has elapsed */
	while (LPC_TIM2->TCR & 0x01);
  }
  else if ( timer_num == 3 )
  {
	LPC_TIM3->TCR = 0x02;		/* reset timer */
	LPC_TIM3->PR  = 0x00;		/* set prescaler to zero */
	LPC_TIM3->MR0 = delayInMs * (SystemCoreClock / (LPC_SC->PCLKSEL&0x1F) / 1000 - 1);
	LPC_TIM3->IR  = 0xff;		/* reset all interrrupts */
	LPC_TIM3->MCR = 0x04;		/* stop timer on match */
	LPC_TIM3->TCR = 0x01;		/* start timer */
  
	/* wait until delay time has elapsed */
	while (LPC_TIM3->TCR & 0x01);
  }
  return;
}

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void TIMER0_IRQHandler (void) 
{  
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  timer0_counter++;
  return;
}

/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void TIMER1_IRQHandler (void)  
{  
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  timer1_counter++;
  return;
}

/******************************************************************************
** Function name:		Timer2_IRQHandler
**
** Descriptions:		Timer/Counter 2 interrupt handler
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void TIMER2_IRQHandler (void)  
{  
  LPC_TIM2->IR = 1;			/* clear interrupt flag */
  timer2_counter++;
  return;
}

/******************************************************************************
** Function name:		Timer3_IRQHandler
**
** Descriptions:		Timer/Counter 3 interrupt handler
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void TIMER3_IRQHandler (void)  
{  
  LPC_TIM3->IR = 1;			/* clear interrupt flag */
  timer3_counter++;
  return;
}

/******************************************************************************
** Function name:		enable_timer
**
** Descriptions:		Enable timer
**
** parameters:			timer number: 0 or 1 or 2 or 3
** Returned value:		None
** 
******************************************************************************/
void enable_timer( uint8_t timer_num )
{
  if ( timer_num == 0 )
  {
	LPC_TIM0->TCR = 1;
  }
  else if ( timer_num == 1 )
  {
	LPC_TIM1->TCR = 1;
  }
  else if ( timer_num == 2 )
  {
	LPC_TIM2->TCR = 1;
  }
  else if ( timer_num == 3 )
  {
	LPC_TIM3->TCR = 1;
  }
  return;
}

/******************************************************************************
** Function name:		disable_timer
**
** Descriptions:		Disable timer
**
** parameters:			timer number: 0 or 1 oe 2 or 3
** Returned value:		None
** 
******************************************************************************/
void disable_timer( uint8_t timer_num )
{
  if ( timer_num == 0 )
  {
	LPC_TIM0->TCR = 0;
  }
  else if ( timer_num == 1 )
  {
	LPC_TIM1->TCR = 0;
  }
  else if ( timer_num == 2 )
  {
	LPC_TIM2->TCR = 0;
  }
  else if ( timer_num == 3 )
  {
	LPC_TIM2->TCR = 0;
  }
  return;
}

/******************************************************************************
** Function name:		reset_timer
**
** Descriptions:		Reset timer
**
** parameters:			timer number: 0 or 1 or 2 or 3
** Returned value:		None
** 
******************************************************************************/
void reset_timer( uint8_t timer_num )
{
  uint32_t regVal;

  if ( timer_num == 0 )
  {
	regVal = LPC_TIM0->TCR;
	regVal |= 0x02;
	LPC_TIM0->TCR = regVal;
  }
  else if ( timer_num == 1 )
  {
	regVal = LPC_TIM1->TCR;
	regVal |= 0x02;
	LPC_TIM1->TCR = regVal;
  }
  else if ( timer_num == 2 )
  {
	regVal = LPC_TIM2->TCR;
	regVal |= 0x02;
	LPC_TIM2->TCR = regVal;
  }
  else if ( timer_num == 3 )
  {
	regVal = LPC_TIM3->TCR;
	regVal |= 0x02;
	LPC_TIM3->TCR = regVal;
  }
  return;
}

/******************************************************************************
** Function name:		init_timer
**
** Descriptions:		Initialize timer, set timer interval, reset timer,
**						install timer interrupt handler
**
** parameters:			timer number and timer interval
** Returned value:		true or false, if the interrupt handler can't be
**						installed, return false.
** 
******************************************************************************/
uint32_t init_timer ( uint8_t timer_num, uint32_t TimerInterval ) 
{
  if ( timer_num == 0 )
  {
	timer0_counter = 0;
	LPC_SC->PCONP |= 0x00000002;

	LPC_TIM0->TCR = 2;
	LPC_TIM0->MR0 = TimerInterval;
	LPC_TIM0->MCR = 3;				/* Interrupt and Reset on MR0 */

	NVIC_EnableIRQ(TIMER0_IRQn);
	LPC_TIM0->TCR = 1;
	return (TRUE);
  }
  else if ( timer_num == 1 )
  {
	timer1_counter = 0;
	LPC_SC->PCONP |= 0x00000004;
	LPC_TIM1->MR0 = TimerInterval;
	LPC_TIM1->MCR = 3;				/* Interrupt and Reset on MR0 */

	NVIC_EnableIRQ(TIMER1_IRQn);
	return (TRUE);
  }
  else if ( timer_num == 2 )
  {
	timer2_counter = 0;
	LPC_SC->PCONP |= 0x00400000;
	LPC_TIM2->MR0 = TimerInterval;
	LPC_TIM2->MCR = 3;				/* Interrupt and Reset on MR0 */

	NVIC_EnableIRQ(TIMER2_IRQn);
	return (TRUE);
  }
  else if ( timer_num == 3 )
  {
	timer3_counter = 0;
	LPC_SC->PCONP |= 0x00800000;
	LPC_TIM3->MR0 = TimerInterval;
	LPC_TIM3->MCR = 3;				/* Interrupt and Reset on MR0 */

	NVIC_EnableIRQ(TIMER3_IRQn);
	return (TRUE);
  }
  return (FALSE);
}

/******************************************************************************
**                            End Of File
******************************************************************************/
