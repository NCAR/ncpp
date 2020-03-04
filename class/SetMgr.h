/*
-------------------------------------------------------------------------
OBJECT NAME:	SetMgr.h

FULL NAME:	Data Set Manager

TYPE:		

COPYRIGHT:	University Corporation for Atmospheric Research, 1997-2001
-------------------------------------------------------------------------
*/

#ifndef SETMGR_H
#define SETMGR_H

#include "define.h"

#include "DataSet.h"
#include "DataFile.h"
#include <raf/rafTime.h>

class Panel;

/* -------------------------------------------------------------------- */
class SetManager
{
public:
  friend void	AutoScaleAccum(SetManager&, Panel *),
		AutoScaleConc(SetManager&, Panel *),
		AutoScaleSurface(SetManager&, Panel *),
		AutoScaleVolume(SetManager&, Panel *);

	SetManager();

  void		Clear();

  size_t	NumberOfSets() const		{ return(numberSets); }

  int		AveragingRate() const		{ return(avRate); }
  void		SetAverageRate(int newRate);

  size_t	NumberRecords() const		{ return(nRecords); }
  void		SetNumberRecords(size_t newCnt);

  DataType	DataTypes() const		{ return(dataType); }
  void		SetDataTypes(DataType newDT);
  void		SetNormalize(NormType newN);
  NormType	GetNormalization() const	{ return(normType); }
  void		SetCompute(bool x);

  void		SetStartTime(FlightClock start);

  bool		Add(DataFile *file, Probe *prb);
  void		Delete(DataFile *file, Probe *prb);

  DataSet	*FirstSet()
    { return(numberSets == 0 ? (DataSet *)NULL : set[currentSet = 0]); }

  DataSet	*NextSet()
    { return(++currentSet < numberSets ? set[currentSet] : (DataSet *)NULL); }


  void	ReadCurrentSet();
  void	ReadAllSets();

  void	PageForward();
  void	PageBackward();

private:
  int		avRate;		// Averaging rate.
  size_t	nRecords;	// Number records to display.
  DataType	dataType;
  NormType	normType;

  FlightClock	currentTime;	// StartTime to use for new data.

  size_t	numberSets;
  size_t	currentSet;

  DataSet	*set[MAX_DATASETS];

  float		minAccum, maxAccum, minBin, maxBin;
  float		minConc, maxConc, minCell, maxCell;
  float		minSurf, maxSurf, minVol, maxVol;

  void		findMinMax(), setEndTime(size_t idx);

};	// END SETMGR.H

#endif
