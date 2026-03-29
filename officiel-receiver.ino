#include <SPI.h>
#include <RF24.h>

RF24 radio(9, 10);
const byte address[6] = "NODE1";

struct Data {
  int speed;
};

Data data;

// Only direction pins
int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  radio.begin();
  radio.setChannel(108);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(0, address);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    radio.read(&data, sizeof(data));

    if (data.speed > 0) {
      // FORWARD
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    } 
    else if (data.speed < 0) {
      // BACKWARD
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    } 
    else {
      // STOP
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
    }
  }
}