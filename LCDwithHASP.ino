//Include the library files

#define BLYNK_TEMPLATE_ID "TMPLE0it4KBl"
#define BLYNK_TEMPLATE_NAME "home automation"
#define BLYNK_AUTH_TOKEN "UfG9NC4xwyHJOhOsNsGGjq9bXHv2Pv_y"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "LiquidCrystal_I2C.h"
#include <ESP32Servo.h> //includes the servo library

Servo myservo1;
Servo myservo2;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Hauto";
char pass[] = "hauto123";

BlynkTimer timer;

LiquidCrystal_I2C lcd(0x27,16,2);


#define ldr1 35 // set ldr 1 Analog input pin of East ldr as an integer
#define ldr2 34 // set ldr 2 Analog input pin of West ldr as an integer

//Define the relay pins
#define relay1 13
#define relay2 12
#define relay3 14
#define relay4 27
#define relay5 26
#define relay6 25
#define relay7 33
#define relay8 32

#define button1_vpin    V0
#define button2_vpin    V1
#define button3_vpin    V2 
#define button4_vpin    V3
#define button5_vpin    V4
#define button6_vpin    V5
int pos2 = 90; // initial position of the Horizontal movement controlling servo motor
int pos1 = 90; // initial position of the Horizontal movement controlling servo motor
int tolerance = 30; // allowable tolerance setting - so solar servo motor isn't constantly in motion

bool value1;
bool value2;
bool value3;
bool value4;
bool value5;  
bool value6; 
// #define button7_vpin    V6
// #define button8_vpin    V7

// Get the button values
// BLYNK_WRITE(V0) {
//   bool value0 = param.asInt();
//   // Check these values and turn the relay1 ON and OFF
//   if (value0 == 1) {
//     digitalWrite(relay1, LOW);
//   } else {
//     digitalWrite(relay1, HIGH);
//   }
// }

//Change the virtual pins according the rooms

//------------------------------------------------------------------------------
// This function is called every time the device is connected to the Blynk.Cloud
// Request the latest state from the server
BLYNK_CONNECTED() {
  Blynk.syncVirtual(button1_vpin);
  Blynk.syncVirtual(button2_vpin);
  Blynk.syncVirtual(button3_vpin);
  Blynk.syncVirtual(button4_vpin);
  Blynk.syncVirtual(button5_vpin);
  Blynk.syncVirtual(button6_vpin);
  // Blynk.syncVirtual(button7_vpin);
  // Blynk.syncVirtual(button0_vpin);
}

//Get the button values
BLYNK_WRITE(button1_vpin) {
   value1 = param.asInt();
  // Check these values and turn the relay2 ON and OFF
  if (value1 == 1) {
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, LOW);
  } else {
    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, HIGH);
  }
}
//Get the button values
BLYNK_WRITE(button2_vpin) {
  value2 = param.asInt();
  // Check these values and turn the relay2 ON and OFF
  if (value2 == 1) {
    digitalWrite(relay3, LOW);
    digitalWrite(relay4, LOW);
  } else {
    digitalWrite(relay3, HIGH);
    digitalWrite(relay4, HIGH);
  }
}
//Get the button values
BLYNK_WRITE(button3_vpin) {
  value3 = param.asInt();
  // Check these values and turn the relay3 ON and OFF
  if (value3 == 1) {
    digitalWrite(relay5, LOW);
  } else {
    digitalWrite(relay5, HIGH);
  }
}
//Get the button values
BLYNK_WRITE(button4_vpin) {
   value4 = param.asInt();
  // Check these values and turn the relay4 ON and OFF
  if (value4 == 1) {
    digitalWrite(relay6, LOW);
  } else {
    digitalWrite(relay6, HIGH);
  }
}
//Get the button values
BLYNK_WRITE(button5_vpin) {
   value5 = param.asInt();
  // Check these values and turn the relay5 ON and OFF
  if (value5 == 1) {
    digitalWrite(relay7, LOW);
  } else {
    digitalWrite(relay7, HIGH);
  }
}
//Get the button values
BLYNK_WRITE(button6_vpin) {
  value6 = param.asInt();
  // Check these values and turn the relay6 ON and OFF
  if (value6 == 1) {
    digitalWrite(relay8, LOW);
  } else {
    digitalWrite(relay8, HIGH);
  }
}
//Get the button values
// BLYNK_WRITE(button7_vpin) {
//   bool value7 = param.asInt();
//   // Check these values and turn the relay7 ON and OFF
//   if (value7 == 1) {
//     digitalWrite(relay7, LOW);
//   } else {
//     digitalWrite(relay7, HIGH);
//   }
// }
// //Get the button values
// BLYNK_WRITE(button8_vpin) {
//   bool value8 = param.asInt();
//   // Check these values and turn the relay8 ON and OFF
//   if (value8 == 1) {
//     digitalWrite(relay8, LOW);
//   } else {
//     digitalWrite(relay8, HIGH);
//   }
// }

void setup() {
  //Set the relay pins as output pins
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(relay5, OUTPUT);
  pinMode(relay6, OUTPUT);
  pinMode(relay7, OUTPUT);
  pinMode(relay8, OUTPUT);

  // Turn OFF the relay
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  digitalWrite(relay8, HIGH);
  myservo1.attach(15); // attaches the servo on digital pin 13 to the horizontal movement servo motor 
  myservo2.attach(2); // attaches the servo on digital pin 12 to the horizontal movement servo motor 
  pinMode(ldr1, INPUT); //set East ldr pin as an input
  pinMode(ldr2, INPUT); //set West ldr pin as an input
  myservo1.write(pos1); // write the starting position of the horizontal movement servo motor 
  myservo2.write(pos2);
  // Serial.begin(9600); // write the starting position of the horizontal movement servo motor 
  // delay(10); // 1 second delay to allow the solar panel to move to its staring position before comencing solar tracking

  
  lcd.init();
  lcd.backlight();
  lcd.clear();

  //Initialize the Blynk library
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  delay(200);
}

void loop() {
  //Run the Blynk library
  Blynk.run();
  timer.run();
  if(value1==0||value1==1||value2==0||value2==1||value3==0||value3==1||value4==0||value4==1||value5==0||value5==1||value6==0||value6==1)
  {
    lcd.setCursor(0,0);
    lcd.print("1");
    lcd.setCursor(3,0);
    lcd.print("2");
    lcd.setCursor(6,0);
    lcd.print("3");
    lcd.setCursor(9,0);
    lcd.print("4");
    // if(value1==1||value1==0){
    if(value1==1){
    lcd.setCursor(14,0);
    lcd.print("SP");
    }
    else if(value1==0){
    lcd.setCursor(14,0);
    lcd.print("CH");
    }
    // }
    // else if(value2==1||value2==0){
    lcd.setCursor(12,1);
    if(value2==1){
    lcd.setCursor(12,1);
    lcd.print("M->C");
    }
    else if(value2==0){
    lcd.setCursor(12,1);
    lcd.print("Main");
    }
    // }
    // else if(value3==1||value3==0){
    lcd.setCursor(0,1);
    if(value3==1){
    lcd.print("ON ");
    }
    else if(value3==0){
    lcd.setCursor(0,1);
    lcd.print("OFF");
    }
    // }
    // else if(value4==1||value4==0){
    if(value4==1){
    lcd.setCursor(3,1);
    lcd.print("ON ");
    }
    else if(value4==0){
    lcd.setCursor(3,1);
    lcd.print("OFF");
    }
    // }
    // else if(value5==1||value5==0){
    if(value5==1){
    lcd.setCursor(6,1);
    lcd.print("ON ");
    }
    else if(value5==0){
    lcd.setCursor(6,1);
    lcd.print("OFF");
    }
    // }
    // else if(value6==1||value6==0){
    if(value6==1){
    lcd.setCursor(9,1);
    lcd.print("ON ");
    }
    else if(value6==0){
    lcd.setCursor(9,1);
    lcd.print("OFF");
    }
    // }
  }
    int val1 = analogRead(ldr1); // read the value of ldr 1
      // Serial.println(val1);
    int val2 = analogRead(ldr2); // read the value of ldr 2
          // Serial.println(val2);
    if((abs(val1 - val2) <= tolerance) || (abs(val2 - val1) <= tolerance)) {
    //no servo motor horizontal movement will take place if the ldr value is within the allowable tolerance
    }else {
    if(val1 > val2) // if ldr1 senses more light than ldr2 
    {
    pos1 = pos1+1; // decrement the 90 degree poistion of the horizontal servo motor - this will move the panel position Eastward
    pos2 = pos2-1; // decrement the 90 degree poistion of the horizontal servo motor - this will move the panel position Eastward
    }
    if(val1 < val2) // if ldr2 senses more light than ldr1
    {
    pos1 = pos1-1; // increment the 90 degree position of the horizontal motor - this will move the panel position Westward
    pos2 = pos2+1; // increment the 90 degree position of the horizontal motor - this will move the panel position Westward
    }
    }
        
    if(pos1 > 180) {pos1 = 180;} // reset the horizontal postion of the motor to 180 if it tries to move past this point
    if(pos2 > 180) {pos2 = 180;} // reset the horizontal postion of the motor to 180 if it tries to move past this point
    if(pos1 < 0) {pos1 = 0;} // reset the horizontal position of the motor to 0 if it tries to move past this point
    if(pos2 < 0) {pos2 = 0;} // reset the horizontal position of the motor to 0 if it tries to move past this point
    myservo1.write(pos1); // write the starting position to the horizontal motor
    myservo2.write(pos2); // write the starting position to the horizontal motor
    delay(50);
}