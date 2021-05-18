//for Tof sensor
#include <Adafruit_VL53L0X.h>

// address we will assign if dual sensor is present
#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31
#define LOX3_ADDRESS 0x32
#define LOX4_ADDRESS 0x33
#define LOX5_ADDRESS 0x34
//#define HIGH_SPEED
//#define LOX6_ADDRESS 0x35

// set the pins to shutdown
#define SHT_LOX1 19
#define SHT_LOX2 18
#define SHT_LOX3 5
#define SHT_LOX4 17
#define SHT_LOX5 16
//#define SHT_LOX6 4

// objects for the vl53l0x
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox3 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox4 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox5 = Adafruit_VL53L0X();
//Adafruit_VL53L0X lox6 = Adafruit_VL53L0X();

// this holds the measurement
VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2;
VL53L0X_RangingMeasurementData_t measure3;
VL53L0X_RangingMeasurementData_t measure4;
VL53L0X_RangingMeasurementData_t measure5;
//VL53L0X_RangingMeasurementData_t measure6;

//for OLED
#include <Wire.h> 
#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h> 
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define motorPin 23

struct distant {
   int a;
   int b;
   int c;
   int d;
   int e;
//   int f;
};

#define maxdis 240
#define mindis 40
#define led 15

void setID() {
  //for tof sensor
  
  // all reset
  digitalWrite(SHT_LOX1, LOW);    
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
  digitalWrite(SHT_LOX4, LOW);
  digitalWrite(SHT_LOX5, LOW);
//  digitalWrite(SHT_LOX6, LOW);
  delay(20);
  Serial.println("reset ok");
  
  // all unreset
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, HIGH);
  digitalWrite(SHT_LOX3, HIGH);
  digitalWrite(SHT_LOX4, HIGH);
  digitalWrite(SHT_LOX5, HIGH);
//  digitalWrite(SHT_LOX6, HIGH);
  delay(20);

  // activating LOX1 and reseting LOX2-5
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
  digitalWrite(SHT_LOX4, LOW);
  digitalWrite(SHT_LOX5, LOW);
//  digitalWrite(SHT_LOX6, LOW);

  // initing LOX1
  if(!lox1.begin(LOX1_ADDRESS)) {
    Serial.println(F("Failed to boot first VL53L0X"));
    while(1);
  }
  delay(15);

  // activating LOX2
  digitalWrite(SHT_LOX2, HIGH);
  digitalWrite(SHT_LOX3, LOW);
  digitalWrite(SHT_LOX4, LOW);
  digitalWrite(SHT_LOX5, LOW);
//  digitalWrite(SHT_LOX6, LOW);
  delay(15);

  //initing LOX2
  if(!lox2.begin(LOX2_ADDRESS)) {
    Serial.println(F("Failed to boot second VL53L0X"));
    while(1);
  }

  // activating LOX3
  digitalWrite(SHT_LOX3, HIGH);
  digitalWrite(SHT_LOX4, LOW);
  digitalWrite(SHT_LOX5, LOW);
//  digitalWrite(SHT_LOX6, LOW);
  delay(15);

  //initing LOX3
  if(!lox3.begin(LOX3_ADDRESS)) {
    Serial.println(F("Failed to boot third VL53L0X"));
    while(1);
  }

  // activating LOX4
  digitalWrite(SHT_LOX4, HIGH);
  digitalWrite(SHT_LOX5, LOW);
//  digitalWrite(SHT_LOX6, LOW);
  delay(15);

  //initing LOX4
  if(!lox4.begin(LOX4_ADDRESS)) {
    Serial.println(F("Failed to boot 4th VL53L0X"));
    while(1);
  }

  // activating LOX5
  digitalWrite(SHT_LOX5, HIGH);
//  digitalWrite(SHT_LOX6, LOW);
  delay(15);

  //initing LOX5
  if(!lox5.begin(LOX5_ADDRESS)) {
    Serial.println(F("Failed to boot 5th VL53L0X"));
    while(1);
  }

//  // activating LOX6
//  digitalWrite(SHT_LOX6, HIGH);
//  delay(15);
//
//  //initing LOX6
//  if(!lox6.begin(LOX6_ADDRESS)) {
//    Serial.println(F("Failed to boot 6th VL53L0X"));
//    while(1);
//  }
  
}


struct distant read_dual_sensors() {
  lox1.rangingTest(&measure1, false); // pass in 'true' to get debug data printout!
  lox2.rangingTest(&measure2, false); // pass in 'true' to get debug data printout!
  lox3.rangingTest(&measure3, false); // pass in 'true' to get debug data printout!
  lox4.rangingTest(&measure4, false); // pass in 'true' to get debug data printout!
  lox5.rangingTest(&measure5, false); // pass in 'true' to get debug data printout!
//  lox6.rangingTest(&measure6, false); // pass in 'true' to get debug data printout!

  // print sensor one reading
  Serial.print(F("1: "));
  if(measure1.RangeStatus != 4) {     // if not out of range
    Serial.print(measure1.RangeMilliMeter);
  } else {
    Serial.print(F("Out of range"));
  }
  Serial.print(F("   "));

  // print sensor two reading
  Serial.print(F(" 2: "));
  if(measure2.RangeStatus != 4) {
    Serial.print(measure2.RangeMilliMeter);
  } else {
    Serial.print(F("Out of range"));
  }
  
  // print sensor three reading
  Serial.print(F(" 3: "));
  if(measure3.RangeStatus != 4) {
    Serial.print(measure3.RangeMilliMeter);
  } else {
    Serial.print(F("Out of range"));
  }

  // print sensor 4 reading
  Serial.print(F(" 4: "));
  if(measure4.RangeStatus != 4) {
    Serial.print(measure4.RangeMilliMeter);
  } else {
    Serial.print(F("Out of range"));
  }

  // print sensor 5 reading
  Serial.print(F(" 5: "));
  if(measure5.RangeStatus != 4) {
    Serial.print(measure5.RangeMilliMeter);
  } else {
    Serial.print(F("Out of range"));
  }

//  // print sensor 6 reading
//  Serial.print(F("6: "));
//  if(measure6.RangeStatus != 4) {
//    Serial.print(measure6.RangeMilliMeter);
//  } else {
//    Serial.print(F("Out of range"));
//  }

  Serial.println();

  struct distant dis;
  dis.a = measure1.RangeMilliMeter;
  dis.b = measure2.RangeMilliMeter;
  dis.c = measure3.RangeMilliMeter;
  dis.d = measure4.RangeMilliMeter;
  dis.e = measure5.RangeMilliMeter;
//  dis.f = measure6.RangeMilliMeter;
  return dis;
  
}

void setup() {

  //for OLED
//  ESP.wdtDisable();
//  ESP.wdtFeed();
//  
  Serial.begin(115200);

  // wait until serial port opens for native USB devices
  while (! Serial) { delay(1); }

  //for tof sensor
  pinMode(SHT_LOX1, OUTPUT);
  pinMode(SHT_LOX2, OUTPUT);
  pinMode(SHT_LOX3, OUTPUT);
  pinMode(SHT_LOX4, OUTPUT);
  pinMode(SHT_LOX5, OUTPUT);
//  pinMode(SHT_LOX6, OUTPUT);
  Serial.println(F("Shutdown pins inited..."));
  digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
  digitalWrite(SHT_LOX4, LOW);
  digitalWrite(SHT_LOX5, LOW);
//  digitalWrite(SHT_LOX6, LOW);
  Serial.println(F("Both in reset mode...(pins are low)"));
  Serial.println(F("Starting..."));
  setID();

  
  //for OLED
  Wire.begin();
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  pinMode(motorPin, OUTPUT);
  pinMode(led, OUTPUT);
}

void writeOLED(struct distant dis_oled){
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0, 6);
  display.println("Distance");

  display.setCursor(0, 16);
  //   Display static text
  display.print("1: ");
  display.print(dis_oled.a);
  display.print("mm");
  display.display();

  display.setCursor(0, 26);
  //   Display static text
  display.print("2: ");
  display.print(dis_oled.b);
  display.print("mm");
  display.display();

  display.setCursor(0, 36);
  //   Display static text
  display.print("3: ");
  display.print(dis_oled.c);
  display.print("mm");
  display.display();

  display.setCursor(0, 46);
  //   Display static text
  display.print("4: ");
  display.print(dis_oled.d);
  display.print("mm");
  display.display();

  display.setCursor(0, 56);
  //   Display static text
  display.print("5: ");
  display.print(dis_oled.e);
  display.print("mm");
  display.display();
}

void vibrate(int virsignal){
  if (virsignal == 0){
    digitalWrite(motorPin, HIGH); //not vibrate
  }
  else if (virsignal == 1){
    digitalWrite(motorPin, LOW); //vibrate
  }  
}

void loop() {
  struct distant distance;

  //for OLED
//  ESP.wdtFeed();
  display.clearDisplay();

  distance = read_dual_sensors();
  writeOLED(distance);

  if (((distance.a < maxdis) && (distance.a > mindis)) || ((distance.b < maxdis)&& (distance.b > mindis)) || ((distance.c < maxdis)&& (distance.c > mindis)) || ((distance.d < maxdis)&& (distance.d > mindis)) || ((distance.e < maxdis)&& (distance.e > mindis)))
    
    digitalWrite(led, LOW);
  else
    digitalWrite(led, HIGH);
    
  delay(100);
}
