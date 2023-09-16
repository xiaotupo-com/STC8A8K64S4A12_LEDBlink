/**
 * @File 			delay.c
 * @Version			V1.0
 * @Description		软件延时
 * @Author			小土坡
 * @Email			xiaotupo@163.com
 * @Date            2023-9-16
*/
#include "delay.h"
#include "xtp_define.h"

void Delay1ms(void)	//@24.000MHz
{
	u8 data i, j;

	_nop_();
	i = 32;
	j = 40;
	do
	{
		while (--j);
	} while (--i);
}

void delay_ms(int ms)
{
	int i;
	for(i=0;i<ms;i++)
	{
		Delay1ms();
	}
}