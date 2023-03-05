#include <TheThingsNetwork.h>

#define loraSerial Serial1
#define debugSerial Serial

// Replace REPLACE_ME with TTN_FP_EU868 or TTN_FP_US915
#define freqPlan TTN_FP_EU868

TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);

int     reset_port = 5;
int     RN2483_power_port = 6; //Note that an earlier version of the Marvin doesn't support seperate power to RN2483

void setup()
{
  loraSerial.begin(57600);
  debugSerial.begin(9600);

  //Enable power to the RN2483
  pinMode(RN2483_power_port, OUTPUT);
  digitalWrite(RN2483_power_port, HIGH);
  debugSerial.println("RN2483 Powered up");
  delay(1000);
  
  //Disable reset pin
  pinMode(reset_port, OUTPUT);
  digitalWrite(reset_port, HIGH);
}

void loop()
{
  debugSerial.println("Device Information");
  debugSerial.println();
  ttn.showStatus();
  debugSerial.println();
  debugSerial.println("Use the EUI to register the device for OTAA");
  debugSerial.println("-------------------------------------------");
  debugSerial.println();

  delay(10000);
}
