#include <Pixy2.h>

int in1 = 2;
int pwm1 = 3;
int in3= 4;
int pwm2 = 5;

Pixy2 pixy;
int state = 0;

void setup()
{
  Serial.begin(115200);
  Serial.print("Starting...\n");
  pinMode(in1, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(pwm2, OUTPUT);
  pinMode(pwm1, OUTPUT);
  pixy.init();
  pixy.setLamp(1,1);
}

void loop()
{
  int i;
  pixy.ccc.getBlocks();


  // If there are detect blocks, print them!
  if (pixy.ccc.numBlocks)
  {
    for (i=0; i<pixy.ccc.numBlocks; i++)
    {
      if(pixy.ccc.blocks[i].m_height<18)
      {
        state = 0;
        break;
        }
      else{
          int x = pixy.ccc.blocks[i].m_x;
          Serial.print("X: ");
          Serial.println(x);
        if(x < 140)
          state = 2;
        else if(x>=140 && x<180)
          state = 1;
        else if(x>=180)
          state = 3;
//        else
//          state = 0;
      }
    }
  }

  Serial.print("State: ");
  Serial.println(state);
  moveMotor(state);
}

void moveMotor(int state){

  switch(state){
    //STOP
    case 0:
      digitalWrite(in1,HIGH);
      digitalWrite(in3,HIGH);
      analogWrite(pwm1,0);
      analogWrite(pwm2,0);
      delay(30);
      break;
    //FORWARD
    case 1:
      digitalWrite(in1,HIGH);
      digitalWrite(in3,HIGH);
      analogWrite(pwm1,100);
      analogWrite(pwm2,100);
      delay(30);
      break;
    // LEFT
    case 3:
      digitalWrite(in1,HIGH);
      digitalWrite(in3,HIGH);
      analogWrite(pwm1,50);
      analogWrite(pwm2,100);
      delay(30);
      break;
    // RIGHT
    case 2:
      digitalWrite(in1,HIGH);
      digitalWrite(in3,HIGH);
      analogWrite(pwm1,100);
      analogWrite(pwm2,50);
      delay(30);
      break;
    default: break;
}}
