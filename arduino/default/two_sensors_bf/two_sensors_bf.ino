#include <util/delay.h>

//  Variables
int APin = 0;        // Sensor1 connected to ANALOG PIN 0
int BPin = 1;        // Sensor2 connected to ANALOG PIN 1
const int PWM_PIN = 5;

int sampling_rate = 250;
long int baudrate = 115200;

unsigned int aVal = 0;
unsigned int bVal = 0;
int PWM = 0;
int prev_PWM = 0;
int bf = 0;

// To compute: inter_sample_interval_us
//int(round(float(1000/sampling_rate))) ->use this formula to calculate. Here it can not be made dymanic due to library limitation
// Also account for the average processing delay, and substract from the value, e.g. for 250 sampling rate, 4 - 0.7
// 0.1 -> ADC, 0.2 - serial.Print, 0.1 - Misc
double inter_sample_interval_us = 3.3;

// The SetUp Function:
void setup() {
   Serial.begin(baudrate);         // Set's up Serial Communication at certain speed.
   pinMode(APin, INPUT);
   pinMode(BPin, INPUT);
}

// The Main Loop Function
void loop() {

    bf = Serial.read();
    switch(bf)
    {
      case '0':
        PWM = 0;
        prev_PWM = PWM;
        break;
      case '1':
        PWM = 70;
        prev_PWM = PWM;
        break;
      case '2':
        PWM = 80;
        prev_PWM = PWM;
        break;
      case '3':  
        PWM = 90;
        prev_PWM = PWM;
        break;
      case '4':
        PWM = 100;
        prev_PWM = PWM;
        break;
      case '5':  
        PWM = 110;
        prev_PWM = PWM;
        break;
      case '6':
        PWM = 120;
        prev_PWM = PWM;
        break;
      case '7':  
        PWM = 130;
        prev_PWM = PWM;
        break;
      case '8':  
        PWM = 140;
        prev_PWM = PWM;
        break;
      default:
        PWM = prev_PWM;
        break;
    }

   analogWrite(PWM_PIN, PWM);
   
   aVal = analogRead(APin); // Read the Sensor1 value. Assign this value to the "aVal" variable.
   bVal = analogRead(BPin); // Read the Sensor2 value. Assign this value to the "bVal" variable.

   Serial.print(aVal); // Send the aVal value to Serial.
   Serial.print(",");
   Serial.println(bVal); // Send the bVal value to Serial.
   
   noInterrupts();
   _delay_ms(inter_sample_interval_us);
   interrupts();
}