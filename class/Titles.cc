/*
-------------------------------------------------------------------------
OBJECT NAME:	Titles.cc

COPYRIGHT:	University Corporation for Atmospheric Research, 1997-2009
-------------------------------------------------------------------------
*/

#include "Titles.h"


/* -------------------------------------------------------------------- */
Titles::Titles(const Widget parent) : TextWindow(parent, "titles")
{

}

/* -------------------------------------------------------------------- */
void Titles::Update(const std::string fileName)
{
  NcAtt         *attr;
  NcVar         *var;
  NcFile	file(fileName.c_str());
  char		*title;


  Clear();
  Append(fileName.c_str());
  Append("\n\n");

  if (file.is_valid() == false)
    {
    snprintf(buffer, BUFFSIZE, "Can't open %s.", fileName.c_str());
    ErrorMsg(buffer);
    return;
    }


  for (int i = 0; i < file.num_vars(); ++i)
    {
    var = file.get_var(i);

//    units = var->get_att("units")->as_string(0);

    if ((attr = var->get_att("long_name")))
      title = attr->as_string(0);

    snprintf(buffer, BUFFSIZE, "%-16s %s\n", var->name(), title);
    Append(buffer);
    }

  MoveTo(0);

}	/* END UPDATE */

/* END TITLES.CC */
