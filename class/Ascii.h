/*
-------------------------------------------------------------------------
OBJECT NAME:	Ascii.h

FULL NAME:	View ASCII cell data.

TYPE:		

COPYRIGHT:	University Corporation for Atmospheric Research, 1998
-------------------------------------------------------------------------
*/

#ifndef ASCII_H
#define ASCII_H

#include "define.h"

#include "SetMgr.h"
#include "PlotMgr.h"
#include "raf/TextWindow.h"


/* -------------------------------------------------------------------- */
/**
 * Class for ASCII data display.  This creates and updates a basic text widget.
 * Widget is filled with the ASCII data from what is being displayed on the
 * plot windows.
 */
class Ascii : public TextWindow
{
public:
	Ascii(const Widget parent);

  void	Update(SetManager& sets, PlotManager *plotMgr);

private:

};	// END ASCII.H

#endif
