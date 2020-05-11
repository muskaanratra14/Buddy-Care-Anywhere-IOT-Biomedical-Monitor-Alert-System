#include <LiquidCrystal.h>
//*************************************************
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);
/********************************************************************/
int pulsePin = A0;                 // Pulse Sensor purple wire connected to analog pin 0
int blinkPin = 13;                // pin to blink led at each beat 
// these variables are volatile because they are used during the interrupt service routine!
volatile int BPM;                   // used to hold the pulse rate
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // holds the time between beats, the Inter-Beat Interval
volatile boolean Pulse = false;     // true when pulse wave is high, false when it's low
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.
/********************************************************************/ 
int swi = 10;
unsigned long previousMillis=0;
//*************************************************
void setup() 
{
  Serial.begin(9600);
  pinMode(swi,INPUT_PULLUP);
  digitalWrite(swi,HIGH);
  lcd.begin(16, 2);
  pinMode(blinkPin,OUTPUT);
  digitalWrite(blinkPin,LOW);
  lcd.print(" IOT-Biomedical "); //IoT - Biomedical Monitor Alert System (Temp + Hearbeat)
  lcd.setCursor(0, 1);
  lcd.print(" Monitor System ");
  delay(3000);
  lcd.clear();
  interruptSetup();       
  previousMillis = millis();
  
}
//*************************************************
void loop()
{
 
   if (QS == true)                       // Quantified Self flag is true when arduino finds a heartbeat
  {      
    if(BPM>20 && BPM<200)
    {
      //lcd.setCursor(0, 1);lcd.print("P:        ");lcd.setCursor(3, 1);lcd.print(BPM);lcd.setCursor(9, 1);lcd.print("bpm");
      Serial.print("<");Serial.print("P");Serial.print(BPM);Serial.print(">");
    }
    else
    {
      BPM=0;
      //lcd.setCursor(0, 1);lcd.print("P:        ");lcd.setCursor(3, 1);lcd.print('-');lcd.setCursor(9, 1);lcd.print("bpm");
      Serial.print("<");Serial.print("P");Serial.print(BPM);Serial.print(">");
    }
    QS = false;                      // reset the Quantified Self flag for next time    
  }
  
  
  if(digitalRead(swi)==HIGH)
  {
   lcd.setCursor(0, 0);lcd.print("Reading.....     ");
   lcd.setCursor(0, 1);lcd.print("P:        ");lcd.setCursor(3, 1);lcd.print(BPM);lcd.print(" bpm         ");  
   if(millis() - previousMillis > 15000){Serial.print("<");Serial.print("U");Serial.print(">");previousMillis = millis();} 
  }
  else
  {
    // Nothing
    lcd.setCursor(0, 0);lcd.print("Reading a Button");
    lcd.setCursor(0, 1);lcd.print("     Press..    ");
  }
  
  
  
}
//*************************************************



