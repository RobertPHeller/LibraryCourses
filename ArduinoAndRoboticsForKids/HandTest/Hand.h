// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Sun Mar 3 16:16:04 2024
//  Last Modified : <240303.1700>
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
/// @file Hand.h
/// @author Robert Heller
/// @date Sun Mar 3 16:16:04 2024
/// 
///
//////////////////////////////////////////////////////////////////////////////

#ifndef __HAND_H
#define __HAND_H

#include <Servo.h>

class Hand
{
public:
    Hand();
    void Grip();
    void Release();
    void Rotate(int degrees);
    void Lift(int degrees);
    void Pan(int degrees);
    void Begin(int gripServo, int wristServo, int panServo, int tiltServo);
private:
    enum {
        GRIP = 0,
        RELEASE = 180
    };
    Servo _gripper;
    Servo _wrist;
    Servo _pan;
    Servo _tilt;
};

#endif // __HAND_H

