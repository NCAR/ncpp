/*
-------------------------------------------------------------------------
OBJECT NAME:	Titles.h

FULL NAME:	View Variable Titles

TYPE:		

COPYRIGHT:	University Corporation for Atmospheric Research, 1997
-------------------------------------------------------------------------
*/

#ifndef TITLES_H
#define TITLES_H

#include "define.h"

#include "raf/TextWindow.h"
#include "DataFile.h"


/* -------------------------------------------------------------------- */
/**
 * Class for the variable names, units and titles window.
 * View Menu -> Variable Titles.
 */
class Titles : public TextWindow
{
public:

	Titles(const Widget parent);
  void	Update(const std::string fileName);

private:

};	// END TITLES.H

#endif
