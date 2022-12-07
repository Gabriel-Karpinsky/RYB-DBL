#include <Arduino.h>
#include <M5stack.h>

const int pResistor = 15; //photot resistor assignedto pin 15 
int counter;
const int delayMs = 20;
float val_old = 0, val_new = 0, time_old = 0, time_new = 1;
float threshold = 1000;
float period = 0;
float freq = 0, temp_freq = 0, temp_old = 0, temp_new = 0;
int int_freq = 0;
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
  M5.Lcd.setTextSize(2);

  M5.Lcd.drawLine(0, 90, 320, 90, WHITE);
}
void loop() {
val_new = analogRead(pResistor); // reads value on pin

M5.Lcd.drawLine(x_pos, 91, x_pos, 109, BLACK);

if(val_new >= threshold && val_old <= threshold){ // if value previously was below threshold and now is over it
    time_old = time_new;                          // register it as a peak of the wave
    time_new = millis();

    period = time_new - time_old; // calculates the period of the wave
    temp_freq = 60/(period/1000); //frequency calculation
    //Glitch detection
    temp_old = temp_new; //temporarily variable storage
    temp_new = temp_freq; //
    
    if(temp_old+20<temp_new || temp_old-20>temp_new){ //
      temp_new = temp_old ;
    }else if (counter == 3){
      freq = temp_freq/counter;
      temp_freq = 0;
      counter = 0;
    }else{
      counter++;
    }  
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.printf("FREQ = %06.2f\n", freq);
    M5.Lcd.printf("Period = %06.2f\n", period);
    M5.Lcd.printf("int_FREQ = %04i\n", int_freq);
    M5.Lcd.drawLine(x_pos, 91, x_pos, 109, WHITE);
    int_freq = (int)freq;
}

  /*value = analogRead(pResistor);//Reads value of heartsensor and assigns it to float value
  
  tempreading = tempreading + value; //Variable to average 10 reading to be desplayed as one 
  
  if(value<min_v){ 
    min_v = value;
  }
  if(value>max_v){ 
    max_v = value;
  }*/

  /*if(x==10){
    //M5.Lcd.printf("Current_v = %10.1f\n",tempreading/20);//???
    M5.Lcd.printf("MAX = %09.4f\n", max_v);
    M5.Lcd.printf("MIN = %09.4f\n", min_v);
    M5.Lcd.printf("Y = %03i\n", y);
    M5.Lcd.printf("FREQ = %09.4f\n", freq);
    M5.Lcd.printf("Period = %09.4f\n", period);
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
  }*/

  //graphing functionality
  //~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>
  /*if(x_pos == 320){
    x_pos = 0;
  }*/

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


  //~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>

  val_old = val_new;

  x_pos++;

  if(x_pos == 320){
    x_pos = 0;
  }
  delay(delayMs); //sampling rate of 240BPM*2*5<--(for ekg patern)
}

/*void Clear_Screen(){//clear screen and set cursor back to start
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("");
}*/