/*
-------------------------------------------------------------------------
OBJECT NAME:	y200.cc

FULL NAME:	200Y Class

DESCRIPTION:	

COPYRIGHT:	University Corporation for Atmospheric Research, 1999
-------------------------------------------------------------------------
*/

#include "y200.h"


/* -------------------------------------------------------------------- */
Y200::Y200(NcFile *file, NcVar &av, int zbo) : Probe200(file, av, zbo)
{
  NcVarAtt attr;

  if (!(attr = _avar.getAtt("nDiodes")).isNull())
    attr.getValues(&_nDiodes);
  else
    _nDiodes = 24;

  if (!(attr = _avar.getAtt("ArmDistance")).isNull())
    attr.getValues(&_armDistance);
  else
    _armDistance = 263.0;

  ComputeWidths();

}	/* END CONSTRUCTOR */

/* END Y200.CC */
