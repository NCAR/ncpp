/*
-------------------------------------------------------------------------
OBJECT NAME:	ncHeader.cc

COPYRIGHT:	University Corporation for Atmospheric Research, 1997-8
-------------------------------------------------------------------------
*/

#include "ncHeader.h"


/* -------------------------------------------------------------------- */
ncHeader::ncHeader(const Widget parent) : TextWindow(parent, "header")
{

}

/* -------------------------------------------------------------------- */
void ncHeader::Update(const std::string fileName)
{
  FILE	*pp;
  char command[256];

  Clear();
  Append(fileName.c_str());
  Append("\n\n");

  snprintf(command, 256, "ncdump -h %s", fileName.c_str());
  if ((pp = popen(command, "r")) == NULL)
    {
    snprintf(buffer, BUFFSIZE, "Can't open pipe [%s]", command);
    ErrorMsg(buffer);
    }

  while (fread(buffer, BUFFSIZE, 1, pp) > 0)
    Append(buffer);

  strcpy(strchr(buffer, '}')+1, "\n\n");
  Append(buffer);

  pclose(pp);

  MoveTo(0);

}	/* END UPDATE */

/* END NCHEADER.CC */
