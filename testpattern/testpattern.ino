#include <avr/sleep.h>
#include <avr/power.h>

// Small test program to generate a singnal pattern for the 
// Amiga adapter for the RGBtoHDMI upscaler.
// Using an Arduino Micro which I have lying around.

//      Singal  Arduino pin     Atmega

#define CDAC    3            // OC0B 
#define CSYNC   2            // PD1

#define RED0    4            //  
#define RED1    5            // 
#define RED2    6            // 
#define RED3    7            // 
#define BLUE0   8            // 

#define GREEN3  A5           // 
#define GREEN2  A4           // 
#define GREEN1  A3           // 
#define GREEN0  A2           // 
#define BLUE3   A1           // 
#define BLUE2   A0           // 
#define BLUE1   13           // 

#define MODE60  11


void setup() 
{
    delay(2000);  // give boot-loader more time after interrupt 
    power_usb_disable();  // do not let USB interrupts interfere
  
    noInterrupts();

    // configure output pins
    pinMode(CDAC,  OUTPUT);  
    pinMode(CSYNC, OUTPUT);  
    pinMode(RED0, OUTPUT);  
    pinMode(RED1, OUTPUT);  
    pinMode(RED2, OUTPUT);  
    pinMode(RED3, OUTPUT);  
    pinMode(BLUE0, OUTPUT);  
    pinMode(GREEN3, OUTPUT);  
    pinMode(GREEN2, OUTPUT);  
    pinMode(GREEN1, OUTPUT);  
    pinMode(GREEN0, OUTPUT);  
    pinMode(BLUE3, OUTPUT);  
    pinMode(BLUE2, OUTPUT);  
    pinMode(BLUE1, OUTPUT);  

    pinMode(MODE60, INPUT_PULLUP);
    
    // -- TIMER 1 register setup (for horizontal sync)
    // set to mode 7 for 10-bit counter (fast PWM)
    // will count 0 to 1023 for a 64 us period
    // and triggers an interrupt
    TCCR1A = 
      B00000011;   // WGM1:0=3
    TCCR1B = 
      B00001000    // WGM3=1
    | B00000001 ;  // clock source = full speed

    // -- TIMER0 register setup (for 8Mhz pixel clock)
    // set to mode 7 (fast PCM mode)
    TCCR0A = 
      B00000011    // WGM1:0=3
    | B00110000;   // COM0B : Clear OC0B on Compare Match, set OC0B at TOP
    TCCR0B = 
      B00001000    // WGM3=1
    | B00000001;   // clock source = full speed
      
    OCR0A = 1; // count only to 1,
    OCR0B = 0; // clear output bit at 0
    
    // set timers to well-defined initial values to force timers to run
    // in harmonic operation from now on
    TCNT1H = 0;    // prepare high-byte for timer1 conter
    TCNT1L = 0;    // clear timer1 counter
    TCNT0 =  0;    // set timer0 counter to specified start value
       
    // enable timer 1 overflow interrupt at the next line start
    TIMSK1 = 0x01;  // B00000001;     

    // disable all other interrupts
    TIMSK0 = 0x00;
    TIMSK3 = 0x00;
    TIMSK4 = 0x00;

    // turn on the sleep feature
    sleep_enable();

    interrupts();
}

void sync(byte lowtime)
{
  byte i;
  
  // wait for next interrupt
  sleep_cpu();
  
  // bring CSYNC down for specified time 
  for (i=0; i<lowtime; i++)
  {
    PORTD = B00000000;
    PORTD = B00000000;
    PORTD = B00000000;
  }
  PORTD = B00000010;
}

void loop() 
{
  int i;
  bool mode60;
  
  for (i=0; i<3; i++) { sync(130); }    // 3 lines vertical syncs
  for (i=0; i<50; i++) { sync(11); }    // 50 lines top blanking

  mode60 = (digitalRead(MODE60) == LOW);
  
  for (i=0; i<20; i++)                  // 20 lines red pattern
  { 
      sync(11); 
      digitalWrite(CSYNC, HIGH);
      digitalWrite(RED0, HIGH);
      digitalWrite(RED1, HIGH);
      digitalWrite(RED2, HIGH);
      digitalWrite(RED3, HIGH);
      digitalWrite(RED0, LOW);
      digitalWrite(RED1, LOW);
      digitalWrite(RED2, LOW);
      digitalWrite(RED3, LOW);
  }    
  
  for (i=0; i<5; i++) { sync(11); }     // 5 empty lins
  
  for (i=0; i<20; i++)                  // 20 lines green pattern
  { 
      sync(11); 
      digitalWrite(CSYNC, HIGH);
      digitalWrite(GREEN0, HIGH);
      digitalWrite(GREEN1, HIGH);
      digitalWrite(GREEN2, HIGH);
      digitalWrite(GREEN3, HIGH);
      digitalWrite(GREEN0, LOW);
      digitalWrite(GREEN1, LOW);
      digitalWrite(GREEN2, LOW);
      digitalWrite(GREEN3, LOW);
  }    
  
  for (i=0; i<5; i++) { sync(11); }     // 5 empty lins
  
  for (i=0; i<20; i++)                  // 20 lines blue pattern
  { 
      sync(11); 
      digitalWrite(CSYNC, HIGH);
      digitalWrite(BLUE0, HIGH);
      digitalWrite(BLUE1, HIGH);
      digitalWrite(BLUE2, HIGH);
      digitalWrite(BLUE3, HIGH);
      digitalWrite(BLUE0, LOW);
      digitalWrite(BLUE1, LOW);
      digitalWrite(BLUE2, LOW);
      digitalWrite(BLUE3, LOW);
  }    

  for (i=0; i<140; i++) { sync(11); }     // 140 empty lins
  
  if (!mode60)
  {   for (i=0; i<50; i++) { sync(11); }  // 50 more empty lines for 50 Hz mode
  }
                                          // 313 Total
}


// timer interrupt does nothing but wakes up the main thread 
ISR(TIMER1_OVF_vect)
{
}
