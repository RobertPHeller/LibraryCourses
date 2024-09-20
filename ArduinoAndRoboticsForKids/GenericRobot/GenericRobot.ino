// -!- C++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Fri Sep 20 14:02:29 2024
//  Last Modified : <240920.1405>
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
const int FrontechoPin = 9;
const int FronttrigPin = 8;
// Start the Front sensor -- two pin mode.
SRF05 FrontSensor(FronttrigPin,FrontechoPin);
// Rear
const int RearechoPin = 11;
const int ReartrigPin = 10
// Start the Rear sensor -- two pin mode.
SRF05 RearSensor(ReartrigPin,RearechoPin);

DFMobile Robot (4,5,7,6);     // initiate the Motor pin

void setup() {
    // put your setup code here, to run once:
    Robot.Direction (LOW,HIGH);  // initiate the positive direction
}
                
void loop() {
    // put your main code here, to run repeatedly:
}    
