#include <msp430g2553.h>
#include  "uart.h"


void Send_Data(volatile unsigned char c)
{
	while((IFG2&UCA0TXIFG)==0);
	UCA0TXBUF = c;
}

void Send_Int(int n)
{
	int casa, dig;
	if(n==0)
	{
		Send_Data('0');
		return;
	}

	if(n<0)
	{
		Send_Data('-');
		n = -n;
	}

	for(casa = 1; casa<=n; casa *= 10);

	casa /= 10;
	while(casa>0)
	{
		dig = (n/casa);
		Send_Data(dig+'0');
		n -= dig*casa;
		casa /= 10;
	}
}

void Send_String(char str[])
{
	int i;
	for(i=0; str[i]!= '\0'; i++)
		Send_Data(str[i]);
}

void Init_UART()
{
  //--------- Setting the UART function for P1.1 & P1.2 --------//

   P1SEL  |=  RX + TX;  // P1.1 UCA0RXD input
   P1SEL2 |=  RX + TX;  // P1.2 UCA0TXD output

  //------------ Configuring the UART(USCI_A0) ----------------//

   UCA0CTL1 |=  UCSSEL_2 + UCSWRST;  // USCI Clock = SMCLK,USCI_A0 disabled
   UCA0BR0   =  130;                 // 104 From datasheet table-
   UCA0BR1   =  6;                   // -selects baudrate =9600,clk = SMCLK
   UCA0MCTL  =  UCBRS_1;             // Modulation value = 1 from datasheet
   // UCA0STAT |=  UCLISTEN;            // loop back mode enabled
   UCA0CTL1 &= ~UCSWRST;             // Clear UCSWRST to enable USCI_A0

  //---------------- Enabling the interrupts ------------------//

   // IE2 |= UCA0TXIE;                  // Enable the Transmit interrupt
   IE2 |= UCA0RXIE;                  // Enable the Receive  interrupt
   _BIS_SR(GIE);                     // Enable the global interrupt
}
