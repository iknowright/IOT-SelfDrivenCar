#include <LRemote.h>

#define FRONT_T 10
#define FRONT_E 11
#define RIGHT_T 6
#define RIGHT_E 7
#define LEFT_T 8
#define LEFT_E 9

#define LEFT_W1 16
#define LEFT_W2 17
#define RIGHT_W1 14
#define RIGHT_W2 15

#define MOTORL 4
//#define MOTORR 5

LRemoteButton button_forward,button_left,button_right,button_backward;
//LRemoteSlider slider;
LRemoteLabel label;
//LRemoteSwitch switchButton;

void forward(int n)
{
  digitalWrite(LEFT_W1, LOW);
  digitalWrite(LEFT_W2, HIGH);
  digitalWrite(RIGHT_W1, LOW);
  digitalWrite(RIGHT_W2, HIGH);
  delay(n);
}
void left(int n)
{
  digitalWrite(LEFT_W1, LOW);
  digitalWrite(LEFT_W2, LOW);
  digitalWrite(RIGHT_W1, LOW);
  digitalWrite(RIGHT_W2, HIGH);
  delay(n);
}
void right(int n)
{
  digitalWrite(LEFT_W1, LOW);
  digitalWrite(LEFT_W2, HIGH);
  digitalWrite(RIGHT_W1, LOW);
  digitalWrite(RIGHT_W2, LOW);
  delay(n);
}
void backward(int n)
{
  digitalWrite(LEFT_W1, HIGH);
  digitalWrite(LEFT_W2, LOW);
  digitalWrite(RIGHT_W1, HIGH);
  digitalWrite(RIGHT_W2, LOW);
  delay(n);
}
void hold(int n)
{
  digitalWrite(LEFT_W2, LOW);
  digitalWrite(LEFT_W1, LOW);
  digitalWrite(RIGHT_W2, LOW);
  digitalWrite(RIGHT_W1, LOW);
  delay(n);
}

void setup() {

  pinMode(LEFT_W1, OUTPUT);
  pinMode(LEFT_W2, OUTPUT);
  pinMode(RIGHT_W1, OUTPUT);
  pinMode(RIGHT_W2, OUTPUT);
  analogWrite(MOTORL, 195);//每一個馬達真實轉數不一
  //analogWrite(MOTORR, 255);

  /*****************************************************/
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  Serial.println("Start configuring remote");
  // Setup the Remote Control's UI canvas
  LRemote.setName("LinkIt 7697");
  LRemote.setOrientation(RC_PORTRAIT);
  LRemote.setGrid(3, 5);

  // Add a forward button
  button_forward.setText("Forward");
  button_forward.setPos(1, 1);
  button_forward.setSize(1, 1);
  button_forward.setColor(RC_PINK);
  LRemote.addControl(button_forward);

  button_backward.setText("Backward");
  button_backward.setPos(1, 3);
  button_backward.setSize(1, 1);
  button_backward.setColor(RC_PINK);
  LRemote.addControl(button_backward);

  button_left.setText("LEFT");
  button_left.setPos(0, 2);
  button_left.setSize(1, 1);
  button_left.setColor(RC_PINK);
  LRemote.addControl(button_left);

  button_right.setText("RIGHT");
  button_right.setPos(2, 2);
  button_right.setSize(1, 1);
  button_right.setColor(RC_PINK);
  LRemote.addControl(button_right);

  // Add a simple text label
  label.setText("Car Contoller");
  label.setPos(0, 0);
  label.setSize(3, 1);
  label.setColor(RC_GREY);
  LRemote.addControl(label);

  // Start broadcasting our remote contoller
  // This method implicitly initialized underlying BLE subsystem
  // to create a BLE peripheral, and then start advertisement on it.
  LRemote.begin();
  Serial.println("begin() returned");
}

void loop() {

  // check if we are connect by some BLE central device, e.g. an mobile app
  if(!LRemote.connected()) {
    Serial.println("waiting for connection");
    delay(1000);
  } else {
    delay(100);
  }
  
  // Process the incoming BLE write request
  // and translate them to control events
  LRemote.process();

  // Now we poll each control's status
  
  if(button_forward.getValue()){
    forward(0);
  }
  else if(button_backward.getValue()){
    backward(0);
  }
  else if(button_left.getValue()){
    left(0);
  }
  else if(button_right.getValue()){
    right(0);
  }
  else{
    hold(0);
  }

}