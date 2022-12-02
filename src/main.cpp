#include <Arduino.h>
#include <M5stack.h>

const int pResistor = 15; //photot resistor assignedto pin 15 

float value, val_old = 0, val_new = 0, time_old = 0, time_new = 1;
float threshold = 1000;
float period = 0;
float freq = 0;
float tempreading;
float min_v = 5000, max_v = 0;

int x = 0, y = 0, x_pos = 0;
int y_pos[320] = {239};

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
val_new = analogRead(pResistor); // reads value on pin

if(val_new >= threshold && val_old <= threshold){ // if value previously was below threshold and now is over it
    time_old = time_new;                          // register it as a peak of the wave
    time_new = millis();

    period = time_new - time_old; // calculates the period of the wave

    freq = 60/(period/1000); //frequency calculation
}

  value = analogRead(pResistor);//Reads value of heartsensor and assigns it to float value
  
  tempreading = tempreading + value; //Variable to average 10 reading to be desplayed as one 
  
  if(value<min_v){ 
    min_v = value;
  }
  if(value>max_v){ 
    max_v = value;
  }

  if(x==10){
    //M5.Lcd.printf("Current_v = %10.1f\n",tempreading/20);//???
    M5.Lcd.printf("MAX = %09.4f\n", max_v);
    M5.Lcd.printf("MIN = %09.4f\n", min_v);
    M5.Lcd.printf("Y = %03i\n", y);
    M5.Lcd.printf("FREQ = %08.4f\n", freq);
    //M5.Lcd.printf("Period = %08.4f\n", period);
    M5.Lcd.setCursor(0, 0); 
    x = 0;//reset counter 
    tempreading = 0; //reset temp value
    y++;//add to clear screen counter
  }else{
    x++;
  }

  if(y==20){//clear screen every 20 prints
    //Clear_Screen();
    min_v = 5000;//reset min and max value counter
    max_v = 0;
    y=0;
  }

  //graphing functionality
  //~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>
  if(x_pos == 320){
    x_pos = 0;
  }

  M5.Lcd.drawPixel(x_pos, y_pos[x_pos], BLACK);

  y_pos[x_pos] = 230 - (120 * (value / 4095));

  if(value == 4095){
    M5.Lcd.drawPixel(x_pos, y_pos[x_pos], YELLOW);
  }

  else if(value < 4095 && value >= threshold){
    M5.Lcd.drawPixel(x_pos, y_pos[x_pos], GREEN);
  }

  else if(value < threshold){
    M5.Lcd.drawPixel(x_pos, y_pos[x_pos], RED);
  }


  //~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>

  val_old = analogRead(pResistor);

  x_pos++;

  delay(20); //sampling rate of 240BPM*2*5<--(for ekg patern)
}

void Clear_Screen(){//clear screen and set cursor back to start
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("");
}
