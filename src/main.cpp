#include <Arduino.h>
#include <M5stack.h>

const int pResistor = 15; //photot resistor assignedto pin 15 
int x_pos = 0;
int y_pos[320]={239};
float val_old = 0, val_new = 0, time_old = 0, time_new = 1;
float threshold = 1000;
float period = 0;
float freq = 0;
float tempreading;
float min_v = 5000, max_v = 0;

int x = 0, y = 0;

void Clear_Screen(); //forward declaration of clear screen

void setup() {
  M5.begin(); //Init M5Core. Initialize M5Core
  M5.Power.begin(); //Init Power module. Initialize the power module
  pinMode(pResistor, INPUT); //Set pResistor as INPUT
  Serial.begin(115200); //Serial setup for terminal monitoring
  M5.Lcd.setTextSize(2);
  delay(5000);//start up delay experiment
}
void loop() {
val_new = analogRead(pResistor); // reads value on pin

if(val_new >= threshold && val_old <= threshold){ //added or condition
    time_old = time_new; // register it as a peak of the wave
    time_new = millis();
    period = time_new - time_old; // calculates the period of the wave
    freq = 60/(period/1000); //frequency calculation
}
  tempreading = tempreading + val_new; //Variable to average 10 reading to be desplayed as one 
  
  if(val_new<min_v){ 
    min_v = val_new;
  }else if(val_new>max_v){ 
    max_v = val_new;
  }

  if(x==10){
    M5.Lcd.printf("Current_v = %5.01f\n",tempreading/x);//???
    M5.Lcd.printf("MAX = %09.4f\n", max_v);
    M5.Lcd.printf("MIN = %09.4f\n", min_v);
    M5.Lcd.printf("Y = %03i\n", y);
    M5.Lcd.printf("FREQ = %08.4f\n", freq);
    M5.Lcd.printf("Period = %06.2f\n", period);
    M5.Lcd.setCursor(0, 0); 
    x = 0;//reset counter 
    tempreading = 0; //reset temp value
    y++;//add to clear screen counter
  }else{
    x++;
  }

  //graphing functionality
  //~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>
  if(x_pos == 320){
    x_pos = 0;
  }

  M5.Lcd.drawPixel(x_pos, y_pos[x_pos], BLACK);

  y_pos[x_pos] = 230 - (120 * (val_new / 4095));

  if(val_new == 4095){
    M5.Lcd.drawPixel(x_pos, y_pos[x_pos], YELLOW);
  }

  else if(val_new < 4095 && val_new >= threshold){
    M5.Lcd.drawPixel(x_pos, y_pos[x_pos], GREEN);
  }

  else if(val_new < threshold){
    M5.Lcd.drawPixel(x_pos, y_pos[x_pos], RED);
  }
  x_pos++;
  //~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>
  
  if(y==20){//clear screen every 20 prints
    //Clear_Screen();
    min_v = 5000;//reset work around accidental light exposure
    max_v = 0;
    y=0;
  }
  //val_old = analogRead(pResistor);
  val_old = val_new;
  delay(20); //sampling rate of 240BPM*2*5<--(for ekg patern)
}

/*void Clear_Screen(){//clear screen and set cursor back to start
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("");
}*/