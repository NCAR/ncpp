/*
-------------------------------------------------------------------------
OBJECT NAME:	Probe100.cc

FULL NAME:	Probe100 Class

COPYRIGHT:	University Corporation for Atmospheric Research, 1999-2009
-------------------------------------------------------------------------
*/

#include "Probe100.h"


/* -------------------------------------------------------------------- */
Probe100::Probe100(NcFile *file, NcVar &av, int zbo) : Probe(file, av, zbo)
{
  NcVarAtt		attr;
printf("Probe100::ctor\n");
  if (!(attr = _cvar.getAtt("Density")).isNull() || !(attr = _avar.getAtt("Density")).isNull())
    attr.getValues(&_DENS);
  else
    _DENS = 1.0;

  if (!(attr = _cvar.getAtt("PLWfactor")).isNull() || !(attr = _avar.getAtt("PLWfactor")).isNull())
    attr.getValues(&_PLWfac);
  else
    _PLWfac = 1.0e-6;

  if (!(attr = _cvar.getAtt("DBZfactor")).isNull() || !(attr = _avar.getAtt("DBZfactor")).isNull())
    attr.getValues(&_DBZfac);
  else
    _DBZfac = 1.0e6;

  for (size_t i = 0; i < _otherVars.size(); ++i)
    {
    if (_otherVars[i].getName().compare("TASX") == 0)
      _tasIdx = i;

    if (_otherVars[i].getName().starts_with("CONC"))
      _concIdx = i;

    if (_otherVars[i].getName().starts_with("PLWC"))
      _lwIdx = i;

    if (_otherVars[i].getName().starts_with("DBZ"))
      _dbzIdx = i;

    if (_otherVars[i].getName().starts_with("DBAR"))
      _dbarIdx = i;

    if (_otherVars[i].getName().starts_with("DISP"))
      _dispIdx = i;
    }

}	/* END CONSTRUCTOR */

// END PROBE100.CC
