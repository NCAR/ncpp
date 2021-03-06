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
SetManager::SetManager() : numberSets(0), currentSet(0)
{
avRate = 10;
nRecords = 1;
dataType = CONCENTRATION;

}	/* END CONTRUCTOR */

/* -------------------------------------------------------------------- */
void SetManager::Clear()
{
  for (size_t i = 0; i < numberSets; ++i)
    delete set[i];

  numberSets = 0;
  currentSet = 0;

}	/* END CLEAR */

/* -------------------------------------------------------------------- */
void SetManager::SetNumberRecords(size_t newCnt)
{
  nRecords = newCnt;

  for (size_t i = 0; i < numberSets; ++i)
    {
    set[i]->ResizeData(nRecords);
    setEndTime(i);
    }

  ReadAllSets();

}	/* END SETNUMBERRECORDS */

/* -------------------------------------------------------------------- */
void SetManager::SetStartTime(FlightClock newTime)
{
  currentTime = newTime;

  for (size_t i = 0; i < numberSets; ++i)
    {
    set[i]->startTime = currentTime;
    setEndTime(i);
    }

  ReadAllSets();

}	/* END SETSTARTTIME */

/* -------------------------------------------------------------------- */
void SetManager::SetAverageRate(int newRate)
{
  avRate = newRate;
  SetStartTime(currentTime);
  ReadAllSets();

}	/* END SETAVERAGERATE */

/* -------------------------------------------------------------------- */
void SetManager::SetDataTypes(DataType newDT)
{
  if (newDT & SURFACE || newDT & VOLUME)
    newDT |= CONCENTRATION;

  dataType = newDT;

  for (size_t i = 0; i < numberSets; ++i)
    set[i]->SetDataTypes(dataType);

  ReadAllSets();
  findMinMax();

}	/* END SETDATATYPES */

/* -------------------------------------------------------------------- */
void SetManager::SetNormalize(NormType n)
{
  normType = n;

  for (size_t i = 0; i < numberSets; ++i)
    set[i]->SetNormalize(normType);

  findMinMax();

}       /* END SETNORMALIZE */

/* -------------------------------------------------------------------- */
void SetManager::SetCompute(bool x)
{
  for (size_t i = 0; i < numberSets; ++i)
    set[i]->SetCompute(x);

  ReadAllSets();

}	/* END SETCOMPUTE */

/* -------------------------------------------------------------------- */
bool SetManager::Add(DataFile *file, Probe *prb)
{
  size_t idx = numberSets;

  // All sets must have same data rate, reject ones that don't match the 1st.
  if (numberSets > 0)
    {
    if (prb->DataRate() != set[0]->probe()->DataRate())
      {
      ErrorMsg("Data rate does not match other selected probes.");
      return(false);
      }
    }

  ++numberSets;

  set[idx] = new DataSet(file, prb, currentTime, nRecords, dataType, normType);
  setEndTime(idx);
  set[idx]->ReadData(nRecords, avRate);

  findMinMax();

  return(true);

}	/* END ADD */

/* -------------------------------------------------------------------- */
void SetManager::Delete(DataFile *file, Probe *prb)
{
  size_t i;

  for (i = 0; i < numberSets; ++i)
    if (file == set[i]->file() && prb == set[i]->probe())
      {
      delete set[i];
      --numberSets;
      break;
      }

  for (; i < numberSets; ++i)
    set[i] = set[i+1];

  findMinMax();

}	/* END DELETE */

/* -------------------------------------------------------------------- */
void SetManager::ReadCurrentSet()
{
  set[currentSet]->ReadData(nRecords, avRate);

  findMinMax();

}	/* END READCURRENTSET */

/* -------------------------------------------------------------------- */
void SetManager::ReadAllSets()
{
  for (size_t i = 0; i < numberSets; ++i)
    set[i]->ReadData(nRecords, avRate);

  findMinMax();

}	/* END READALLSETS */

/* -------------------------------------------------------------------- */
void SetManager::PageForward()
{
  currentTime += (nRecords * avRate) / FirstSet()->probe()->DataRate();

  for (size_t i = 0; i < numberSets; ++i)
    {
    set[i]->startTime += (nRecords * avRate) / FirstSet()->probe()->DataRate();
    set[i]->endTime = set[i]->startTime + ((nRecords * avRate) /
		FirstSet()->probe()->DataRate());
    set[i]->ReadData(nRecords, avRate);
    }

  findMinMax();

}	/* END PAGEFORWARD */

/* -------------------------------------------------------------------- */
void SetManager::PageBackward()
{
  currentTime -= (nRecords * avRate) / FirstSet()->probe()->DataRate();

  for (size_t i = 0; i < numberSets; ++i)
    {
    set[i]->startTime -= (nRecords * avRate) / FirstSet()->probe()->DataRate();
    set[i]->endTime = set[i]->startTime + ((nRecords * avRate) /
		FirstSet()->probe()->DataRate());
    set[i]->ReadData(nRecords, avRate);
    }

  findMinMax();

}	/* END PAGEBACKWARD */

/* -------------------------------------------------------------------- */
void SetManager::findMinMax()
{
  if (dataType & COUNTS)
    {
    if (numberSets == 0)
      {
      minBin = 0.0;
      maxBin = 16.0;
      minAccum = 0.0;
      maxAccum = 10.0;
      }
    else
      {
      minBin = 0;
      maxBin = set[0]->probe()->VectorLength();
      minAccum = set[0]->minAccum;
      maxAccum = set[0]->maxAccum;

      for (size_t i = 1; i < numberSets; ++i)
        {
        minAccum = std::min(minAccum, set[i]->minAccum);
        maxAccum = std::max(maxAccum, set[i]->maxAccum);

        maxBin = std::max(maxBin, (float)set[i]->probe()->VectorLength());
        }
      }
    }


  if (dataType & CONCENTRATION)
    {
    if (numberSets == 0)
      {
      minCell = 0.0;
      maxCell = 1.0;
      minConc = 0.0;
      maxConc = 10.0;
      }
    else
      {
      size_t	i;
      Probe	*prb = set[0]->probe();

      for (i = 0; prb->CellSize(i) == 0; ++i);
      minCell = prb->CellSize(i);

      for (i = prb->VectorLength()-1; prb->CellSize(i) == 0; --i);
      maxCell = prb->CellSize(i);

      for (i = 1; i < numberSets; ++i)
        {
        prb = set[i]->probe();

        minCell = std::min(minCell, prb->CellSize(0));
        maxCell = std::max(maxCell, prb->CellSize(prb->VectorLength()-1));
        }


      minConc = FLT_MAX;
      maxConc = -FLT_MAX;

      for (i = 0; i < numberSets; ++i)
        {
        if (set[i]->minConc > 0)
          minConc = std::min(minConc, set[i]->minConc);
        if (set[i]->maxConc > 0)
          maxConc = std::max(maxConc, set[i]->maxConc);
        }

      if (maxConc == -FLT_MAX)
        maxConc = 1.0;
      if (minConc == FLT_MAX)
        minConc = maxConc / 1000;
      }

    if (minCell == 0.0)
      minCell = 0.1;
    }


  if (dataType & SURFACE)
    {
    if (numberSets == 0)
      {
      minSurf = 0.0;
      maxSurf = 10.0;
      }
    else
      {
      minSurf = set[0]->minSurf;
      maxSurf = set[0]->maxSurf;

      for (size_t i = 1; i < numberSets; ++i)
        {
        minSurf = std::min(minSurf, set[i]->minSurf);
        maxSurf = std::max(maxSurf, set[i]->maxSurf);
        }
      }
    }


  if (dataType & VOLUME)
    {
    if (numberSets == 0)
      {
      minVol = 0.0;
      maxVol = 10.0;
      }
    else
      {
      minVol = set[0]->minVol;
      maxVol = set[0]->maxVol;

      for (size_t i = 1; i < numberSets; ++i)
        {
        minVol = std::min(minVol, set[i]->minVol);
        maxVol = std::max(maxVol, set[i]->maxVol);
        }
      }
    }

}	/* END FINDMINMAX */

/* -------------------------------------------------------------------- */
void SetManager::setEndTime(size_t idx)
{
  if (set[idx]->probe()->DataRate() == 1)
    set[idx]->endTime = set[idx]->startTime + (nRecords * avRate);
  else
    set[idx]->endTime = set[idx]->startTime +
				(nRecords / set[idx]->probe()->DataRate());

  if (set[idx]->endTime <= set[idx]->startTime)
    set[idx]->endTime = set[idx]->startTime + 1;

}	/* END SETENDTIME */

/* END SETMGR.CC */
