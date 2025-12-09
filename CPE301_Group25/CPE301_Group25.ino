//Creators: Chris Aboujaoude, Ervin Martinez, Tevon Westby, Zachary Duggan
#define RBE       0x80
#define TBE       0x20

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


typedef enum STATE {DISABLED, IDLE, ERROR, RUNNING} STATE;
STATE dev_state = DISABLED;


void setup() {
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
  }
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
