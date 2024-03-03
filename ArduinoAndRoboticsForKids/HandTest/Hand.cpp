// -!- C++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Sun Mar 3 16:21:51 2024
//  Last Modified : <240303.1659>
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
/// @file Hand.cpp
/// @author Robert Heller
/// @date Sun Mar 3 16:21:51 2024
/// 
///
//////////////////////////////////////////////////////////////////////////////

static const char rcsid[] = "@(#) : $Id$";


#include <Servo.h>
#include "Hand.h"


Hand::Hand()
{
}

void Hand::Begin(int gripServo, int wristServo, int panServo, int tiltServo)
{
    _gripper.attach(gripServo);
    _wrist.attach(wristServo);
    _pan.attach(panServo);
    _tilt.attach(tiltServo);
}

void Hand::Grip()
{
    _gripper.write(GRIP);
}

void Hand::Release()
{
    _gripper.write(RELEASE);
}

void Hand::Rotate(int degrees)
{
    _wrist.write(degrees+90);
}

void Hand::Lift(int degrees)
{
    _tilt.write(degrees+90);
}

void Hand::Pan(int degrees)
{
    _pan.write(degrees+90);
}

