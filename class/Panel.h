/*
-------------------------------------------------------------------------
OBJECT NAME:	Panel.h

FULL NAME:	Panel Information

TYPE:		

COPYRIGHT:	University Corporation for Atmospheric Research, 1997-8
-------------------------------------------------------------------------
*/

#ifndef PANEL_H
#define PANEL_H

#include "define.h"
#include "raf/Canvas.h"
#include "DataSet.h"
#include "raf/PixMap.h"
#include "raf/PostScript.h"
#include "raf/XPen.h"
#include "raf/XFonts.h"

struct panelDims
        {
        int     TH, BH;         /* Top & Bottom Horizontal, in Pixels   */
        int     LV, RV;         /* Left & Right Vertical, in Pixels     */

        int     HD, VD;         /* Horizontal & Vertical Distance, in Pixels*/
	int	ZD;
        };

struct axisInfo
        {
	std::string	label;
        bool	logScale;
        bool	invertAxis;
        int	nMajorTics, nMinorTics;
        double	min, max;
        };

class PlotInfo;


/* -------------------------------------------------------------------- */
/**
 * Class to render a panel on the main canvas window.
 */
class Panel
{
public:
	Panel(DataType dt);

  void	DrawPlotFrames(PlotInfo& p),
	PrintPlotFrames(PlotInfo& p, PostScript& pen);

  void	DrawHistogram(DataSet *, int, int, DataType, Drawable, XPen&);
  void	PrintHistogram(DataSet *, int, int, DataType, PostScript&);

  void	Print(FILE *fp);

  void	SetSizeX(PlotInfo& p, int th, int bh, int lv, int rv),
	SetSizePS(PlotInfo& p, int th, int bh, int lv, int rv);

  void	IncrementRow(int), DecrementColumn(int),
	IncrementColumn(int), DecrementRow(int),
	IncrementXYZPos(int), DecrementXYZPos(int);

  bool	AutoLabels;
  bool	AutoScale;
  bool	AutoTics;

  int	ticLength;

  struct axisInfo	xAxis, yAxis, zAxis;

  struct panelDims	dimsX, dimsPS;

private:
  static const float	cosFactor, sinFactor;

  void	drawLabels(PlotInfo& p),
	printLabels(PlotInfo& p, PostScript& pen),
	xTicsLabelsX(PlotInfo& p, bool labels),
	yTicsLabelsX(PlotInfo& p, bool labels),
	xTicsLabelsPS(PlotInfo& p, PostScript& pen, bool labels),
	yTicsLabelsPS(PlotInfo& p, PostScript& pen, bool labels),
	draw3dCube(Drawable surface, XPen& pen);

};	// END PANEL.H

#endif
