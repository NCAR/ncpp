/*
-------------------------------------------------------------------------
OBJECT NAME:	Titles.cc

COPYRIGHT:	University Corporation for Atmospheric Research, 1997-2009
-------------------------------------------------------------------------
*/

#include "Titles.h"

#include <ncFile.h>

/* -------------------------------------------------------------------- */
Titles::Titles(const Widget parent) : TextWindow(parent, "titles")
{

}

/* -------------------------------------------------------------------- */
void Titles::Update(const std::string fileName)
{
  netCDF::NcFile	*file = new netCDF::NcFile(fileName.c_str(), netCDF::NcFile::read);
  NcVar         var;
  NcVarAtt      attr;
  char		title[512];


  Clear();
  Append(fileName.c_str());
  Append("\n\n");

  if (file->isNull())
  {
    snprintf(buffer, BUFFSIZE, "Can't open %s.", fileName.c_str());
    ErrorMsg(buffer);
    delete file;
    return;
  }


  std::multimap<std::string, NcVar> varList = file->getVars();
  for (auto it = varList.begin(); it != varList.end(); ++it)
  {
    var = it->second;

//    units = var->get_att("units")->as_string(0);

    try
    {
      attr = var.getAtt("long_name");
      if (!attr.isNull())
      {
         int len = attr.getAttLength();
         attr.getValues(title);
         title[len] = '\0';
      }
    }
    catch(const netCDF::exceptions::NcException& e)
    {
      title[0] = 0;
    }

    snprintf(buffer, BUFFSIZE, "%-16s %s\n", var.getName().c_str(), title);
    Append(buffer);
  }

  MoveTo(0);

  delete file;

}	/* END UPDATE */

/* END TITLES.CC */
