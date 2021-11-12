// use Arduino-IDE

#include <SPI.h>

#include <TFT_eSPI.h> // Hardware-specific library

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

const int w = tft.width();
const int h = tft.height();


void setup() {

  tft.init();

  tft.setRotation(1);

  tft.fillScreen(TFT_BLACK);
}

void loop() {


}
