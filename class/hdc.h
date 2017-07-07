/*
-------------------------------------------------------------------------
OBJECT NAME:	hdc.h

FULL NAME:	HDC

COPYRIGHT:	University Corporation for Atmospheric Research, 2017
-------------------------------------------------------------------------
*/

#ifndef HDC_H
#define HDC_H

#include "Probe100.h"


/* -------------------------------------------------------------------- */
class HDC : public Probe100
{
public:
	HDC(NcFile *file, NcVar *av);

  friend class EditDiameters;

  void	ComputeConcentration(float *accum, float *conc, long countV[],
		const std::vector<float *> & otherVarData);

};	// END HDC.H

#endif
