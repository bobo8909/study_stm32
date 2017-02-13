//#include "system_stm32f10x.h"
//#include "stm32f10x_spi.h"
#include "usart.h"
#include <stdio.h>
#include "stm32f10x.h"

int main(void)
{
    usart_init();
    printf("usart init ok\r\n");

    while(1);         
}
