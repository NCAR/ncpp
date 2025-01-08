/*
-------------------------------------------------------------------------
OBJECT NAME:	x200.cc

FULL NAME:	200X Class

DESCRIPTION:	

COPYRIGHT:	University Corporation for Atmospheric Research, 1999
-------------------------------------------------------------------------
*/

#include "x200.h"


/* -------------------------------------------------------------------- */
X200::X200(NcFile *file, NcVar &av, int zbo) : Probe200(file, av, zbo)
{
  NcVarAtt	attr;

  if (!(attr = _avar.getAtt("nDiodes")).isNull())
    attr.getValues(&_nDiodes);
  else
    _nDiodes = 15;

  if (!(attr = _avar.getAtt("ArmDistance")).isNull())
    attr.getValues(&_armDistance);
  else
    _armDistance = 61.0;

  ComputeWidths();

}	/* END CONSTRUCTOR */

/* END X200.CC */
