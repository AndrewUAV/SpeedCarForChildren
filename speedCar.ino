#include <Servo.h> 

#define ARM_RX 2
Servo arm_servo;

#define ARM_PWM 1800
#define DISARM_PWM 1800

#define SERVO_RX 3
#define THROTTLE_RX 4

#define TEST_PWM 8
Servo test_servo;

bool is_arming_flag = true;


void setup_rx(){
  arm_servo.attach(ARM_RX);

  pinMode(ARM_PWM, INPUT);
  pinMode(DISARM_PWM, INPUT);
}

bool is_arming(){
  int arm_pwm = arm_servo.readMicroseconds();
  if (arm_pwm < DISARM_PWM && is_arming_flag){
      Serial.println("DISARM");
      is_arming_flag = false;  
  }
  else if (!is_arming_flag){
      Serial.println("ARM");
      is_arming_flag = true;
  }
  return true;
}

void setup_test_pwm(){
  test_servo.attach(TEST_PWM);
}

void send_test_pwm(){
  test_servo.writeMicroseconds(500);
  delay(30);
}



void setup() {
  Serial.begin(9600);    
  setup_rx();
  setup_test_pwm();
}

void loop() {
  // put your main code here, to run repeatedly:
  send_test_pwm();
  is_arming();
}
