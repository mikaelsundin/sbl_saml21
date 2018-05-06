
/* Minimal Cortex SAM L21 device vectors with systick */
typedef struct _DeviceVectors{
	/* Stack pointer */
	void* pvStack;

	/* Cortex-M handlers */
	void* pfnReset_Handler;
	void* pfnNMI_Handler;
	void* pfnHardFault_Handler;
	void* pfnReservedM12;
	void* pfnReservedM11;
	void* pfnReservedM10;
	void* pfnReservedM9;
	void* pfnReservedM8;
	void* pfnReservedM7;
	void* pfnReservedM6;
	void* pfnSVC_Handler;
	void* pfnReservedM4;
	void* pfnReservedM3;
	void* pfnPendSV_Handler;
	void* pfnSysTick_Handler;
}DeviceVectors;


/* Memory location */
#define AC                            (0x43001000ul)
#define ADC                           (0x43000C00ul)
#define AES                           (0x42003400ul)
#define CCL                           (0x43001C00ul)
#define DAC                           (0x42003000ul)
#define DMAC                          (0x44000400ul)
#define DSU                           (0x41002000ul)
#define EIC                           (0x40002400ul)
#define EVSYS                         (0x43000000ul)
#define GCLK                          (0x40001800ul)
#define MCLK                          (0x40000400ul)
#define MTB                           (0x41006000ul)
#define NVMCTRL                       (0x41004000ul)
#define NVMCTRL_CAL                   (0x00800000ul)
#define NVMCTRL_LOCKBIT               (0x00802000ul)
#define NVMCTRL_OTP1                  (0x00806000ul)
#define NVMCTRL_OTP2                  (0x00806008ul)
#define NVMCTRL_OTP3                  (0x00806010ul)
#define NVMCTRL_OTP4                  (0x00806018ul)
#define NVMCTRL_OTP5                  (0x00806020ul)
#define NVMCTRL_TEMP_LOG              (0x00806030ul)
#define NVMCTRL_USER                  (0x00804000ul)
#define OPAMP                         (0x43001800ul)
#define OSCCTRL                       (0x40000C00ul)
#define OSC32KCTRL                    (0x40001000ul
#define PAC                           (0x44000000ul)
#define PM                            (0x40000000ul)
#define PORT                          (0x40002800ul)
#define PORT_IOBUS                    (0x60000000ul)
#define RSTC                          (0x40000800ul)
#define RTC                           (0x40002000ul)
#define SERCOM0                       (0x42000000ul)
#define SERCOM1                       (0x42000400ul)
#define SERCOM2                       (0x42000800ul)
#define SERCOM3                       (0x42000C00ul)
#define SERCOM4                       (0x42001000UL)
#define SERCOM5                       (0x43000400UL) 
#define SUPC                          (0x40001400ul)
#define TAL                           (0x40002C00ul)
#define TC0                           (0x42002000ul)
#define TC1                           (0x42002400ul)
#define TC4                           (0x43000800ul)
#define TCC0                          (0x42001400ul)
#define TCC1                          (0x42001800ul)
#define TCC2                          (0x42001C00ul)
#define TRNG                          (0x42003800ul)
#define USB                           (0x41000000ul)
#define WDT                           (0x40001C00ul)

typedef enum IRQn
{
	/******  Cortex-M0+ Processor Exceptions Numbers ******************************/
	NonMaskableInt_IRQn      = -14,/**<  2 Non Maskable Interrupt                 */
	HardFault_IRQn           = -13,/**<  3 Cortex-M0+ Hard Fault Interrupt        */
	SVCall_IRQn              = -5, /**< 11 Cortex-M0+ SV Call Interrupt           */
	PendSV_IRQn              = -2, /**< 14 Cortex-M0+ Pend SV Interrupt           */
	SysTick_IRQn             = -1, /**< 15 Cortex-M0+ System Tick Interrupt       */
	/******  SAML21G18A-specific Interrupt Numbers ***********************/
	SYSTEM_IRQn              =  0, /**<  0 SAML21G18A System Interrupts */
	MCLK_IRQn                =  0, /**<  0 SAML21G18A Main Clock (MCLK) */
	OSCCTRL_IRQn             =  0, /**<  0 SAML21G18A Oscillators Control (OSCCTRL) */
	OSC32KCTRL_IRQn          =  0, /**<  0 SAML21G18A 32k Oscillators Control (OSC32KCTRL) */
	PAC_IRQn                 =  0, /**<  0 SAML21G18A Peripheral Access Controller (PAC) */
	PM_IRQn                  =  0, /**<  0 SAML21G18A Power Manager (PM) */
	SUPC_IRQn                =  0, /**<  0 SAML21G18A Supply Controller (SUPC) */
	TAL_IRQn                 =  0, /**<  0 SAML21G18A Trigger Allocator (TAL) */
	WDT_IRQn                 =  1, /**<  1 SAML21G18A Watchdog Timer (WDT) */
	RTC_IRQn                 =  2, /**<  2 SAML21G18A Real-Time Counter (RTC) */
	EIC_IRQn                 =  3, /**<  3 SAML21G18A External Interrupt Controller (EIC) */
	NVMCTRL_IRQn             =  4, /**<  4 SAML21G18A Non-Volatile Memory Controller (NVMCTRL) */
	DMAC_IRQn                =  5, /**<  5 SAML21G18A Direct Memory Access Controller (DMAC) */
	USB_IRQn                 =  6, /**<  6 SAML21G18A Universal Serial Bus (USB) */
	EVSYS_IRQn               =  7, /**<  7 SAML21G18A Event System Interface (EVSYS) */
	SERCOM0_IRQn             =  8, /**<  8 SAML21G18A Serial Communication Interface 0 (SERCOM0) */
	SERCOM1_IRQn             =  9, /**<  9 SAML21G18A Serial Communication Interface 1 (SERCOM1) */
	SERCOM2_IRQn             = 10, /**< 10 SAML21G18A Serial Communication Interface 2 (SERCOM2) */
	SERCOM3_IRQn             = 11, /**< 11 SAML21G18A Serial Communication Interface 3 (SERCOM3) */
	SERCOM4_IRQn             = 12, /**< 12 SAML21G18A Serial Communication Interface 4 (SERCOM4) */
	SERCOM5_IRQn             = 13, /**< 13 SAML21G18A Serial Communication Interface 5 (SERCOM5) */
	TCC0_IRQn                = 14, /**< 14 SAML21G18A Timer Counter Control 0 (TCC0) */
	TCC1_IRQn                = 15, /**< 15 SAML21G18A Timer Counter Control 1 (TCC1) */
	TCC2_IRQn                = 16, /**< 16 SAML21G18A Timer Counter Control 2 (TCC2) */
	TC0_IRQn                 = 17, /**< 17 SAML21G18A Basic Timer Counter 0 (TC0) */
	TC1_IRQn                 = 18, /**< 18 SAML21G18A Basic Timer Counter 1 (TC1) */
	TC4_IRQn                 = 21, /**< 21 SAML21G18A Basic Timer Counter 4 (TC4) */
	ADC_IRQn                 = 22, /**< 22 SAML21G18A Analog Digital Converter (ADC) */
	AC_IRQn                  = 23, /**< 23 SAML21G18A Analog Comparators (AC) */
	DAC_IRQn                 = 24, /**< 24 SAML21G18A Digital-to-Analog Converter (DAC) */
	PTC_IRQn                 = 25, /**< 25 SAML21G18A Peripheral Touch Controller (PTC) */
	AES_IRQn                 = 26, /**< 26 SAML21G18A Advanced Encryption Standard (AES) */
	TRNG_IRQn                = 27, /**< 27 SAML21G18A True Random Generator (TRNG) */

	PERIPH_COUNT_IRQn        = 28  /**< Number of peripheral IDs */
} IRQn_Type;

/*
 * \brief Configuration of the Cortex-M0+ Processor and Core Peripherals
 */

#define LITTLE_ENDIAN          1
#define __CM0PLUS_REV          1         /*!< Core revision r0p1 */
#define __MPU_PRESENT          0         /*!< MPU present or not */
#define __NVIC_PRIO_BITS       2         /*!< Number of bits used for Priority Levels */
#define __VTOR_PRESENT         1         /*!< VTOR present or not */
#define __Vendor_SysTickConfig 0         /*!< Set to 1 if different SysTick Config is used */

//TODO:adapt after cpu
#define FLASH_SIZE            0x00040000ul /* 256 kB */
#define FLASH_ADDR			  0x00000000ul

