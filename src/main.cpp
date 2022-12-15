#include <Arduino.h>
#include <M5stack.h>

const int pResistor = 15; //photot resistor assignedto pin 15 
const int size = 10;
int counter;
const int delayMs = 1;
float val_old = 0, val_new = 0, time_old = 0, time_new = 1;
float threshold = 1200;
float period = 0;
float freq = 0, old_freq = 0,avg_freq = 0, out_freq = 0;
int freq_array[size] = {};
int int_freq = 0,int_out_freq = 0;
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
  delay(1000);//start up delay experiment
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
    freq = 60/(period/1000);
    //Glitch detection
    freq_array[counter] = freq;
    
    /*if(freq_array[counter]+50<old_freq || freq_array[counter]-50>old_freq){ //
      freq_array[counter] = 0;
      if(counter>0){
        counter--;
      } 
    }*/
    old_freq =freq;
    if (counter == size-1){
      avg_freq = 0;
      out_freq = 0;
      for(int i=0; i<size-1;i++){
        avg_freq += freq_array[i];
      }
      out_freq = avg_freq/counter;
      counter = 0;
    }else{
      counter++;
    }  
    int_freq = (int)freq;
    int_out_freq = (int)out_freq;
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.printf("FREQ = %06.2f\n", freq);
    M5.Lcd.printf("Period = %06.2f\n", period);
    //M5.Lcd.printf("int_FREQ = %04i\n", int_freq);
    M5.Lcd.printf("int_FREQ = %04i\n", int_out_freq);
    M5.Lcd.drawLine(x_pos, 91, x_pos, 109, WHITE);

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
  //~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>~<>

  val_old = val_new;

  x_pos++;

  if(x_pos == 320){
    x_pos = 0;
  }
  delay(delayMs); //sampling rate of 240BPM*2*5<--(for ekg patern)
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/*void Clear_Screen(){//clear screen and set cursor back to start
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("");
}*/