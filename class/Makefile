#
# ncpp C++ class makefile
#
RAFINC=	${JLOCAL}/include
O2D=	../obj

#	Solaris
#
#INCLUDES=	-I${RAFINC} -I/usr/dt/include
#DEFINES=	-DSVR4

#	Linux
#
#INCLUDES= -I${RAFINC} -I/usr/X11R6/include
#DEFINES=

#CXXFLAGS=	-O ${INCLUDES} ${DEFINES}

OBJS=	Ascii.o CanvasWindow.o DataFile.o DataSet.o DataSource.o\
	EditDiameters.o EditPlotParms.o FileMgr.o Header.o\
	MovieControl.o Panel.o PlotInfo.o PlotMgr.o Probe.o\
	Probe100.o Probe200.o SetMgr.o Titles.o VarsWin.o Colors.o\
	fssp.o s100.o s200.o f300.o pcasp.o x260.o x200.o y200.o\
	2D.o hvps.o uhsas.o cdp.o

SRCS=	Ascii.cc CanvasWindow.cc DataFile.cc DataSet.cc DataSource.cc\
	EditDiameters.cc EditPlotParms.cc FileMgr.cc Header.cc\
	MovieControl.cc Panel.cc PlotInfo.cc PlotMgr.cc Probe.cc\
	Probe100.cc Probe200.cc SetMgr.cc Titles.cc VarsWin.cc Colors.cc\
	fssp.cc s100.cc s200.cc f300.cc pcasp.cc x260.cc x200.cc y200.cc\
	2D.cc hvps.cc uhsas.cc cdp.cc

HDRS=	define.h

all: ${OBJS}


${OBJS}: ${HDRS}

Ascii.o:		Ascii.h SetMgr.h ${RAFINC}/raf/TextWindow.h DataSet.h PlotMgr.h PlotInfo.h
CanvasWindow.o:		CanvasWindow.h ${RAFINC}/raf/Window.h

DataFile.o:		DataFile.h Probe.h ${RAFINC}/raf/Time.h fssp.h f300.h pcasp.h x260.h x200.h y200.h s100.h hvps.h uhsas.h
DataSet.o:		DataSet.h Probe.h DataFile.h
DataSource.o:		DataSource.h FileMgr.h SetMgr.h Probe.h

EditDiameters.o:	EditDiameters.h ${RAFINC}/raf/Window.h FileMgr.h
EditPlotParms.o:	EditPlotParms.h ${RAFINC}/raf/Window.h
FileMgr.o:		FileMgr.h DataFile.h
Header.o:		Header.h ${RAFINC}/raf/TextWindow.h
MovieControl.o:		MovieControl.h ${RAFINC}/raf/Window.h ${RAFINC}/raf/Time.h PlotMgr.h ${RAFINC}/raf/Application.h FileMgr.h PlotMgr.h SetMgr.h

Panel.o:		Panel.h ${RAFINC}/raf/Canvas.h DataSet.h PlotInfo.h ${RAFINC}/raf/PostScript.h ${RAFINC}/raf/PixMap.h ${RAFINC}/raf/XFonts.h ${RAFINC}/raf/XPen.h

PlotInfo.o:		PlotInfo.h ${RAFINC}/raf/Canvas.h Panel.h ${RAFINC}/raf/Printer.h SetMgr.h Colors.h ${RAFINC}/raf/XFonts.h ${RAFINC}/raf/XPen.h ${RAFINC}/raf/PostScript.h

PlotMgr.o:		PlotMgr.h ${RAFINC}/raf/Window.h DataSource.h ${RAFINC}/raf/Canvas.h DataFile.h EditPlotParms.h PlotInfo.h SetMgr.h Colors.h ${RAFINC}/raf/XFonts.h ${RAFINC}/raf/XPen.h

SetMgr.o:		SetMgr.h DataSet.h
Titles.o:		Titles.h
VarsWin.o:		VarsWin.h ${RAFINC}/raf/TextWindow.h SetMgr.h PlotMgr.h PlotInfo.h

Colors.o:		Colors.h


Probe.o:		Probe.h
Probe200.o:		Probe200.h Probe.h
Probe100.o:		Probe100.h Probe.h
fssp.o:			fssp.h Probe100.h
cdp.o:			cdp.h Probe100.h
s100.o:			s100.h Probe100.h
s200.o:			s200.h Probe.h
f300.o:			f300.h Probe.h
pcasp.o:		pcasp.h Probe.h
hvps.o:			hvps.h Probe.h
uhsas.o:		uhsas.h Probe.h
x260.o:			x260.h Probe200.h Probe.h
x200.o:			x200.h Probe200.h Probe.h
y200.o:			y200.h Probe200.h Probe.h
2D.o:			2D.h Probe200.h Probe.h


clean:
	${RM} *.o
