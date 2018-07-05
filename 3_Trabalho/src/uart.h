#ifndef UART
#define UART

#define     RX               BIT1
#define     TX               BIT2
#define     LED_UART              BIT6

void Send_Data(volatile unsigned char c);
void Send_Int(int n);
void Send_String(char str[]);
void Init_UART();

#endif
