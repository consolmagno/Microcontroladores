#include <msp430g2533.h>
#include "totc.h"
#include "ds18b20.h"
#include "lcd16x2.h"
#include "uart.h"

float temperature=0;
int T_Limite = 10;

# define RLY1 BIT7

int main()
{
  WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
  //------------------- Configure the Clocks -------------------//

     DCOCTL  = 0;             // Select lowest DCOx and MODx settings
     BCSCTL1 = CALBC1_16MHZ;   // Set range
     DCOCTL  = CALDCO_16MHZ;   // Set DCO step + modulation

  //---------------- Configuring the LED's ----------------------//

     P1DIR  |=  BIT0 + BIT6 + RLY1;  // P1.0 and P1.6 output
     P1OUT  &= ~BIT0 + BIT6;  // P1.0 and P1.6 = 0

  //---------------- Inicializando os Modulos ----------------------//
     Initialize_LCD();
     Clear_LCDScreen();
	   Init_UART();

  //---------------- Loop Principal ----------------------//
	for(;;)
	{

		temperature=GetData();
		delay_ms(100);

    // Display LCD
    LCDSet_CursorPosition(0,2);
    Print_String("Projeto TOTC");
    LCDSet_CursorPosition(1,0);
    Print_String("Temp:");
    LCDSet_CursorPosition(1,6);
    LCD_outdec(temperature*100, 2);

    // Bluetooth UART
    // Send_String("Temp:");
    Send_Int((int)temperature*100);
    Send_String("\n");
    P1OUT &= ~LED_UART;

    // Controle de Temperatura
    if ( temperature< T_Limite) //Ativa o relé
      P1OUT |= RLY1;
    else  // desliga
      P1OUT &=~ RLY1;
	}
  return 0;
}
