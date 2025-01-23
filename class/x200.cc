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
;
  getIntAttribute(_avar, "_nDiodes", _nDiodes, 15);
  getFloatAttribute(_avar, "ArmDistance", _armDistance, 61.0);

  ComputeWidths();

}	/* END CONSTRUCTOR */

/* END X200.CC */
