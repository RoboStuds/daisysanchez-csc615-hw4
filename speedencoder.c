/****************************************************************************************************************************************
* 
* Class: CSC-615-01 Spring 2020
*
* Name: Daisy Sanchez
*
* Student ID: 912740223 
* 
* Project: Assignment 4 – Motors & Speed Encoder
*
* File: speedencoder.c
*
* Description: 
*
*****************************************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <time.h>

//pulse counters
int counter1 = 0;
int counter2 = 0;

//code disk for speed encoder has 20 grids (slots)
double grids = 20;

//wheel diameter in millimeters
//double diameter =

//motor 1 pulse count
void countmotor1()
{
    counter1++;
}

//motor 2 pulse count
void countermotor2()
{
    counter2++;
}

void time()
{
    timer1.detachInterrupt();
    Serial.print("Speed of motor1: ");
    double rotation1 = (counter1 / grids) * 60.00;
    Serial.print(rotation1);
    Serial.print("Rotation per minute: ");
    counter1 = 0;
    Serial.print("Speed of motor2: ");
    double rotation2 = (counter2 / grids) * 60.00;
    Serial.print(rotation2);
    Serial.print("Rotation per minute: ");
    counter2 = 0;
    timer1.detachInterupt();
}

void setup() 
{
  Serial.begin(9600);
  
  Timer1.initialize(1000000); // set timer for 1sec
  attachInterrupt(digitalPinToInterrupt 1, countermotor1, RISING);  // Increase counter 1 when speed sensor pin goes High
  attachInterrupt(digitalPinToInterrupt 7, countermotor2, RISING);  // Increase counter 2 when speed sensor pin goes High
  Timer1.attachInterrupt(time); // Enable the timer
}

void forward()
{
    //counter1 = 0;
    //counter2 = 0;

    printf("Motor moving forward\n");

    //Motor 1 moves forward
    digitalWrite(0, HIGH);
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);

    //Motor 2 moves forward
    digitalWrite(6, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);

    //while (){
    //}
}

void backward()
{

    //counter1 = 0;
    //counter2 = 0;

    printf("Motor moving backward\n");

    //Motor 1 moves Backward
    digitalWrite(0, HIGH);
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);

    //Motor 2 moves Backward
    digitalWrite(6, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);

    //while(){
    //}
}

void stop()
{

    printf("Motors stop\n");

    //Stop the Motors
    digitalWrite(0, LOW);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(6, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
}

int main(void)
{

    wiringPiSetup();

    //pin for encoder 1
    pinMode(1, OUTPUT);

    //pin for encoder 2
    pinMode(7, OUTPUT);

    //Motor 1
    pinMode(0, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);

    //Motor 2
    pinMode(6, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);

    int speed = 10;

    softPwmCreate(0, speed, 100);
    softPwmCreate(6, speed, 100);

    int var = 0;

    while (var < 2)
    {
        forward();

        delay(5000);

        backward();

        delay(5000);

        stop();

        var++;
        speed += 30;

        //Change speed
        softPwmWrite(0, speed);
        softPwmWrite(6, speed);
    }

    return 0;
}