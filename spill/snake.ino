#include <SPI.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();      

const int BLOCK_SIZE = 10;
const int XPin = 35;
const int YPin = 34;

const int w = tft.width(); // 320
const int h = tft.height(); // 480
char currentDirection = 'R';
int xPos = 0;
int yPos = 0;

int positions[1][2] = [[0,0]]; // a list with all cordinates.
int size = 1;
bool growing = true;

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
  //generating new pos for snake head
  int oldX = xPos;
  int oldY = yPos;


if (growing)
{
  int newPositions[size+1][2];
  //opying last element to new last
  newPositions[size+1][0] = positions[size][0];
  newPositions[size+1][1] = positions[size][1];
  for (int i = size-1; i > 0; i--)
  {
      newPositions[i+1][0] = positions[i][0];
      newPositions[i+1][1] = positions[i][1];
  }
  int positions = newPositions;
  size ++;
}else{
  //if not growing in size overvriting last digit
  for (int i = size-1; i > 0; i--)
  {
      positions[i+1][0] = positions[i][0];
      positions[i+1][1] = positions[i][1];
  }
}
positions[0][0] = xPos;
positions[0][1] = yPos;


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

  drawSnake();
  delay(100);


}

void drawSnake(){
  if (!growing)
  {
    tft.drawRect(positions[size][0], positions[size][0], BLOCK_SIZE, BLOCK_SIZE, TFT_GREEN);
    tft.fillRect(positions[size][0], positions[size][0], BLOCK_SIZE, BLOCK_SIZE, TFT_BLACK);
  }
  for (int i = 0; i < size; i++)
  {
    tft.fillRect(positions[i][0],positions[i][0], BLOCK_SIZE, BLOCK_SIZE, TFT_WHITE); 
  }
  

}
