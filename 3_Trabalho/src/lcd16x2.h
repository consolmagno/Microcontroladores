#ifndef LCD16x2
#define LCD16x2

#define     LCD_DIR               P2DIR
#define     LCD_OUT               P2OUT

#define     LCD_PIN_D4            BIT0          // P1.4
#define     LCD_PIN_D5            BIT1          // P1.5
#define     LCD_PIN_D6            BIT2          // P1.6
#define     LCD_PIN_D7            BIT3          // P1.7
#define     LCD_PIN_RS            BIT4          // P1.0
#define     LCD_PIN_EN            BIT5          // P1.1

#define     LCD_PIN_MASK  ((LCD_PIN_RS | LCD_PIN_EN | LCD_PIN_D7 | LCD_PIN_D6 | LCD_PIN_D5 | LCD_PIN_D4))

#define     FALSE                 0
#define     TRUE                  1

void LCDSet_CursorPosition(char Row, char Col);
void Clear_LCDScreen();
void Initialize_LCD(void);
void Print_String(char *Text);
void LCD_outdec(long data, unsigned char ndigits);
void SendByte(char ByteToSend, int IsData);

#endif
