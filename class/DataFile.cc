/*
-------------------------------------------------------------------------
OBJECT NAME:	DataFile.cc

FULL NAME:	netCDF Data File Class

DESCRIPTION:	

COPYRIGHT:	University Corporation for Atmospheric Research, 1997-2013
-------------------------------------------------------------------------
*/

#include "DataFile.h"

#include <unistd.h>

#include <ncFile.h>
#include <ncDim.h>
#include <ncVar.h>
#include <ncAtt.h>
#include <ncGroupAtt.h>
//#include <ncType.h>
//#include <ncString.h>
//#include <exception> //error handling

/* Put into config file. */

// Add matching to enum in Probe.h, and ctor of Probe.cc
static const char *validProbeNames[] = {
	"AFSSP","AF300","APCAS","A260X","AASAS","A200X","A200Y","A300X",
	"AMASP","A1DC","A2DC","A1DP","A2DP","AS100","AS200","AS300",
	"ACDP", "ARDMA","ACLMT","ACMCA","AHVPS","AUHSAS","ASID","ACAPS",
	"APDI", "A2D3", "ACIP", "APIP", "AHDC",
	"A1DSH", "A1DSV", "A2DSA", "A2DSR", "A2DH", NULL };


/* -------------------------------------------------------------------- */
DataFile::DataFile(const char fName[]) : _fileName(fName), _nProbes(0)
{
  int		    zeroBinOffset = 1;	// Default to older files which have it.
  NcGroupAtt	    attr;


  // Open Input File
  _file = new netCDF::NcFile(fName, netCDF::NcFile::read);

  if (_file->isNull())
  {
    snprintf(buffer, BUFFSIZE, "Can't open %s.", fName);
    ErrorMsg(buffer);
    return;
  }


  attr = _file->getAtt("project");
  if (attr.isNull()){
    attr = (_file->getAtt("ProjectName"));
  }else if (! attr.isNull())
    _projName = attr.getName();

  attr = _file->getAtt("FlightNumber");
  if (! attr.isNull()){
    attr.getValues(&_flightNum);
  }

  attr = _file->getAtt("FlightDate");
  if (! attr.isNull())
    attr.getValues(&_flightDate);
  
  attr = _file->getAtt("SizeDistributionLegacyZeroBin");
  if (!attr.isNull())
  {
    std::string zeroAttr;
    attr.getValues(zeroAttr);
    if (zeroAttr.compare("no") == 0)
      zeroBinOffset = 0; 
  }

  attr = _file->getAtt("WARNING");
  if (attr.isNull())
    _prelimData = false;
  else
    _prelimData = true;

  attr = _file->getAtt("TimeInterval");
  if (!attr.isNull())
  {
    char ti[128];
    attr.getValues(ti);
    _startTime = ti; 
    _endTime = strchr(ti, '-')+1;
  }
  else
  {
    ErrorMsg("netCDF attribute TimeInterval not found, this could be a problem.");
  }


  // Bump up endTime if we have midnight roll-over.
  if (_endTime < _startTime)
    _endTime += 86400;

  /* Scan variables for PMS1D vectors.
   */
  std::multimap<std::string, NcVar> vars = _file->getVars();
  for (auto it = vars.begin(); it != vars.end(); ++it)
  {
    NcVar avar = it->second;

    if (avar.getName().compare("base_time") == 0 ||
        avar.getName().compare("time_offset") == 0)
      continue;

    if (avar.getDimCount() >= 3 && validProbeName(avar.getName().c_str()))
      {
      if (avar.getName().compare("AFSSP") == 0)
        probe[_nProbes++] = new FSSP(_file, avar, zeroBinOffset);
      else
      if (avar.getName().compare("AF300") == 0 ||
           avar.getName().compare("AS300") == 0)
        probe[_nProbes++] = new F300(_file, avar, zeroBinOffset);
      else
      if (avar.getName().compare("AASAS") == 0 ||
           avar.getName().compare("APCAS") == 0)
        probe[_nProbes++] = new PCASP(_file, avar, zeroBinOffset);
      else
      if (avar.getName().compare("AS100") == 0)
        probe[_nProbes++] = new S100(_file, avar, zeroBinOffset);
      else
      if (avar.getName().compare("ACDP") == 0)
        probe[_nProbes++] = new CDP(_file, avar, zeroBinOffset);
      else
      if (avar.getName().compare("AS200") == 0)
        probe[_nProbes++] = new S200(_file, avar, zeroBinOffset);
      else
      if (avar.getName().compare("AUHSAS") == 0)
        probe[_nProbes++] = new UHSAS(_file, avar, zeroBinOffset);
      else
      if (avar.getName().compare("AHDC") == 0)
        probe[_nProbes++] = new HDC(_file, avar, zeroBinOffset);
      else
      if (avar.getName().compare("A260X") == 0)
        probe[_nProbes++] = new X260(_file, avar, zeroBinOffset);
      else
      if (avar.getName().compare("AMASP") == 0)
        probe[_nProbes++] = new F300(_file, avar, zeroBinOffset);
      else
//      if ( avar.getName().compare("AHVPS") == 0)
//        probe[_nProbes++] = new HVPS(_file, avar, zeroBinOffset);
//      else
      if (avar.getName().compare("A200X") == 0)
        probe[_nProbes++] = new X200(_file, avar, zeroBinOffset);
      else
      if (avar.getName().compare("A200Y") == 0)
        probe[_nProbes++] = new Y200(_file, avar, zeroBinOffset);
      else
      if (avar.getName().compare("ACIP") == 0)
        probe[_nProbes++] = new TwoDCIP(_file, avar, zeroBinOffset);
      else
      if (avar.getName().compare("APIP") == 0)
        probe[_nProbes++] = new TwoDPIP(_file, avar, zeroBinOffset);
      else
      if (avar.getName().compare("A2DC") == 0 ||
          avar.getName().compare("A1DC") == 0)
        probe[_nProbes++] = new TwoDC(_file, avar, zeroBinOffset);
      else
      if (avar.getName().compare("A2DP") == 0 ||
          avar.getName().compare("A1DP") == 0)
        probe[_nProbes++] = new TwoDP(_file, avar, zeroBinOffset);
      else
      if (avar.getName().compare("A2DH") == 0 ||	// HVPS
          avar.getName().compare("A1DH") == 0)
        probe[_nProbes++] = new TwoDH(_file, avar, zeroBinOffset);
      else
      if (avar.getName().compare("A2D3") == 0 ||	// 3V-CPI
          avar.getName().compare("A1D3") == 0 ||
          avar.getName().compare("A1DS") == 0 ||
          avar.getName().compare("A2DS") == 0)
        probe[_nProbes++] = new TwoDS(_file, avar, zeroBinOffset);
      else
        probe[_nProbes++] = new Probe(_file, avar, zeroBinOffset);
      }
    }

}	/* END CONSTRUCTOR */

/* -------------------------------------------------------------------- */
DataFile::~DataFile()
{
  for (size_t i = 0; i < _nProbes; ++i)
    delete probe[i];

  delete _file;

}	/* END DESTRUCTOR */

/* -------------------------------------------------------------------- */
bool DataFile::validProbeName(const char target[]) const
{
  int	i;

  for (i = 0; validProbeNames[i]; ++i)
    if (strncmp(validProbeNames[i], target, strlen(validProbeNames[i])) == 0)
      return(true);

  return(false);

}	/* END VALIDPROBENAME */

/* END DATAFILE.CC */
