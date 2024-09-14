// -!- C++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Wed Sep 11 20:49:30 2024
//  Last Modified : <240913.1657>
//
//  Description	
//
//  Notes
//
//  History
//	
/////////////////////////////////////////////////////////////////////////////
//
//    Copyright (C) 2024  Robert Heller D/B/A Deepwoods Software
//			51 Locke Hill Road
//			Wendell, MA 01379-9728
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the Free Software
//    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
// 
//
//////////////////////////////////////////////////////////////////////////////

static const char rcsid[] = "@(#) : $Id$";

#include <SRF05.h>
#include <DFMobile.h>

// Define pins
// 8 front trigger
// 9 front echo
// 10 rear trigger
// 11 rear echo
//
// Front
const int echoPin = 9;
const int trigPin = 8;
// Closeness is 5 cm
#define CLOSE 5
// Start the sensor -- two pin mode.
SRF05 sensor(trigPin,echoPin);

DFMobile Robot (4,5,7,6);     // initiate the Motor pin

void setup() {
    Robot.Direction (LOW,HIGH);  // initiate the positive direction
    pinMode(13,OUTPUT);
}

void turn()
{
    digitalWrite(13,HIGH);
    Robot.Speed(-255,255);
    delay(800);
    digitalWrite(13,LOW);
}
void forward()
{
    Robot.Speed(128,128);
}

void loop() {
    // Get distance in cm
    int distance = sensor.getCentimeter();
    if (distance < CLOSE)
    {
        turn();
    }
    forward();
    delay(500);
}    
