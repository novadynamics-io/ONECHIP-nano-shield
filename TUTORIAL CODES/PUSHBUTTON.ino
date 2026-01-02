#define PB1 3
#define PB2 2

void setup() {
pinMode(PB1, INPUT_PULLUP);
pinMode(PB2, INPUT_PULLUP);
Serial.begin(9600);
}

void loop() {
Serial.print(digitalRead(PB1));
Serial.println(digitalRead(PB2));
delay(10);
}
