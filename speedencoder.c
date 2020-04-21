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

//code disk for speed encoder has 20 grids
double grids = 20;

//wheel diameter in millimeters
double diameter = 66.10

//pulse counters
int counter1 = 0;
int counter2 = 0;

//motor 1 pulse count
void countmotor1
{
    counter1++;
}

//motor 2 pulse count 
void countermotor2
{
    counter2++;
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
        movingforward = forward();

        delay(5000);

        movingbackwards = backward();

        delay(5000);

        stopmoving = stop();

        var++;
        speed += 30;

        //Change speed
        softPwmWrite(0, speed);
        softPwmWrite(6, speed);
    }

    return 0;
}