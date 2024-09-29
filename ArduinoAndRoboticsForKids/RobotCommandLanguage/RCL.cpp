// -!- C++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Tue Sep 24 12:35:57 2024
//  Last Modified : <240928.2052>
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
/// @file RCL.cpp
/// @author Robert Heller
/// @date Tue Sep 24 12:35:57 2024
/// 
///
//////////////////////////////////////////////////////////////////////////////

static const char rcsid[] = "@(#) : $Id$";


#include "RCL.h"
#ifdef __AVR__
#include <avr/io.h>
#include <avr/pgmspace.h>
#elif defined(ESP8266)
#include <pgmspace.h>
#elif defined(__IMXRT1052__) || defined(__IMXRT1062__)
// PROGMEM is defefind for T4 to place data in specific memory section
#undef PROGMEM
#define PROGMEM
#else
#define PROGMEM
#endif
#ifndef pgm_read_byte
#define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#endif
#ifndef pgm_read_word
#define pgm_read_word(addr) (*(const unsigned short *)(addr))
#endif
#ifndef pgm_read_dword
#define pgm_read_dword(addr) (*(const unsigned long *)(addr))
#endif
// Pointers are a peculiar case...typically 16-bit on AVR boards,
// 32 bits elsewhere.  Try to accommodate both...

#if !defined(__INT_MAX__) || (__INT_MAX__ > 0xFFFF)
#define pgm_read_pointer(addr) ((void *)pgm_read_dword(addr))
#else
#define pgm_read_pointer(addr) ((void *)pgm_read_word(addr))
#endif

#if defined(ARDUINO_DFROBOT_ROMEO_ESP32S3)
#define strcmp_P strcmp
#undef pgm_read_word
#define pgm_read_word(x) x
#endif


int RobotCommandLanguage::lookup_word(const char *word) const
{
    /* *** MUST BE IN ALPHABETICAL ORDER (for binary search) *** */
    static const struct {
        const char w[16];
        uint16_t id;
    } reserved_words[] PROGMEM = {
        {"ACCELERATION", ACCELERATION},
        {"ANGLE", ANGLE},
        {"FRONT", FRONT},
        {"GRIP", GRIP},
        {"HEADING", HEADING},
        {"HEADLIGHT", HEADLIGHT},
        {"LEFT", LEFT},
        {"MAGNETOMETER", MAGNETOMETER},
        {"MOTOR", MOTOR},
        {"OFF", OFF},
        {"ON", ON},
        {"ORIENTATION", ORIENTATION},
        {"PAN", PAN},
        {"REAR", REAR},
        {"REMOTE", REMOTE},
        {"RIGHT", RIGHT},
        {"TEMPERATURE", TEMPERATURE},
        {"TILT", TILT},
        {"TURN", TURN},
        {"UNTIL", UNTIL},
        {"WHILE", WHILE},
        {"WRIST", WRIST},
        {"ZERO", ZERO}
    };
    const int count = sizeof(reserved_words) / sizeof(reserved_words[0]);
    int m,l,e,comp;
    
    l = 0; e = count;
    while (e > l) {
        m = (l+e)/2;
        comp = strcmp_P(word,reserved_words[m].w);
        if (comp == 0) return pgm_read_word(reserved_words[m].id);
        else if (comp < 0) e = m;
        else l = m+1;
    }
    return NOTWORD;
}

int RobotCommandLanguage::yylex()
{
    static char word[64];
    if (lp_ == NULL) lp_ = command_;
    while (*lp_ != '\0' && *lp_ <= ' ' && *lp_ != '\n') lp_++;
    if (*lp_ == '\n' || *lp_ == '\0') {
        return (EOL);
    }
    if (isdigit(*lp_) ||
        ((*lp_ == '+' || *lp_ == '-') && isdigit(*(lp_+1))))
    {
        char *p = word;
        *p++ = *lp_++;
        while (isdigit(*lp_)) *p++ = *lp_++;
        if (*lp_ == '.')
        {
            *p++ = *lp_++;
            while (isdigit(*lp_)) *p++ = *lp_++;
            *p = '\0';
            yylval.fval = atof(word);
            return(FLOAT);
        }
        *p = '\0';
        yylval.ival = atoi(word);
        return(INTEGER);
    } else if (isalpha(*lp_))
    {
        char *p = word;
        while (isalpha(*lp_))
        {
            char c = *lp_++;
            if (islower(c)) c = toupper(c);
            *p++ = c;
        }
        *p = '\0';
        return lookup_word(word);
    } else if (*lp_ == '<')
    {
        lp_++;
        if (*lp_ == '=')
        {
            lp_++;
            return LE;
        } else if (*lp_ == '>')
        {
            lp_++;
            return NE;
        } else return LT;
    } else if (*lp_ == '>')
    {
        lp_++;
        if (*lp_ == '=')
        {
            lp_++;
            return GE;
        } else return GT;
    } else if (*lp_ == '=')
    {
        lp_++;
        if (*lp_ == '=')
        {
            lp_++;
            return EQ;
        } else return '=';
    } else if (*lp_ == '!')
    {
        lp_++;
        if (*lp_ == '=')
        {
            lp_++;
            return NE;
        } else return '!';
    } else
    {
        return(*lp_++);
    }
}

int RobotCommandLanguage::parse_()
{
    switch (yylex())
    {
    case FRONT: /* FRONT EOL {SendFrontDistance();} ; */
        if (yylex() == EOL) SendFrontDistance();
        else return -1;
        break;
    case REAR: /* REAR EOL {SendRearDistance();} ; */
        if (yylex() == EOL) SendRearDistance();
        else return -1;
        break;
    case MOTOR: /* MOTOR INTEGER ',' INTEGER EOL {Motor(CheckRangeInt($2,-255,255),CheckRangeInt($4,-255,255));} ; */
        {
            int left, right;
            if (yylex() == INTEGER)
            {
                left = CheckRangeInt(yylval.ival,-255,255);
                if (yylex() == ',')
                {
                    if (yylex() == INTEGER)
                    {
                        right = CheckRangeInt(yylval.ival,-255,255);
                        if (yylex() == EOL) Motor(left,right);
                        else return -1;
                    } else return -1;
                } else return -1;
            } else return -1;
        }
        break;
    case GRIP: /* GRIP FLOAT EOL {Grip(CheckRangeFloat($2,0,100));} ; */
        {
            double gamount;
            if (yylex() == FLOAT)
            {
                gamount = CheckRangeFloat(yylval.fval,0,100);
                if (yylex() == EOL) Grip(gamount);
                else return -1;
            } else return -1;
        }
        break;
    case WRIST: /* WRIST FLOAT EOL {Wrist(CheckRangeFloat($2,-90,90));} ; */
        {
            double wangle;
            if (yylex() == FLOAT)
            {
                wangle = CheckRangeFloat(yylval.fval,-90,90);
                if (yylex() == EOL) Wrist(wangle);
                else return -1;
            } else return -1;
        }
        break;
    case PAN: /* PAN FLOAT EOL {Pan(CheckRangeFloat($2,-90,90));} ; */ 
        {
            double pangle;
            if (yylex() == FLOAT)
            {
                pangle = CheckRangeFloat(yylval.fval,-45,45);
                if (yylex() == EOL) Pan(pangle);
                else return -1;
            } else return -1;
        }
        break;
    case TILT: /* TILT FLOAT EOL {Tilt(CheckRangeFloat($2,-90,90));} ; */ 
        {
            double tangle;
            if (yylex() == FLOAT)
            {
                tangle = CheckRangeFloat(yylval.fval,-45,45);
                if (yylex() == EOL) Tilt(tangle);
                else return -1;
            } else return -1;
        }
        break;
    case REMOTE: /* REMOTE EOL {SendRemote();} ; */
        if (yylex() == EOL) SendRemote();
        else return -1;
        break;
    case HEADLIGHT: /* HEADLIGHT (ON {Headlight(1);} | OFF {Headlight(0);}) EOL ; */
        {
            int onoff;
            if (yylex() == ON) {
                onoff = 1;
            } else if (yylex() == OFF) {
                onoff = 0;
            } else return -1;
            if (yylex() == EOL) Headlight(onoff);
            else return -1;
        }
        break;
    case ACCELERATION: /* ACCELERATION EOL {SendAcceleration();} ; */
        if (yylex() == EOL) SendAcceleration();
        else return -1;
        break;
    case ORIENTATION: /* ORIENTATION EOL {SendOrientation();} ; */
        if (yylex() == EOL) SendOrientation();
        else return -1;
        break;
    case ZERO: /* ZERO (ANGLE {ZeroAngle();} | HEADING {ZeroHeading();}) EOL; */ 
        {
            int what = yylex();
            if (what == ANGLE || what == HEADING)
            {
                if (yylex() == EOL)
                {
                    switch (what)
                    {
                    case ANGLE:
                        ZeroAngle();
                        break;
                    case HEADING:
                        ZeroHeading();
                        break;
                    default: return -1;
                    }
                } else return -1;
            } else return -1;
        }
        break;
    case TURN: /* TURN (LEFT | RIGHT) INTEGER (WHILE|UNTIL) (ANGLE|HEADING) cont FLOAT EOL
                *     {DoTurn($2,CheckRangeInt($3,10,100),$4,$5,$6,CheckRangeFloat($7,0,360));} ;
                * cond : '<' | '>' | ('<' '>' ) | ('!' '=') | ( '<' '=') | ('>' '=') ; */
        {
            int direction = yylex();
            if (direction == LEFT || direction == RIGHT)
            {
                if (yylex() == INTEGER)
                {
                    int speed = CheckRangeInt(yylval.ival,10,100);
                    int loop = yylex();
                    if (loop == WHILE || loop == UNTIL)
                    {
                        int what = yylex();
                        if (what == ANGLE || what == HEADING)
                        {
                            int cond = yylex();
                            if (IsConditional(cond))
                            {
                                if (yylex() == FLOAT)
                                {
                                    double value = CheckRangeFloat(yylval.fval,0,360);
                                    if (yylex() == EOL)
                                    {
                                        DoTurn(direction,speed,loop,what,cond,value);
                                    } else return -1;
                                } else return -1;
                            } else return -1;
                        } else return -1;
                    } else return -1;
                } else return -1;
            } else return -1;
        }
        break;
    case TEMPERATURE:
        if (yylex() == EOL) SendTemperature();
        else return -1;
        break;
    case MAGNETOMETER:
        if (yylex() == EOL) SendMagnetometer();
        else return -1;
        break;
    default: return -1;
    }
    return 0;
}
