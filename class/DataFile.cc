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
  }else if (!attr.isNull()){
    formatAttribute(attr, _projName);
  }

  attr = _file->getAtt("FlightNumber");
  if (! attr.isNull()){
    formatAttribute(attr, _flightNum);
  }

  attr = _file->getAtt("FlightDate");
  if (! attr.isNull())
    formatAttribute(attr, _flightDate);
  
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

    if (avar.getName().starts_with("base_time") == 0 ||
        avar.getName().starts_with("time_offset") == 0)
      continue;

    if (avar.getDimCount() >= 3 && validProbeName(avar.getName().c_str()))
      {
      if (avar.getName().starts_with("AFSSP") == 0)
        probe[_nProbes++] = new FSSP(_file, avar, zeroBinOffset);
      else
      if (avar.getName().starts_with("AF300") == 0 ||
           avar.getName().starts_with("AS300") == 0)
        probe[_nProbes++] = new F300(_file, avar, zeroBinOffset);
      else
      if (avar.getName().starts_with("AASAS") == 0 ||
           avar.getName().starts_with("APCAS") == 0)
        probe[_nProbes++] = new PCASP(_file, avar, zeroBinOffset);
      else
      if (avar.getName().starts_with("AS100") == 0)
        probe[_nProbes++] = new S100(_file, avar, zeroBinOffset);
      else
      if (avar.getName().starts_with("ACDP") == 0)
        probe[_nProbes++] = new CDP(_file, avar, zeroBinOffset);
      else
      if (avar.getName().starts_with("AS200") == 0)
        probe[_nProbes++] = new S200(_file, avar, zeroBinOffset);
      else
      if (avar.getName().starts_with("AUHSAS") == 0)
        probe[_nProbes++] = new UHSAS(_file, avar, zeroBinOffset);
      else
      if (avar.getName().starts_with("AHDC") == 0)
        probe[_nProbes++] = new HDC(_file, avar, zeroBinOffset);
      else
      if (avar.getName().starts_with("A260X") == 0)
        probe[_nProbes++] = new X260(_file, avar, zeroBinOffset);
      else
      if (avar.getName().starts_with("AMASP") == 0)
        probe[_nProbes++] = new F300(_file, avar, zeroBinOffset);
      else
//      if ( avar.getName().starts_with("AHVPS") == 0)
//        probe[_nProbes++] = new HVPS(_file, avar, zeroBinOffset);
//      else
      if (avar.getName().starts_with("A200X") == 0)
        probe[_nProbes++] = new X200(_file, avar, zeroBinOffset);
      else
      if (avar.getName().starts_with("A200Y") == 0)
        probe[_nProbes++] = new Y200(_file, avar, zeroBinOffset);
      else
      if (avar.getName().starts_with("ACIP") == 0)
        probe[_nProbes++] = new TwoDCIP(_file, avar, zeroBinOffset);
      else
      if (avar.getName().starts_with("APIP") == 0)
        probe[_nProbes++] = new TwoDPIP(_file, avar, zeroBinOffset);
      else
      if (avar.getName().starts_with("A2DC") == 0 ||
          avar.getName().starts_with("A1DC") == 0)
        probe[_nProbes++] = new TwoDC(_file, avar, zeroBinOffset);
      else
      if (avar.getName().starts_with("A2DP") == 0 ||
          avar.getName().starts_with("A1DP") == 0)
        probe[_nProbes++] = new TwoDP(_file, avar, zeroBinOffset);
      else
      if (avar.getName().starts_with("A2DH") == 0 ||	// HVPS
          avar.getName().starts_with("A1DH") == 0)
        probe[_nProbes++] = new TwoDH(_file, avar, zeroBinOffset);
      else
      if (avar.getName().starts_with("A2D3") == 0 ||	// 3V-CPI
          avar.getName().starts_with("A1D3") == 0 ||
          avar.getName().starts_with("A1DS") == 0 ||
          avar.getName().starts_with("A2DS") == 0)
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
void DataFile::formatAttribute(const netCDF::NcGroupAtt attr, std::string& attName)
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
