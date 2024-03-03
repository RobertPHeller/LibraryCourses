// -!- C++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Sun Mar 3 16:14:48 2024
//  Last Modified : <240303.1701>
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

#include <Servo.h>
#include "Hand.h"

const int gripper = 3;
const int wrist = 9;
const int pan = 10;
const int tilt = 11;

Hand hand;

static const char rcsid[] = "@(#) : $Id$";

void setup() {
    // put your setup code here, to run once:
    hand.Begin(gripper,wrist,pan,tilt);
}
                
void loop() {
    // put your main code here, to run repeatedly:
    hand.Rotate(-90);
    delay(100);
    hand.Rotate(0);
    delay(100);
    hand.Rotate(90);
    delay(100);
    hand.Rotate(0);
    delay(100);
    hand.Pan(-90);
    delay(100);
    hand.Pan(0);
    delay(100);
    hand.Pan(90);
    delay(100);
    hand.Pan(0);
    delay(100);
    hand.Lift(-90);
    delay(100);
    hand.Lift(0);
    delay(100);
    hand.Lift(90);
    delay(100);
    hand.Lift(0);
    delay(100);
    hand.Grip();
    delay(100);
    hand.Release();
    delay(100);
}    
