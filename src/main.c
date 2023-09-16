/**
 * @File 			main.c
 * @Version			V1.0
 * @Description		STC8A LED 闪烁 Demo
 * @Author			小土坡
 * @Email			xiaotupo@163.com
 * @Date            2023-9-16
*/
#include "stc8a8k64s4.h"
#include "xtp_define.h"
#include "delay.h"

sbit LED1 = P3^7;

u32 led_count = 0;
u8 led_dir_flag = 0; // 0: led_count++, 1: led_count--

void clock_config(void)
{
    P_SW2 |= (1<<7); // 开启时钟寄存器配置使能
    CLKSEL = 0x00; 		// 主时钟选择24MHz，关闭系统时钟外部输出模式
    while (!(IRC24MCR & 0x01)); // 等待24MHz频率稳定标志为1
    CLKDIV = 0; // 分频0，最终系统频率为24MHz
    P_SW2 &= ~(1<<7); // 关闭时钟寄存器配置使能
}

void gpio_config(void)
{
    // 配置 P3^7为推挽输出
    P3M0 &= 0xFF;
    P3M1 &= 0x7F;

    P_SW2 |= (1<<7); // 开启时钟寄存器配置使能
    // 禁能 P3^7 内部4.1k上拉电阻
    P3PU &= 0x7F;
    P_SW2 &= ~(1<<7); // 关闭时钟寄存器配置使能
}

void led_run(void)
{

    if (led_dir_flag==0)
    {
        led_count+=2;
        if (led_count >= 1000) led_dir_flag = 1;
    }
    else if (led_dir_flag ==1)
    {
        led_count-=2;
        if (led_count<=3) led_dir_flag = 0;
    }

    delay_ms(led_count);
    LED1 = ~LED1;
}

int main(void)
{
    clock_config(); // 配置时钟
    gpio_config();	// IO 配置
    while(1)
    {
        led_run();
    }
}