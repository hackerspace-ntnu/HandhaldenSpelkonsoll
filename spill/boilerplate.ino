#include <SPI.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();      

const int BLOCK_SIZE = 10;
const int XPin = 35;
const int YPin = 34;

const int w = tft.width(); // 320
const int h = tft.height(); // 480
char currentDirection;
int xPos = 0;
int yPos = 0;

void setup() {
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  pinMode(XPin, INPUT);
  pinMode(YPin, INPUT);
  drawFrame();
  drawGrid();
  tft.fillRect(xPos, yPos, BLOCK_SIZE, BLOCK_SIZE, TFT_WHITE); 
}

void loop() {
  int x = analogRead(XPin);
  int y = analogRead(YPin);
  delay(10);

  char prevDir = currentDirection;

  if (x == 0) {
    if (prevDir != 'D'){
      currentDirection = 'U'; 
    } 
  }
  else if (y == 0) {
    if (prevDir != 'L'){
      currentDirection = 'R'; 
    }
  }
  else if (y == 4095 && x == 4095) {
    if (prevDir == 'U') {
      currentDirection = 'L';
    }
    else if (prevDir == 'R') {
      currentDirection = 'D';
    }
    else if (prevDir == 'D') {
      currentDirection = 'L';
    }
    else if (prevDir == 'L') {
      currentDirection = 'D';
    }
  }
  moveBlock();
}



void drawFrame() {
  tft.drawFastVLine(0, 0, w, TFT_GREEN);
  tft.drawFastVLine(h-1, 0, w, TFT_GREEN);
  tft.drawFastHLine(0, 0, h, TFT_GREEN);
  tft.drawFastHLine(0, w-1, h, TFT_GREEN);
}

void drawGrid() {
  for (int i=BLOCK_SIZE; i<h; i+=BLOCK_SIZE) {
    tft.drawFastVLine(i, 0, w, TFT_GREEN);
  }
  for (int j=BLOCK_SIZE; j<w; j+=BLOCK_SIZE) {
    tft.drawFastHLine(0, j, h, TFT_GREEN);
  }
}

void moveBlock() {
  int oldX = xPos;
  int oldY = yPos;
  switch(currentDirection) {
    case 'U':
      if (yPos-BLOCK_SIZE >= 0) {
        yPos -= BLOCK_SIZE;
      }
      break;
     case 'D':
      if (yPos+BLOCK_SIZE < w) {
        yPos += BLOCK_SIZE;
      }
      break;
     case 'L':
      if (xPos-BLOCK_SIZE >= 0) {
        xPos -= BLOCK_SIZE;
      }
      break;
     case 'R':
      if (xPos+BLOCK_SIZE < h) {
        xPos += BLOCK_SIZE;
      }
      break;   
  }
  tft.drawRect(oldX, oldY, BLOCK_SIZE, BLOCK_SIZE, TFT_GREEN);
  tft.fillRect(oldX, oldY, BLOCK_SIZE, BLOCK_SIZE, TFT_BLACK);
  tft.fillRect(xPos, yPos, BLOCK_SIZE, BLOCK_SIZE, TFT_WHITE); 
  delay(100);
  
}