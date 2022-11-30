#include <Arduino.h>
#include <M5stack.h>
const int pResistor = 15;

float value;
int x = 0;
void Clear_Screen();
void setup() {
  M5.begin(); //Init M5Core. Initialize M5Core
  M5.Power.begin(); //Init Power module. Initialize the power module
                    /* Power chip connected to gpio21, gpio22, I2C device
                      Set battery charging voltage and current
                      If used battery, please call this function in your project */
  //M5.Lcd.print("Hello World"); // Print text on the screen (string) Print text on the screen (string)
  pinMode(pResistor, INPUT);
  Serial.begin(115200);
  //delay(5000);
}
/* After the program in setup() runs, it runs the program in loop()
The loop() function is an infinite loop in which the program runs repeatedly
After the program in the setup() function is executed, the program in the loop() function will be executed
The loop() function is an endless loop, in which the program will continue to run repeatedly */

void loop() {
  value = analogRead(pResistor);
  delay(20);
  if(x==10){
    Clear_Screen();
    x = 0;
  }else{
    x++;
  }
  M5.Lcd.printf("%10.04f\n",value);
  //M5.Lcd.fillScreen(BLACK);
  //M5.Lcd.drawFloat(value,20,20,1);
 
}
void Clear_Screen(){
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("");
}
