##-*- makefile -*-############################################################
#
#  System        : 
#  Module        : 
#  Object Name   : $RCSfile$
#  Revision      : $Revision$
#  Date          : $Date$
#  Author        : $Author$
#  Created By    : Robert Heller
#  Created       : Tue Sep 24 11:54:51 2024
#  Last Modified : <240928.2102>
#
#  Description	
#
#  Notes
#
#  History
#	
#  $Log$
#
##############################################################################
#
#    Copyright (C) 2024  Robert Heller D/B/A Deepwoods Software
#			51 Locke Hill Road
#			Wendell, MA 01379-9728
#
#    This program is free software; you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation; either version 2 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program; if not, write to the Free Software
#    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#
# 
#
##############################################################################


BOARDSPEC = arduino:avr:uno

TARGET=build.stamp_$(subst :,_,$(BOARDSPEC))

all: $(TARGET)


$(TARGET): RobotCommandLanguage.ino RCL.h RCL.cpp RobotCommands.h RobotCommands.cpp config.h
	-rm -rf /tmp/arduino_build_*
	arduino --verify --board $(BOARDSPEC) -v --preserve-temp-files RobotCommandLanguage.ino
	touch $(TARGET)

upload: $(TARGET)
	arduino --upload --board $(BOARDSPEC) --port /dev/ttyACM0 RobotCommandLanguage.ino

