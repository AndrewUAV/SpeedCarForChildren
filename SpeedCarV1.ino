#include <Wire.h>
#include <Servo.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define THROTTLE_SERVO 9 
#define YAW_SERVO 10

#define THROTTLE_MIN_PWM 1000
#define THROTTLE_TRIM_PWM 1500
#define THROTTLE_MAX_PWM 2000

#define YAW_MIN_PWM 1000
#define YAW_TRIM_PWM 1500
#define YAW_MAX_PWM 2000

#define THROTTLE_RX_MIN_PWM 1000
#define THROTTLE_RX_MAX_PWM 2000
#define YAW_RX_MIN_PWM 1000
#define YAW_RX_MAX_PWM 2000

#define DISPLAY_SCREEN_WIDTH 128
#define DISPLAY_SCREEN_HEIGHT 64
#define DISPLAY_ADDRESS 0x3C
#define DISPLAY_TEXT_SIZE 2
#define DISPLAY_COLOR SSD1306_WHITE
#define DISPLAY_CURSOR_X 0
#define DISPLAY_CURSOR_Y 0

Servo throttle_servo;
Servo yaw_servo;

Adafruit_SSD1306 display(DISPLAY_SCREEN_WIDTH, DISPLAY_SCREEN_HEIGHT, &Wire, -1);

void setup_out_servos(){
  throttle_servo.attach(THROTTLE_SERVO);
  yaw_servo.attach(YAW_SERVO);
  delay(500);
  throttle_servo.writeMicroseconds(THROTTLE_MIN_PWM);
  yaw_servo.writeMicroseconds(YAW_TRIM_PWM);
  delay(1000);
}

int scale_throttle_servo(int input){
  int output = map(input, THROTTLE_RX_MIN_PWM, THROTTLE_RX_MAX_PWM,
  THROTTLE_MIN_PWM, THROTTLE_MAX_PWM);
  if (output < THROTTLE_MIN_PWM) output = THROTTLE_MIN_PWM;
  if (output > THROTTLE_MAX_PWM) output = THROTTLE_MAX_PWM;
  return output;
}

int scale_yaw_servo(int input){
  int output = map(input, YAW_RX_MIN_PWM, YAW_RX_MAX_PWM,
  YAW_MIN_PWM, YAW_MAX_PWM);
  if (output < YAW_MIN_PWM) output = YAW_MIN_PWM;
  if (output > YAW_MAX_PWM) output = YAW_MAX_PWM;
  return output;
}

void setup_random(){
  randomSeed(analogRead(A0));
}

int generate_random_pwm(){
  return random(1000, 2001);
}

void throttle_control(){
  throttle_servo.writeMicroseconds(scale_throttle_servo(generate_random_pwm()));
}

void yaw_control(){
  yaw_servo.writeMicroseconds(scale_yaw_servo(generate_random_pwm()));
}

void setup_display(){
  display.begin(SSD1306_SWITCHCAPVCC, DISPLAY_ADDRESS); 
  display.clearDisplay();
  display.setTextSize(DISPLAY_TEXT_SIZE);
  display.setTextColor(DISPLAY_COLOR);
  display.setCursor(DISPLAY_CURSOR_X, DISPLAY_CURSOR_Y);
  display.println("START");
  display.display();
}


void update_display_text(String text){
  display.clearDisplay();
  display.println(text);
  display.display();
}


void setup() {
  setup_random();
  setup_out_servos();
  setup_display();
}

void loop() {
  throttle_control();
  yaw_control();
  delay(200);
}
