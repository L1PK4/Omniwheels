#include <math.h>
#define lIN1 12
#define lIN2 13
#define lIN3 10
#define lIN4 11

#define rIN1 4
#define rIN2 5
#define rIN3 6
#define rIN4 7


struct Vector
{
  int x,y;
  Vector(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}

  void set_coordinates(int x_ = 0, int y_ = 0){ 
    x = x_; y = y_; 
    }
  
  float countangle() {
    return atan(y/x); 
  }
  int countlength() {
    return sqrt( x * x + y * y);
  }
  int countpwr_x() // Вектора правой направленности
  {
    return 255 * (-x - y);
  }
  int countpwr_y() // Вектора левой направленности
  {
    return 255 * (x - y);
  }
};


void setup() {
  pinMode(lIN1, OUTPUT);
  pinMode(lIN2, OUTPUT);
  pinMode(lIN3, OUTPUT);
  pinMode(lIN4, OUTPUT);
  pinMode(rIN1, OUTPUT);
  pinMode(rIN2, OUTPUT);
  pinMode(rIN3, OUTPUT);
  pinMode(rIN4, OUTPUT);
  Serial.begin(9600);
}


void setwheelspeed(int wheel, int speed)
{
  switch (wheel)
  {
  case 0:
    analogWrite(rIN1,(speed > 0)?speed:0);
    analogWrite(rIN2,(speed > 0)?0:abs(speed));
    break;
  case 1:
    analogWrite(rIN4,(speed > 0)?speed:0);
    analogWrite(rIN3,(speed > 0)?0:abs(speed));
    break;
  case 2:
    analogWrite(lIN1,(speed > 0)?speed:0);
    analogWrite(lIN2,(speed > 0)?0:abs(speed));
    break;
  case 3:
    analogWrite(lIN4,(speed > 0)?speed:0);
    analogWrite(lIN3,(speed > 0)?0:abs(speed));
    break;
  }
}

void start_moving(Vector vec)
{
  setwheelspeed(0, vec.countpwr_x());
  setwheelspeed(1, vec.countpwr_y());
  setwheelspeed(2, vec.countpwr_y());
  setwheelspeed(3, vec.countpwr_x());
}

void rotate(bool dir)
{
    setwheelspeed(0,200 * (dir?1:-1));
    setwheelspeed(1,200 * (!dir?1:-1));
    setwheelspeed(2,200 * (dir?1:-1));
    setwheelspeed(3,200 * (!dir?1:-1));
}

Vector vec;
String command, x[2];
int i;

void loop() {
  if (Serial.available())
  {
    command = Serial.readStringUntil('\n');
    if(command[0] == 'L')
    {
      for(i = 2;command[i] != ' ';i++)x[0] += command[i];
      for(;i < command.length();i++)x[1] += command[i];
      vec.set_coordinates(x[0].toInt(), x[1].toInt());
      start_moving(vec);
    }
    else if (command[0] == 'R')
    {
      rotate(String(command[2]).toInt());
    } 
  }
}
