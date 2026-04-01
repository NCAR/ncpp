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
    snprintf(buffer, BUFFSIZE, "%s\n", set->probe()->Name().c_str());
    Append(buffer);

    for (size_t i = 0; i < set->probe()->nOtherVars(); ++i)
      {
      snprintf(buffer, BUFFSIZE, "  %-12s", set->probe()->OtherVarName(i).c_str());

      for (size_t j = 0; j < sets.NumberRecords(); ++j)
        {
        if (strlen(buffer) + 64 >= BUFFSIZE)
          {
          Append(buffer);
          buffer[0] = '\0';
          }
        snprintf(&buffer[strlen(buffer)], 64, "%10.3f", set->OtherVar(i, j));
        }

      strncat(buffer, "\n", BUFFSIZE - strlen(buffer) - 1);
      Append(buffer);
      buffer[0] = '\0';
      }

    Append("\n");
    }

  MoveTo(0);

}	/* END UPDATE */

/* END VARSWIN.CC */
