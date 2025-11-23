#define PB1 3
#define PB2 2

void setup() {
pinMode(PB1,PULLUP_INPUT);
pinMode(PB2,PULLUP_INPUT);
Serial.begin(9600);
}

void loop() {
Serial.print(digitalRead(PB1));
Serial.println(digitalRead(PB2));
delay(10);
}
