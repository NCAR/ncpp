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
#include <string>
#include <netcdf>

using namespace netCDF;


/* -------------------------------------------------------------------- */
/**
 * The base class for all probes.  Contains all metadata and methods to read
 * the data.
 */
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

//@{
  /// Return start and last of the size-distribution to display.
  size_t FirstBin() const	{ return(_firstBin); }
  size_t LastBin() const	{ return(_lastBin); }
//@}
//@{
  /// If the file has the legacy (pre 2022) zeroth bin, use an offset of one.
  int ZeroBinOffset() const	{ return(_zeroBinOffset); }
  void SetZeroBinOffset(int z)	{ _zeroBinOffset = z; }
//@}

  /// Do we have a matching concentration to a found counts variable.
  bool	HaveConcentrations() const	{ return(!_cvar.isNull()); }

  virtual float CellSize(int idx) const	{ return(_diameter[idx]); }
  virtual float BinWidth(int idx) const	{ return(_binWidth[idx]); }

  /// Read the raw counts data from the netCDF File.  The "A" var
  bool	ReadCounts(long start[], const long count[], float *data);

  /// Read the concentration data from the netCDF File.  The "C" var
  bool	ReadConcen(long start[], const long count[], float *data);

  virtual void	UpdateCellDiams(const int first, const int last,
		const float *newDiams);


  /**
   * Compute concentrations and otherVars instead of reading them from the
   * netCDF file.
   */
  virtual void ComputeConcentration(float *accum, float *conc, long countV[],
		const std::vector<float *> & otherVarData);

  /**
   * Appears unused.  The FSSP / S100 has four size ranges, we've only ever
   * used the first.
   */
  virtual void SetRange(int)	{}

//@{
  /// Number of ancillary variables.
  size_t	nOtherVars()			{ return(_otherVars.size()); }
/// @TODO this returning a warning on clang "returns temporary data"
  /// Retrieve a specific ancillary variable name
  const char	*OtherVarName(size_t idx)	{ return(_otherVars[idx].getName().c_str()); }

  /// Read ancillary variable data from the netCDF file.
  bool	ReadOtherVar(size_t idx, long start[], const long count[], float *data);
//@}

  virtual int	SetEditWindow(Widget txt[]);
  virtual int	ApplyEditWindow(Widget txt[]);

  bool	operator==(Probe& rhs) { return(_name == rhs._name); }

  bool	operator==(const Probe& rhs) { return(_name == rhs._name); }

protected:
//@{
  /**
   * Methods to retrieve netCDF attributes of various data types.  These will trap
   * any exceptions that the netCDF API will throw.
   *
   * @param var the variable to get the attribute from
   * @param target the attribute name to get
   * @param output the variable to place the attribute, this is the return data
   * @param defaultValue is the value to use if the attribute does not exist
   * @returns true/false as to success of reading attribute (i.e. did it exist)
   */
  bool getStringAttribute(NcVar& var, const char target[], std::string& output);
  bool getIntAttribute(NcVar& var, const char target[], int& output, int defaultValue = 0);
  bool getFloatAttribute(NcVar& var, const char target[], float& output, float defaultValue = 0.0);
  bool getVectorOfFloatAttributes(NcVar& var, const char target[], std::vector<float>& output);
//@}
  /// Compute bin widths.
  virtual void	ComputeWidths();

  /// Raw histogram variable in the netCDF file.
  NcVar		_avar;
  /// Concentrations size-distribution variable in the netCDF file.
  NcVar		_cvar;

  /// netCDF ancillary and derived variables for this probe.
  std::vector<NcVar > _otherVars;

  ProbeType	_type;
  std::string  _name;
  std::string  _serialNum;
  std::string  _units;

  size_t _vectorLength;
  size_t _dataRate;
  size_t _firstBin, _lastBin;

  float		_missing_value;

  /**
   * Files prior to 2022 had a zeroth bin (e.g. 31 instead of 30).  This will be
   * used as an offset to index with.  Set to 0 for new files, set to 1 for old
   * files.
   */
  int		_zeroBinOffset;

  std::vector<float> _diameter, _midPointDiam, _binWidth, _sampleVolume;

};	// END PROBE.H

#endif
