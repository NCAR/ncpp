/*
-------------------------------------------------------------------------
OBJECT NAME:	SetMgr.cc

FULL NAME:	Set Manager Class

DESCRIPTION:	

COPYRIGHT:	University Corporation for Atmospheric Research, 1997-8
-------------------------------------------------------------------------
*/

#include "SetMgr.h"

#include <algorithm>
#include <cfloat>

/* -------------------------------------------------------------------- */
SetManager::SetManager() :
	_avRate(10), _nRecords(1), _dataType(CONCENTRATION),
	_numberSets(0), _currentSet(0)
{

}	/* END CONTRUCTOR */

/* -------------------------------------------------------------------- */
void SetManager::Clear()
{
  for (size_t i = 0; i < _numberSets; ++i)
    delete set[i];

  _numberSets = 0;
  _currentSet = 0;

}	/* END CLEAR */

/* -------------------------------------------------------------------- */
void SetManager::SetNumberRecords(size_t newCnt)
{
  _nRecords = newCnt;

  for (size_t i = 0; i < _numberSets; ++i)
    {
    set[i]->ResizeData(_nRecords);
    setEndTime(i);
    }

  ReadAllSets();

}	/* END SETNUMBERRECORDS */

/* -------------------------------------------------------------------- */
void SetManager::SetStartTime(FlightClock newTime)
{
  _currentTime = newTime;

  for (size_t i = 0; i < _numberSets; ++i)
    {
    set[i]->startTime = _currentTime;
    setEndTime(i);
    }

  ReadAllSets();

}	/* END SETSTARTTIME */

/* -------------------------------------------------------------------- */
void SetManager::SetAverageRate(int newRate)
{
  _avRate = newRate;
  SetStartTime(_currentTime);
  ReadAllSets();

}	/* END SETAVERAGERATE */

/* -------------------------------------------------------------------- */
void SetManager::SetDataTypes(DataType newDT)
{
  if (newDT & SURFACE || newDT & VOLUME)
    newDT |= CONCENTRATION;

  _dataType = newDT;

  for (size_t i = 0; i < _numberSets; ++i)
    set[i]->SetDataTypes(_dataType);

  ReadAllSets();
  findMinMax();

}	/* END SETDATATYPES */

/* -------------------------------------------------------------------- */
void SetManager::SetNormalize(NormType n)
{
  _normType = n;

  for (size_t i = 0; i < _numberSets; ++i)
    set[i]->SetNormalize(_normType);

  findMinMax();

}       /* END SETNORMALIZE */

/* -------------------------------------------------------------------- */
void SetManager::SetCompute(bool x)
{
  for (size_t i = 0; i < _numberSets; ++i)
    set[i]->SetCompute(x);

  ReadAllSets();

}	/* END SETCOMPUTE */

/* -------------------------------------------------------------------- */
bool SetManager::Add(DataFile *file, Probe *prb)
{
  size_t idx = _numberSets;

  // All sets must have same data rate, reject ones that don't match the 1st.
  if (_numberSets > 0)
    {
    if (prb->DataRate() != set[0]->probe()->DataRate())
      {
      ErrorMsg("Data rate does not match other selected probes.");
      return(false);
      }
    }

  ++_numberSets;

  set[idx] = new DataSet(file, prb, _currentTime, _nRecords, _dataType, _normType);
  setEndTime(idx);
  set[idx]->ReadData(_nRecords, _avRate);

  findMinMax();

  return(true);

}	/* END ADD */

/* -------------------------------------------------------------------- */
void SetManager::Delete(DataFile *file, Probe *prb)
{
  size_t i;

  for (i = 0; i < _numberSets; ++i)
    if (file == set[i]->file() && prb == set[i]->probe())
      {
      delete set[i];
      --_numberSets;
      break;
      }

  for (; i < _numberSets; ++i)
    set[i] = set[i+1];

  findMinMax();

}	/* END DELETE */

/* -------------------------------------------------------------------- */
void SetManager::ReadCurrentSet()
{
  set[_currentSet]->ReadData(_nRecords, _avRate);

  findMinMax();

}	/* END READCURRENTSET */

/* -------------------------------------------------------------------- */
void SetManager::ReadAllSets()
{
  for (size_t i = 0; i < _numberSets; ++i)
    set[i]->ReadData(_nRecords, _avRate);

  findMinMax();

}	/* END READALLSETS */

/* -------------------------------------------------------------------- */
void SetManager::PageForward()
{
  _currentTime += (_nRecords * _avRate) / FirstSet()->probe()->DataRate();

  for (size_t i = 0; i < _numberSets; ++i)
    {
    set[i]->startTime += (_nRecords * _avRate) / FirstSet()->probe()->DataRate();
    set[i]->endTime = set[i]->startTime + ((_nRecords * _avRate) /
		FirstSet()->probe()->DataRate());
    set[i]->ReadData(_nRecords, _avRate);
    }

  findMinMax();

}	/* END PAGEFORWARD */

/* -------------------------------------------------------------------- */
void SetManager::PageBackward()
{
  _currentTime -= (_nRecords * _avRate) / FirstSet()->probe()->DataRate();

  for (size_t i = 0; i < _numberSets; ++i)
    {
    set[i]->startTime -= (_nRecords * _avRate) / FirstSet()->probe()->DataRate();
    set[i]->endTime = set[i]->startTime + ((_nRecords * _avRate) /
		FirstSet()->probe()->DataRate());
    set[i]->ReadData(_nRecords, _avRate);
    }

  findMinMax();

}	/* END PAGEBACKWARD */

/* -------------------------------------------------------------------- */
void SetManager::findMinMax()
{
  if (_dataType & COUNTS)
    {
    if (_numberSets == 0)
      {
      _minBin = 0.0;
      _maxBin = 16.0;
      _minAccum = 0.0;
      _maxAccum = 10.0;
      }
    else
      {
      _minBin = 0;
      _maxBin = set[0]->probe()->VectorLength();
      _minAccum = set[0]->minAccum;
      _maxAccum = set[0]->maxAccum;

      for (size_t i = 1; i < _numberSets; ++i)
        {
        _minAccum = std::min(_minAccum, set[i]->minAccum);
        _maxAccum = std::max(_maxAccum, set[i]->maxAccum);

        _maxBin = std::max(_maxBin, (float)set[i]->probe()->VectorLength());
        }
      }
    }


  if (_dataType & CONCENTRATION)
    {
    if (_numberSets == 0)
      {
      _minCell = 0.0;
      _maxCell = 1.0;
      _minConc = 0.0;
      _maxConc = 10.0;
      }
    else
      {
      size_t	i;
      Probe	*prb = set[0]->probe();

      for (i = 0; prb->CellSize(i) == 0; ++i);
      _minCell = prb->CellSize(i);

      for (i = prb->VectorLength()-1; prb->CellSize(i) == 0; --i);
      _maxCell = prb->CellSize(i);

      for (i = 1; i < _numberSets; ++i)
        {
        prb = set[i]->probe();

        _minCell = std::min(_minCell, prb->CellSize(0));
        _maxCell = std::max(_maxCell, prb->CellSize(prb->VectorLength()-1));
        }


      _minConc = FLT_MAX;
      _maxConc = -FLT_MAX;

      for (i = 0; i < _numberSets; ++i)
        {
        if (set[i]->minConc > 0)
          _minConc = std::min(_minConc, set[i]->minConc);
        if (set[i]->maxConc > 0)
          _maxConc = std::max(_maxConc, set[i]->maxConc);
        }

      if (_maxConc == -FLT_MAX)
        _maxConc = 1.0;
      if (_minConc == FLT_MAX)
        _minConc = _maxConc / 1000;
      }

    if (_minCell == 0.0)
      _minCell = 0.1;
    }


  if (_dataType & SURFACE)
    {
    if (_numberSets == 0)
      {
      _minSurf = 0.0;
      _maxSurf = 10.0;
      }
    else
      {
      _minSurf = set[0]->minSurf;
      _maxSurf = set[0]->maxSurf;

      for (size_t i = 1; i < _numberSets; ++i)
        {
        _minSurf = std::min(_minSurf, set[i]->minSurf);
        _maxSurf = std::max(_maxSurf, set[i]->maxSurf);
        }
      }
    }


  if (_dataType & VOLUME)
    {
    if (_numberSets == 0)
      {
      _minVol = 0.0;
      _maxVol = 10.0;
      }
    else
      {
      _minVol = set[0]->minVol;
      _maxVol = set[0]->maxVol;

      for (size_t i = 1; i < _numberSets; ++i)
        {
        _minVol = std::min(_minVol, set[i]->minVol);
        _maxVol = std::max(_maxVol, set[i]->maxVol);
        }
      }
    }

}	/* END FINDMINMAX */

/* -------------------------------------------------------------------- */
void SetManager::setEndTime(size_t idx)
{
  if (set[idx]->probe()->DataRate() == 1)
    set[idx]->endTime = set[idx]->startTime + (_nRecords * _avRate);
  else
    set[idx]->endTime = set[idx]->startTime +
				(_nRecords / set[idx]->probe()->DataRate());

  if (set[idx]->endTime <= set[idx]->startTime)
    set[idx]->endTime = set[idx]->startTime + 1;

}	/* END SETENDTIME */

/* END SETMGR.CC */
