#include <Canbus.h>
#include <defaults.h>
#include <global.h>
#include <mcp2515.h>
#include <mcp2515_defs.h>
#include <FRCCAN.h>

namespace
{
  constexpr unsigned long UPDATE_MS = 5;
  unsigned long last_update_ms = 0;

  constexpr int INTPU_PIN = 9;
  uint8_t last_pin_value = 0xFF;

  constexpr unsigned long CAN_TX_MS = 1000;
  unsigned long last_pin_tx_ms = 0;

  constexpr uint32_t DEVICE_NUBMER = 6;
}

void setup()
{
  Serial.begin(9600);
  Serial.println("CAN Write - Testing transmission of CAN Bus messages");
  pinMode(INTPU_PIN, INPUT_PULLUP); // set pin 9 as INPUT
  delay(500);

  // Initialise MCP2515 CAN controller
  if (Canbus.init(CANSPEED_1000))
  {
    Serial.println("CAN Init ok");
  }
  else
  {
    Serial.println("Can't init CAN");
  }

  delay(500);
}

void loop()
{
  // TOTALLY AN RTOS
  const unsigned long NOW = millis();
  if ((NOW - last_update_ms) <= UPDATE_MS)
  {
    return;
  }
  last_update_ms = NOW;

  // read pin
  const uint8_t PIN_VALUE = (uint8_t)digitalRead(INTPU_PIN);
  if (ShouldTransmit(PIN_VALUE, NOW))
  {
    Serial.print("tx ");
    Serial.print(PIN_VALUE);
    Serial.print(" ");
    Serial.println(millis());
    CanTx(PIN_VALUE, NOW);
  }

  last_pin_value = PIN_VALUE;
}

bool ShouldTransmit(uint8_t value, const unsigned long &now)
{
  return (last_pin_value != value) || ((now - last_pin_tx_ms) >= CAN_TX_MS);
}

void CanTx(uint8_t value, const unsigned long &now)
{
  // tx CAN
  FRCCAN message(11, 8, 5, 7, DEVICE_NUBMER);
  message.Get()->header.rtr = 0;
  message.Get()->header.length = 8;
  message.Get()->data[0] = 0xFF;
  message.Get()->data[1] = 0xFF;
  message.Get()->data[2] = 0xFF;
  message.Get()->data[3] = 0xFF;
  message.Get()->data[4] = 0xFF;
  message.Get()->data[5] = 0xFF;
  message.Get()->data[6] = 0xFF;
  message.Get()->data[7] = value;

  mcp2515_bit_modify(CANCTRL, (1 << REQOP2) | (1 << REQOP1) | (1 << REQOP0), 0);
  mcp2515_send_message(message.Get());
  last_pin_tx_ms = now;
}