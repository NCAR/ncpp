/*
-------------------------------------------------------------------------
OBJECT NAME:	f300.cc

FULL NAME:	FSSP-300 Class

DESCRIPTION:	

COPYRIGHT:	University Corporation for Atmospheric Research, 1999
-------------------------------------------------------------------------
*/

#include "f300.h"


/* -------------------------------------------------------------------- */
F300::F300(NcFile *file, NcVar &av, int zbo) : Probe(file, av, zbo)
{
  _tasIdx = _concIdx = _dbarIdx = _volIdx = -1;

  for (size_t i = 0; i < _otherVars.size(); ++i)
    {
    if (_otherVars[i].getName().compare("TASX") == 0)
      _tasIdx = i;

    if (_otherVars[i].getName().starts_with("CONC"))
      _concIdx = i;

    if (_otherVars[i].getName().starts_with("DBAR"))
      _dbarIdx = i;

    if (_otherVars[i].getName().starts_with("PVOL"))
      _volIdx = i;
    }
}	/* END CONSTRUCTOR */

/* -------------------------------------------------------------------- */
void F300::ComputeConcentration(float *accum, float *conc, long countV[],
	const std::vector<float *> & otherVarData)
{
  size_t bin;
  int	i;
  std::vector <float> dia;
  float	*counts, *concentration, *tas;
  double vol;

  tas = otherVarData[_tasIdx];
printf("f300: SampleArea needs to come from netCDF file.  Currently hardcoded 0.65.\n");
  for (i = 0; i < countV[0] * countV[1]; ++i)
    {
    counts = &accum[i * VectorLength()];
    concentration = &conc[i * VectorLength()];

    vol = tas[i] / DataRate() * 0.065;    /* Sample Area taken from cal in 1994 */

    for (bin = FirstBin(); bin <= LastBin(); ++bin)
      _sampleVolume[bin] = vol;

    dia = _midPointDiam;

#define P_VOLUME

#include "pms1d_cv"

    otherVarData[_concIdx][i] = _totalConcen;
    otherVarData[_dbarIdx][i] = _dbar;

    if (_volIdx >= 0)
      otherVarData[_volIdx][i] = _pvol;
    }

}	/* END COMPUTECONCENTRATION */

/* END F300.CC */
