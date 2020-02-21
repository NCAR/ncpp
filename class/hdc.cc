/*
-------------------------------------------------------------------------
OBJECT NAME:	hdc.cc

FULL NAME:	HDC Class

DESCRIPTION:	

COPYRIGHT:	University Corporation for Atmospheric Research, 2017
-------------------------------------------------------------------------
*/

#include "hdc.h"


/* -------------------------------------------------------------------- */
HDC::HDC(NcFile *file, NcVar *av) : Probe100(file, av)
{
  NcAtt *attr;

  if ((attr = _cvar->get_att("SampleVolume")) || (attr = _avar->get_att("SampleVolume")))
      _sampleVol = attr->as_float(0);
  else
      _sampleVol = 13;

}	/* END CONSTRUCTOR */

/* -------------------------------------------------------------------- */
void HDC::ComputeConcentration(float *accum, float *conc, long countV[],
	const std::vector<float *> & otherVarData)
{
  size_t bin;
  int	i;
  std::vector<float> dia;
  float	*counts, *concentration;

  for (i = 0; i < countV[0] * countV[1]; ++i)
    {
    counts = &accum[i * VectorLength()];
    concentration = &conc[i * VectorLength()];

    for (bin = FirstBin(); bin <= LastBin(); ++bin)
      _sampleVolume[bin] = _sampleVol;

    dia = _midPointDiam;

#define PLWC
#define DBZ

#include "pms1d_cv"

    //otherVarData[_concIdx][i] = _totalConcen;
    //otherVarData[_lwIdx][i] = _plwc;
    //otherVarData[_dbzIdx][i] = _dbz;
    }

}	// END COMPUTECONCENTRATION

// END HDC.CC
