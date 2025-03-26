#include <Canbus.h>
#include <defaults.h>
#include <global.h>
#include <mcp2515.h>
#include <mcp2515_defs.h>

namespace
{
  constexpr unsigned long UPDATE_MS = 5;
  unsigned long last_update_ms = 0;

  constexpr int INTPU_PIN = 9;
  uint8_t last_pin_value = 0xFF;

  constexpr unsigned long CAN_TX_MS = 1000;
  unsigned long last_pin_tx_ms = 0;
}

void setup()
{
  Serial.begin(9600);
  Serial.println("CAN Write - Testing transmission of CAN Bus messages");
  delay(1000);

  // Initialise MCP2515 CAN controller
  if (Canbus.init(CANSPEED_1000))
  {
    Serial.println("CAN Init ok");
  }
  else
  {
    Serial.println("Can't init CAN");
  }

  pinMode(INTPU_PIN, INPUT_PULLUP); // set pin 9 as INPUT
  delay(100);
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
  last_pin_tx_ms = now;
  // tx CAN
  tCAN message;
  message.id = 0x01011840;
  message.header.rtr = 0;
  message.header.length = 8;
  message.data[0] = 0xFF;
  message.data[1] = 0xFF;
  message.data[2] = 0xFF;
  message.data[3] = 0xFF;
  message.data[4] = 0xFF;
  message.data[5] = 0xFF;
  message.data[6] = 0xFF;
  message.data[7] = value;

  mcp2515_bit_modify(CANCTRL, (1 << REQOP2) | (1 << REQOP1) | (1 << REQOP0), 0);
  mcp2515_send_message(&message);
}