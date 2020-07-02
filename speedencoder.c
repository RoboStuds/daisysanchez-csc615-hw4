/****************************************************************************************************************************************
* 
* Class: CSC-615-01 Spring 2020
*
*
*
* 
* 
* Project: Assignment 4 – Motors & Speed Encoder
*
* File: speedencoder.c
*
* Description: We connected two motors to two channels on the Motor Shield. Each motor will have a speed encoder wheel
* and an infrared speed sensor. One of the speed sensors will be connected to the Raspberry Pi, the other will be 
* connected to the LS7366R. We will read the speed encoder sensor by directly connecting the sensor to a digital 
* pin on the Raspberry Pi and creating a multi-threaded application where the thread is responsible for reading 
* that pin and providing a speed to the main program. The second motor will use the LS7366R to do the counting. 
* The speed sensor is connected to the LS7366R and use the SPI interface to get the counts from the chip.
*****************************************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <time.h>

PI_THREAD(mythread)
{
    int pulse = 0;
    double pulseold = 0;
    double total = 0;
    double velocity = 0;
    double radius = 1.25;

    int starttime;
    int endtime;

    while(1) {
        starttime = millis();
        endtime = starttime + 1000;
        while (millis() < endtime)
        {
            if (digitalRead(8))
            {
                pulse = pulse + 1;
                while (digitalRead(8))
                    ;
            }
        }
        total = pulse - pulseold;
        pulseold = pulse;
        velocity = (2 * 3.14 * radius * total / 20);

        printf("cm per seconds: %f\n", velocity);
    }
    return 0;
    
}

void forward()
{

    printf("Motor moving forward\n");

    //Motor 1 moves forward
    digitalWrite(0, HIGH);
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);

    //Motor 2 moves forward
    digitalWrite(6, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);

}

void backward()
{

    printf("Motor moving backward\n");

    //Motor 1 moves Backward
    digitalWrite(0, HIGH);
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);

    //Motor 2 moves Backward
    digitalWrite(6, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);

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
    pinMode(8, INPUT);

    //Motor 1
    pinMode(0, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);

    //Motor 2
    pinMode(6, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);

    int x = piThreadCreate(mythread);
    if (x != 0)
        printf("didnt work\n");

    int speed = 10;

    softPwmCreate(0, speed, 100);
    softPwmCreate(6, speed, 100);

    int var = 0;

    while (var < 2)
    {
        printf("PWM: %d\n", speed);

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
