/*
-------------------------------------------------------------------------
OBJECT NAME:	pcasp.cc

FULL NAME:	ASAS/PCASP

DESCRIPTION:	

COPYRIGHT:	University Corporation for Atmospheric Research, 1999
-------------------------------------------------------------------------
*/

#include "pcasp.h"


/* -------------------------------------------------------------------- */
PCASP::PCASP(NcFile *file, NcVar &av, int zbo) : Probe(file, av, zbo)
{
  _concIdx = _dispIdx = _dbarIdx = _volIdx = -1;

  for (size_t i = 0; i < _otherVars.size(); ++i)
    {
    if (_otherVars[i].getName().starts_with("PACT"))
      _actIdx = i;

    if (_otherVars[i].getName().starts_with("PFLWC"))
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
void PCASP::ComputeConcentration(float *accum, float *conc, long countV[],
	const std::vector<float *> & otherVarData)
{
  size_t bin;
  int	i;
  std::vector<float> dia;
  float		*counts, *concentration;
  float		*flow, *activity;
  double	vol;

  flow = otherVarData[_flowIdx];
  activity = otherVarData[_actIdx];

  for (i = 0; i < countV[0] * countV[1]; ++i)
    {
    counts = &accum[i * VectorLength()];
    concentration = &conc[i * VectorLength()];

    vol = (1.0 - activity[i] * DataRate()) * (flow[i] / DataRate());

    for (bin = FirstBin(); bin <= LastBin(); ++bin)
      _sampleVolume[bin] = (float)vol;

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

/* END PCASP.CC */
