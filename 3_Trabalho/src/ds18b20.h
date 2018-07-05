#ifndef DS18B20
#define DS18B20

#define DS18B20_OUT 					 P1OUT
#define DS18B20_DIR 				   P1DIR
#define DS18B20_SEL					   P1SEL
#define DS18B20_IN					   P1IN
#define DS18B20_DATA_IN_PIN    BIT4
// #define DS18B20_VCC			       BIT3
// #define DS18B20_GND          	 BIT1

#define DS18B20_SKIP_ROM             0xCC
#define DS18B20_READ_SCRATCHPAD      0xBE
#define DS18B20_CONVERT_T            0x44

void Init_DS18B20(void);
unsigned int Reset_DS18B20 ( void );
void DS18B20_HI(void);
void DS18B20_LO(void);
void WriteZero(void);
void WriteOne(void);
unsigned int ReadBit(void);
void Write_DS18B20 (unsigned char,int );
unsigned int Read_DS18B20 ( void );
float GetData(void);
#endif
