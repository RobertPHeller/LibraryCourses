#*****************************************************************************
#
#  System        : 
#  Module        : 
#  Object Name   : $RCSfile$
#  Revision      : $Revision$
#  Date          : $Date$
#  Author        : $Author$
#  Created By    : Robert Heller
#  Created       : Fri Feb 9 09:01:43 2024
#  Last Modified : <240211.1227>
#
#  Description	
#
#  Notes
#
#  History
#	
#*****************************************************************************
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
#*****************************************************************************


import Part
from FreeCAD import Base
import FreeCAD as App

from abc import ABCMeta, abstractmethod, abstractproperty
from math import *


class HeadlightBoard(object):
    @staticmethod
    def Width():
        return 109.22
    @staticmethod
    def Length():
        return 15.24
    @staticmethod
    def Thickness():
        return 1.5
    def __init__(self,name,origin):
        self.name = name
        if not isinstance(origin,Base.Vector):
            raise RuntimeError("origin is not a Vector!")
        self.origin = origin
        self.board = Part.makePlane(HeadlightBoard.Width(),HeadlightBoard.Length(),origin).extrude(Base.Vector(0,0,HeadlightBoard.Thickness()))
    def show(self,doc=None):
        if doc==None:
            doc = App.activeDocument()
        obj = doc.addObject("Part::Feature",self.name)
        obj.Shape=self.board
        obj.Label=self.name
        obj.ViewObject.ShapeColor=tuple([0.0,1.0,0.0])
        

class CasingSizes(object):
    @staticmethod
    def Width():
        return HeadlightBoard.Width()+(.125*25.4)
    @staticmethod
    def Length():
        return HeadlightBoard.Length()+(.125*25.4)
    @staticmethod
    def RearHeight():
        return .375*25.4
    @staticmethod
    def FrontHeight():
        return .125*25.4
    @staticmethod
    def RearFlange():
        return .5*25.4
    @staticmethod
    def HeadlightHoleDiameter():
        return .24*25.4
    @staticmethod
    def HeadLightYOffset():
        return 7.62+(.0625*25.4)
    @staticmethod
    def HeadLightXEndOffset():
        return 7.62+(.0625*25.4)

class RearHeadlightCasing(CasingSizes):
    def __init__(self,name,origin):
        self.name = name
        if not isinstance(origin,Base.Vector):
            raise RuntimeError("origin is not a Vector!")
        self.origin = origin
        self.casing = Part.makePlane(CasingSizes.Width(),CasingSizes.Length(),origin).extrude(Base.Vector(0,0,.125*25.4))
        h1orig = origin.add(Base.Vector(CasingSizes.HeadLightYOffset(),CasingSizes.HeadLightXEndOffset(),0))
        h1 = Part.Face(Part.Wire(Part.makeCircle((.9*CasingSizes.HeadlightHoleDiameter())/2.0,h1orig))).extrude(Base.Vector(0,0,.125*25.4))
        print("*** h1orig is ",h1orig.x, h1orig.y, h1orig.z)
        self.casing = self.casing.cut(h1)
        h2orig = origin.add(Base.Vector(CasingSizes.HeadLightYOffset(),CasingSizes.Length()-CasingSizes.HeadLightXEndOffset(),0))
        h2 = Part.Face(Part.Wire(Part.makeCircle((.9*CasingSizes.HeadlightHoleDiameter())/2.0,h2orig))).extrude(Base.Vector(0,0,.125*25.4))
        print("*** h2orig is ",h2orig.x, h2orig.y, h2orig.z)
        self.casing = self.casing.cut(h2)
    def show(self,doc=None):
        if doc==None:
            doc = App.activeDocument()
        obj = doc.addObject("Part::Feature",self.name)
        obj.Shape=self.casing
        obj.Label=self.name
        obj.ViewObject.ShapeColor=tuple([0.5,0.5,0.5])
        











if __name__ == '__main__':
    App.ActiveDocument=App.newDocument("Temp") 
    doc = App.activeDocument() 
    rearcase = RearHeadlightCasing("rearcase",Base.Vector(0,0,0))
    rearcase.show(doc)
    Gui.SendMsgToActiveView("ViewFit")
    
