/*
-------------------------------------------------------------------------
OBJECT NAME:	2D.cc

FULL NAME:	2D Class

DESCRIPTION:	Probe classes for 2DC, 2DP, and 2DS/3V-CPI.

COPYRIGHT:	University Corporation for Atmospheric Research, 2000-2013
-------------------------------------------------------------------------
*/

#include "2D.h"


/* -------------------------------------------------------------------- */
TwoDS::TwoDS(NcFile *file, NcVar &av, int zbo) : TwoD(file, av, zbo)
{
  _dof_const = 5.13;

  if (_resolution == 0)
    _resolution = 0.010;
  if (_armDistance == 0)
    _armDistance = 50.8;
}

/* -------------------------------------------------------------------- */
TwoDH::TwoDH(NcFile *file, NcVar &av, int zbo) : TwoD(file, av, zbo)
{
  _dof_const = 8.0;

  if (_resolution == 0)
    _resolution = 0.150;
  if (_armDistance == 0)
    _armDistance = 162.5;
}

/* -------------------------------------------------------------------- */
TwoDCIP::TwoDCIP(NcFile *file, NcVar &av, int zbo) : TwoD(file, av, zbo)
{
  if (_resolution == 0)
    _resolution = 0.025;
  if (_armDistance == 0)
    _armDistance = 70;
}

/* -------------------------------------------------------------------- */
TwoDPIP::TwoDPIP(NcFile *file, NcVar &av, int zbo) : TwoD(file, av, zbo)
{
  if (_resolution == 0)
    _resolution = 0.1;
  if (_armDistance == 0)
    _armDistance = 70;
}

/* -------------------------------------------------------------------- */
TwoDC::TwoDC(NcFile *file, NcVar &av, int zbo) : TwoD(file, av, zbo)
{
  if (_resolution == 0)
    _resolution = 0.025;
  if (_armDistance == 0)
    _armDistance = 61;
}

/* -------------------------------------------------------------------- */
TwoDP::TwoDP(NcFile *file, NcVar &av, int zbo) : TwoD(file, av, zbo)
{
  if (_resolution == 0)
    _resolution = 0.2;
  if (_armDistance == 0)
    _armDistance = 261;
}

/* -------------------------------------------------------------------- */
TwoD::TwoD(NcFile *file, NcVar &av, int zbo) : Probe200(file, av, zbo)
{
  getFloatAttribute(_avar, "Resolution", _resolution);
  getFloatAttribute(_avar, "ArmDistance", _armDistance);

  _resolution /= 1000;

  ComputeWidths();

  for (size_t i = 0; i < _otherVars.size(); ++i)
    {
    // Search here.  Probe200 search turns up shado-or conc.
    if (_otherVars[i].getName().starts_with("CONC1D") ||
        _otherVars[i].getName().starts_with("CONC2D"))
      _concIdx = i;
    }

}	/* END CONSTRUCTOR */

/* -------------------------------------------------------------------- */
void TwoD::ComputeConcentration(float *accum, float *conc, long countV[],
	const std::vector<float *> & otherVarData)
{
  size_t bin;
  int	time;
  std::vector<float> dia;
  float	*counts, *concentration;
  float	*tas, tasx;

  tas = otherVarData[_tasIdx];

  for (time = 0; time < countV[0] * countV[1]; ++time)
    {
    counts = &accum[time * VectorLength()];
    concentration = &conc[time * VectorLength()];

    tasx = tas[time] / DataRate();

    for (bin = FirstBin(); bin <= LastBin(); ++bin)
      {
      _sampleVolume[bin] = tasx * (_dof[bin] * _esw[bin]) * 0.001;
      if (_deadTimeIdx >= 0)
        _sampleVolume[bin] *= (((float)1000 - otherVarData[_deadTimeIdx][time]) / 1000);
      }

    dia = _midPointDiam;

#define PLWC
#define DBZ

#include "pms1d_cv"

    otherVarData[_concIdx][time] = _totalConcen;
    otherVarData[_lwIdx][time] = _plwc;
    otherVarData[_dbarIdx][time] = _dbar;
    otherVarData[_dispIdx][time] = _disp;
    otherVarData[_dbzIdx][time] = _dbz;
    }

}	/* END COMPUTECONCENTRATION */

/* END 2D.CC */
