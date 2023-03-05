#include <TheThingsNetwork.h>

// Set your AppEUI and AppKey
const char *appEui = "0059AC0000010198";
const char *appKey = "649D42A1A350A72FE2DA646FBE3D2210";

#define loraSerial Serial1
#define debugSerial Serial

// Replace REPLACE_ME with TTN_FP_EU868 or TTN_FP_US915
#define freqPlan TTN_FP_EU868
#define LED_BUILTIN 13

TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);

int     reset_port = 5;
int     RN2483_power_port = 6; //Note that an earlier version of the Marvin doesn't support seperate power to RN2483

void setup()
{
  loraSerial.begin(57600);
  debugSerial.begin(9600);

  // Wait a maximum of 10s for Serial Monitor
  while (!debugSerial && millis() < 10000)
    ;

  //Enable power to the RN2483
  pinMode(RN2483_power_port, OUTPUT);
  digitalWrite(RN2483_power_port, HIGH);
  debugSerial.println("RN2483 Powered up");
  delay(1000);
  
  //Disable reset pin
  pinMode(reset_port, OUTPUT);
  digitalWrite(reset_port, HIGH);

  debugSerial.println("-- STATUS");
  ttn.showStatus();

  debugSerial.println("-- JOIN");
  ttn.join(appEui, appKey);
}

void loop()
{
  debugSerial.println("-- LOOP");

  // Prepare payload of 1 byte to indicate LED status
  byte payload[1];
  payload[0] = (digitalRead(LED_BUILTIN) == HIGH) ? 1 : 0;

  // Send it off
  ttn.sendBytes(payload, sizeof(payload));

  delay(60000);
}
