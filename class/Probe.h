/*
-------------------------------------------------------------------------
OBJECT NAME:	Probe.h

FULL NAME:	Probe Information

TYPE:		Base class

COPYRIGHT:	University Corporation for Atmospheric Research, 1997-2007
-------------------------------------------------------------------------
*/

#ifndef PROBE_H
#define PROBE_H

#include "define.h"

#include <vector>
#include <ncFile.h>
#include <ncVar.h>
#include <ncDim.h>
#include <ncAtt.h>

using namespace netCDF;


/* -------------------------------------------------------------------- */
class Probe
{
public:
	//Probe(NcFile *file, NcVar *av, int zbo);
	Probe(NcFile *file, NcVar &av, int zbo);
	virtual ~Probe();

  enum	ProbeType	{ NoProbe, FSSP, F300, PCASP, X260, X200, Y200, MASP, X300, TWODC, TWODP, TWODS, HVPS, S100, S200, S300, RDMA, CLIMET, CMCA, CDP, UHSAS, SIDII, CAPS, PDI, CIP, PIP, HDC };

  std::string	Name() const	{ return(_name); }
  std::string	Units() const	{ return(_units); }
  std::string	Title() const	{ return(_units); }
  ProbeType	Type() const	{ return(_type); }

  size_t VectorLength() const	{ return(_vectorLength); }
  size_t DataRate() const	{ return(_dataRate); }
  float FillValue() const	{ return _missing_value; }

  size_t FirstBin() const	{ return(_firstBin); }
  size_t LastBin() const	{ return(_lastBin); }

  int ZeroBinOffset() const	{ return(_zeroBinOffset); }
  void SetZeroBinOffset(int z)	{ _zeroBinOffset = z; }

  bool	HaveConcentrations() const	{ return(_cvar.isNull()); }

  virtual float CellSize(int idx) const	{ return(_diameter[idx]); }
  virtual float BinWidth(int idx) const	{ return(_binWidth[idx]); }

  bool	ReadCounts(long start[], const long count[], float *data);
  bool	ReadConcen(long start[], const long count[], float *data);

  virtual void	UpdateCellDiams(const int first, const int last,
		const float *newDiams);

  virtual void ComputeConcentration(float *accum, float *conc, long countV[],
		const std::vector<float *> & otherVarData);

  virtual void SetRange(int)	{}

  size_t	nOtherVars()			{ return(_otherVars.size()); }
  const char	*OtherVarName(size_t idx)	{ return(_otherVars[idx].getName().c_str()); }

  bool	ReadOtherVar(size_t idx, long start[], const long count[], float *data);

  virtual int	SetEditWindow(Widget txt[]);
  virtual int	ApplyEditWindow(Widget txt[]);

  bool	operator==(Probe& rhs) { return(_name == rhs._name); }

  bool	operator==(const Probe& rhs) { return(_name == rhs._name); }

protected:
  void getAttributeValue(std::string attribute, std::string & retVal);
  void getAttributeValue(std::string attribute, size_t * retVal);
  void getAttributeValue(std::string attribute, float * retVal);
  void getAttributeValue(std::string attribute, std::vector<float> & retVal);
  virtual void	ComputeWidths();

  NcVar		_avar, _cvar;		// netCDF variable ID.
  std::vector<NcVar > _otherVars;	// Hskping & Derived Vars for action box

  ProbeType	_type;
  std::string	_name;
  std::string	_serialNum;
  std::string	_units;

  size_t _vectorLength;
  size_t _dataRate;
  size_t _firstBin, _lastBin;

  float		_missing_value;

  /* Files prior to 2022 had a zeroth bin (e.g. 31 instead of 30).  This will be
   * used as an offset to index with.  Set to 0 for new files, set to 1 for old
   * files.
   */
  int		_zeroBinOffset;

  std::vector<float> _diameter, _midPointDiam, _binWidth, _sampleVolume;

};	// END PROBE.H

#endif
