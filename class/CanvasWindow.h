/*
-------------------------------------------------------------------------
OBJECT NAME:	CanvasWindow.h

FULL NAME:	Create Main Canvas Window

TYPE:		

COPYRIGHT:	University Corporation for Atmospheric Research, 1997
-------------------------------------------------------------------------
*/

#ifndef CANWINDOW_H
#define CANWINDOW_H

#include "define.h"

#include "raf/Window.h"

#include <Xm/CascadeB.h>
#include <Xm/DrawingA.h>
#include <Xm/PushB.h>
#include <Xm/RowColumn.h>
#include <Xm/Separator.h>


/* -------------------------------------------------------------------- */
/**
 * Thin class that creates the main canvas window and the menus.
 */
class CanvasWindow : public WinForm
{
public:
		CanvasWindow(const Widget parent);

  Widget	DrawingArea()	{ return(_drawA); }

private:
  Widget	_drawA;

};	// END CANVASWINDOW.H

#endif
