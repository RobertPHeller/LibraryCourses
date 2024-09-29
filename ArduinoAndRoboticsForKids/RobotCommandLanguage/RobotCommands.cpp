// -!- C++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Tue Sep 24 12:15:57 2024
//  Last Modified : <240928.2048>
//
//  Description	
//
//  Notes
//
//  History
//	
/////////////////////////////////////////////////////////////////////////////
/// @copyright
///    Copyright (C) 2024  Robert Heller D/B/A Deepwoods Software
///			51 Locke Hill Road
///			Wendell, MA 01379-9728
///
///    This program is free software; you can redistribute it and/or modify
///    it under the terms of the GNU General Public License as published by
///    the Free Software Foundation; either version 2 of the License, or
///    (at your option) any later version.
///
///    This program is distributed in the hope that it will be useful,
///    but WITHOUT ANY WARRANTY; without even the implied warranty of
///    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
///    GNU General Public License for more details.
///
///    You should have received a copy of the GNU General Public License
///    along with this program; if not, write to the Free Software
///    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
/// @file RobotCommands.cpp
/// @author Robert Heller
/// @date Tue Sep 24 12:15:57 2024
/// 
///
//////////////////////////////////////////////////////////////////////////////

static const char rcsid[] = "@(#) : $Id$";

#include <Arduino.h>
#include "RobotCommands.h"
#include <SRF05.h>
#include <DFMobile.h>
#if defined(ARDUINO_AVR_UNO)
#include <Servo.h>
#include <IRremote.h>
#elif defined(ARDUINO_DFROBOT_ROMEO_ESP32S3)
#include <ESP32Servo.h>
#endif
#include <Adafruit_LSM6DSOX.h>
#include <Adafruit_LIS3MDL.h>

#include "config.h"

#if defined(ARDUINO_AVR_UNO)
#define  RX_Pin 0
#define  TX_Pin 1
#define  Front_Pin 2
#define  Grip_Pin 3
#define  M1_Pin 4
#define  E1_Pin 5
#define  E2_Pin 6
#define  M2_Pin 7
#define  Rear_Pin  8
#define  Wrist_Pin  9
#define  Pan_Pin  10
#define  Tilt_Pin  11
#define  IR_Pin 12
#define  Headlights_Pin 13

#define  LDR_Pin A0
#elif defined(ARDUINO_DFROBOT_ROMEO_ESP32S3)
#define  RX_Pin 44
#define  TX_Pin 43
#define  Front_Pin 12 
#define  Grip_Pin 13
#define  M1_Pin 10
#define  E1_Pin 9
#define  E2_Pin 47
#define  M2_Pin 11
#define  Rear_Pin 14
#define  Wrist_Pin 21
#define  Pan_Pin 7
#define  Tilt_Pin 15
#define  IR_Pin 16
#define  Headlights_Pin 17

#define  LDR_Pin 17
#endif
/* Ultrasonic Sensors */
SRF05 FrontSensor(Front_Pin);
SRF05 RearSensor(Rear_Pin);

/* Wheel motors */
DFMobile Robot (M1_Pin,E1_Pin,M2_Pin,E2_Pin);     // initiate the Motor pins

/* Gripper + Pan & Tilt */
Servo grip, wrist, pan, tilt;

#if defined(ARDUINO_AVR_UNO)
/* Remote control */
IRrecv irrecv(IR_Pin);
#elif defined(ARDUINO_DFROBOT_ROMEO_ESP32S3)
#endif
#ifdef ACCEL
Adafruit_LSM6DSOX lsm6ds;
#endif
#ifdef MAG
Adafruit_LIS3MDL lis3mdl;
#endif

void RobotCommands::setup()
{
#ifdef ACCEL
    bool lsm6ds_success;
#endif
#ifdef MAG
    bool lis3mdl_success;
#endif
    
    Robot.Direction (LOW,HIGH);  // initiate the positive direction 
    /* Gripper servos */
    grip.attach(Grip_Pin);
    wrist.attach(Wrist_Pin);
    pan.attach(Pan_Pin);
    tilt.attach(Tilt_Pin);
#if defined(ARDUINO_AVR_UNO)
    /* Remote control */
    irrecv.enableIRIn();
#elif defined(ARDUINO_DFROBOT_ROMEO_ESP32S3)
#endif
    /* Headlights */
    pinMode(Headlights_Pin,OUTPUT);
    digitalWrite(Headlights_Pin,LOW);

    // hardware I2C mode, can pass in address & alt Wire

#ifdef ACCEL
    lsm6ds_success = lsm6ds.begin_I2C();
#endif
#ifdef MAG
    lis3mdl_success = lis3mdl.begin_I2C();
    lis3mdl.setDataRate(LIS3MDL_DATARATE_155_HZ);
    lis3mdl.setRange(LIS3MDL_RANGE_4_GAUSS);
    lis3mdl.setPerformanceMode(LIS3MDL_MEDIUMMODE);
    lis3mdl.setIntThreshold(500);
    lis3mdl.configInterrupt(false, false, true, // enable z axis
                            true, // polarity
                            false, // don't latch
                            true); // enabled!
#endif
}

void RobotCommands::SendFrontDistance()
{
    Serial.print("Front Distance ");
    Serial.println(FrontSensor.getCentimeter());
}

void RobotCommands::SendRearDistance()
{
    Serial.print("Rear Distance ");
    Serial.println(FrontSensor.getCentimeter());
}

void RobotCommands::Motor(int left, int right)
{
    Robot.Speed(left,right);
    Serial.print("Robot ");
    Serial.print(left);
    Serial.print(",");
    Serial.println(right);
}

int RobotCommands::CheckRangeInt(int v, int lower, int upper)
{
    if (v < lower) v = lower;
    if (v > upper) v = upper;
    return v;
}

double RobotCommands::CheckRangeFloat(double v, double lower, double upper)
{
    if (v < lower) v = lower;
    if (v > upper) v = upper;
    return v;
}

void RobotCommands::Grip(double gamount)
{
    Serial.println("Grip: N/A");
}

void RobotCommands::Wrist(double wangle)
{
    Serial.println("Wrist: N/A");
}

void RobotCommands::Pan(double pangle)
{
    Serial.println("Pan: N/A");
}

void RobotCommands::Tilt(double tangle)
{
    Serial.println("Tilt: N/A");
}

void RobotCommands::SendRemote()
{
    Serial.println("Remote: N/A");
}

void RobotCommands::Headlight(int onoff)
{
    Serial.println("Headlight: N/A");
}

void RobotCommands::SendAcceleration()
{
    Serial.println("Acceleration: N/A");
}

void RobotCommands::SendOrientation()
{
    Serial.println("Orientation: N/A");
}

void RobotCommands::SendTemperature()
{
    Serial.println("Temperature: N/A");
}

void RobotCommands::SendMagnetometer()
{
    Serial.println("Magnetometer: N/A");
}

void RobotCommands::ZeroAngle()
{
    Serial.println("Zero Angle: N/A");
}

void RobotCommands::ZeroHeading()
{
    Serial.println("Zero Heading: N/A");
}

void RobotCommands::DoTurn(int direction,int speed,int loop, int what, int cond, double value)
{
    Serial.println("DoTurn ...: N/A");
}

