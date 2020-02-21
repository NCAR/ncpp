/*
-------------------------------------------------------------------------
OBJECT NAME:	Colors.h

FULL NAME:	Colors

TYPE:		

DESCRIPTION:	Provide a series of Colors that are always the same for
		both X & PostScript.

COPYRIGHT:	University Corporation for Atmospheric Research, 1997-2000
-------------------------------------------------------------------------
*/

#ifndef COLORS_H
#define COLORS_H

#include "define.h"

#define BLACK		0
#define BACKGROUND	8

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

#include <stdint.h>

#ifdef PNG
#include <png.h>
#endif

/* -------------------------------------------------------------------- */
class Colors
{
public:
	Colors(const Widget w);

  size_t	NumberOfColors()	{ return numberColors; }
  void		ResetColors()		{ colorIndex = 0; resetColors(); }
  void		SetColorNames(char str[]);

  uint32_t	GetColor(size_t indx);
  uint32_t	NextColor();
  uint32_t	CurrentColor();

  float	*GetColorPS(size_t indx);
  float	*NextColorPS();
  float	*CurrentColorPS();

#ifdef PNG
  void		SavePNG(const char outFile[], XImage *image);
  uint16_t	*GetColorRGB_X(size_t idx);
#endif


private:
  void		resetColors();

#ifdef PNG
  void		checkByteSwap(XImage *image);
  size_t	getColorIndex(uint32_t pixel);
#endif

  Widget _w;
  size_t	colorIndex, numberColors;
  bool		Color;

};	// END COLORS.H

#endif
