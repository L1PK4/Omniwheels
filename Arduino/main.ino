#include <math.h>
#define lIN1 2
#define lIN2 3
#define lIN3 4
#define lIN4 5

#define rIN1 6
#define rIN2 7
#define rIN3 8
#define rIN4 9


struct Vector
{
  int x,y;
  Vector(int x_ = 0, int y_ = 0) : x(x_), y(y_) {
    }

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
    return 0.5 * (x + y);
  }
  int countpwr_y() // Вектора левой направленности
  {
    return 0.5 * (-x + y);
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
  Serial.begin(115200);
}


void setwheelspeed(int wheel, int speed)
{

  switch (wheel)
  {
  case 0:
    analogWrite(rIN1,(speed > 0)?speed:0);
    analogWrite(rIN2,(speed > 0)?0:-speed);
    break;
  case 1:
    analogWrite(lIN1,(speed > 0)?speed:0);
    analogWrite(lIN2,(speed > 0)?0:-speed);
  case 2:
    analogWrite(rIN3,(speed > 0)?speed:0);
    analogWrite(rIN4,(speed > 0)?0:-speed);
  case 3:
    analogWrite(lIN3,(speed > 0)?speed:0);
    analogWrite(lIN4,(speed > 0)?0:-speed);
  default:
    break;
  }
}

void start_moving(Vector vec)
{
  setwheelspeed(0, vec.countpwr_x());
  setwheelspeed(1, vec.countpwr_x());
  setwheelspeed(2, vec.countpwr_y());
  setwheelspeed(3, vec.countpwr_y());
}

void rotate(bool dir)
{
    setwheelspeed(0,100 * (dir?1:-1));
    setwheelspeed(1,100 * (!dir?1:-1));
    setwheelspeed(2,100 * (!dir?1:-1));
    setwheelspeed(3,100 * (dir?1:-1));
}
Vector vec = new Vector();
String command, x[2];

void loop() {
  if (Serial.available())
  {
    command = Serial.readStringUntil('\n');
    if(command[0] == 'L')
    {
      for(int i = 2, j = 0; i < command.length(); i++ )
      {
        if (command[i] == ' ') j = 1;
        else x[j] += command[i];
      }
      vec.set_coordinates(x[0].toInt(),x[1].toInt());
      start_moving(vec);
    }
    else if (command[0] == 'R')
    {
      rotate(command[2]);
    }
    
  }
}