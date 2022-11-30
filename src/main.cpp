#include <Arduino.h>
#include <M5stack.h>
const int pResistor = 15; //photot resistor assignedto pin 15 

float value;
float tempreading;
int x = 0, y = 0;

void Clear_Screen(); //forward declaration of clear screen

void setup() {
  M5.begin(); //Init M5Core. Initialize M5Core
  M5.Power.begin(); //Init Power module. Initialize the power module
  pinMode(pResistor, INPUT); //Set pResistor as INPUT
  Serial.begin(115200); //Serial setup for terminal monitoring
  delay(5000);//start up delay experiment
}
void loop() {
  value = analogRead(pResistor);//Reads value of heartsensor and assigns it to float value
  tempreading = tempreading + value; //Variable to average 10 reading to be desplayed as one 
  delay(20); //sampling rate of 240BPM*2*5<--(for ekg patern)
  if(x==10){
    M5.Lcd.printf("%10.04f\n",tempreading/10);
    x = 0;//reset counter 
    tempreading = 0; //reset temp value
    y++;//add to clear screen counter
  }else{
    x++;
  }

  if(y==20){//clear screen every 20 prints
    Clear_Screen();
  }
}

void Clear_Screen(){//clear screen and set cursor back to start
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("");
}
