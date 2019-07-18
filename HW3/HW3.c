#include "MKL25Z4.h"

void delay(unsigned int length_ms)
{
   SIM_SCGC5 |= SIM_SCGC5_LPTMR_MASK;  // Make sure clock is enabled
   LPTMR0_CSR = 0;                     // Reset LPTMR settings
   LPTMR0_CMR = length_ms;             // Set compare value (in ms)
   // Use 1kHz LPO with no prescaler
   LPTMR0_PSR = LPTMR_PSR_PCS(1) | LPTMR_PSR_PBYP_MASK;
    // Start the timer and wait for it to reach the compare value
   LPTMR0_CSR = LPTMR_CSR_TEN_MASK;
   while (!(LPTMR0_CSR & LPTMR_CSR_TCF_MASK))
       ;
   LPTMR0_CSR = 0;                     // Turn off timer
 }

#define LED1 (1)
#define LED2 (2)
#define LED3 (7)
#define KEY (1)
#define MASK(x) (1UL << (x))
 
/** GPIO - Register Layout Typedef */
#define __I volatile const
#define __O volatile
#define __IO volatile
	

/** GPIO - Register Layout Typedef */
typedef struct {
__IO uint32_t PDOR; /**< Data Output, offset: 0x0 */
__O uint32_t PSOR; /**< Set Output, offset: 0x4 */
__O uint32_t PCOR; /**< Clear Output, offset: 0x8 */
__O uint32_t PTOR; /**< Toggle Output, offset: 0xC */
__I uint32_t PDIR; /**< Data Input, offset: 0x10 */
__IO uint32_t PDDR; /**< Data Direction, offset: 0x14 */
}GPIO_type;

/* GPIO - Peripheral instance base addresses */
/** Peripheral PTA base address */
#define PTA_BASE	(0x400FF000u)
#define PTC_BASE	(0x400FF080u)
/** Peripheral PTA base pointer */
#define PTA 		((GPIO_Type *)PTA_BASE)
#define PTC 		((GPIO_Type *)PTC_BASE)

typedef struct {
  __IO uint32_t PCR[32];	/** Pin Control Register n, array offset: 0x0, array step: 0x4 */
  __O  uint32_t GPCLR;	/** Global Pin Control Low Register, offset: 0x80 */
  __O  uint32_t GPCHR;	/** Global Pin Control High Register, offset: 0x84 */
       uint8_t RESERVED_0[24];
  __IO uint32_t ISFR;	/** Interrupt Status x Register, offset: 0xA0 */
}PORT_type;

/* PORT - Peripheral instance base addresses */
/** Peripheral PORTA base address */
#define PORTA_BASE 	(0x40049000u)
#define PORTC_BASE (0x4004B000u)
/** Peripheral PORTA base pointer */
#define PORTA 		((PORT_Type *)PORTA_BASE)
#define PORTC 		((PORT_Type *)PORTC_BASE)

#define PORT_PCR_MUX_MASK 	0x700u
#define PORT_PCR_MUX_SHIFT   	8
#define PORT_PCR_MUX(x)	 (((uint32_t)(((uint32_t)(x))<<PORT_PCR_MUX_SHIFT)) &PORT_PCR_MUX_MASK)

int main(){
	int x=0;
	// Port A and C : Enable Clock 
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;   
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK; 
	//3 LED pins GPIO
	PORTC->PCR[LED1] &= ~PORT_PCR_MUX_MASK;          
	PORTC->PCR[LED1] |= PORT_PCR_MUX(1);          
	PORTC->PCR[LED2] &= ~PORT_PCR_MUX_MASK;          
	PORTC->PCR[LED2] |= PORT_PCR_MUX(1);     
	PORTC->PCR[LED3] &= ~PORT_PCR_MUX_MASK;          
	PORTC->PCR[LED3] |= PORT_PCR_MUX(1);
	//key pin GPIO
	PORTA->PCR[KEY] &= ~PORT_PCR_MUX_MASK;          
	PORTA->PCR[KEY] |= PORT_PCR_MUX(1); 
	PTC->PDDR |= MASK(LED1) | MASK (LED2) | MASK (LED3);
	PTA->PDDR &= ~MASK(KEY);
	PTC->PDOR &= ~MASK(LED1) & ~MASK(LED2) & ~MASK(LED3);
	
	
	while(1) {
		if(!(PTA->PDIR & MASK(KEY))) {
			delay(1000);
			if(x==2){
				 x = 0;
			}
			else x++;
			}
			if (x==0){
				PTC->PDOR &= ~MASK(LED3);
				PTC->PDOR &= MASK(LED1);
			}
			if (x==1){
				PTC->PDOR &= ~MASK(LED1);
				PTC->PDOR &= MASK(LED2);
			}
			if (x==2){
				PTC->PDOR &= ~MASK(LED2);
				PTC->PDOR &= MASK(LED3);
			}
	}
}