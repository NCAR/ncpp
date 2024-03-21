/*
-------------------------------------------------------------------------
OBJECT NAME:	2D.h

FULL NAME:	2D

TYPE:		Derived class for 2DC, 2DP, and 2DS (3V-CPI).

COPYRIGHT:	University Corporation for Atmospheric Research, 2000-2013
-------------------------------------------------------------------------
*/

#ifndef TWOD_H
#define TWOD_H

#include "Probe200.h"


/* -------------------------------------------------------------------- */
class TwoD : public Probe200
{
public:
	TwoD(NcFile *file, NcVar *av, int zbo);

  void	ComputeConcentration(float *accum, float *conc, long countV[],
		const std::vector<float *> & otherVarData);

};


// SPEC 2DS and/or 3V-CPI
class TwoDS : public TwoD
{
public:
	TwoDS(NcFile *file, NcVar *av, int zbo);
};

class TwoDH : public TwoD
{
public:
	TwoDH(NcFile *file, NcVar *av, int zbo);
};

class TwoDC : public TwoD
{
public:
	TwoDC(NcFile *file, NcVar *av, int zbo);
};

class TwoDP : public TwoD
{
public:
	TwoDP(NcFile *file, NcVar *av, int zbo);
};

class TwoDCIP : public TwoD
{
public:
	TwoDCIP(NcFile *file, NcVar *av, int zbo);
};

class TwoDPIP : public TwoD
{
public:
	TwoDPIP(NcFile *file, NcVar *av, int zbo);
};
#endif
