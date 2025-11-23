#define PWM1 6
#define AIN1 7
#define BIN1 8

#define PWM2 9
#define AIN2 10
#define BIN2 11

void setup(){
  pinMode(PWM1,OUTPUT);
  pinMode(AIN1,OUTPUT);
  pinMode(BIN1,OUTPUT);
  
  pinMode(PWM2,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(BIN2,OUTPUT);
}

void loop(){
  forward();
  delay(2000);
  
  stop();
  delay(2000);
  
  backward();
  delay(2000);
  
  stop();
  delay(2000);
}

void stop(){
analogWrite(PWM1,0);
analogWrite(PWM2,0);
}

void forward(){
  digitalWrite(AIN1,1);
  digitalWrite(AIN2,1);
  digitalWrite(BIN1,0);
  digitalWrite(BIN2,0);
  analogWrite(PWM1,255);
  analogWrite(PWM2,255);
  
}
void backward(){
  digitalWrite(AIN1,0);
  digitalWrite(AIN2,0);
  digitalWrite(BIN1,1);
  digitalWrite(BIN2,1);
  analogWrite(PWM1,255);
  analogWrite(PWM2,255);

}
