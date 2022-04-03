//Find the center of a circle

#include <BasicLinearAlgebra.h>
using namespace BLA;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
  }

float x[] = {-17.07, -14.58, -6.25, 7.26, 24.9, 46.97, 68.7, 91.98, 113.77, 131.82, 145.41, 153.43, 156.9};
float y[] = {-8.95, 11.67, 30.88, 46.89, 59.44, 66.09, 66.49, 61.72, 51.64, 35.93, 17.1, -6.18, -28.85};

int numberOfPoints = 13;
for( int i = 0; i < numberOfPoints; i++){
  Serial.print(x[i]);
  Serial.print('\t');
  Serial.println(y[i]);
  }

Serial.println("The above points make up a half circle.");




float circ_x;
float circ_y;
float circ_r;
FindCircleCenter(x,y,numberOfPoints, circ_x, circ_y, circ_r);

Serial.println("");
Serial.println("Circle that fits the data best: ");

Serial.print("X coord: ");
Serial.println(circ_x);
Serial.print("Y coord: ");
Serial.println(circ_y);
Serial.print("Radius: ");
Serial.println(circ_r);
}

void loop() {
  
}

void FindCircleCenter(float x[], float y[], int count, float& out_x, float& out_y, float& out_r){

  float sum_xx = 0;
  float sum_xy = 0;
  float sum_x = 0;
  float sum_yy = 0;
  float sum_y = 0;

  float sum_x_xx_yy = 0;
  float sum_y_xx_yy = 0;
  float sum_xx_yy = 0;

  for( int i = 0; i < count; i++){
    sum_xx = sum_xx + x[i] * x[i];
    sum_xy = sum_xy + x[i] * y[i];
    sum_x = sum_x + x[i];
    sum_yy = sum_yy + y[i] * y[i];
    sum_y = sum_y + y[i];

    sum_x_xx_yy = sum_x_xx_yy + x[i]*(x[i]*x[i] + y[i]*y[i]);
    sum_y_xx_yy = sum_y_xx_yy + y[i] * (x[i] * x[i] + y[i] * y[i]);
    sum_xx_yy = sum_xx_yy + x[i]*x[i] + y[i] * y[i];    
  }

  BLA::Matrix<3,3> lhs = {sum_xx, sum_xy, sum_x, sum_xy, sum_yy, sum_y, sum_x, sum_y, count};
  BLA::Matrix<3,1> rhs = {sum_x_xx_yy,sum_y_xx_yy,sum_xx_yy};
  Invert(lhs);
  BLA::Matrix<3,1> result = lhs * rhs;
  float a = result(0); // coeff
  float b = result(1); // coeff
  float c = result(2); // coeff

  out_x = a / 2; // x coordinate of center
  out_y = b / 2; // y coordinate of center
  out_r = (sqrt(4*c+a*a+b*b))/2; // Radius of circle
}
