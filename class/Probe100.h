/*
-------------------------------------------------------------------------
OBJECT NAME:	Probe100.h

FULL NAME:	Probe100 base class

COPYRIGHT:	University Corporation for Atmospheric Research, 1999-2009
-------------------------------------------------------------------------
*/

#ifndef PROBE100_H
#define PROBE100_H

#include "Probe.h"


/* -------------------------------------------------------------------- */
/**
 * intermediate class between Probe and all PMS1D forward scattering style
 * probes.  This includes FSSP, CDP, SPP-100 and others.
 */
class Probe100 : public Probe
{
public:
	Probe100(NcFile *file, NcVar &av, int zbo);

  friend class EditDiameters;


protected:
  float	_PLWfac, _DBZfac, _DENS, _DOF, _beamDiameter, _sampleVol;
  float	_totalConcen, _dbar, _plwc, _disp, _dbz;

  int	_tasIdx;					// Inputs
  int	_concIdx, _lwIdx, _dbzIdx, _dbarIdx, _dispIdx;	// Outputs

};	// END PROBE100.H

#endif
