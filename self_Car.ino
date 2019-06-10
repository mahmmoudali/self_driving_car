//Libraries
#include "Ultrasonic.h"
//Define pins ultrasonic(trig,echo)
Ultrasonic ultrasonic(A0,A1);

//Variables
int distance;
//Motors
const int m1f=12;
const int m1b=11;
const int m2f=10;
const int m2b=9;

// TCS230 pins connected to Arduino
const int s0 = 6;
const int s1 = 5;
const int s2 = 4;
const int s3 = 3;
const int out = 2;

//Color_sensor
int red = 0;
int green = 0;
int blue = 0;

char r;
const int buzz=8;
//
void forward();
void backward();
void right();
void left();
void stopp();
int color_recogition();
int d ();

void setup() {
Serial.begin(9600);
//****Color_sensor****
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);
  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);
//
  pinMode(buzz,OUTPUT);
//Motors
pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(9 ,OUTPUT);

  stopp();
}

void loop() {
  //****ultra_sonic****
  
distance = ultrasonic.Ranging(CM); //Use 'CM' for centimeters or 'INC' for inches
  //Print distance...
  Serial.print("Object found at: ");
  Serial.print(distance);
  Serial.println("cm");
  if (distance < 30)
    {digitalWrite(buzz, 1);
    stopp();
    }
  else
    digitalWrite(buzz, 0); 


  //Motors_control
  while (Serial.available()>0)
 {
  r=Serial.read();
  switch(r){
    case 'F' :
    forward();
    break;
    case 'G' :    
    backward();
    break;
    case 'R' :
    right();
    break;
    case 'L' :
    left();
    break;
    case 'X' :
    stopp();
    break;
    }
 
}
//color-recognize
    if(color_recogition()==2)
    stopp();
}


int color_recogition(){
  int c;
   color();
  Serial.print("R =");
  Serial.print(red, DEC);
  Serial.print(" G = ");
  Serial.print(green, DEC);
  Serial.print(" B = ");
  Serial.print(blue, DEC);
  Serial.print("\t");

  if (red < blue && red < green && red < 25)
  {
    if (green - blue >= 10 && green - blue <= 25 && green - ( 2 * red ) >= 8 )
    {
      Serial.println(" - (Red Color)");
      c=1;
    }

   /*else if (green - red <= 10 && green - red >= -3 && blue >= green)
    {
      Serial.println(" - (Yellow Color)");
    }
    
    else if (blue - red >= 3 && blue - red <= 10 &&  green - ( 2 * red ) <= 5)
    {
      Serial.println(" - (Pink Color)");
    }
    */
    else if (green - blue >= -5 && green - blue <= 5 && green - ( 2 * red ) <= 5 )
    {
      Serial.println(" - (Orange Color)");
      c=2;
    }

  }

  else if (green < red && green < blue && green < 25)
  {
    Serial.println(" - (Green Color)");
    c=3;
  }
/*
  else if ((red > green &&  blue < green) && blue < 25 && red > 40)
  {
    
    Serial.println(" - (Blue Color)");
  }

  /*else if (red - (2 * blue) >= -2 && red - (2 * blue) <= 5 && green - red < 10)
  {
    
    Serial.println(" - (Purple Color)");
  }
  else if (blue < red && blue < green && (blue && red && green) < 25)
  {

    if (red - green <= 5 && red - green >= 0 && ((green - blue) || (red - blue)) < 5 && blue < 50)
    {
      
      Serial.println(" - (White Color)");
    }*/
  

  Serial.println();

  delay(300);
  return c;
}


void color()
{
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  //count OUT, pRed, RED
  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s3, HIGH);
  //count OUT, pBLUE, BLUE
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s2, HIGH);
  //count OUT, pGreen, GREEN
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
}

//manual_control_methods
void forward(){
  
  digitalWrite(m1f,1);
   digitalWrite(m1b,0);
    digitalWrite(m2f,1);
     digitalWrite(m2b,0);
     
}
void backward(){
  digitalWrite(m1f,0);
   digitalWrite(m1b,1);
    digitalWrite(m2f,0);
     digitalWrite(m2b,1);
     
}void right(){
  digitalWrite(m1f,0);
   digitalWrite(m1b,1);
    digitalWrite(m2f,1);
     digitalWrite(m2b,0);
  
     
}void left(){
  digitalWrite(m1f,1);
   digitalWrite(m1b,0);
    digitalWrite(m2f,0);
     digitalWrite(m2b,1);
     
}
void stopp(){
  digitalWrite(m1f,1);
   digitalWrite(m1b,1);
    digitalWrite(m2f,1);  
     digitalWrite(m2b,1);
     
}
