/*
-------------------------------------------------------------------------
OBJECT NAME:	FileMgr.h

FULL NAME:	Data File Manager

TYPE:		

COPYRIGHT:	University Corporation for Atmospheric Research, 1997
-------------------------------------------------------------------------
*/

#ifndef FILEMGR_H
#define FILEMGR_H

#include "define.h"

#include "DataFile.h"
#include "PlotMgr.h"


/* -------------------------------------------------------------------- */
class FileManager
{
public:
	FileManager();

  friend class DataSource;

  void		NewFile(const char fileName[]);
  void		AddFile(const char fileName[]);

  void		SetCurrentFile(int newFile)	{ _currentFile = newFile; }

  size_t	NumberOfFiles()	const	{ return _numberFiles; }
  DataFile	*CurrentFile() const
	{ return(_numberFiles == 0 ? (DataFile *)NULL : _dataFile[_currentFile]); }

  DataFile	*FirstFile()
	{ return(_numberFiles == 0 ? (DataFile *)NULL : _dataFile[_nextCnt = 0]); }

  DataFile	*NextFile()
	{ return(++_nextCnt == _numberFiles ? (DataFile *)NULL : _dataFile[_nextCnt]); }

private:
  size_t	_numberFiles;
  size_t	_currentFile;
  size_t	_nextCnt;

  DataFile	*_dataFile[MAX_DATAFILES];

};	// END FILEMGR.H

#endif
