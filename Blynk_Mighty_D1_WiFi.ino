/**************************************************************
 * Blynk is a platform with iOS and Android apps to control
 * Arduino, Raspberry Pi and the likes over the Internet.
 * You can easily build graphic interfaces for all your
 * projects by simply dragging and dropping widgets.
 *
 *   Downloads, docs, tutorials: http://www.blynk.cc
 *   Blynk community:            http://community.blynk.cc
 *   Social networks:            http://www.fb.com/blynkapp
 *                               http://twitter.com/blynk_app
 *
 * Blynk library is licensed under MIT license
 * This example code is in public domain.
 *
 **************************************************************
 * This example runs directly on ESP8266 chip.
 *
 * Note: This requires ESP8266 support package:
 *   https://github.com/esp8266/Arduino
 *
 * Please be sure to select the right ESP8266 module
 * in the Tools -> Board menu!
 *
 * NOTE: SmartConfig might not work in your environment.
 *       Please try basic ESP8266 SmartConfig examples
 *       before using this sketch!
 *
 * Change Blynk auth token to run :)
 * 
 * Plus WiFi-config function into Blynk Mighty D1
 *
 **************************************************************/
#define BLYNK_TEMPLATE_ID "TMPLWyqbEHNV"
#define BLYNK_DEVICE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "tTwRu1Rgt0ca4W1FdseXtvzeLjL-_PWK"
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h> // Arduino IDE <1.6.6
//#include <PZEM004T.h>
#define BLYNK_PRINT Serial
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

BlynkTimer timer;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
//char auth[] = "4e08a6a3122343f5beb5c1c94369b4a7"; //imtbtest01;
//char auth[] = "f82b3aa574924044bcf36597bbab2779"; //imtbtest02; 
char auth[] = BLYNK_AUTH_TOKEN; //imtbtest01;

char ssid[] = "Kai";  //at home;
char pass[] = "12345678";   //at home;

//char ssid[] = "Classroom";  //at I40 Center;
//char pass[] = "ntustclassroom";   //at I40 Center;

//char ssid[] = "Jason iphone";
//char pass[] = "iphone0316";

//PZEM004T pzem(&Serial);
int x,y,z;
int voltage;
IPAddress ip(192,168,1,1);
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
void mySensor(){
  voltage = analogRead(A0);
   sensors_event_t event; 
 accel.getEvent(&event);
// x=event.acceleration.x;
// y=event.acceleration.y;
// z=event.acceleration.z;
 /* Display the results (acceleration is measured in m/s^2) */
 Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print(" ");
 Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print(" ");
 Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print(" ");Serial.println("m/s^2 ");
 //判斷是否有喝水動作/////////////////////////////////
  if(event.acceleration.y<7){
    z=1;
  }
  else{
    z=0;
  }
/*  if(voltage>500)
  {
    x=0;
  }
  else
 {
    x=1
 }*/
 //判斷水瓶水量/////////////////////////////////
if(voltage>330){
  voltage=330;
}
if(voltage<240){
  voltage=240;
}
  y=(330-voltage)/0.257;
 if(y>350){
 y=350;
 }
 x=350-y;
 //資料上傳/////////////////
  Serial.println(voltage);
  Blynk.virtualWrite(V0,x);
  Blynk.virtualWrite(V1,y);
  Blynk.virtualWrite(V2,z);
  Blynk.virtualWrite(V3,voltage);
}
void setup()
{
  Serial.begin(9600);
  
  Blynk.begin(auth, ssid, pass);
  //pzem.setAddress(ip);
  WiFi.mode(WIFI_STA);

  int cnt = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (cnt++ >= 10) {
      WiFi.beginSmartConfig();
      while (1) {
        delay(1000);
        if (WiFi.smartConfigDone()) {
          Serial.println();
          Serial.println("SmartConfig: Success");
          break;
        }
        Serial.print("|");
      }
    }
  }

  WiFi.printDiag(Serial);

  Blynk.config(auth);
  Serial.println("Accelerometer Test"); Serial.println("");
 
 /* Initialise the sensor */
 if(!accel.begin())
 {
 /* There was a problem detecting the ADXL345 ... check your connections */
 Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
 while(1);
 }
 
 /* Set the range to whatever is appropriate for your project */
 accel.setRange(ADXL345_RANGE_16_G);
 // displaySetRange(ADXL345_RANGE_8_G);
 // displaySetRange(ADXL345_RANGE_4_G);
 // displaySetRange(ADXL345_RANGE_2_G);
 
 /* Display some basic information on this sensor */
 displaySensorDetails();
 
 /* Display additional settings (outside the scope of sensor_t) */
 displayDataRate();
 displayRange();
 Serial.println("");
  timer.setInterval(1000L,mySensor);
 
}

void loop()
{
 // voltage = analogRead(A0);
 // int x,y,z;
  Blynk.run();
  timer.run();
  /* Get a new sensor event */ 
 //sensors_event_t event; 
 //accel.getEvent(&event);
 //x=event.acceleration.x;
 //y=event.acceleration.x;
 //z=event.acceleration.x;
 /* Display the results (acceleration is measured in m/s^2) */
 //Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print(" ");
 //Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print(" ");
 //Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print(" ");Serial.println("m/s^2 ");
  
  //Serial.println(voltage);
  //Blynk.virtualWrite(V0,x);
  //Blynk.virtualWrite(V1,y);
  //Blynk.virtualWrite(V2,z);
  //Blynk.virtualWrite(V3,voltage);
 //delay(500);
//  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(1000);                       // wait for a second
//  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
//  delay(1000);                       // wait for a second  
}


BLYNK_READ(V0) {
  float v = x;
  //if (v < 0.0) v = 0.0;
  Serial.println(x);
  Blynk.virtualWrite(V0,v);
  }

BLYNK_READ(V1) {
  float i = y;
  //if (i < 0.0) i = 0.0;
  Serial.println(y);
  Blynk.virtualWrite(V1,i);
  }

BLYNK_READ(V2) {
  float p =z;
  //if (p < 0.0) p = 0.0;
  Serial.println(z);
  Blynk.virtualWrite(V2,p);
  }

BLYNK_READ(V3) {
  float e = voltage;
  //if (e < 0.0) e = 0.0;
  Serial.println(voltage);
  Blynk.virtualWrite(V3,e);
  }

  void displaySensorDetails(void)
{
 sensor_t sensor;
 accel.getSensor(&sensor);
 Serial.println("------------------------------------");
 Serial.print ("Sensor: "); Serial.println(sensor.name);
 Serial.print ("Driver Ver: "); Serial.println(sensor.version);
 Serial.print ("Unique ID: "); Serial.println(sensor.sensor_id);
 Serial.print ("Max Value: "); Serial.print(sensor.max_value); Serial.println(" m/s^2");
 Serial.print ("Min Value: "); Serial.print(sensor.min_value); Serial.println(" m/s^2");
 Serial.print ("Resolution: "); Serial.print(sensor.resolution); Serial.println(" m/s^2"); 
 Serial.println("------------------------------------");
 Serial.println("");
 delay(500);
}
void displayDataRate(void)
{
 Serial.print ("Data Rate: "); 
 
 switch(accel.getDataRate())
 {
 case ADXL345_DATARATE_3200_HZ:
 Serial.print ("3200 "); 
 break;
 case ADXL345_DATARATE_1600_HZ:
 Serial.print ("1600 "); 
 break;
 case ADXL345_DATARATE_800_HZ:
 Serial.print ("800 "); 
 break;
 case ADXL345_DATARATE_400_HZ:
 Serial.print ("400 "); 
 break;
 case ADXL345_DATARATE_200_HZ:
 Serial.print ("200 "); 
 break;
 case ADXL345_DATARATE_100_HZ:
 Serial.print ("100 "); 
 break;
 case ADXL345_DATARATE_50_HZ:
 Serial.print ("50 "); 
 break;
 case ADXL345_DATARATE_25_HZ:
 Serial.print ("25 "); 
 break;
 case ADXL345_DATARATE_12_5_HZ:
 Serial.print ("12.5 "); 
 break;
 case ADXL345_DATARATE_6_25HZ:
 Serial.print ("6.25 "); 
 break;
 case ADXL345_DATARATE_3_13_HZ:
 Serial.print ("3.13 "); 
 break;
 case ADXL345_DATARATE_1_56_HZ:
 Serial.print ("1.56 "); 
 break;
 case ADXL345_DATARATE_0_78_HZ:
 Serial.print ("0.78 "); 
 break;
 case ADXL345_DATARATE_0_39_HZ:
 Serial.print ("0.39 "); 
 break;
 case ADXL345_DATARATE_0_20_HZ:
 Serial.print ("0.20 "); 
 break;
 case ADXL345_DATARATE_0_10_HZ:
 Serial.print ("0.10 "); 
 break;
 default:
 Serial.print ("???? "); 
 break;
 } 
 Serial.println(" Hz"); 
}
 
void displayRange(void)
{
 Serial.print ("Range: +/- "); 
 
 switch(accel.getRange())
 {
 case ADXL345_RANGE_16_G:
 Serial.print ("16 "); 
 break;
 case ADXL345_RANGE_8_G:
 Serial.print ("8 "); 
 break;
 case ADXL345_RANGE_4_G:
 Serial.print ("4 "); 
 break;
 case ADXL345_RANGE_2_G:
 Serial.print ("2 "); 
 break;
 default:
 Serial.print ("?? "); 
 break;
 } 
 Serial.println(" g"); 
}
