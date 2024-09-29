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
#  Last Modified : <240929.0930>
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
PORT=/dev/ttyACM0
BUILDDIR=build.$(subst :,_,$(BOARDSPEC))

TARGET=$(BUILDDIR)/RobotCommandLanguage.ino.hex

all: $(TARGET)


$(TARGET): RobotCommandLanguage.ino RCL.h RCL.cpp RobotCommands.h RobotCommands.cpp config.h
	-mkdir $(BUILDDIR)
	arduino --verify --board $(BOARDSPEC) -v --pref build.path=$(BUILDDIR)  RobotCommandLanguage.ino

upload: $(TARGET)
	arduino --upload --board $(BOARDSPEC) --pref build.path=$(BUILDDIR) --port $(PORT) RobotCommandLanguage.ino

