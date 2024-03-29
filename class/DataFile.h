/*
-------------------------------------------------------------------------
OBJECT NAME:	DataFile.h

FULL NAME:	Data File Class

COPYRIGHT:	University Corporation for Atmospheric Research, 1997-2007
-------------------------------------------------------------------------
*/

#ifndef DATAFILE_H
#define DATAFILE_H

#include "define.h"

#include "fssp.h"
#include "cdp.h"
#include "s100.h"
#include "s200.h"
#include "f300.h"
#include "pcasp.h"
#include "x260.h"
#include "x200.h"
#include "y200.h"
#include "2D.h"
#include "hvps.h"
#include "uhsas.h"
#include "hdc.h"

#include "raf/rafTime.h"


/* -------------------------------------------------------------------- */
class DataFile
{
public:
	DataFile(const char fName[]);
	~DataFile();

  const std::string&	FileName() const	{ return(fileName); }
  const std::string&	ProjectName() const	{ return(projName); }
  const std::string&	FlightNumber() const	{ return(flightNum); }
  const std::string&	FlightDate() const	{ return(flightDate); }

  FlightClock	StartTime()	const	{ return(startTime); }
  FlightClock	EndTime()	const	{ return(endTime); }

  size_t	NumberOfProbes() const	{ return(_nProbes); }

  bool  operator==(DataFile& rhs) { return(fileName == rhs.fileName); }
  bool  operator==(const DataFile& rhs) { return(fileName == rhs.fileName); }

  bool  isPreliminaryData()	{ return prelimData; }

  Probe		*probe[MAX_PROBES];

private:
  NcFile	*file;

  NcError	*err;

  std::string	fileName;
  std::string	projName, flightNum, flightDate;

  size_t	_nProbes;

  FlightClock	startTime, endTime;

  bool	validProbeName(const char target[]) const;

  bool  prelimData;

};	// END DATAFILE.H

#endif
