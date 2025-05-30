/*
-------------------------------------------------------------------------
OBJECT NAME:	uhsas.cc

FULL NAME:	UHSAS

DESCRIPTION:	

COPYRIGHT:	University Corporation for Atmospheric Research, 2001
-------------------------------------------------------------------------
*/

#include "uhsas.h"


/* -------------------------------------------------------------------- */
UHSAS::UHSAS(NcFile *file, NcVar &av, int zbo) : Probe(file, av, zbo)
{
  _concIdx = _dispIdx = _dbarIdx = _volIdx = -1;

  for (size_t i = 0; i < _otherVars.size(); ++i)
    {
    if (_otherVars[i].getName().starts_with("UFLWC"))
      _flowIdx = i;

    if (_otherVars[i].getName().starts_with("CONC"))
      _concIdx = i;

    if (_otherVars[i].getName().starts_with("DISP"))
      _dispIdx = i;

    if (_otherVars[i].getName().starts_with("DBAR"))
      _dbarIdx = i;

    if (_otherVars[i].getName().starts_with("PVOL"))
      _volIdx = i;
    }
}	/* END CONSTRUCTOR */

/* -------------------------------------------------------------------- */
void UHSAS::ComputeConcentration(float *accum, float *conc, long countV[],
	const std::vector<float *> & otherVarData)
{
  size_t	bin;
  int		i;
  std::vector<float> dia;
  float		*counts, *concentration;
  float		*flow;

  flow = otherVarData[_flowIdx];

  for (i = 0; i < countV[0] * countV[1]; ++i)
    {
    counts = &accum[i * VectorLength()];
    concentration = &conc[i * VectorLength()];

    for (bin = FirstBin(); bin <= LastBin(); ++bin)
      _sampleVolume[bin] = flow[i];

    dia = _midPointDiam;

#define P_VOLUME

#include "pms1d_cv"

    otherVarData[_concIdx][i] = _totalConcen;
    otherVarData[_dispIdx][i] = _disp;
    otherVarData[_dbarIdx][i] = _dbar;

    if (_volIdx >= 0)
      otherVarData[_volIdx][i] = _pvol;
    }

}	/* END COMPUTECONCENTRATION */

/* END UHSAS.CC */
