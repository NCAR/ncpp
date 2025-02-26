/*
-------------------------------------------------------------------------
OBJECT NAME:	autoscale.c

FULL NAME:	Friend functions to move min/max from SetMgr to Panel

ENTRY POINTS:	AutoScaleAccum()
		AutoScaleConc()
		AutoScaleSurface()
		AutoScaleVolume()

DESCRIPTION:	

COPYRIGHT:	University Corporation for Atmospheric Research, 1997
-------------------------------------------------------------------------
*/

#include "define.h"

#include "SetMgr.h"
#include "Panel.h"

//using namespace std;

/* -------------------------------------------------------------------- */
void AutoScaleAccum(SetManager& sets, Panel *panel)
{
  if (panel->AutoScale)
    {
    panel->xAxis.min = panel->xAxis.logScale ? 1.0 : sets._minBin;
    panel->xAxis.max = panel->xAxis.logScale ? 100.0 : sets._maxBin;

    panel->yAxis.min = panel->yAxis.logScale ? 1.0 : 0.0;

    if (sets._maxAccum > 0)
      panel->yAxis.max = pow(10.0, ceil(log10((double)sets._maxAccum)));

    if (panel->yAxis.min == panel->yAxis.max)
      panel->yAxis.max += 1.0;
    }

}	/* END AUTOSCALE */

/* -------------------------------------------------------------------- */
void AutoScaleConc(SetManager& sets, Panel *panel)
{
  if (!panel->AutoScale)
    return;

  if (panel->xAxis.logScale)
    {
    panel->xAxis.min = pow(10.0, floor(log10(sets._minCell)));
    panel->xAxis.max = pow(10.0, ceil(log10(sets._maxCell)));
    }
  else
    {
    panel->xAxis.min = 0.0;
    panel->xAxis.max = sets._maxCell;
    }

  if (panel->yAxis.logScale)
    {
    if (sets._maxConc <= 0.0)
      panel->yAxis.max = 1.0;
    else
      panel->yAxis.max = pow(10.0, ceil(log10(sets._maxConc)));

    if (sets._minConc <= 0.0)
      panel->yAxis.min = panel->yAxis.max / 10000;	// 5 decades less than max.
    else
      panel->yAxis.min = pow(10.0, floor(log10(sets._minConc)));
    }
  else
    {
    panel->yAxis.min = 0.0;
    panel->yAxis.max = sets._maxConc;
    }

  if (sets._maxConc == 0.0)
    panel->yAxis.max = 1.0;

  if (panel->yAxis.min == panel->yAxis.max)
    panel->yAxis.max += 10.0;

}	/* END AUTOSCALE */

/* -------------------------------------------------------------------- */
void AutoScaleSurface(SetManager& sets, Panel *panel)
{
  if (!panel->AutoScale)
    return;

  if (panel->xAxis.logScale)
    {
    panel->xAxis.min = pow(10.0, floor(log10(sets._minCell)));
    panel->xAxis.max = pow(10.0, ceil(log10(sets._maxCell)));
    }
  else
    {
    panel->xAxis.min = 0.0;
    panel->xAxis.max = sets._maxCell;
    }

  if (panel->yAxis.logScale)
    {
    if (sets._minConc <= 0.0)
      panel->yAxis.min = 0.01;
    else
      panel->yAxis.min = pow(10.0, floor(log10(sets._minSurf)));
    panel->yAxis.max = pow(10.0, ceil(log10(sets._maxSurf)));
    }
  else
    {
    panel->yAxis.min = 0.0;
    panel->yAxis.max = sets._maxSurf;
    }

  if (sets._maxSurf == 0.0)
    panel->yAxis.max = 10.0;

  if (panel->yAxis.min == panel->yAxis.max)
    panel->yAxis.max += 10.0;

}	/* END AUTOSCALE */

/* -------------------------------------------------------------------- */
void AutoScaleVolume(SetManager& sets, Panel *panel)
{
  if (!panel->AutoScale)
    return;

  if (panel->xAxis.logScale)
    {
    panel->xAxis.min = pow(10.0, floor(log10(sets._minCell)));
    panel->xAxis.max = pow(10.0, ceil(log10(sets._maxCell)));
    }
  else
    {
    if (sets._minConc <= 0.0)
      panel->yAxis.min = 0.01;
    else
      panel->yAxis.min = pow(10.0, floor(log10(sets._minVol)));
    panel->xAxis.max = sets._maxCell;
    }

  if (panel->yAxis.logScale)
    {
    panel->yAxis.min = 0.01;
    panel->yAxis.max = pow(10.0, ceil(log10(sets._maxVol)));
    }
  else
    {
    panel->yAxis.min = 0.0;
    panel->yAxis.max = sets._maxVol;
    }

  if (sets._maxVol == 0.0)
    panel->yAxis.max = 10.0;

  if (panel->yAxis.min == panel->yAxis.max)
    panel->yAxis.max += 10.0;

}	/* END AUTOSCALE */

/* AUTOSCALE.CC */
