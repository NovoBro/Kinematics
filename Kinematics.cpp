// Equations:
// v = vi + a * t
// x = ((v + vi) / 2 ) * t
// x = vi * t + a * t * t / 2
// v * v = vi * vi + 2 * a * x
// ymax = (vi * sin(angle)) * (vi * sin(angle)) / 2 / ay
// t = 2 * vi * sin(angle) / ay
// xFinal = vi * vi * sin( 2 * angle ) / ay

// To Do:
// Replace repetitive code with loops
// Margin of Error and Check

#include <string>
#include <iostream>
#include <cmath>
#include <cfloat>
#include <cstdlib>
#include <stdio.h>
using namespace std;

bool is_number(const std::string& s);

double solve_time1(double velocity, double velocityInitial, double acceleration); //Uses v = vi + a * t

double solve_time2(double pos, double velocity, double velocityInitial); //Uses x = ((v + vi) / 2 ) * t

double solve_pos1(double velocity, double velocityInitial, double time); //Uses x = ((v + vi) / 2 ) * t

double solve_pos2(double velocityInitial, double time, double acceleration); //Uses x = vi * t + a * t * t / 2

double solve_velocity(double velocityXDirection, double velocityYDirection); //Uses Pythagorean Theorem

double solve_velocityInitial(double velocityInitialXDirection, double velocityInitialYDirection); //Uses Pythagorean Theorem

double solve_acceleration(double accelerationXDirection, double accelerationYDirection); //Uses Pythagorean Theorem

double solve_velocityDirection1(double velocityInitial, double acceleration, double time); //Uses v = vi + a * t

double solve_velocityDirection2(double velocityInitial, double acceleration, double pos); //Uses v * v = vi * vi + 2 * a * x

double solve_velocityDirection3(double pos, double velocityInitial, double time); //Uses x = ((v + vi) / 2 ) * t

double solve_velocityInitialDirection1(double velocity, double acceleration, double time); //Uses v = vi + a * t

double solve_velocityInitialDirection2(double velocity, double acceleration, double pos); //Uses v * v = vi * vi + 2 * a * x

double solve_velocityInitialDirection3(double pos, double velocity, double time); //Uses x = ((v + vi) / 2 ) * t

double solve_velocityInitialDirection4(double velocityInitial, double velocityInitialOtherDirection); //Uses Pythagorean Theorem

double solve_velocityInitialXDirection(double velocity, double angle); //Uses v = cos(angle)x

double solve_velocityInitialYDirection(double velocity, double angle); //Uses v = cos(angle)y

double solve_accelerationDirection1(double velocity, double velocityInitial, double time); //Uses v = vi + a * t

double solve_accelerationDirection2(double pos, double velocityInitial, double time); //Uses x = vi * t + a * t * t / 2

double solve_accelerationDirection3(double velocity, double velocityInitial, double pos); //Uses v * v = vi * vi + 2 * a * x

double solve_accelerationDirection4(double acceleration, double accelerationOtherDirection); //Uses Pythagorean Theorem

double solve_accelerationXDirection1(double acceleration, double angle); //Uses v * cos(angle) = x

double solve_accelerationYDirection1(double yMax, double velocityInitial, double angle); // ymax = (vi * sin(angle)) * (vi * sin(angle)) / 2 / ay

double solve_accelerationYDirection2(double velocityInitial, double angle, double time); // t = 2 * vi * sin(angle) / ay

double solve_accelerationYDirection3(double velocityInitial, double angle, double xFinal); // xFinal = vi * vi * sin( 2 * angle ) / ay

double solve_accelerationYDirection4(double acceleration, double angle); //Uses v * sin(angle) = y

double solve_finalTime1(double xFinal, double velocityXDirection, double velocityInitialXDirection); //Uses x = ((v + vi) / 2 ) * t

double solve_xFinal1(double velocityInitial, double angle, double accelerationYDirection); // xFinal = vi * vi * sin( 2 * angle ) / ay

double solve_xFinal2(double velocityXDirection, double velocityInitialXDirection, double timeFinal); //Uses x = ((v + vi) / 2 ) * t

double solve_yMaxTime1(double yMax, double velocityYDirection, double velocityInitialYDirection); //Uses x = ((v + vi) / 2 ) * t

double solve_yMax1(double velocityInitialYDirection, double angle, double accelerationYDirection); //Uses ymax = (vi * sin(angle)) * (vi * sin(angle)) / 2 / ay

double solve_yMax2(double velocityYDirection, double velocityInitialYDirection, double accelerationYDirection); //Uses v * v = vi * vi + 2 * a * x

double solve_yMax3(double velocityYDirection, double velocityInitialYDirection, double yMaxTime); //Uses x = ((v + vi) / 2 ) * t

double solve_yInitial1(double velocityYDirection, double velocityInitialYDirection, double time); //Uses x = ((v + vi) / 2 ) * t

double solve_yInitial2(double velocityInitialYDirection, double time, double accelerationYDirection); //Uses x = vi * t + a * t * t / 2

double solve_angle1(double time, double accelerationYDirection, double velocityInitial); //Uses t = 2 * vi * sin(angle) / ay

double solve_angle2(double xFinal, double accelerationYDirection, double velocityInitial); //Uses xFinal = vi * vi * sin( 2 * angle ) / ay

double solve_angle3(double velocityInitialXDirection, double velocityInitial); //Uses trig properties

double solve_angle4(double velocityInitialYDirection, double velocityInitial); //Uses trig properties



int main(){
  bool given[16]; //keeps track of which variables are user-generated
  double xPos; //(distance)
  double yPos; //(height)
  double yInitial; //(initial height)
  double velocity;
  double velocityXDirection;
  double velocityYDirection;
  double velocityInitial; //(velocity at t = 0)
  double velocityInitialXDirection;
  double velocityInitialYDirection;
  double acceleration;
  double accelerationXDirection; //(acceleration in the x direction)
  double accelerationYDirection; //(acceleration in the y direction)
  double time;
  double timeFinal = DBL_MAX; //The time when yPos == 0
  double yMaxTime = DBL_MAX; //The time when yPos == yMax
  double yMax = DBL_MAX; //(maximum height reached)
  double xFinal = DBL_MAX; //(final distance/range)
  double angle; //(launch angle)
  string ifUnknown = " If unknown, enter \"?\" or \"n\".";
  string temp;
  double temp2;
  bool hideCurrent = false;
  bool newInfo = true;

  //Initialize given
  for(int i = 0; i < 16; i++) given[i] = false;

  printf( "%s%s", "\33[", "33m" ); //sets color to yellow
  cout << "Enter the time." << ifUnknown << endl;
  printf( "%s%s", "\33[", "m" ); //sets color to white
  cin >> temp;
  if(is_number(temp))
  {
    time = stod(temp);
    given[0] = true;
  }
  else time = DBL_MAX;

  printf( "%s%s", "\33[", "33m" );
  cout << "Enter the x position." << ifUnknown << endl;
  printf( "%s%s", "\33[", "m" );
  cin >> temp;
  if(is_number(temp))
  {
    xPos = stod(temp);
    given[1] = true;
  }
  else xPos = DBL_MAX;

  printf( "%s%s", "\33[", "33m" );
  cout << "Enter the y position." << ifUnknown << endl;
  printf( "%s%s", "\33[", "m" );
  cin >> temp;
  if(is_number(temp))
  {
    yPos = stod(temp);
    given[2] = true;
  }
  else yPos = DBL_MAX;

  printf( "%s%s", "\33[", "33m" );
  cout << "Enter the velocity." << ifUnknown << endl;
  printf( "%s%s", "\33[", "m" );
  cin >> temp;
  if(is_number(temp))
  {
    velocity = stod(temp);
    given[3] = true;
  }
  else velocity = DBL_MAX;

  printf( "%s%s", "\33[", "33m" );
  cout << "Enter the velocity in the x direction." << ifUnknown << endl;
  printf( "%s%s", "\33[", "m" );
  cin >> temp;
  if(is_number(temp))
  {
    velocityXDirection = stod(temp);
    given[4] = true;
  }
  else velocityXDirection = DBL_MAX;

  printf( "%s%s", "\33[", "33m" );
  cout << "Enter the velocity in the y direction." << ifUnknown << endl;
  printf( "%s%s", "\33[", "m" );
  cin >> temp;
  if(is_number(temp))
  {
    velocityYDirection = stod(temp);
    given[5] = true;
  }
  else velocityYDirection = DBL_MAX;

  printf( "%s%s", "\33[", "33m" );
  cout << "Enter the initial velocity." << ifUnknown << endl;
  printf( "%s%s", "\33[", "m" );
  cin >> temp;
  if(is_number(temp))
  {
    velocityInitial = stod(temp);
    given[6] = true;
  }
  else velocityInitial = DBL_MAX;

  printf( "%s%s", "\33[", "33m" );
  cout << "Enter the initial velocity in the x direction." << ifUnknown << endl;
  printf( "%s%s", "\33[", "m" );
  cin >> temp;
  if(is_number(temp))
  {
    velocityInitialXDirection = stod(temp);
    given[7] = true;
  }
  else velocityInitialXDirection = DBL_MAX;

  printf( "%s%s", "\33[", "33m" );
  cout << "Enter the initial velocity in the y direction." << ifUnknown << endl;
  printf( "%s%s", "\33[", "m" );
  cin >> temp;
  if(is_number(temp))
  {
    velocityInitialYDirection = stod(temp);
    given[8] = true;
  }
  else velocityInitialYDirection = DBL_MAX;

  printf( "%s%s", "\33[", "33m" );
  cout << "Enter the acceleration." << ifUnknown << endl;
  printf( "%s%s", "\33[", "m" );
  cin >> temp;
  if(is_number(temp))
  {
    acceleration = stod(temp);
    given[9] = true;
  }
  else acceleration = DBL_MAX;

  printf( "%s%s", "\33[", "33m" );
  cout << "Enter the acceleration in the x direction." << ifUnknown << endl;
  printf( "%s%s", "\33[", "m" );
  cin >> temp;
  if(is_number(temp))
  {
    accelerationXDirection = stod(temp);
    given[10] = true;
  }
  else accelerationXDirection = DBL_MAX;

  printf( "%s%s", "\33[", "33m" );
  cout << "Enter the acceleration in the y direction. (must be negative)" << ifUnknown << endl;
  printf( "%s%s", "\33[", "m" );
  cin >> temp;
  if(is_number(temp))
  {
    accelerationYDirection = -abs(stod(temp));
    given[11] = true;
  }
  else accelerationYDirection = DBL_MAX;

  printf( "%s%s", "\33[", "33m" );
  cout << "Enter the total time. " << ifUnknown << endl;
  printf( "%s%s", "\33[", "m" );
  cin >> temp;
  if(is_number(temp))
  {
    timeFinal = stod(temp);
    given[12] = true;
  }
  else timeFinal = DBL_MAX;

  printf( "%s%s", "\33[", "33m" );
  cout << "Enter the range. (displacement) " << ifUnknown << endl;
  printf( "%s%s", "\33[", "m" );
  cin >> temp;
  if(is_number(temp))
  {
    xFinal = stod(temp);
    given[13] = true;
  }
  else xFinal = DBL_MAX;

  printf( "%s%s", "\33[", "33m" );
  cout << "Enter the initial height." << ifUnknown << endl;
  printf( "%s%s", "\33[", "m" );
  cin >> temp;
  if(is_number(temp))
  {
    yInitial = stod(temp);
    given[14] = true;
  }
  else yInitial = DBL_MAX;

  printf( "%s%s", "\33[", "33m" );
  cout << "Enter the launch angle. (in radians) " << ifUnknown << endl;
  printf( "%s%s", "\33[", "m" );
  cin >> temp;
  if(is_number(temp))
  {
    angle = stod(temp);
    given[15] = true;
  }
  else angle = DBL_MAX;

  //hide information about the current position if none is given
  if(time == DBL_MAX && xPos == DBL_MAX && yPos == DBL_MAX && velocity == DBL_MAX && velocityXDirection == DBL_MAX && velocityYDirection == DBL_MAX)
    hideCurrent = true;

  cout << endl;

  //------------------------------------------------------------------------------

  //This loop will attempt to solve for any unknown variables. If it finds any, it will loop again.
  int i = 0;
  while(newInfo == true){
    newInfo = false;
    i++;
    cout << "Loop #" << i << endl;

    //Solve for time if unknown
    if(time == DBL_MAX)
    {
      if(velocityXDirection != DBL_MAX && velocityInitialXDirection != DBL_MAX && accelerationXDirection != DBL_MAX && accelerationXDirection != 0)
      {
        time = solve_time1(velocityXDirection, velocityInitialXDirection, accelerationXDirection);
        newInfo = true;
        cout << "Solved for time" << endl;
      }
      else if(xPos != DBL_MAX && velocityXDirection != DBL_MAX && velocityInitialXDirection != DBL_MAX)
      {
        time = solve_time2(xPos, velocityXDirection, velocityInitialXDirection);
        newInfo = true;
        cout << "Solved for time" << endl;
      }
    }

    //Solve for xPos if unknown
    if(xPos == DBL_MAX)
    {
      if(velocityXDirection != DBL_MAX && velocityInitialXDirection != DBL_MAX && time != DBL_MAX)
      {
        xPos = solve_pos1(velocityXDirection, velocityInitialXDirection, time);
        newInfo = true;
        cout << "Solved for x" << endl;
      }
      else if(velocityInitial != DBL_MAX && time != DBL_MAX && accelerationXDirection != DBL_MAX)
      {
        xPos = solve_pos2(velocityInitialXDirection, time, accelerationXDirection);
        newInfo = true;
        cout << "Solved for x" << endl;
      }
    }

    //Solve for yPos if unknown
    if(yPos == DBL_MAX)
    {
      if(velocityYDirection != DBL_MAX && velocityInitialYDirection != DBL_MAX && time != DBL_MAX)
      {
        yPos = solve_pos1(velocityYDirection, velocityInitialYDirection, time);
        newInfo = true;
        cout << "Solved for y" << endl;
      }
      else if(velocityInitialYDirection != DBL_MAX && time != DBL_MAX && accelerationYDirection != DBL_MAX)
      {
        yPos = solve_pos2(velocityInitialYDirection, time, accelerationYDirection);
        newInfo = true;
        cout << "Solved for y" << endl;
      }
    }

    //Solve for velocity if unknown
    if(velocity == DBL_MAX)
    {
      if(velocityXDirection != DBL_MAX && velocityYDirection != DBL_MAX)
      {
        velocity = solve_velocity(velocityXDirection, velocityYDirection);
        newInfo = true;
        cout << "Solved for velocity" << endl;
      }
    }

    //Solve for velocity in the x direction if unknown
    if(velocityXDirection== DBL_MAX)
    {
      if(velocityInitialXDirection != DBL_MAX && accelerationXDirection != DBL_MAX && time != DBL_MAX)
      {
        velocityXDirection = solve_velocityDirection1(velocityInitialXDirection, accelerationXDirection, time);
        newInfo = true;
        cout << "Solved for velocity in the x direction" << endl;
      }
      else if(velocityInitialXDirection != DBL_MAX && accelerationXDirection != DBL_MAX && xPos != DBL_MAX)
      {
        velocityXDirection = solve_velocityDirection2(velocityInitialXDirection, accelerationXDirection, xPos);
        newInfo = true;
        cout << "Solved for velocity in the x direction" << endl;
      }
      else if(xPos != DBL_MAX && velocityInitialXDirection != DBL_MAX && time != DBL_MAX)
      {
        velocityXDirection = solve_velocityDirection3(xPos, velocityInitialXDirection, time);
        newInfo = true;
        cout << "Solved for velocity in the x direction" << endl;
      }
    }

    //Solve for velocity in the y direction if unknown
    if(velocityYDirection == DBL_MAX)
    {
      if(velocityInitialYDirection != DBL_MAX && accelerationYDirection != DBL_MAX && time != DBL_MAX)
      {
        velocityYDirection = solve_velocityDirection1(velocityInitialYDirection, accelerationYDirection, time);
        newInfo = true;
        cout << "Solved for velocity in the y direction" << endl;
      }
      else if(velocityInitialYDirection != DBL_MAX && accelerationYDirection != DBL_MAX && yPos != DBL_MAX)
      {
        velocityYDirection = solve_velocityDirection2(velocityInitialYDirection, accelerationYDirection, yPos);
        newInfo = true;
        cout << "Solved for velocity in the y direction" << endl;
      }
      else if(yPos != DBL_MAX && velocityInitialYDirection != DBL_MAX && time != DBL_MAX)
      {
        velocityYDirection = solve_velocityDirection3(yPos, velocityInitialYDirection, time);
        newInfo = true;
        cout << "Solved for velocity in the y direction" << endl;
      }
    }

    //Solve for initial velocity if unknown
    if(velocityInitial == DBL_MAX)
    {
      if(velocityInitialXDirection != DBL_MAX && velocityInitialYDirection != DBL_MAX)
      {
        velocityInitial = solve_velocityInitial(velocityInitialXDirection, velocityInitialYDirection);
        newInfo = true;
        cout << "Solved for initial velocity" << endl;
      }
    }

    //Solve for initial velocity in the x direction if unknown
    if(velocityInitialXDirection == DBL_MAX)
    {
      if(velocityXDirection != DBL_MAX && accelerationXDirection != DBL_MAX && time != DBL_MAX)
      {
        velocityInitialXDirection = solve_velocityInitialDirection1(velocityXDirection, accelerationXDirection, time);
        newInfo = true;
        cout << "Solved for initial velocity in the x direction" << endl;
      }
      else if(velocityXDirection != DBL_MAX && accelerationXDirection != DBL_MAX && xPos != DBL_MAX)
      {
        velocityInitialXDirection = solve_velocityInitialDirection2(velocityXDirection, accelerationXDirection, xPos);
        newInfo = true;
        cout << "Solved for initial velocity in the x direction" << endl;
      }
      else if(xPos != DBL_MAX && velocityXDirection != DBL_MAX && time != DBL_MAX)
      {
        velocityInitialXDirection = solve_velocityInitialDirection3(xPos, velocityXDirection, time);
        newInfo = true;
        cout << "Solved for initial velocity in the x direction" << endl;
      }
      else if(velocityInitial != DBL_MAX && angle != DBL_MAX)
      {
        velocityInitialXDirection = solve_velocityInitialXDirection(velocityInitial, angle);
        newInfo = true;
        cout << "Solved for initial velocity in the x direction" << endl;
      }
      else if(velocityInitial != DBL_MAX && velocityInitialYDirection != DBL_MAX)
      {
        velocityInitialXDirection = solve_velocityInitialDirection4(velocityInitial, velocityInitialYDirection);
        newInfo = true;
        cout << "Solved for initial velocity in the x direction" << endl;
      }
    }

    //Solve for initial velocity in the y direction if unknown
    if(velocityInitialYDirection == DBL_MAX)
    {
      if(velocityYDirection != DBL_MAX && accelerationYDirection != DBL_MAX && time != DBL_MAX)
      {
        velocityInitialYDirection = solve_velocityInitialDirection1(velocityYDirection, accelerationYDirection, time);
        newInfo = true;
        cout << "Solved for initial velocity in the y direction" << endl;
      }
      else if(velocityYDirection != DBL_MAX && accelerationYDirection != DBL_MAX && yPos != DBL_MAX)
      {
        velocityInitialYDirection = solve_velocityInitialDirection2(velocityYDirection, accelerationYDirection, yPos);
        newInfo = true;
        cout << "Solved for initial velocity in the y direction" << endl;
      }
      else if(yPos != DBL_MAX && velocityYDirection != DBL_MAX && time != DBL_MAX)
      {
        velocityInitialYDirection = solve_velocityInitialDirection3(yPos, velocityYDirection, time);
        newInfo = true;
        cout << "Solved for initial velocity in the y direction" << endl;
      }
      else if(velocityInitial != DBL_MAX && angle != DBL_MAX)
      {
        velocityInitialYDirection = solve_velocityInitialYDirection(velocityInitial, angle);
        newInfo = true;
        cout << "Solved for initial velocity in the y direction" << endl;
      }
      else if(velocityInitial != DBL_MAX && velocityInitialXDirection != DBL_MAX)
      {
        velocityInitialYDirection = solve_velocityInitialDirection4(velocityInitial, velocityInitialXDirection);
        newInfo = true;
        cout << "Solved for initial velocity in the y direction" << endl;
      }
    }

    //Solve for acceleration if unknown
    if(acceleration == DBL_MAX)
    {
      if(accelerationXDirection != DBL_MAX && accelerationYDirection != DBL_MAX)
      {
        acceleration = solve_acceleration(accelerationXDirection, accelerationYDirection);
        newInfo = true;
        cout << "Solved for acceleration" << endl;
      }
    }

    //Solve for acceleration in the x direction if unknown
    if(accelerationXDirection == DBL_MAX)
    {
      if(velocityXDirection != DBL_MAX && velocityInitialXDirection != DBL_MAX && time != DBL_MAX)
      {
        accelerationXDirection = solve_accelerationDirection1(velocityXDirection, velocityInitialXDirection, time);
        newInfo = true;
        cout << "Solved for acceleration in the x direction" << endl;
      }
      else if(xPos != DBL_MAX && velocityInitialXDirection != DBL_MAX && time != DBL_MAX)
      {
        accelerationXDirection = solve_accelerationDirection2(xPos, velocityInitialXDirection, time);
        newInfo = true;
        cout << "Solved for acceleration in the x direction" << endl;
      }
      else if(velocityXDirection != DBL_MAX && velocityInitialXDirection != DBL_MAX && xPos != DBL_MAX)
      {
        accelerationXDirection = solve_accelerationDirection3(velocityXDirection, velocityInitialXDirection, xPos);
        newInfo = true;
        cout << "Solved for acceleration in the x direction" << endl;
      }
      else if(acceleration != DBL_MAX && accelerationYDirection != DBL_MAX)
      {
        accelerationXDirection = solve_accelerationDirection4(acceleration, accelerationYDirection);
        newInfo = true;
        cout << "Solved for acceleration in the x direction" << endl;
      }
      else if(acceleration != DBL_MAX && angle != DBL_MAX)
      {
        accelerationXDirection = solve_accelerationXDirection1(acceleration, angle);
        newInfo = true;
        cout << "Solved for acceleration in the x direction" << endl;
      }
    }

    //Solve for acceleration in the y direction if unknown
    if(accelerationYDirection == DBL_MAX)
    {
      if(velocityYDirection != DBL_MAX && velocityInitialYDirection != DBL_MAX && time != DBL_MAX)
      {
        accelerationYDirection = solve_accelerationDirection1(velocityYDirection, velocityInitialYDirection, time);
        newInfo = true;
        cout << "Solved for acceleration in the y direction" << endl;
      }
      else if(yPos != DBL_MAX && velocityInitialYDirection != DBL_MAX && time != DBL_MAX)
      {
        accelerationYDirection = solve_accelerationDirection2(yPos, velocityInitialYDirection, time);
        newInfo = true;
        cout << "Solved for acceleration in the y direction" << endl;
      }
      else if(velocityYDirection != DBL_MAX && velocityInitialYDirection != DBL_MAX && yPos != DBL_MAX)
      {
        accelerationYDirection = solve_accelerationDirection3(velocityYDirection, velocityInitialYDirection, yPos);
        newInfo = true;
        cout << "Solved for acceleration in the y direction" << endl;
      }
      else if(acceleration != DBL_MAX && accelerationXDirection != DBL_MAX)
      {
        accelerationYDirection = solve_accelerationDirection4(acceleration, accelerationXDirection);
        newInfo = true;
        cout << "Solved for acceleration in the y direction" << endl;
      }
      else if(yMax != DBL_MAX && velocityInitialYDirection != DBL_MAX && angle != DBL_MAX)
      {
        accelerationYDirection = solve_accelerationYDirection1(yMax, velocityInitialYDirection, angle);
        newInfo = true;
        cout << "Solved for acceleration in the y direction" << endl;
      }
      else if(velocityInitialYDirection != DBL_MAX && angle != DBL_MAX && time != DBL_MAX)
      {
        accelerationYDirection = solve_accelerationYDirection2(velocityInitialYDirection, angle, time);
        newInfo = true;
        cout << "Solved for acceleration in the y direction" << endl;
      }
      else if(velocityInitialYDirection != DBL_MAX && angle != DBL_MAX && xFinal != DBL_MAX)
      {
        accelerationYDirection = solve_accelerationYDirection3(velocityInitialYDirection, angle, xFinal);
        newInfo = true;
        cout << "Solved for acceleration in the y direction" << endl;
      }
      else if(acceleration != DBL_MAX && angle != DBL_MAX)
      {
        accelerationYDirection = solve_accelerationYDirection4(acceleration, angle);
        newInfo = true;
        cout << "Solved for acceleration in the y direction" << endl;
      }
    }

    //Solve for time when yPos == 0 if unknown
    if(timeFinal == DBL_MAX)
    {
      if(xFinal != DBL_MAX && velocityXDirection != DBL_MAX && velocityInitialXDirection != DBL_MAX)
      {
        timeFinal = solve_finalTime1(xFinal, velocityXDirection, velocityInitialXDirection);
        newInfo = true;
        cout << "Solved for total time" << endl;
      }
    }

    //Solve for range if unknown
    if(xFinal == DBL_MAX)
    {
      if(velocityInitial != DBL_MAX && angle != DBL_MAX && accelerationYDirection != DBL_MAX)
      {
        xFinal = solve_xFinal1(velocityInitial, angle, accelerationYDirection);
        newInfo = true;
        cout << "Solved for range" << endl;
      }
      else if(velocityXDirection != DBL_MAX && velocityInitialXDirection != DBL_MAX && timeFinal != DBL_MAX)
      {
        xFinal = solve_xFinal2(velocityXDirection, velocityInitialXDirection, timeFinal);
        newInfo = true;
        cout << "Solved for range" << endl;
      }
    }

    //Solve for time at maximum height if unknown
    if(yMaxTime == DBL_MAX)
    {
      if(yMax != DBL_MAX && velocityYDirection != DBL_MAX && velocityInitialYDirection != DBL_MAX)
      {
        yMaxTime = solve_yMaxTime1(yMax, velocityYDirection, velocityInitialYDirection);
        newInfo = true;
        cout << "Solved for time at maximum height" << endl;
      }
    }

    //Solve for maximum height if unknown
    if(yMax == DBL_MAX)
    {
      if(velocityInitialYDirection != DBL_MAX && angle != DBL_MAX && accelerationYDirection != DBL_MAX)
      {
        yMax = solve_yMax1(velocityInitialYDirection, angle, accelerationYDirection);
        newInfo = true;
        cout << "Solved for maximum height" << endl;
      }
      else if(velocityYDirection != DBL_MAX && velocityInitialYDirection != DBL_MAX && accelerationYDirection != DBL_MAX)
      {
        yMax = solve_yMax2(velocityYDirection, velocityInitialYDirection, accelerationYDirection);
        newInfo = true;
        cout << "Solved for maximum height" << endl;
      }
      else if(velocityYDirection != DBL_MAX && velocityInitialYDirection != DBL_MAX && yMaxTime != DBL_MAX)
      {
        yMax = solve_yMax3(velocityYDirection, velocityInitialYDirection, yMaxTime);
        newInfo = true;
        cout << "Solved for maximum height" << endl;
      }
    }

    //Solve for initial height if unknown
    if(yInitial == DBL_MAX)
    {
      if(velocityYDirection != DBL_MAX && velocityInitialYDirection != DBL_MAX && time != DBL_MAX)
      {
        yInitial = solve_yInitial1(velocityYDirection, velocityInitialYDirection, time);
        newInfo = true;
        cout << "Solved for initial height" << endl;
      }
      else if(velocityInitialYDirection != DBL_MAX && time != DBL_MAX && accelerationYDirection != DBL_MAX)
      {
        yInitial = solve_yInitial2(velocityInitialYDirection, time, accelerationYDirection);
        newInfo = true;
        cout << "Solved for initial height" << endl;
      }
    }

    //Solve for launch angle if unknown
    if(angle == DBL_MAX)
    {
      if(time != DBL_MAX && accelerationYDirection != DBL_MAX && velocityInitial != DBL_MAX)
      {
        angle = solve_angle1(time, accelerationYDirection, velocityInitial);
        newInfo = true;
        cout << "Solved for launch angle" << endl;
      }
      else if(xFinal != DBL_MAX && accelerationYDirection != DBL_MAX && velocityInitial != DBL_MAX)
      {
        angle = solve_angle2(xFinal, accelerationYDirection, velocityInitial);
        newInfo = true;
        cout << "Solved for launch angle" << endl;
      }
      else if(velocityInitialXDirection != DBL_MAX && velocityInitial != DBL_MAX)
      {
        angle = solve_angle3(velocityInitialXDirection, velocityInitial);
        newInfo = true;
        cout << "Solved for launch angle" << endl;
      }
      else if(velocityInitialYDirection != DBL_MAX && velocityInitial != DBL_MAX)
      {
        angle = solve_angle4(velocityInitialYDirection, velocityInitial);
        newInfo = true;
        cout << "Solved for launch angle" << endl;
      }
    }
  }

  //If the vetex of the parabola is out of range, the highest point is the final point
  if(yMaxTime != DBL_MAX && yMaxTime > timeFinal) yMaxTime = timeFinal;

  //------------------------------------------------------------------------------

  cout << endl;

  if(hideCurrent == false){
    if (time == DBL_MAX) cout << "Time: ?" << endl;
    else
    {
      cout << "Time: ";
      if(!given[0]) printf( "%s%s", "\33[", "32m" );
      cout << time << endl;
    }
    printf( "%s%s", "\33[", "m" );

    if (xPos == DBL_MAX) cout << "x: ?" << endl;
    else
    {
      cout << "x: ";
      if(!given[1]) printf( "%s%s", "\33[", "32m" );
      cout << xPos << endl;
    }
    printf( "%s%s", "\33[", "m" );

    if (yPos == DBL_MAX) cout << "y: ?" << endl;
    else
    {
      cout << "y: ";
      if(!given[2]) printf( "%s%s", "\33[", "32m" );
      cout << yPos << endl;
    }
    printf( "%s%s", "\33[", "m" );

    if (velocity == DBL_MAX) cout << "Velocity: ?" << endl;
    else
    {
      cout << "Velocity: ";
      if(!given[3]) printf( "%s%s", "\33[", "32m" );
      cout << velocity << endl;
    }
    printf( "%s%s", "\33[", "m" );

    if (velocityXDirection == DBL_MAX) cout << "Velocity in the x Direction: ?" << endl;
    else
    {
      cout << "Velocity in the x Direction: ";
      if(!given[4]) printf( "%s%s", "\33[", "32m" );
      cout << velocityXDirection << endl;
    }
    printf( "%s%s", "\33[", "m" );

    if (velocityYDirection == DBL_MAX) cout << "Velocity in the y Direction: ?" << endl;
    else
    {
      cout << "Velocity in the y Direction: ";
      if(!given[5]) printf( "%s%s", "\33[", "32m" );
      cout << velocityYDirection << endl;
    }
    printf( "%s%s", "\33[", "m" );
  }

  if (velocityInitial == DBL_MAX) cout << "Initial Velocity: ?" << endl;
  else
  {
    cout << "Initial Velocity: ";
    if(!given[6]) printf( "%s%s", "\33[", "32m" );
    cout << velocityInitial << endl;
  }
  printf( "%s%s", "\33[", "m" );

  if (velocityInitialXDirection == DBL_MAX) cout << "Initial Velocity in the x Direction: ?" << endl;
  else
  {
    cout << "Initial Velocity in the x Direction: ";
    if(!given[7]) printf( "%s%s", "\33[", "32m" );
    cout << velocityInitialXDirection << endl;
  }
  printf( "%s%s", "\33[", "m" );

  if (velocityInitialYDirection == DBL_MAX) cout << "Initial Velocity in the y Direction: ?" << endl;
  else
  {
    cout << "Initial Velocity in the y Direction: ";
    if(!given[8]) printf( "%s%s", "\33[", "32m" );
    cout << velocityInitialYDirection << endl;
  }
  printf( "%s%s", "\33[", "m" );

  if (acceleration == DBL_MAX) cout << "Acceleration: ?" << endl;
  else
  {
    cout << "Acceleration: ";
    if(!given[9]) printf( "%s%s", "\33[", "32m" );
    cout << acceleration << endl;
  }
  printf( "%s%s", "\33[", "m" );

  if (accelerationXDirection == DBL_MAX) cout << "Acceleration in the x Direction: ?" << endl;
  else
  {
    cout << "Acceleration in the x Direction: ";
    if(!given[10]) printf( "%s%s", "\33[", "32m" );
    cout << accelerationXDirection << endl;
  }
  printf( "%s%s", "\33[", "m" );

  if (accelerationYDirection == DBL_MAX) cout << "Acceleration in the y Direction: ?" << endl;
  else
  {
    cout << "Acceleration in the y Direction: ";
    if(!given[11]) printf( "%s%s", "\33[", "32m" );
    cout << accelerationYDirection << endl;
  }
  printf( "%s%s", "\33[", "m" );

  if (timeFinal == DBL_MAX) cout << "Total Time: ?" << endl;
  else
  {
    cout << "Total Time: ";
    if(!given[12]) printf( "%s%s", "\33[", "32m" );
    cout << timeFinal << endl;
  }
  printf( "%s%s", "\33[", "m" );

  if (xFinal == DBL_MAX) cout << "Range: ?" << endl;
  else
  {
    cout << "Range: ";
    if(!given[13]) printf( "%s%s", "\33[", "32m" );
    cout << xFinal << endl;
  }
  printf( "%s%s", "\33[", "m" );

  if (yMax == DBL_MAX) cout << "Maximum Height: ?" << endl;
  else
  {
    cout << "Maximum Height: ";
    printf( "%s%s", "\33[", "32m" );
    cout << yMax << endl;
  }
  printf( "%s%s", "\33[", "m" );

  if (yMaxTime == DBL_MAX) cout << "Time at Maximum Height: ?" << endl;
  else
  {
    cout << "Time at Maximum Height: ";
    printf( "%s%s", "\33[", "32m" );
    cout << yMaxTime << endl;
  }
  printf( "%s%s", "\33[", "m" );

  if (yInitial == DBL_MAX) cout << "Initial Height: ?" << endl;
  else if (!given[14] || yInitial != 0)
  {
    cout << "Initial Height: ";
    if(!given[14]) printf( "%s%s", "\33[", "32m" );
    cout << yInitial << endl;
  }
  printf( "%s%s", "\33[", "m" );

  if (angle == DBL_MAX) cout << "Launch Angle: ?" << endl;
  else
  {
    cout << "Launch Angle: ";
    if(!given[15]) printf( "%s%s", "\33[", "32m" );
    cout << angle << endl;
  }
  printf( "%s%s", "\33[", "m" );

  return 1;
}

bool is_number(const string& s)
{
    char* end = nullptr;
    double val = strtod(s.c_str(), &end);
    return end != s.c_str() && *end == '\0' && val != HUGE_VAL;
}

double solve_time1(double velocity, double velocityInitial, double acceleration) //Uses v = vi + a * t
{
  return ((velocity - velocityInitial) / 2 * acceleration);
}

double solve_time2(double pos, double velocity, double velocityInitial) //Uses x = ((v + vi) / 2 ) * t
{
  return pos / ((velocity + velocityInitial) / 2);
}

double solve_pos1(double velocity, double velocityInitial, double time) //Uses x = ((v + vi) / 2 ) * t
{
  return ((velocity + velocityInitial) / 2 * time);
}

double solve_pos2(double velocityInitial, double time, double acceleration) //Uses x = vi * t + a * t * t / 2
{
  return velocityInitial * time + acceleration * pow(time, 2) / 2;
}

double solve_velocity(double velocityXDirection, double velocityYDirection)
{
  return sqrt(pow(velocityXDirection, 2) + pow(velocityYDirection, 2));
}

double solve_velocityInitial(double velocityInitialXDirection, double velocityInitialYDirection)
{
  return sqrt(pow(velocityInitialXDirection, 2) + pow(velocityInitialYDirection, 2));
}

double solve_acceleration(double accelerationXDirection, double accelerationYDirection)
{
  return sqrt(pow(accelerationXDirection, 2) + pow(accelerationYDirection, 2));
}

double solve_velocityDirection1(double velocityInitial, double acceleration, double time) //Uses v = vi + a * t
{
  return velocityInitial + acceleration * time;
}

double solve_velocityDirection2(double velocityInitial, double acceleration, double pos) //Uses v * v = vi * vi + 2 * a * x
{
  return sqrt(pow(velocityInitial, 2) + 2 * acceleration * pos);
}

double solve_velocityDirection3(double pos, double velocityInitial, double time) //Uses x = ((v + vi) / 2 ) * t
{
  return pos / time * 2 - velocityInitial;
}

double solve_velocityInitialDirection1(double velocity, double acceleration, double time) //Uses v = vi + a * t
{
  return - velocity + acceleration * time;
}

double solve_velocityInitialDirection2(double velocity, double acceleration, double pos) //Uses v * v = vi * vi + 2 * a * x
{
  return sqrt(- pow(velocity, 2) + 2 * acceleration * pos);
}

double solve_velocityInitialDirection3(double pos, double velocity, double time) //Uses x = ((v + vi) / 2 ) * t
{
  return pos / time * 2 - velocity;
}

double solve_velocityInitialDirection4(double velocityInitial, double velocityInitialOtherDirection) //Uses Pythagorean Theorem
{
  return sqrt(pow(velocityInitial, 2) - pow(velocityInitialOtherDirection, 2));
}

double solve_velocityInitialXDirection(double velocity, double angle) //Uses v = cos(angle)x
{
  return velocity / cos(angle);
}

double solve_velocityInitialYDirection(double velocity, double angle) //Uses v = cos(angle)y
{
  return velocity / sin(angle);
}

double solve_accelerationDirection1(double velocity, double velocityInitial, double time) //Uses v = vi + a * t
{
  return (velocity - velocityInitial) / time;
}

double solve_accelerationDirection2(double pos, double velocityInitial, double time) //Uses x = vi * t + a * t * t / 2
{
  return (pos - velocityInitial * time) / (pow(time, 2) / 2);
}

double solve_accelerationDirection3(double velocity, double velocityInitial, double pos) //Uses v * v = vi * vi + 2 * a * x
{
  return (pow(velocity, 2) - pow(velocityInitial, 2)) / (2 * pos);
}

double solve_accelerationDirection4(double acceleration, double accelerationOtherDirection) //Uses Pythagorean Theorem
{
  return sqrt(pow(acceleration, 2) - pow(accelerationOtherDirection, 2));
}

double solve_accelerationXDirection1(double acceleration, double angle) //Uses v * cos(angle) = x
{
  return acceleration * cos(angle);
}

double solve_accelerationYDirection1(double yMax, double velocityInitial, double angle) // ymax = (vi * sin(angle)) * (vi * sin(angle)) / 2 / ay
{
  return pow((velocityInitial * sin(angle)), 2) / (2 * yMax);
}

double solve_accelerationYDirection2(double velocityInitial, double angle, double time) // t = 2 * vi * sin(angle) / ay
{
  return (2 * velocityInitial * sin(angle)) / time;
}

double solve_accelerationYDirection3(double velocityInitial, double angle, double xFinal) // xFinal = vi * vi * sin( 2 * angle ) / ay
{
  return (pow(velocityInitial, 2) * sin(2 * angle)) / xFinal;
}

double solve_accelerationYDirection4(double acceleration, double angle) //Uses v * sin(angle) = y
{
  return acceleration * sin(angle);
}

double solve_finalTime1(double xFinal, double velocityXDirection, double velocityInitialXDirection) //Uses x = ((v + vi) / 2 ) * t
{
  return xFinal / ((velocityXDirection + velocityInitialXDirection) / 2);
}

double solve_xFinal1(double velocityInitial, double angle, double accelerationYDirection) // xFinal = vi * vi * sin( 2 * angle ) / ay
{
  return (pow(velocityInitial, 2) * sin(2 * angle)) / -accelerationYDirection;
}

double solve_xFinal2(double velocityXDirection, double velocityInitialXDirection, double timeFinal) //Uses x = ((v + vi) / 2 ) * t
{
  return (velocityXDirection + velocityInitialXDirection) / 2 * timeFinal;
}

double solve_yMaxTime1(double yMax, double velocityYDirection, double velocityInitialYDirection) //Uses x = ((v + vi) / 2 ) * t
{
  return yMax / ((velocityYDirection + velocityInitialYDirection) / 2);
}

double solve_yMax1(double velocityInitialYDirection, double angle, double accelerationYDirection) //Uses ymax = (vi * sin(angle)) * (vi * sin(angle)) / 2 / ay
{
  return pow(velocityInitialYDirection * sin(angle), 2) / (2 * -accelerationYDirection);
}

double solve_yMax2(double velocityYDirection, double velocityInitialYDirection, double accelerationYDirection) //Uses v * v = vi * vi + 2 * a * x
{
  return (pow(velocityYDirection, 2) - pow(velocityInitialYDirection, 2)) / (2 * accelerationYDirection);
}

double solve_yMax3(double velocityYDirection, double velocityInitialYDirection, double yMaxTime) //Uses x = ((v + vi) / 2 ) * t
{
  return (velocityYDirection + velocityInitialYDirection) / 2 * yMaxTime;
}

double solve_yInitial1(double velocityYDirection, double velocityInitialYDirection, double time) //Uses x = ((v + vi) / 2 ) * t
{
  return ((velocityYDirection + velocityInitialYDirection) / 2 * time);
}

double solve_yInitial2(double velocityInitialYDirection, double time, double accelerationYDirection) //Uses x = vi * t + a * t * t / 2
{
  return velocityInitialYDirection * time + accelerationYDirection * pow(time, 2) / 2;
}

double solve_angle1(double time, double accelerationYDirection, double velocityInitial) //Uses t = 2 * vi * sin(angle) / ay
{
  return asin(time * (-accelerationYDirection) / 2 / velocityInitial);
}

double solve_angle2(double xFinal, double accelerationYDirection, double velocityInitial) //Uses xFinal = vi * vi * sin( 2 * angle ) / ay
{
  return asin(xFinal * (-accelerationYDirection) / pow(velocityInitial, 2)) / 2;
}

double solve_angle3(double velocityInitialXDirection, double velocityInitial) //Uses trig properties
{
  return acos(velocityInitialXDirection/velocityInitial);
}

double solve_angle4(double velocityInitialYDirection, double velocityInitial) //Uses trig properties
{
  return asin(velocityInitialYDirection / velocityInitial);
}
