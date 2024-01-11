#include <stdint.h>
#include <stdlib.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
    //RCC register for enabling GPIOA
	uint32_t*  pClkCtrlReg = (uint32_t*)(0x40023800 + 0x30);
	uint32_t* pGPIOAModeReg = (uint32_t*)(0x40020000 + 0x00);
	uint32_t*  pGPIOAOoutDataReg = (uint32_t*)(0x40020000 + 0x14);

	// Adresele de registre pentru configurarea pinilor GPIOB
	uint32_t* pClkCtrlRegB = (uint32_t*)(0x40023800 + 0x44);
	uint32_t* pGPIOBModeReg = (uint32_t*)(0x40020400 + 0x00);
	uint32_t* pGPIOBInputDataReg = (uint32_t*)(0x40020400 + 0x10);

	uint32_t delay = 0;
	//int randNum;

	//------------GPIOA---------------------------------------------
	// enable GPIOA
	uint32_t mask = 0x01 << 0;
	*pClkCtrlReg |= mask;

	// set GPIOA pin 5 as output
	mask = 0x01 << 10;
	*pGPIOAModeReg &= ~(0x3 <<10);
	*pGPIOAModeReg |= mask;


	// set GPIOA pin 5 HIGH
	mask = 0x01 << 5;
	*pGPIOAOoutDataReg |= mask;
	// Enable GPIOA pin 13 (PA13) ca intrare
	//*pGPIOAModeReg &= ~(0x3 << (2 * 13));

	// -------------GPIOB--------------------------------------------
	// Activează ceasul pentru GPIOB
	*pClkCtrlRegB |= (0x01 << 1);

	// Configurează GPIOB pin 13 (PB13) ca intrare
	*pGPIOBModeReg &= ~(0x3 << (2 * 13));  // 2 biți/pin, PB13

	/*
	for (int i = 0; i < 3; i++){
		randNum = rand() % 10 + 1;
	}
	*/


	while (1){

		if ((*pGPIOBInputDataReg & (0x01 << 13)) != 0) {
			for (delay =0; delay < 1000000; delay++);
			*pGPIOAOoutDataReg |= mask;
			for (delay =0; delay < 1000000; delay++);
		 	 }
		else{
			for (delay =0; delay < 1000000; delay++);
			*pGPIOAOoutDataReg &= ~mask;
			for (delay =0; delay < 1000000; delay++);
		}
		 }

	/*
	for (int j = 0; j < randNum; j++){
		*pGPIOAOoutDataReg |= mask;
		for (delay =0; delay < 1000000; delay++);
		*pGPIOAOoutDataReg &= ~mask;
		for (delay =0; delay < 1000000; delay++);
		}
	*/

	return 0;
}
