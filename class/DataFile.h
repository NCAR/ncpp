/*
-------------------------------------------------------------------------
OBJECT NAME:	DataFile.h

FULL NAME:	netCDF Data File Class

COPYRIGHT:	University Corporation for Atmospheric Research, 1997-2025
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

class NcFile;

/* -------------------------------------------------------------------- */
/**
 * Class to hold information about an open file.  This includes a list of
 * Probes.
 */
class DataFile
{
public:
	DataFile(const char fName[]);
	~DataFile();

  const std::string&	FileName() const	{ return(_fileName); }
  const std::string&	ProjectName() const	{ return(_projName); }
  const std::string&	FlightNumber() const	{ return(_flightNum); }
  const std::string&	FlightDate() const	{ return(_flightDate); }

  FlightClock	StartTime()	const	{ return(_startTime); }
  FlightClock	EndTime()	const	{ return(_endTime); }

  size_t	NumberOfProbes() const	{ return(_nProbes); }

  bool  operator==(DataFile& rhs) { return(_fileName == rhs._fileName); }
  bool  operator==(const DataFile& rhs) { return(_fileName == rhs._fileName); }

  /**
   * The netCDF file has a global attirbute marking it as prelininary data.
   * @returns true/false if it was found.
   */
  bool  isPreliminaryData()	{ return _prelimData; }

  /// List of Probes found in the file.
  Probe		*probe[MAX_PROBES];

private:
  netCDF::NcFile	*_file;

  std::string	_fileName;
  std::string	_projName, _flightNum, _flightDate;

  size_t	_nProbes;

  FlightClock	_startTime, _endTime;

  /**
   * ncpp only works against a fixed set of Probe variable names.  This method
   * validates the name against a fixed list.
   * See list in DataFile.cc
   */
  bool	validProbeName(const char target[]) const;

  /// Read netCDF string attributes and make sure properly null terminated.
  void getStringAttribute(const netCDF::NcGroupAtt attr, std::string& attName);

  bool  _prelimData;

};	// END DATAFILE.H

#endif
