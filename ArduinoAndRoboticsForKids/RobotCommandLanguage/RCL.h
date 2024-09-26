// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Tue Sep 24 12:28:22 2024
//  Last Modified : <240926.1123>
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
/// @file RCL.h
/// @author Robert Heller
/// @date Tue Sep 24 12:28:22 2024
/// 
///
//////////////////////////////////////////////////////////////////////////////

#ifndef __RCL_H
#define __RCL_H

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "RobotCommands.h"

class RobotCommandLanguage : public RobotCommands
{
public:
    RobotCommandLanguage() : lp_(NULL) {}
    int ParseCommand(char *command)
    {
        strncpy(command_,command,sizeof(command_));
        command_[sizeof(command_)-1] = '\0';
        lp_ = NULL;
        return parse_();
    }
private:
    friend class RobotCommands;
    int lookup_word(const char *word) const;
    int yylex();
    char command_[256];
    char *lp_;
    int parse_();
    union {
        int ival;
        float fval;
    } yylval;
    enum {INTEGER=258,FLOAT,EOL,NOTWORD,FRONT,REAR,MOTOR,GRIP,WRIST,PAN,TILT,
        REMOTE,HEADLIGHT,ON,OFF,ACCELERATION,ORIENTATION,TURN,WHILE,UNTIL,
        ANGLE,HEADING,ZERO,LEFT,RIGHT,EQ,NE,LT,GT,LE,GE
    };
    inline bool IsConditional(int cond) const
    {
        return cond == EQ ||
              cond == NE ||
              cond == LT ||
              cond == GT ||
              cond == LE ||
              cond == GE;
    }
    
};


#endif // __RCL_H

