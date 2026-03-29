#include <SPI.h>
#include <RF24.h>

RF24 radio(9, 10);
const byte address[6] = "NODE1";

struct Data {
  int speed;
};

Data data;

const int forwardBtn = 4;
const int backwardBtn = 5;

void setup() {
  pinMode(forwardBtn, INPUT_PULLUP);
  pinMode(backwardBtn, INPUT_PULLUP);

  radio.begin();
  radio.setChannel(108);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(address);
  radio.stopListening();
}

void loop() {
  bool fwd = digitalRead(forwardBtn) == LOW;
  bool bwd = digitalRead(backwardBtn) == LOW;

  if (fwd && !bwd) {
    data.speed = 255;   // forward
  } 
  else if (bwd && !fwd) {
    data.speed = -255;  // backward
  } 
  else {
    data.speed = 0;     // stop
  }

  radio.write(&data, sizeof(data));

  delay(50);
}