/**************************************************
 *
 * Part one of the system initialization code, contains low-level
 * initialization, plain thumb variant.
 *
 * Copyright 2009 IAR Systems. All rights reserved.
 *
 * $Revision: 33529 $
 *
 **************************************************/

;
; The modules in this file are included in the libraries, and may be replaced
; by any user-defined modules that define the PUBLIC symbol _program_start or
; a user defined start symbol.
; To override the cstartup defined in the library, simply add your modified
; version to the workbench project.
;
; The vector table is normally located at address 0.
; When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
; The name "__vector_table" has special meaning for C-SPY:
; it is where the SP start value is found, and the NVIC vector
; table register (VTOR) is initialized to this address if != 0.
;
; Cortex-M version
;

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        PUBLIC  __vector_table
        PUBLIC  __vector_table_0x1c

        DATA
__vector_table
        DCD     sfe(CSTACK)                 ; Top of Stack
        DCD     __iar_program_start         ; Reset Handler
        DCD     NMI_Handler                 ; NMI Handler
        DCD     HardFault_Handler           ; Hard Fault Handler
        DCD     MemManage_Handler           ; MPU Fault Handler
        DCD     BusFault_Handler            ; Bus Fault Handler
        DCD     UsageFault_Handler          ; Usage Fault Handler
__vector_table_0x1c
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     SVC_Handler                 ; SVCall Handler
        DCD     DebugMon_Handler            ; Debug Monitor Handler
        DCD     0                           ; Reserved
        DCD     PendSV_Handler              ; PendSV Handler
        DCD     SysTick_Handler             ; SysTick Handler
        DCD     WDT_IRQHandler              ; Watchdog Handler
        DCD     TIMER0_IRQHandler             ; TIMER0 Handler
        DCD     TIMER1_IRQHandler             ; TIMER1 Handler
        DCD     TIMER2_IRQHandler             ; TIMER2 Handler
        DCD     TIMER3_IRQHandler             ; TIMER3 Handler
        DCD     UART0_IRQHandler            ; UART0 Handler
        DCD     UART1_IRQHandler            ; UART1 Handler
        DCD     UART2_IRQHandler            ; UART2 Handler
        DCD     UART3_IRQHandler            ; UART3 Handler
        DCD     PWM1_IRQHandler             ; PWM1 Handler
        DCD     I2C0_IRQHandler             ; I2C0 Handler
        DCD     I2C1_IRQHandler             ; I2C1 Handler
        DCD     I2C2_IRQHandler             ; I2C2 Handler
        DCD     SPIFI_IRQHandler            ; SPIFI
        DCD     SSP0_IRQHandler             ; SSP0 Handler
        DCD     SSP1_IRQHandler             ; SSP1 Handler
        DCD     PLL0_IRQHandler             ; PLL0 Handler
        DCD     RTC_IRQHandler              ; RTC Handler
        DCD     EINT0_IRQHandler            ; EXT Interupt 0 Handler
        DCD     EINT1_IRQHandler            ; EXT Interupt 1 Handler
        DCD     EINT2_IRQHandler            ; EXT Interupt 2 Handler
        DCD     EINT3_IRQHandler            ; EXT Interupt 3 Handler
        DCD     ADC_IRQHandler              ; ADC Handler
        DCD     BOD_IRQHandler              ; BOD Handler
        DCD     USB_IRQHandler              ; USB Handler
        DCD     CAN_IRQHandler              ; CAN Handler
        DCD     DMA_IRQHandler              ; General Purpose DMA Handler
        DCD     I2S_IRQHandler              ; I2S Handler
        DCD     ENET_IRQHandler             ; Ethernet Handler
        DCD     MCI_IRQHandler            ; 45: SD/MMC card I/F
        DCD     MCPWM_IRQHandler          ; 46: Motor Control PWM
        DCD     QEI_IRQHandler            ; 47: Quadrature Encoder Interface
        DCD     PLL1_IRQHandler           ; 48: PLL1 Lock (USB PLL)
	DCD	USBActivity_IRQHandler    ; 49: USB Activity interrupt to wakeup
	DCD	CANActivity_IRQHandler    ; 50: CAN Activity interrupt to wakeup
	DCD	UART4_IRQHandler          ; 51: UART4
	DCD	SSP2_IRQHandler           ; 52: SSP2
	DCD	LCD_IRQHandler            ; 53: LCD
	DCD	GPIO_IRQHandler           ; 54: GPIO
	DCD	PWM0_IRQHandler           ; 55: PWM0
	DCD	KFLASH_IRQHandler         ; 56: KFLASH SHELL

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;

      PUBWEAK NMI_Handler       
      PUBWEAK HardFault_Handler 
      PUBWEAK MemManage_Handler 
      PUBWEAK BusFault_Handler  
      PUBWEAK UsageFault_Handler
      PUBWEAK SVC_Handler       
      PUBWEAK DebugMon_Handler  
      PUBWEAK PendSV_Handler    
      PUBWEAK SysTick_Handler   
      PUBWEAK WDT_IRQHandler    
      PUBWEAK TIMER0_IRQHandler   
      PUBWEAK TIMER1_IRQHandler   
      PUBWEAK TIMER2_IRQHandler   
      PUBWEAK TIMER3_IRQHandler   
      PUBWEAK UART0_IRQHandler  
      PUBWEAK UART1_IRQHandler  
      PUBWEAK UART2_IRQHandler  
      PUBWEAK UART3_IRQHandler  
      PUBWEAK PWM1_IRQHandler   
      PUBWEAK I2C0_IRQHandler   
      PUBWEAK I2C1_IRQHandler   
      PUBWEAK I2C2_IRQHandler   
      PUBWEAK SPIFI_IRQHandler
      PUBWEAK SSP0_IRQHandler   
      PUBWEAK SSP1_IRQHandler   
      PUBWEAK PLL0_IRQHandler   
      PUBWEAK RTC_IRQHandler    
      PUBWEAK EINT0_IRQHandler  
      PUBWEAK EINT1_IRQHandler  
      PUBWEAK EINT2_IRQHandler  
      PUBWEAK EINT3_IRQHandler  
      PUBWEAK ADC_IRQHandler    
      PUBWEAK BOD_IRQHandler    
      PUBWEAK USB_IRQHandler    
      PUBWEAK CAN_IRQHandler    
      PUBWEAK DMA_IRQHandler  
      PUBWEAK I2S_IRQHandler    
      PUBWEAK ENET_IRQHandler         
      PUBWEAK MCI_IRQHandler
      PUBWEAK MCPWM_IRQHandler
      PUBWEAK QEI_IRQHandler
      PUBWEAK PLL1_IRQHandler
      PUBWEAK USBActivity_IRQHandler
      PUBWEAK CANActivity_IRQHandler
      PUBWEAK UART4_IRQHandler
      PUBWEAK SSP2_IRQHandler
      PUBWEAK LCD_IRQHandler
      PUBWEAK GPIO_IRQHandler
      PUBWEAK PWM0_IRQHandler
      PUBWEAK KFLASH_IRQHandler
      
        SECTION .text:CODE:REORDER(1)
        THUMB
NMI_Handler       
HardFault_Handler 
MemManage_Handler 
BusFault_Handler  
UsageFault_Handler
SVC_Handler       
DebugMon_Handler  
PendSV_Handler    
SysTick_Handler   
WDT_IRQHandler    
TIMER0_IRQHandler   
TIMER1_IRQHandler   
TIMER2_IRQHandler   
TIMER3_IRQHandler   
UART0_IRQHandler  
UART1_IRQHandler  
UART2_IRQHandler  
UART3_IRQHandler  
PWM1_IRQHandler   
I2C0_IRQHandler   
I2C1_IRQHandler   
I2C2_IRQHandler   
SPIFI_IRQHandler
SSP0_IRQHandler   
SSP1_IRQHandler   
PLL0_IRQHandler   
RTC_IRQHandler    
EINT0_IRQHandler  
EINT1_IRQHandler  
EINT2_IRQHandler  
EINT3_IRQHandler  
ADC_IRQHandler    
BOD_IRQHandler    
USB_IRQHandler    
CAN_IRQHandler    
DMA_IRQHandler  
I2S_IRQHandler    
ENET_IRQHandler         
MCI_IRQHandler
MCPWM_IRQHandler
QEI_IRQHandler
PLL1_IRQHandler
USBActivity_IRQHandler
CANActivity_IRQHandler
UART4_IRQHandler
SSP2_IRQHandler
LCD_IRQHandler
GPIO_IRQHandler
PWM0_IRQHandler
KFLASH_IRQHandler
Default_Handler          
        B Default_Handler 
        END
