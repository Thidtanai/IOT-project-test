/*  Include */
#include <SPI.h>
#include <RFID.h>

/*  Define  */
#define SS_PIN D2
#define RST_PIN D1
#define BLYNK_FIRMWARE_VERSION "0.1.0"
#define BLYNK_PRINT Serial
#define APP_DEBUG
/*  Blynk connection  */
#define BLYNK_TEMPLATE_ID "TMPL2DbS7Ca_"
#define BLYNK_TEMPLATE_NAME "IOT Project"
#include "BlynkEdgent.h"


RFID rfid(SS_PIN, RST_PIN);

//  RFID variable
int buzzPin = D4;
//  Blynk variable
const int ledPin3 = D3;
const int ledPin4 = D4;

// Setup variables:
int serNum0;
int serNum1;
int serNum2;
int serNum3;
int serNum4;

void setup()
{
  Serial.begin(115200);
  delay(100);

  //RFID
  SPI.begin();
  rfid.init();
  //BLYNK
  BlynkEdgent.begin();
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  digitalWrite(ledPin3, HIGH);
  digitalWrite(ledPin4, HIGH);
}

//------------------------- Blynk -----------------------------------
BLYNK_WRITE(V3) {
// Read the value of the Button widget
int buttonValue = param.asInt();

// If the button is pressed, turn the LED on; otherwise, turn it off
if (buttonValue == 1) {
digitalWrite(ledPin1, LOW);
} else {
digitalWrite(ledPin1, HIGH);
}
}

BLYNK_WRITE(V4) {
// Read the value of the Button widget
int buttonValue = param.asInt();

// If the button is pressed, turn the LED on; otherwise, turn it off
if (buttonValue == 1) {

digitalWrite(ledPin2, LOW);
} else {
digitalWrite(ledPin2, HIGH);
}
}
//---------------------------------------------------------------------------

void loop()
{
  //blynk
  BlynkEdgent.run();

  //
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      if (rfid.serNum[0] != serNum0
          && rfid.serNum[1] != serNum1
          && rfid.serNum[2] != serNum2
          && rfid.serNum[3] != serNum3
          && rfid.serNum[4] != serNum4
         ) {
        /* With a new cardnumber, show it. */
        Serial.println(" ");
        Serial.println("Card found");
        serNum0 = rfid.serNum[0];
        serNum1 = rfid.serNum[1];
        serNum2 = rfid.serNum[2];
        serNum3 = rfid.serNum[3];
        serNum4 = rfid.serNum[4];

        //Serial.println(" ");
        Serial.println("Cardnumber:");
        Serial.print("Dec: ");
        Serial.print(rfid.serNum[0], DEC);
        Serial.print(", ");
        Serial.print(rfid.serNum[1], DEC);
        Serial.print(", ");
        Serial.print(rfid.serNum[2], DEC);
        Serial.print(", ");
        Serial.print(rfid.serNum[3], DEC);
        Serial.print(", ");
        Serial.print(rfid.serNum[4], DEC);
        Serial.println(" ");

        Serial.print("Hex: ");
        Serial.print(rfid.serNum[0], HEX);
        Serial.print(", ");
        Serial.print(rfid.serNum[1], HEX);
        Serial.print(", ");
        Serial.print(rfid.serNum[2], HEX);
        Serial.print(", ");
        Serial.print(rfid.serNum[3], HEX);
        Serial.print(", ");
        Serial.print(rfid.serNum[4], HEX);
        Serial.println(" ");
        //buzzer
        analogWrite(3, 20);
        delay(500);
        analogWrite(3, 0);
      } else {
        /* If we have the same ID, just write a dot. */
        Serial.print(".");
      }
    }
  }

  rfid.halt();
}
