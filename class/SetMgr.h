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
#include "raf/rafTime.h"

class Panel;

/* -------------------------------------------------------------------- */
/**
 * Class to manage the DataSets that are being plotted.
 */
class SetManager
{
public:
  friend void	AutoScaleAccum(SetManager&, Panel *),
		AutoScaleConc(SetManager&, Panel *),
		AutoScaleSurface(SetManager&, Panel *),
		AutoScaleVolume(SetManager&, Panel *);

	SetManager();

  void		Clear();

  size_t	NumberOfSets() const		{ return(_numberSets); }

  int		AveragingRate() const		{ return(_avRate); }
  void		SetAverageRate(int newRate);

  size_t	NumberRecords() const		{ return(_nRecords); }
  void		SetNumberRecords(size_t newCnt);

  DataType	DataTypes() const		{ return(_dataType); }
  void		SetDataTypes(DataType newDT);
  void		SetNormalize(NormType newN);
  NormType	GetNormalization() const	{ return(_normType); }
  void		SetCompute(bool x);

  void		SetStartTime(FlightClock start);

  bool		Add(DataFile *file, Probe *prb);
  void		Delete(DataFile *file, Probe *prb);

  DataSet	*FirstSet()
    { return(_numberSets == 0 ? (DataSet *)NULL : set[_currentSet = 0]); }

  DataSet	*NextSet()
    { return(++_currentSet < _numberSets ? set[_currentSet] : (DataSet *)NULL); }


  void	ReadCurrentSet();
  void	ReadAllSets();

  void	PageForward();
  void	PageBackward();

private:
  int		_avRate;		// Averaging rate.
  size_t	_nRecords;	// Number records to display.
  DataType	_dataType;
  NormType	_normType;

  FlightClock	_currentTime;	// StartTime to use for new data.

  size_t	_numberSets;
  size_t	_currentSet;

  DataSet	*set[MAX_DATASETS];

  float		_minAccum, _maxAccum, _minBin, _maxBin;
  float		_minConc, _maxConc, _minCell, _maxCell;
  float		_minSurf, _maxSurf, _minVol, _maxVol;

  void		findMinMax(), setEndTime(size_t idx);

};	// END SETMGR.H

#endif
