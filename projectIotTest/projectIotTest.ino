/*Dom door lock
 * ใช้SHIPปลดลอค 
 */ 
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

//---------------  Blynk  -----------------
#define BLYNK_FIRMWARE_VERSION "0.1.0"
#define BLYNK_PRINT Serial
#define APP_DEBUG
/*  Blynk connection  */
#define BLYNK_TEMPLATE_ID "TMPL2DbS7Ca_"  //copy from blynk template info
#define BLYNK_TEMPLATE_NAME "IOT Project" //copy from blynk template info
#include "BlynkEdgent.h"
WidgetLCD lcd(V8);  //shown lcd in blynk
//----------------------------------------

#define SS_PIN 10
#define RST_PIN 9
String UID = "0C D5 51 2E";

byte lock = 0;

Servo servo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

MFRC522 rfid(SS_PIN, RST_PIN);


void setup() {
  Serial.begin(9600);
  servo.write(70);
  lcd.init();
  lcd.backlight();
  servo.attach(3);
  SPI.begin();
  rfid.PCD_Init();
}

void loop() {
  lcd.setCursor(4, 0);
  lcd.print("Welcome!");
  lcd.setCursor(1, 1);
  lcd.print("Put your card");

  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scanning");
  Serial.print("NUID tag is :");
  String ID = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    lcd.print(".");
    ID.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    ID.concat(String(rfid.uid.uidByte[i], HEX));
    delay(300);
  }
  ID.toUpperCase();

  if (ID.substring(1) == UID && lock == 0 ) {
    servo.write(70);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Door is locked");
    delay(1500);
    lcd.clear();
    lock = 1;
  } else if (ID.substring(1) == UID && lock == 1 ) {
    servo.write(160);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Door is open");
    delay(1500);
    lcd.clear();
    lock = 0;
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Wrong card!");
    delay(1500);
    lcd.clear();
  }
  //  Show status in blynk lcd
  lcd.clear();
  lcd.print(0, 0, "PRINT STATUS");
}


/*ใช้ไ้เทั้งสองอัน
 * 

#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
String UID = "0C D5 51 2E";
String UID1 = "83 23 38 BB";
byte lock = 0;

Servo servo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

MFRC522 rfid(SS_PIN, RST_PIN);


void setup() {
  Serial.begin(9600);
  servo.write(70);
  lcd.init();
  lcd.backlight();
  servo.attach(3);
  SPI.begin();
  rfid.PCD_Init();
}

void loop() {
  lcd.setCursor(4, 0);
  lcd.print("Welcome!");
  lcd.setCursor(1, 1);
  lcd.print("Put your card");

  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scanning");
  Serial.print("NUID tag is :");
  String ID = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    lcd.print(".");
    ID.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    ID.concat(String(rfid.uid.uidByte[i], HEX));
    delay(300);
  }
  ID.toUpperCase();

  if (ID.substring(1) == UID && lock == 0 ) {
    servo.write(70);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Door is locked");
    delay(1500);
    lcd.clear();
    lock = 1;
  } else if (ID.substring(1) == UID && lock == 1 ) {
    servo.write(160);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Door is open");
    delay(1500);
    lcd.clear();
    lock = 0;
  } else if (ID.substring(1) == UID1 && lock == 1 ) {
    servo.write(160);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Door is open");
    delay(1500);
    lcd.clear();
    lock = 0;
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Wrong card!");
    delay(1500);
    lcd.clear();
  }
  
} */ 
