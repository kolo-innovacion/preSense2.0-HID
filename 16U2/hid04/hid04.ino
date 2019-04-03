
/*
  Copyright (c) 2014-2015 NicoHood
  See the readme for credit to other people.
  Serial HID-Bridge USBhyxifwtdxjpprrmdcepmdtjhkiydqkwbmr
  Select HoodLoader16u2 as board.
  After upload make sure the 16u2 sketch runs, not the HoodLoader2 bootloader.
  This example will type any serial data via keyboard.
*/

/*
  TEST HERE KEYBOARD INPUT
*/


#include "Keyboard.h"
#include "HID.h"

int keyDel = 1;
void setup() {
  // Start the Serial1 which is connected with the IO MCU.
  // Make sure both baud rates are the same
  // you can go up to 2000000 for very fast data transmission.
  Serial1.begin(115200);
  // Sends a clean report to the host. This is important on any Arduino type.
  Keyboard.begin();
  // Start the USB Serial for debugging
  //Serial.begin(115200);
}
void loop() {

  char c = Serial1.read();

  if (c == 'a') {
    sendActive();

  } else if (c == 'b') {
    sendInactive();
    //do nothing
  } else {}
}



void sendActive() {


  //start text: "SV:1200:1"

  Keyboard.write(0x0053);//S
  delay(keyDel);
  Keyboard.write(0x0056);//V
  delay(keyDel);
  Keyboard.write(0x003a);//://WARNING: CHECK SYSTEM LANGUAGE
  delay(keyDel);
  Keyboard.write(0x0031);//1
  delay(keyDel);
  Keyboard.write(0x0032);//2
  delay(keyDel);
  Keyboard.write(0x0030);//0
  delay(keyDel);
  Keyboard.write(0x0030);//0
  delay(keyDel);
  Keyboard.write(0x003a);//://WARNING: CHECK SYSTEM LANGUAGE
  delay(keyDel);
  Keyboard.write(0x0031);//1////////////////////////////////
  delay(keyDel);
  //start enter command (CR+LF)
  Keyboard.write(0x000D);//CR
  delay(keyDel);
  Keyboard.write(0x000A);//LF
  delay(keyDel);

  //Keyboard.write(0x00);

  //delay(10000);
}


void sendInactive() {


  //start text: "SV:1200:0"

  Keyboard.write(0x0053);//S
  delay(keyDel);
  Keyboard.write(0x0056);//V
  delay(keyDel);
  Keyboard.write(0x003a);//://WARNING: CHECK SYSTEM LANGUAGE
  delay(keyDel);
  Keyboard.write(0x0031);//1
  delay(keyDel);
  Keyboard.write(0x0032);//2
  delay(keyDel);
  Keyboard.write(0x0030);//0
  delay(keyDel);
  Keyboard.write(0x0030);//0
  delay(keyDel);
  Keyboard.write(0x003a);//://WARNING: CHECK SYSTEM LANGUAGE
  delay(keyDel);
  Keyboard.write(0x0030);//0////////////////////////////////
  delay(keyDel);
  //start enter command (CR+LF)
  Keyboard.write(0x000D);//CR
  delay(keyDel);
  Keyboard.write(0x000A);//LF
  delay(keyDel);

  //Keyboard.write(0x00);

  //delay(10000);
}
