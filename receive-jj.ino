//the digicorder / digibox of telenet is out of sight
//so remote controller did not work
//you can buy ir-extenders
//this is cheap and easy
//and probably a better solution

//this sketch however lets you automate the selection of channels
//radio stations are on channel "900"
//one push could send out three digits



//arduino sketch adapted to telenet remote control
//protocol is not recognised
//so raw output is read, and send out again



#include <IRremote.h>
int RECV_PIN = 11;        // the pin where you connect the output pin of IR sensor
IRrecv irrecv(RECV_PIN);
decode_results results;
IRsend irsend; // Defaults to pin 3
#define MARK_EXCESS   100
uint16_t irSignal[100] ;


void setup()
{
  Serial.begin(115200);
  irrecv.enableIRIn();
}

void loop()
{

  if (irrecv.decode(&results))
  {
    irrecv.printResultShort(&Serial); //jj
    int codeLen = results.rawlen - 1;
    int value = results.value;
    Serial.println(" ");
    Serial.print("Code: ");
    Serial.println(results.value); //prints the value a a button press
    Serial.println("lengte ");
    Serial.println(codeLen);
    irrecv.printIRResultAsCArray(&Serial);

    if (codeLen > 0)
    {
      Serial.println();
      for (int i = 1; i <= codeLen; i++) {
        irSignal[i - 1] = results.rawbuf[i] * 50; //hard coded 50 

        Serial.print(irSignal[i - 1], DEC);
        Serial.print(" ");

      }

      irsend.sendRaw(irSignal, codeLen, 38);
      Serial.print("send");
      delay(500);
      codeLen = 0;
    }




  }
  irrecv.enableIRIn();
  irrecv.resume();
  delay(500);
  Serial.println("loop");
}
