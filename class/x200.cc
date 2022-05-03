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
X200::X200(NcFile *file, NcVar *av, int zbo) : Probe200(file, av, zbo)
{
  NcAtt		*attr;

  if ((attr = _avar->get_att("nDiodes")))
    _nDiodes = attr->as_int(0);
  else
    _nDiodes = 15;

  if ((attr = _avar->get_att("ArmDistance")))
    _armDistance = attr->as_float(0);
  else
    _armDistance = 61.0;

  ComputeWidths();

}	/* END CONSTRUCTOR */

/* END X200.CC */
