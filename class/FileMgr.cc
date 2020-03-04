/*
-------------------------------------------------------------------------
OBJECT NAME:	FileMgr.cc

COPYRIGHT:	University Corporation for Atmospheric Research, 1997
-------------------------------------------------------------------------
*/

#include "FileMgr.h"


/* -------------------------------------------------------------------- */
FileManager::FileManager() : _numberFiles(0), _currentFile(0)
{

}	/* END CONTRUCTOR */

/* -------------------------------------------------------------------- */
void FileManager::NewFile(const char fileName[])
{
  extern PlotManager	*plotMgr;

  for (size_t i = 0; i < _numberFiles; ++i)
    delete _dataFile[i];

  _numberFiles = 1;
  _currentFile = 0;

  _dataFile[0] = new DataFile(fileName);

  plotMgr->GenerateAutoTitles(*_dataFile[0]);

}	/* END NEWFILE */

/* -------------------------------------------------------------------- */
void FileManager::AddFile(const char fileName[])
{
  _dataFile[_numberFiles++] = new DataFile(fileName);

}	/* END ADDFILE */

/* END FILEMGR.CC */
