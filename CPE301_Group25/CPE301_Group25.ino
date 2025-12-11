//Creators: Chris Aboujaoude, Ervin Martinez, Tevon Westby, Zachary Duggan
#include <LiquidCrystal.h>
#define RBE  0x80
#define TBE  0x20
#define FAN_MASK  0x10
#define GLED_MASK 0x80
#define YLED_MASK 0x20
#define RLED_MASK 0x08
#define BLED_MASK 0x02
#define PCI_MASK  0x0C
#define ST_BTN    0x08
#define RES_BTN   0x04
#define CTRL_BTN  0x02

// Registers for buttons
volatile unsigned char *PORT_B = (unsigned char *) 0x25;
    volatile unsigned char *DDR_B = (unsigned char *) 0x24;
volatile unsigned char *PIN_B = (unsigned char *) 0x23;

//Registers for LEDs
volatile unsigned char *PORT_C = (unsigned char *) 0x28;
volatile unsigned char *DDR_C = (unsigned char *) 0x27;
volatile unsigned char *PIN_C = (unsigned char *) 0x26;

//Registers for ADC
volatile unsigned char* my_ADMUX = (unsigned char*) 0x7C;
  volatile unsigned char* my_ADCSRB = (unsigned char*) 0x7B;
volatile unsigned char* my_ADCSRA = (unsigned char*) 0x7A;
volatile unsigned int* my_ADC_DATA = (unsigned int*) 0x78;

//Registers for UART0
volatile unsigned char *UCSR_0A = (unsigned char *) 0x00C0;
volatile unsigned char *UCSR_0B = (unsigned char *) 0x00C1;
volatile unsigned char *UCSR_0C = (unsigned char *) 0x00C2;
volatile unsigned char *UBRR_0 = (unsigned char *) 0x00C4;
volatile unsigned char *UDR_0 = (unsigned char *) 0x00C6;

// Registers for ISR interrupts
volatile unsigned char *myPCICR = (unsigned char *) 0x68;
volatile unsigned char *myPCIFR = (unsigned char *) 0x3B;
volatile unsigned char *myPCMSK0 = (unsigned char *) 0x6B;


typedef enum STATE {DISABLED, IDLE, ERROR, RUNNING} STATE;
STATE dev_state = DISABLED;

#define LCD_LEN   16
#define LCD_RS    12
#define LCD_EN    11
#define LCD_D4    6
#define LCD_D5    5
#define LCD_D6    4
#define LCD_D7    3      
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
char lcd_buf[LCD_LEN], err_msg[LCD_LEN];
 char state_map[4][16] = {"(DISABLED)", "IDLE", "ERROR", "RUNNING"};
unsigned char led_mask_map[4] = {YLED_MASK, GLED_MASK, RLED_MASK, BLED_MASK};

void setup() {
   lcd.begin(16,2);
  IO_INIT();
  ADC_INIT();
  UART0_INIT(9600);
}

void loop(){
  switch(dev_state){
    case DISABLED:
     break;
   case IDLE:
      break;
    case ERROR:
      break;
    case RUNNING:
        break;
lcd.setCursor(0, 1);
lcd.print(state_map[dev_state]);

 LED_UPDATE(dev_state);
switch(dev_state){
  case DISABLED:
 *PORT_B &= ~FAN_MASK;
break;
 case IDLE:
*PORT_B &= ~FAN_MASK;
   lcd.setCursor(0, 0);
  lcd.print(lcd_buf);
        break;
      case ERROR:
  *PORT_B &= ~FAN_MASK;
     lcd.setCursor(0, 0);
        lcd.print(err_msg);
    break;
      case RUNNING:
     lcd.setCursor(0, 0);
        lcd.print(lcd_buf);
   *PORT_B |= FAN_MASK;
        break;
    }
  }
}
void LED_UPDATE(STATE state){
    *PORT_C = led_mask_map[state];
  }
ISR(PCINT0_vect){
  if (*PIN_B & RES_BTN){
    if (dev_state == ERROR){
      dev_state = IDLE;
    }
  } else if (*PIN_B & ST_BTN){
    if (dev_state == RUNNING || dev_state == IDLE || dev_state == ERROR){
      dev_state = DISABLED;
    } else if (dev_state == DISABLED){
      dev_state = IDLE;
    }
  }
}

void IO_INIT(){
  *DDR_C  |= GLED_MASK;
  *DDR_C  |= YLED_MASK;
  *DDR_C  |= RLED_MASK;
  *DDR_C  |= BLED_MASK;
  *DDR_B  |= FAN_MASK;

  *PORT_B |= ST_BTN;
  *DDR_B  &= ~(ST_BTN);

  *PORT_B |= RES_BTN;
  *DDR_B  &= ~(RES_BTN);

  *PORT_B |= CTRL_BTN;
  *DDR_B  &= ~(CTRL_BTN);

  *myPCICR |= 0x01;
  *myPCMSK0 |= PCI_MASK;
}

void ADC_INIT(){
  *my_ADCSRA |=  0b10000000; 
  *my_ADCSRA &=  0b11011111; 
    
  *my_ADCSRB &=  0b11110111; 
  *my_ADCSRB &=  0b11111000; 
    
  *my_ADMUX  &=  0b01111111; 
  *my_ADMUX  |=  0b01000000; 
  *my_ADMUX  &=  0b11011111; 
  *my_ADMUX  &=  0b11100000;
}

void UART0_INIT(unsigned long baud){
  unsigned long FCPU = 16000000;
  unsigned int tbaud = (FCPU / 16 / baud - 1);

  *UCSR_0A = 0x20;
  *UCSR_0B = 0x18;
  *UCSR_0C = 0x06;
  *UBRR_0 = tbaud;
}
