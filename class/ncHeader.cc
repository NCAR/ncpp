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
  char	command[256];
  int	n;

  Clear();
  Append(fileName.c_str());
  Append("\n\n");

  snprintf(command, 256, "ncdump -h %s", fileName.c_str());
  if ((pp = popen(command, "r")) == NULL)
    {
    snprintf(buffer, BUFFSIZE, "Can't open pipe [%s]", command);
    ErrorMsg(buffer);
    }

  while ((n = fread(buffer, 1, BUFFSIZE-1, pp)) > 0)
  {
    buffer[n] = '\0';
    Append(buffer);
  }

  strcat(buffer, "\n\n");
  Append(buffer);

  pclose(pp);

  MoveTo(0);

}	/* END UPDATE */

/* END NCHEADER.CC */
