#include <Canbus.h>
#include <defaults.h>
#include <global.h>
#include <mcp2515.h>
#include <mcp2515_defs.h>
#include <SPI.h>
#include <SD.h>
#include "FRCCAN.h"
const int chipSelect = 9;
void setup()
{
  Serial.begin(9600); // For debug use
  pinMode(chipSelect, OUTPUT);
  Serial.println("CAN Read - Testing receival of CAN Bus message");
  delay(1000);
  if (Canbus.init(CANSPEED_1000)) // Initialise MCP2515 CAN controller at the specified speed
    Serial.println("CAN Init ok");
  else
    Serial.println("Can't init CAN");
  delay(1000);
  if (!SD.begin(chipSelect))
  {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
}
void loop()
{
  tCAN message;
  if (mcp2515_check_message())
  {
    if (mcp2515_get_message(&message))
    {
      FRCCAN frc_msg(message);

      Serial.print("ID: 0x");
      Serial.print(message.id, HEX);
      Serial.print(", DeviceType: ");
      Serial.print(frc_msg.DeviceType(), DEC);
      Serial.print(", Manufacturer: ");
      Serial.print(frc_msg.Manufacturer(), DEC);
      Serial.print(", APIId: 0x");
      Serial.print(frc_msg.MessageId(), HEX);
      Serial.print(", APIClass: ");
      Serial.print(frc_msg.APIClass(), DEC);
      Serial.print(", APIIndex: ");
      Serial.print(frc_msg.APIIndex(), DEC);
      Serial.print(", DeviceNumber: ");
      Serial.print(frc_msg.DeviceNumber(), DEC);
      Serial.print(", Data: ");

      for (int i = 0; i < message.header.length; i++)
      {
        Serial.print(message.data[i], HEX);
        Serial.print(" ");
      }
      Serial.println("");
      //}
    }
  }
}
