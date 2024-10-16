#include<LPC21xx.h>
typedef struct message
{
unsigned int byteA;
unsigned int byteB;
unsigned int id;
unsigned int dlc;
unsigned int rtr;
}CAN2;


typedef struct can2
{
unsigned int byteA;
unsigned int byteB;
unsigned int id;
unsigned int dlc;
unsigned int rtr;
}msg;



extern void delay_ms(unsigned int ms);
extern void delay_sec(unsigned int sec);
extern void timer1_config(void);
extern void config_timer1_for_VIC();

extern void lcd_data(unsigned char data);
extern void lcd_cmd(unsigned char cmd);
extern void lcd_init(void);
extern void lcd_string(unsigned char *ptr);
extern void lcd_integer(int);
extern void cgram_leftIndc(void);
extern void cgram_rightIndc(void);
extern void cgram_hl(void);
extern void cgram_bA(void);
extern void cgram_bB(void);
extern void cgram_bC(void);
extern void cgram_bD(void);

extern unsigned char uart_rx(void);
extern void uart0_tx(char data);
extern void uart0_init(unsigned int baud);
extern void uart0_tx_int(int n);
extern void uart0_tx_string(char *ptr);
extern void uart0_tx_float(float n);
extern void uart0_rx_string_passwdAuth(int len);
extern void uart0_rx_string(unsigned char *ptr,int len);
		 
extern void config_vic_for_eint0(void);
extern void config_eint0(void);

extern void config_vic_for_uart0(void);  
extern void en_uart0_interrupt(void);

extern void adc_init(void);
extern unsigned int adc_read(unsigned char);

extern void config_vic_for_can2(void);
extern void en_can2_interrupt(void);
extern void can2_init(void);
extern void can2_tx(msg m);

