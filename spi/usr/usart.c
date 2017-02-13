#include "usart.h"
#include <stdarg.h>
#define BAUDRATE115200 115200
void usart_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* config USART1 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

	/*uart TX*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	/*uart RX*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	/*mode config*/
	USART_InitStructure.USART_BaudRate = BAUDRATE115200;      //波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;       //字长
	USART_InitStructure.USART_StopBits = USART_StopBits_1;      //停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;         //奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//硬件控制流
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  //单/双工
	USART_Init(USART1,&USART_InitStructure);
	USART_Cmd(USART1,ENABLE);
}

/*
 * 函数名：fputc
 * 描述  ：重定向c库函数printf到USART1
 * 输入  ：无
 * 输出  ：无
 * 调用  ：由printf调用
 */
int fputc(int ch, FILE *f)
{
	/* 将Printf内容发往串口 */
	USART_SendData(USART1, (unsigned char) ch);
	while (!(USART1->SR & USART_FLAG_TXE));
	
	return (ch);
}
