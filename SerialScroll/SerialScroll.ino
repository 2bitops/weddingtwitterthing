// scrolltext demo for Adafruit RGBmatrixPanel library.
// Demonstrates double-buffered animation on our 16x32 RGB LED matrix:
// http://www.adafruit.com/products/420

// Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.

#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

#define BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0 
 
#define WHITE           0xFFFF

#define CLK 8  // MUST be on PORTB! (Use pin 11 on Mega)
#define LAT A3
#define OE  9
#define A   A0
#define B   A1
#define C   A2
// Last parameter = 'true' enables double-buffering, for flicker-free,
// buttery smooth animation.  Note that NOTHING WILL SHOW ON THE DISPLAY
// until the first call to swapBuffers().  This is normal.
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);
// Double-buffered mode consumes nearly all the RAM available on the
// Arduino Uno -- only a handful of free bytes remain.  Even the
// following string needs to go in PROGMEM:

  String defaultString  = "@johnsarik Best. Centerpieces. Ever. #sevikforever";
  char str[200];
  int textX   = matrix.width();
  int textMin = defaultString.length() * -12;
  int hue     = 0;
  
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {

  // initialize serial:
  Serial.begin(9600);
 // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  matrix.begin();
  matrix.setTextWrap(false); // Allow text to run off right edge
  matrix.setTextSize(2);
  
  inputString.toCharArray(str,defaultString.length()+1);
  textX   = matrix.width();
  textMin = defaultString.length() * -12;
}

void loop() {
  if (stringComplete) {
 
    inputString.toCharArray(str,inputString.length()+1);
    //Serial.println("String received.");
    //Serial.print(str);
    //Serial.print(inputString.length());
    textX   = matrix.width();
    textMin = inputString.length() * -12;
    // clear the string:
    inputString = "";
    stringComplete = false;
   
     }
  // Clear background
  matrix.fillScreen(0);
  matrix.setCursor(textX, 1);
  for (int i = 0; i < sizeof(str); i++) {
    if (str[i] == 0x20)  {
      matrix.setTextColor(BLUE);
    } else if (str[i] == 0x40) {
      matrix.setTextColor(WHITE);
    }  else if (str[i] == 0x23){
      matrix.setTextColor(RED);
    }
    matrix.print(str[i]);
  }
  
  if((--textX) < textMin) textX = matrix.width();
  delay(10);
  // Update display
  //matrix.swapBuffers(false);
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
