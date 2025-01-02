/*
-------------------------------------------------------------------------
OBJECT NAME:	cdp.cc

FULL NAME:	CDP Class

DESCRIPTION:	

COPYRIGHT:	University Corporation for Atmospheric Research, 1999-2009
-------------------------------------------------------------------------
*/

#include "cdp.h"


/* -------------------------------------------------------------------- */
CDP::CDP(NcFile *file, NcVar &av, int zbo) : Probe100(file, av, zbo)
{
  NcVarAtt attr;
printf("CDP::ctor\n");
  if (!(_cvar.getAtt("BeamDiameter")).isNull() || !(_avar.getAtt("BeamDiameter")).isNull())
    attr.getValues(&_beamDiameter);
  else
    _beamDiameter = 0.2;

  if (!(_cvar.getAtt("DepthOfField")).isNull() || !(_avar.getAtt("DepthOfField")).isNull())
    attr.getValues(&_DOF);
  else
    _DOF = 1.2;

}	/* END CONSTRUCTOR */

/* -------------------------------------------------------------------- */
void CDP::ComputeConcentration(float *accum, float *conc, long countV[],
	const std::vector<float *> & otherVarData)
{
  size_t bin;
  int	i;
  std::vector<float> dia;
  float	*counts, *concentration;
  float	*tas, sampleArea;

  tas = otherVarData[_tasIdx];

  sampleArea = _DOF * _beamDiameter;

  for (i = 0; i < countV[0] * countV[1]; ++i)
    {
    counts = &accum[i * VectorLength()];
    concentration = &conc[i * VectorLength()];

    for (bin = FirstBin(); bin <= LastBin(); ++bin)
      _sampleVolume[bin] = (float)tas[i] * sampleArea;

    dia = _midPointDiam;

#define PLWC
#define DBZ

#include "pms1d_cv"

    otherVarData[_concIdx][i] = _totalConcen;
    otherVarData[_lwIdx][i] = _plwc;
    otherVarData[_dbzIdx][i] = _dbz;
    }

}	// END COMPUTECONCENTRATION

// END CDP.CC
