/*
-------------------------------------------------------------------------
OBJECT NAME:	VarsWin.cc

COPYRIGHT:	University Corporation for Atmospheric Research, 1997-2009
-------------------------------------------------------------------------
*/

#include "VarsWin.h"

/* -------------------------------------------------------------------- */
VarsWin::VarsWin(const Widget parent) : TextWindow(parent, "vars")
{

}	/* END CONSTRUCTOR */

/* -------------------------------------------------------------------- */
void VarsWin::Update(SetManager& sets, PlotManager *plotMgr)
{
  DataSet	*set;

  Clear();

  Append(plotMgr->Title().c_str()); Append(", ");
  Append(plotMgr->SubTitle().c_str()); Append("\n\n");

  for (set = sets.FirstSet(); set; set = sets.NextSet())
    {
    strcpy(buffer, set->probe()->Name().c_str());
    strcat(buffer, "\n");

    for (size_t i = 0; i < set->probe()->nOtherVars(); ++i)
      {
      snprintf(&buffer[strlen(buffer)], 64, "  %-12s", set->probe()->OtherVarName(i).c_str());

      for (size_t j = 0; j < sets.NumberRecords(); ++j)
        {
	snprintf(&buffer[strlen(buffer)], 64, "%10.3f", set->OtherVar(i, j));
        }

      strcat(buffer, "\n");
      }

    strcat(buffer, "\n");
    Append(buffer);
    buffer[0] = '\0';
    }

  MoveTo(0);

}	/* END UPDATE */

/* END VARSWIN.CC */
