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
#  Last Modified : <240217.1604>
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
    def WallThickness():
        return (.125*25.4)
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
        return (.375+.5)*25.4
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
        self.casing = Part.makePlane(CasingSizes.Width(),CasingSizes.Length(),\
                                     origin).extrude(Base.Vector(0,0,.125*25.4))
        yoff = CasingSizes.HeadLightYOffset()
        xoff1 = CasingSizes.HeadLightXEndOffset()
        xoff2 = CasingSizes.Width()-CasingSizes.HeadLightXEndOffset()
        #print("*** CasingSizes.Width() = ",CasingSizes.Width(),file=sys.stderr)
        #print("*** yoff = ",yoff,", xoff1 = ",xoff1,", xoff2 = ",xoff2, file=sys.stderr)
        h1orig = origin.add(Base.Vector(xoff1, \
                                        yoff, \
                                        0))
        h1 = Part.Face(Part.Wire(Part.makeCircle((.9*CasingSizes.HeadlightHoleDiameter())/2.0,h1orig))).extrude(Base.Vector(0,0,.125*25.4))
        #print("*** h1orig is ",h1orig.x, h1orig.y, h1orig.z, file=sys.stderr)
        self.casing = self.casing.cut(h1)
        h2orig = origin.add(Base.Vector(xoff2, \
                                        yoff,\
                                        0))
        h2 = Part.Face(Part.Wire(Part.makeCircle((.9*CasingSizes.HeadlightHoleDiameter())/2.0,h2orig))).extrude(Base.Vector(0,0,.125*25.4))
        #print("*** h2orig is ",h2orig.x, h2orig.y, h2orig.z, file=sys.stderr)
        self.casing = self.casing.cut(h2)
        wallThick = CasingSizes.WallThickness()
        wallL = CasingSizes.Width()
        wallW = CasingSizes.Length()
        wallH = CasingSizes.RearHeight()
        w1 = Part.makePlane(wallL,wallThick,origin).extrude(Base.Vector(0,0,wallH))
        w2 = Part.makePlane(wallL,wallThick,origin.add(Base.Vector(0,CasingSizes.Length()-wallThick,0))).extrude(Base.Vector(0,0,wallH))
        w3 = Part.makePlane(wallThick,wallW,origin).extrude(Base.Vector(0,0,wallH))
        w4 = Part.makePlane(wallThick,wallW,origin.add(Base.Vector(CasingSizes.Width()-wallThick,0,0))).extrude(Base.Vector(0,0,wallH))
        self.casing = self.casing.fuse(w1)
        self.casing = self.casing.fuse(w2)
        self.casing = self.casing.fuse(w3)
        self.casing = self.casing.fuse(w4)
        b = HeadlightBoard(name+"_board",origin.add(Base.Vector(wallThick/2.0,wallThick/2.0,wallH-HeadlightBoard.Thickness())))
        self.casing = self.casing.cut(b.board)
        flange = Part.makePlane(wallL,wallThick,origin.add(Base.Vector(0,-wallThick,0))).extrude(Base.Vector(0,0,CasingSizes.RearFlange()))
        self.casing = self.casing.fuse(flange)
    def show(self,doc=None):
        if doc==None:
            doc = App.activeDocument()
        obj = doc.addObject("Part::Feature",self.name)
        obj.Shape=self.casing
        obj.Label=self.name
        obj.ViewObject.ShapeColor=tuple([0.5,0.5,0.5])
    def ExportSTL(self,filename="RearHeadlightCasing.stl"):
        self.casing.exportStl(filename)

class FrontHeadlightCasing(CasingSizes):
    def __init__(self,name,origin):
        self.name = name
        if not isinstance(origin,Base.Vector):
            raise RuntimeError("origin is not a Vector!")
        self.origin = origin
        self.casing = Part.makePlane(CasingSizes.Width(),CasingSizes.Length(),\
                                     origin).extrude(Base.Vector(0,0,.125*25.4))
        yoff = CasingSizes.HeadLightYOffset()
        xoff1 = CasingSizes.HeadLightXEndOffset()
        xoff2 = CasingSizes.Width()-CasingSizes.HeadLightXEndOffset()
        #print("*** CasingSizes.Width() = ",CasingSizes.Width(),file=sys.stderr)
        #print("*** yoff = ",yoff,", xoff1 = ",xoff1,", xoff2 = ",xoff2, file=sys.stderr)
        h1orig = origin.add(Base.Vector(xoff1, \
                                        yoff, \
                                        0))
        h1 = Part.Face(Part.Wire(Part.makeCircle((CasingSizes.HeadlightHoleDiameter())/2.0,h1orig))).extrude(Base.Vector(0,0,.125*25.4))
        #print("*** h1orig is ",h1orig.x, h1orig.y, h1orig.z, file=sys.stderr)
        self.casing = self.casing.cut(h1)
        h2orig = origin.add(Base.Vector(xoff2, \
                                        yoff,\
                                        0))
        h2 = Part.Face(Part.Wire(Part.makeCircle((CasingSizes.HeadlightHoleDiameter())/2.0,h2orig))).extrude(Base.Vector(0,0,.125*25.4))
        #print("*** h2orig is ",h2orig.x, h2orig.y, h2orig.z, file=sys.stderr)
        self.casing = self.casing.cut(h2)
    def show(self,doc=None):
        if doc==None:
            doc = App.activeDocument()
        obj = doc.addObject("Part::Feature",self.name)
        obj.Shape=self.casing
        obj.Label=self.name
        obj.ViewObject.ShapeColor=tuple([0.5,0.5,0.5])
    def ExportSTL(self,filename="FrontHeadlightCasing.stl"):
        self.casing.exportStl(filename)









if __name__ == '__main__':
    App.ActiveDocument=App.newDocument("Temp") 
    doc = App.activeDocument() 
    rearcase = RearHeadlightCasing("rearcase",Base.Vector(0,0,0))
    rearcase.show(doc)
    rearcase.ExportSTL()
    frontcase = FrontHeadlightCasing("frontcase",Base.Vector(0,30,0))
    frontcase.show(doc)
    frontcase.ExportSTL()
    Gui.SendMsgToActiveView("ViewFit")
    
