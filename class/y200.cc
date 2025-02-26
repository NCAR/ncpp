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
  getIntAttribute(_avar, "_nDiodes", _nDiodes, 24);
  getFloatAttribute(_avar, "ArmDistance", _armDistance, 263.0);

  ComputeWidths();

}	/* END CONSTRUCTOR */

/* END Y200.CC */
