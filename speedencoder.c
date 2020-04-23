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

void PI_THREAD(mythread)
{
    int pulse = 0;
    double pulseold = 0;
    double total = 0;
    double RPS = 0;

    int starttime;
    int endtime;

    starttime = millis();
    endtime = starttime + 1000;
    while (millis() < endtime)
    {
        if (digitalRead(1))
        {
            pulse = pulse + 1;
            while (digitalRead(1))
                ;
        }
        total = pulse - pulseold;
        pulseold = pulse;
        RPS = (total / 20);

        printf("Rev per seconds: %f\n", RPS);
    }
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
    pinMode(1, INPUT);

    //pin for encoder 2
    //pinMode(7, INPUT);

    //Motor 1
    pinMode(0, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);

    //Motor 2
    pinMode(6, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);

    int piThreadCreate(mythread);

    int speed = 10;

    softPwmCreate(0, speed, 100);
    softPwmCreate(6, speed, 100);

    int var = 0;

    while (var < 2)
    {
        x = piThreadCreate(mythread);
        if (x != 0)
        printf("didnt work");

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
