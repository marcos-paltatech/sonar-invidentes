#include "srf02_sensor.h"
#include "timer.h"

void srf02_setup()
{
	//I2C_DeInit(I2C1);

	// Clocks
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE); // Este comando rompe a SPI

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

	GPIO_PinRemapConfig(GPIO_Remap_I2C1, ENABLE);

	// GPIOs
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	I2C_InitTypeDef  I2C_InitStructure;
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_16_9;
	I2C_InitStructure.I2C_OwnAddress1 =  SENS_MASTER_ADDRESS;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = SENS_I2C_FREQ;
	I2C_Cmd(I2C1, ENABLE);
	I2C_Init(I2C1, &I2C_InitStructure);

	I2C_AcknowledgeConfig(I2C1, ENABLE);
}


void srf02_setCommand(uint8_t sensorAddr)
{
	// comando para resultado en cms.
	uint8_t command = 0x51;

	//printf ("Esperando bus...\r\n");
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

	// 1. Send I2C1 START condition
	I2C_GenerateSTART(I2C1, ENABLE);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

	// 2. Send the I2C address of the slave with the R/W bit low (even address)
	I2C_Send7bitAddress(I2C1, sensorAddr, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	// 3. Send the internal register number you want to write to
	I2C_SendData(I2C1, 0);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	// 4. Send the command byte (cm)
	I2C_SendData(I2C1, command);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	// 6. Send the stop sequence.
	I2C_GenerateSTOP(I2C1, ENABLE);
}


uint16_t srf02_getResult(uint8_t sensorAddr)
{
	uint8_t low, high;

	// Espero que se libere el bus
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

	// Send START condition
	I2C_GenerateSTART(I2C1, ENABLE);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

	// 2. Send I2C address of the sensor with the R/W bit low (even address)
	I2C_Send7bitAddress(I2C1, sensorAddr, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	// 3. Send Internal address of the bearing register
	I2C_SendData(I2C1, 2);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	// 4. Send a start sequence again (repeated start)
	I2C_GenerateSTART(I2C1, ENABLE);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

	// 5. Send I2C address of the sensor with the R/W bit high (odd address)
	I2C_Send7bitAddress(I2C1, sensorAddr, I2C_Direction_Receiver);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

	sleep(10);
	if(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED))
	{
		high = I2C_ReceiveData(I2C1);
		//printf("Leo alto de %x\r\n", sensorAddr);
	}
	sleep(10);
	I2C_AcknowledgeConfig(I2C1, DISABLE);

	if(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED))
	{
		low = I2C_ReceiveData(I2C1);
		//printf("Leo bajo de %x\r\n", sensorAddr);
	}
	sleep(10);

	I2C_NACKPositionConfig(I2C1, I2C_NACKPosition_Current);

	// Generate STOP condition
	I2C_GenerateSTOP(I2C1, ENABLE);

	// Enable Acknowledgement to be ready for another reception
	I2C_AcknowledgeConfig(I2C1, ENABLE);

	return (high << 8) | low;
}


void srf02_setAddress(uint8_t old, uint8_t new)
{
	printf ("Esperando bus...\r\n");
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

	// Primer comando de la secuencia -> 0xA0
	I2C_GenerateSTART(I2C1, ENABLE);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

	I2C_Send7bitAddress(I2C1, old, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	I2C_SendData(I2C1, 0);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_SendData(I2C1, 0xA0);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_GenerateSTOP(I2C1, ENABLE);

	// Segundo comando de la secuencia -> 0xAA
	I2C_GenerateSTART(I2C1, ENABLE);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

	I2C_Send7bitAddress(I2C1, old, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	I2C_SendData(I2C1, 0);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_SendData(I2C1, 0xAA);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_GenerateSTOP(I2C1, ENABLE);


	// Tercer comando de la secuencia -> 0xA5
	I2C_GenerateSTART(I2C1, ENABLE);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

	I2C_Send7bitAddress(I2C1, old, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	I2C_SendData(I2C1, 0);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_SendData(I2C1, 0xA5);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_GenerateSTOP(I2C1, ENABLE);


	// Nueva direccion
	I2C_GenerateSTART(I2C1, ENABLE);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

	I2C_Send7bitAddress(I2C1, old, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	I2C_SendData(I2C1, 0);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_SendData(I2C1, new);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_GenerateSTOP(I2C1, ENABLE);
}
