// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Tue Sep 24 12:01:53 2024
//  Last Modified : <240926.1949>
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
/// @file RobotCommands.h
/// @author Robert Heller
/// @date Tue Sep 24 12:01:53 2024
/// 
///
//////////////////////////////////////////////////////////////////////////////

#ifndef __ROBOTCOMMANDS_H
#define __ROBOTCOMMANDS_H



class RobotCommands
{
public:
    RobotCommands() {}
    void setup();
    void SendFrontDistance();
    void SendRearDistance();
    void Motor(int left, int right);
    int CheckRangeInt(int v, int lower, int upper);
    double CheckRangeFloat(double v, double lower, double upper);
    void Grip(double gamount);
    void Wrist(double wangle);
    void Pan(double pangle);
    void Tilt(double tangle);
    void SendRemote();
    void Headlight(int onoff);
    void SendAcceleration();
    void SendOrientation();
    void ZeroAngle();
    void ZeroHeading();
    void DoTurn(int direction,int speed,int loop, int what, int cond, double value);
private:
    
};

#endif // __ROBOTCOMMANDS_H

