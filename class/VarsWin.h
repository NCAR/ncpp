/*
-------------------------------------------------------------------------
OBJECT NAME:	VarsWin.h

FULL NAME:	View Housekeeping & derived variables

TYPE:		

COPYRIGHT:	University Corporation for Atmospheric Research, 1998
-------------------------------------------------------------------------
*/

#ifndef VARSWIN_H
#define VARSWIN_H

#include "define.h"

#include "SetMgr.h"
#include "PlotMgr.h"
#include "raf/TextWindow.h"


/* -------------------------------------------------------------------- */
/**
 * Class for displaying the "other variables" window.  These are the down
 * stream scalar variables which this program can not plot.
 */
class VarsWin : public TextWindow
{
public:
	VarsWin(const Widget parent);

  void	Update(SetManager& sets, PlotManager *plotMgr);

private:

};	// END VARSWIN.H

#endif
