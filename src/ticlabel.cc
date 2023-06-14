/*
-------------------------------------------------------------------------
OBJECT NAME:	ticlabel.cc

FULL NAME:	Generate Various Types of Tic Mark Labels.

ENTRY POINTS:	MakeTimeTicLabel()
		MakeTicLabel()
		MakeLogTicLabel()

STATIC FNS:	none

DESCRIPTION:	

COPYRIGHT:	University Corporation for Atmospheric Research, 1997-2023
-------------------------------------------------------------------------
*/

#include "define.h"

static const int LBL_SIZE = 32;
static char	label[LBL_SIZE];

/* -------------------------------------------------------------------- */
std::string MakeTicLabel(float diff, int majorTics, double value)
{
  std::string	tmp;
  int		idiff = (int)diff;

  if (diff < 0.01)
    snprintf(label, LBL_SIZE, "%f", value);
  else
  if (diff < 0.1)
    snprintf(label, LBL_SIZE, "%.4f", value);
  else
  if (diff < 1.0)
    snprintf(label, LBL_SIZE, "%.3f", value);
  else
  if (diff == (float)idiff && (idiff % majorTics) == 0)
    snprintf(label, LBL_SIZE, "%ld", (long)value);
  else
  if (diff < 10.0)
    snprintf(label, LBL_SIZE, "%.2f", value);
  else
  if (diff < 50.0)
    snprintf(label, LBL_SIZE, "%.1f", value);
  else
    snprintf(label, LBL_SIZE, "%ld", (long)value);

  tmp = label;

  return(tmp);

}	/* END MAKETICLABEL */

/* -------------------------------------------------------------------- */
std::string MakeLogTicLabel(double value)
{
  std::string	tmp;

  snprintf(label, LBL_SIZE, "10^%d", (int)rint(log10(value)));
//  snprintf(label, LBL_SIZE, "1.0E%+03d", value);

  tmp = label;

  return tmp;
}

/* -------------------------------------------------------------------- */
std::string MakeYAxisLabel(NormType normalization, DataType dataType)
{
  std::string	label;

  switch (dataType)
  {
  case COUNTS:
    label = "Counts";
    break;

  case CONCENTRATION:
    label = "dN";
    if (normalization == LINEAR)
      label += "/dD (#/cm3/um)";
    else
    if (normalization == LOG)
      label += "/dlogD (#/cm3)";
    else
      label += " (#/cm3)";
    break;

  case SURFACE:
    label = "dS";
    if (normalization == LINEAR)
      label += "/dD (um2/cm3/um)";
    else
    if (normalization == LOG)
      label += "/dlogD (um2/cm3)";
    else
      label += " (um2/cm3)";
    break;

  case VOLUME:
    label = "dV";
    if (normalization == LINEAR)
      label += "/dD (um3/cm3/um)";
    else
    if (normalization == LOG)
      label += "/dlogD (um3/cm3)";
    else
      label += " (um3/cm3)";
    break;
  }

  return label;
}

/* TICLABEL.CC */
