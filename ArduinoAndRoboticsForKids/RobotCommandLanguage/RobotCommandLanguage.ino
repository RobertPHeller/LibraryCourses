// -!- C++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Tue Sep 24 11:44:17 2024
//  Last Modified : <240924.1710>
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

#include "RCL.h"

RobotCommandLanguage parser;

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    Serial.setTimeout(100000);
    parser.setup();
    Serial.println("Ready");
}
                
void loop() {
    // put your main code here, to run repeatedly:
    char buffer[256];
    if (Serial.available() > 0)
    {
        //Serial.print("***");Serial.println(Serial.available());
        size_t b = Serial.readBytesUntil('\r',buffer,sizeof(buffer)-1);
        buffer[b] = '\0';
        //Serial.print("***");Serial.println(b);
        //Serial.print("***");Serial.println(buffer);
        if (parser.ParseCommand(buffer) < 0)
        {
            Serial.println("Parse error");
        }
    } else delay(100);
}    
