#include <Arduino.h>
#include <M5stack.h>

const int pResistor = 15; //photot resistor assignedto pin 15 

float value;
float tempreading;
float min_v = 5000, max_v = 0;

int x = 0, y = 0;

void Clear_Screen(); //forward declaration of clear screen

void setup() {
  M5.begin(); //Init M5Core. Initialize M5Core
  M5.Power.begin(); //Init Power module. Initialize the power module
  pinMode(pResistor, INPUT); //Set pResistor as INPUT
  Serial.begin(115200); //Serial setup for terminal monitoring
  delay(5000);//start up delay experiment
  M5.Lcd.setTextSize(3);
}
void loop() {
  value = analogRead(pResistor);//Reads value of heartsensor and assigns it to float value
  tempreading = tempreading + value; //Variable to average 10 reading to be desplayed as one 
  if(value<min_v){ 
    min_v = value;
  }
  if(value>max_v){ 
    max_v = value;
  }
  delay(20); //sampling rate of 240BPM*2*5<--(for ekg patern)

  if(x==20){
    M5.Lcd.printf("Current_v = %10.04f\n",tempreading/20);//???
    M5.Lcd.printf("MAX = %09.4f\n", max_v);
    M5.Lcd.printf("MIN = %09.4f\n", min_v);
    M5.Lcd.printf("Y = %03i", y);
    M5.Lcd.setCursor(0, 0); 
    x = 0;//reset counter 
    tempreading = 0; //reset temp value
    y++;//add to clear screen counter
  }else{
    x++;
  }

  if(y==20){//clear screen every 20 prints
    //Clear_Screen();
    min_v = 5000;//reset work around accidental light exposure
    max_v = 0;
    y=0;
  }
}

void Clear_Screen(){//clear screen and set cursor back to start
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("");
}
