/*
-------------------------------------------------------------------------
OBJECT NAME:	CanvasWindow.cc

COPYRIGHT:	University Corporation for Atmospheric Research, 1997-2009
-------------------------------------------------------------------------
*/

#include "CanvasWindow.h"

struct menu
	{
	const char	*title;
	void            (*callback)(Widget, XtPointer, XtPointer);
	XtPointer       callData;
	} ;

static struct menu	fileMenu[] = {
	{ "newFile", GetDataFileName, (XtPointer)NewDataFile, },
	{ "addFile", GetDataFileName, (XtPointer)AddDataFile, },
//	{ "separator", NULL, NULL, },
//	{ "Generate File", GetDataFileName, (XtPointer)GenerateFile, },
	{ "separator", NULL, NULL, },
	{ "printSetup", EditPrintParms, NULL, },
	{ "savePS", PrintSave, (XtPointer)1, },
	{ "print", PrintSave, NULL, },
#ifdef PNG
	{ "separator", NULL, NULL, },
	{ "savePNG", SavePNG, NULL, },
#endif
	{ "separator", NULL, NULL, },
	{ "quit", Quit, NULL, },
	{ NULL, NULL, NULL }};

static struct menu	legendMenu[] = {
	{ "editXYparms", EditParms, (void *)XY, },
	{ "editDiams", EditDiams, (void *)NULL, },
	{ NULL, NULL, NULL }};

static struct menu	viewMenu[] = {
	{ "viewASCII", ViewASCII, NULL, },
	{ "viewVars", ViewVars, NULL, },
	{ "viewTitles", ViewTitles, NULL, },
	{ "viewHeader", ViewHeader, NULL, },
	{ NULL, NULL, NULL }};

static struct menu	helpMenu[] = {
        { "EOL Homepage", OpenURL, (XtPointer)1 },
        { "RAF Software Page", OpenURL, (XtPointer)2 },
        { "ncpp User's Manual", OpenURL, (XtPointer)3 },
	{ NULL, NULL, NULL }};

static struct
	{
	const char	*title;
	struct menu	*sub;
	} main_menu[] = {
		{ "File", fileMenu, },
		{ "Edit", legendMenu, },
		{ "View", viewMenu, },
		{ "Help", helpMenu, },
		{ NULL, NULL }};


/* -------------------------------------------------------------------- */
CanvasWindow::CanvasWindow(const Widget parent) : WinForm(parent, "canvas", Form)
{
  int		i, j;
  Cardinal	n;
  Arg		args[8];
  Widget	menubar, menu[5], bttn[16], menu_button[5];

  n = 0;
  menubar = XmCreateMenuBar(Window(), (char *)"menuBar", args, n);
  XtManageChild(menubar);

  for (i = 0; main_menu[i].title; ++i)
    {
    n = 0;
    menu[i] = XmCreatePulldownMenu(menubar, (char *)main_menu[i].title, args, n);

    n = 0;
    XtSetArg(args[n], XmNsubMenuId, menu[i]); ++n;
    menu_button[i] = XmCreateCascadeButton(menubar, (char *)main_menu[i].title, args,n);

    for (j = 0; main_menu[i].sub[j].title; ++j)
      {
      n = 0;

      if (main_menu[i].sub[j].callback == NULL)
        {
        bttn[j] = XmCreateSeparator(menu[i], (char *)main_menu[i].sub[j].title, args,n);
        continue;
        }

      bttn[j] = XmCreatePushButton(menu[i], (char *)main_menu[i].sub[j].title, args, n);
      XtAddCallback(bttn[j], XmNactivateCallback,
        main_menu[i].sub[j].callback, (void *)main_menu[i].sub[j].callData);
      }

    XtManageChildren(bttn, j);
    }

  XtManageChildren(menu_button, i);



  /* Create Graphics Canvas
   */
  n = 0;
  XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM); n++;
  XtSetArg(args[n], XmNbottomAttachment, XmATTACH_FORM); n++;
  XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM); n++;
  XtSetArg(args[n], XmNrightAttachment, XmATTACH_FORM); n++;
  _drawA = XmCreateDrawingArea(Window(), (char *)"canvas", args, n);

  XtAddCallback(_drawA, XmNexposeCallback, (XtCallbackProc)CanvasExpose, NULL);
  XtAddCallback(_drawA, XmNinputCallback, (XtCallbackProc)CanvasInput, NULL);
  XtAddCallback(_drawA, XmNresizeCallback, (XtCallbackProc)CanvasResize, NULL);

  XtManageChild(_drawA);

}	/* END CONSTRUCTOR */

/* END CANVASWINDOW.CC */
