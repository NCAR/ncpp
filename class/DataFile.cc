/*
-------------------------------------------------------------------------
OBJECT NAME:	DataFile.cc

FULL NAME:	netCDF Data File Class

COPYRIGHT:	University Corporation for Atmospheric Research, 1997-2025
-------------------------------------------------------------------------
*/

#include "DataFile.h"

#include <unistd.h>

#include <ncFile.h>
#include <ncDim.h>
#include <ncVar.h>
#include <ncAtt.h>
#include <ncGroupAtt.h>


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

 _nRecords = _file->getDim("Time").getSize();

  // Read in global attributes.

  attr = _file->getAtt("project");
  if (attr.isNull()){
    attr = (_file->getAtt("ProjectName"));
  }else if (!attr.isNull()){
    getStringAttribute(attr, _projName);
  }

  attr = _file->getAtt("FlightNumber");
  if (! attr.isNull()){
    getStringAttribute(attr, _flightNum);
  }

  attr = _file->getAtt("FlightDate");
  if (! attr.isNull())
    getStringAttribute(attr, _flightDate);

  // This will really only show up in post-2022 files.
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


  /* Scan netCDF variable list for probe raw data histogram.  At this time ncpp
   * expects both the raw data histogram and the concentration
   * size-distrobution histogram.  e.g. ACDP & CCDP for a CDP probe.
   * If you find the raw histogram, go ahead and create a Probe The Probe
   * constructor will look for the concentration variable.
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
      if (avar.getName().starts_with("AFSSP") == true)
        probe[_nProbes++] = new FSSP(_file, avar, zeroBinOffset);
      else
      if (avar.getName().starts_with("AF300") == true ||	// F300
           avar.getName().starts_with("AS300") == true)		// DMT upgraded F300
        probe[_nProbes++] = new F300(_file, avar, zeroBinOffset);
      else
      if (avar.getName().starts_with("AASAS") == true ||
           avar.getName().starts_with("APCAS") == true)
        probe[_nProbes++] = new PCASP(_file, avar, zeroBinOffset);
      else
      if (avar.getName().starts_with("AS100") == true)	// DMT upgraded FSSP
        probe[_nProbes++] = new S100(_file, avar, zeroBinOffset);
      else
      if (avar.getName().starts_with("ACDP") == true)
        probe[_nProbes++] = new CDP(_file, avar, zeroBinOffset);
      else
      if (avar.getName().starts_with("AS200") == true)	// DMT upgraded PCASP
        probe[_nProbes++] = new S200(_file, avar, zeroBinOffset);
      else
      if (avar.getName().starts_with("AUHSAS") == true)
        probe[_nProbes++] = new UHSAS(_file, avar, zeroBinOffset);
      else
      if (avar.getName().starts_with("AHDC") == true)	// I don't know.  Did UWyo add this?
        probe[_nProbes++] = new HDC(_file, avar, zeroBinOffset);
      else
      if (avar.getName().starts_with("A260X") == true)
        probe[_nProbes++] = new X260(_file, avar, zeroBinOffset);
      else
      if (avar.getName().starts_with("AMASP") == true)	// Briefly, around 2000.  INDOEX era.
        probe[_nProbes++] = new F300(_file, avar, zeroBinOffset);
      else
//  I believe this is old, 1990's, HVPS.  Which we didn't really use.
//      if ( avar.getName().starts_with("AHVPS") == true)
//        probe[_nProbes++] = new HVPS(_file, avar, zeroBinOffset);
//      else
      if (avar.getName().starts_with("A200X") == true)	// Doubt we've flow one
        probe[_nProbes++] = new X200(_file, avar, zeroBinOffset);
      else
      if (avar.getName().starts_with("A200Y") == true)	// Doubt we've flow one
        probe[_nProbes++] = new Y200(_file, avar, zeroBinOffset);
      else
      if (avar.getName().starts_with("ACIP") == true)	// DMT CIP
        probe[_nProbes++] = new TwoDCIP(_file, avar, zeroBinOffset);
      else
      if (avar.getName().starts_with("APIP") == true)	// DMT PIP
        probe[_nProbes++] = new TwoDPIP(_file, avar, zeroBinOffset);
      else
      if (avar.getName().starts_with("A2DC") == true ||	// 2DC using center-in algo (process2d)
          avar.getName().starts_with("A1DC") == true)	// 2DC using entire-in algo (nimbus)
        probe[_nProbes++] = new TwoDC(_file, avar, zeroBinOffset);
      else
      if (avar.getName().starts_with("A2DP") == true ||
          avar.getName().starts_with("A1DP") == true)
        probe[_nProbes++] = new TwoDP(_file, avar, zeroBinOffset);
      else
      if (avar.getName().starts_with("A2DH") == true ||	// HVPS (center-in)
          avar.getName().starts_with("A1DH") == true)	// HVPS (entire-in)
        probe[_nProbes++] = new TwoDH(_file, avar, zeroBinOffset);
      else
      if (avar.getName().starts_with("A2D3") == true ||	// SPEC 3V-CPI
          avar.getName().starts_with("A1D3") == true ||
          avar.getName().starts_with("A1DS") == true ||
          avar.getName().starts_with("A2DS") == true)	// SPEC 2DS
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
void DataFile::getStringAttribute(const netCDF::NcGroupAtt attr, std::string& attName)
{
  size_t len = attr.getAttLength();
  std::vector<char> buffer(len + 1);
  attr.getValues(buffer.data());
  buffer[len] = '\0';
  attName = std::string(buffer.data());

}       /* END FORMATATTRIBUTE */
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
