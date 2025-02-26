/*
-------------------------------------------------------------------------
OBJECT NAME:	s100.cc

FULL NAME:	DMT modified FSSP-100 Class

DESCRIPTION:	

COPYRIGHT:	University Corporation for Atmospheric Research, 2000
-------------------------------------------------------------------------
*/

#include "s100.h"


/* -------------------------------------------------------------------- */
S100::S100(NcFile *file, NcVar &av, int zbo) : Probe100(file, av, zbo)
{
  NcVarAtt		attr;
  getFloatAttribute(_avar, "BeamDiameter", _beamDiameter, 0.19) || getFloatAttribute(_cvar, "BeamDiameter", _beamDiameter, 0.19);
  getFloatAttribute(_avar, "DepthOfField", _DOF, 3.05) || getFloatAttribute(_cvar, "DepthOfField", _DOF, 3.05);

  _range = 0;	// For FSSP, all other probes must be 0.

  for (size_t i = 0; i < _otherVars.size(); ++i)
    {
    if (_otherVars[i].getName().starts_with("REJAT"))
      _rejATIdx = i;

    if (_otherVars[i].getName().starts_with("OVFLW"))
      _oFlowIdx = i;
    }

}	/* END CONSTRUCTOR */

/* -------------------------------------------------------------------- */
void S100::ComputeConcentration(float *accum, float *conc, long countV[],
	const std::vector<float *> & otherVarData)
{
  int	i;
  size_t bin;
  float	*dia, *counts, *concentration, total_cnts;
  float	*tas, *oFlow, *rejAT, sampleArea;
  double vol;

  tas = otherVarData[_tasIdx];
  rejAT = otherVarData[_rejATIdx];
  oFlow = otherVarData[_oFlowIdx];

  sampleArea = _DOF * _beamDiameter;

  for (i = 0; i < countV[0] * countV[1]; ++i)
    {
    counts = &accum[i * VectorLength()];
    concentration = &conc[i * VectorLength()];

    total_cnts = 0.0;
    for (size_t j = FirstBin(); j < LastBin(); ++j)
      total_cnts += accum[j];

    vol = tas[i] / DataRate() * sampleArea;

    if (total_cnts > 0 && rejAT[i] > 0.0)
      vol *= total_cnts / (total_cnts + rejAT[i] + oFlow[i]);

    for (bin = FirstBin(); bin <= LastBin(); ++bin)
      _sampleVolume[bin] = (float)vol;

    dia = &_midPointDiam[_range << 4];

#define PLWC
#define DBZ

#include "pms1d_cv"

    otherVarData[_concIdx][i] = _totalConcen;
    otherVarData[_lwIdx][i] = _plwc;
    otherVarData[_dbarIdx][i] = _dbar;
    otherVarData[_dispIdx][i] = _disp;
    otherVarData[_dbzIdx][i] = _dbz;
    }

}	/* END COMPUTECONCENTRATION */

/* END S100.CC */
