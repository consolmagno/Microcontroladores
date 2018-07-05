#include <msp430g2533.h>
#include "lcd16x2.h"

void Pulse_LCD()
{
    // pull EN bit low
    LCD_OUT &= ~LCD_PIN_EN;
    __delay_cycles(200);

    // pull EN bit high
    LCD_OUT |= LCD_PIN_EN;
    __delay_cycles(200);

    // pull EN bit low again
    LCD_OUT &= (~LCD_PIN_EN);
    __delay_cycles(200);
}

//-----------------------------------------------------------------------//
// Envie um byte no barramento de dados no modo de 4 bits
// Isso requer o envio dos dados em dois trechos.
// O nibble alto primeiro e depois o nible baixo
//
// Parâmetros:
//
// ByteToSend - o único byte para enviar
//
// IsData - definido como TRUE se o byte for um dado de caractere
// FALSE se for um comando                       //
 //-----------------------------------------------------------------------//
void SendByte(char ByteToSend, int IsData)
{
    // clear out all pins
    // set High Nibble (HN) -
    LCD_OUT &= (~LCD_PIN_MASK);
    LCD_OUT |= ((ByteToSend & 0xF0) >> 4);

    if (IsData == TRUE)
        LCD_OUT |= LCD_PIN_RS;
    else
        LCD_OUT &= ~LCD_PIN_RS;

    Pulse_LCD();

    // clear out all pins
    // set Low Nibble (LN) -
    LCD_OUT &= (~LCD_PIN_MASK);
    LCD_OUT |= ((ByteToSend & 0x0F) );

    if (IsData == TRUE)
        LCD_OUT |= LCD_PIN_RS;
    else
        LCD_OUT &= ~LCD_PIN_RS;

    Pulse_LCD();
}

// Set the position of the cursor on the screen
void LCDSet_CursorPosition(char Row, char Col)
{
    char address;
    // construct address from (Row, Col) pair
    if (Row == 0)
        address = 0;
    else
        address = 0x40;

    address |= Col;
    SendByte(0x80 | address, FALSE);
}

// Clear the screen data and return the
// cursor to home position
void Clear_LCDScreen()
{
    SendByte(0x01, FALSE);
    SendByte(0x02, FALSE);
}

// Initialize the LCD after power-up.
void Initialize_LCD(void)
{
    // set the MSP pin configurations
    // and bring them to low
    LCD_DIR |= LCD_PIN_MASK;
    LCD_OUT &= ~(LCD_PIN_MASK);

    // wait for the LCD to warm up and reach
    // active regions. Remember MSPs can power
    // up much faster than the LCD.
    __delay_cycles(100000);

    // initialize the LCD module
    // 1. Set 4-bit input
    LCD_OUT &= ~LCD_PIN_RS;
    LCD_OUT &= ~LCD_PIN_EN;
    LCD_OUT = 0x20;
    Pulse_LCD();

    // set 4-bit input - second time.
    // (as reqd by the spec.)
    SendByte(0x28, FALSE);

    // 2. Display on, cursor on, blink cursor
    SendByte(0x0E, FALSE);

    // 3. Cursor move auto-increment
    SendByte(0x06, FALSE);
}

// Print a string of characters to the screen
void Print_String(char *Text)
{
    char *c;
    c = Text;

    while ((c != 0) && (*c != 0))
    {
        SendByte(*c, TRUE);
        c++;
    }
}

void LCD_outdec(long data, unsigned char ndigits)
{
  	unsigned char sign, s[6];
  	unsigned int i;
  	sign = ' ';

  	if(data < 0)
    {
  		sign='-';
  		data = -data;
  	}

  	i = 0;

  	do {
  		s[i++] = data % 10 + '0';
  		if(i == ndigits) {
  			s[i++]='.';
  		}
  	} while( (data /= 10) > 0);

  	s[i] = sign;
    for (i = 0; i<5; i++)
    {
        SendByte(s[4-i], TRUE);
    }
}
