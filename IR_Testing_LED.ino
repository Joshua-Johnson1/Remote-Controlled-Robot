#include <IRremote.h>

const int IR_Pin = 3;
const int LED_Pin = 4;
const uint32_t Toggle_Button = 0xBA45FF00;
bool toggleState = false;

void setup() 
{
pinMode(LED_Pin, OUTPUT);
Serial.begin(9600);
IrReceiver.begin(IR_Pin, ENABLE_LED_FEEDBACK);
}

void loop() 
{
  delay(1000);
  //Detect remote input and output to serial monitor
  if (IrReceiver.decode())
  {
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    IrReceiver.resume();
  }

  /*
  For turning a button on/off
  Toggles when the same button is pushed again to enable/disable LED output
  */  
  if (IrReceiver.decodedIRData.decodedRawData == Toggle_Button)
  {
    if (toggleState == false) //LED now turns on
    {
      toggleState = true;
      digitalWrite(LED_Pin, HIGH);
    }
    else if (toggleState == true) //LED now turns off
    {
      toggleState = false;
      digitalWrite(LED_Pin, LOW);
    }
  }
}
