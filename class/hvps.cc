/*
-------------------------------------------------------------------------
OBJECT NAME:	hvps.cc

FULL NAME:	HVPS Class

DESCRIPTION:	

COPYRIGHT:	University Corporation for Atmospheric Research, 2003
-------------------------------------------------------------------------
*/

#include "hvps.h"


/* -------------------------------------------------------------------- */
HVPS::HVPS(NcFile *file, NcVar &av, int zbo) : Probe(file, av, zbo)
{
  _tasIdx = _concIdx = _dbarIdx = _lwIdx = _dispIdx = _dbzIdx = -1;

  for (size_t i = 0; i < _otherVars.size(); ++i)
    {
    if (_otherVars[i].getName().compare("TASX") == 0)
      _tasIdx = i;

    if (_otherVars[i].getName().starts_with("CONC"))
      _concIdx = i;

    if (_otherVars[i].getName().starts_with("PLWC"))
      _lwIdx = i;

    if (_otherVars[i].getName().starts_with("DBAR"))
      _dbarIdx = i;

    if (_otherVars[i].getName().starts_with("DISP"))
      _dispIdx = i;

    if (_otherVars[i].getName().starts_with("DBZ"))
      _dbzIdx = i;
    }

}	/* END CONSTRUCTOR */

/* -------------------------------------------------------------------- */
void HVPS::ComputeConcentration(float *accum, float *conc, long countV[],
	const std::vector<float *> & otherVarData)
{
  size_t bin;
  int	i;
  std::vector<float> dia;
  float	*counts, *concentration, *tas;
  double vol;

  tas = otherVarData[_tasIdx];

  for (i = 0; i < countV[0] * countV[1]; ++i)
    {
    counts = &accum[i * VectorLength()];
    concentration = &conc[i * VectorLength()];

    vol = tas[i] / DataRate() * 200 * 203 * (256-80) * 1.0e-5;

    for (bin = FirstBin(); bin <= LastBin(); ++bin)
      _sampleVolume[bin] = vol;

    dia = _midPointDiam;

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

/* END HVPS.CC */
