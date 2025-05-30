/*
-------------------------------------------------------------------------
OBJECT NAME:	EditDiameters.cc

COPYRIGHT:	University Corporation for Atmospheric Research, 1998-9
-------------------------------------------------------------------------
*/

#include "EditDiameters.h"


/* -------------------------------------------------------------------- */
EditDiameters::EditDiameters(const Widget parent) : WinForm(parent, "editDiams", RowColumn)
{
  Cardinal	n;
  Arg		args[8];
  Widget	diamFrame, RC, probeRC, drFrame, drRC, b[3],
		plRC, innerRC;

  txtCnt = 0;

  n = 0;
  diamFrame = XmCreateFrame(Window(), (char *)"diamFrame", args, n);
  XtManageChild(diamFrame);

  n = 0;
  fileLabel = XmCreateLabel(diamFrame, (char *)"Select Probe", args, n);
  XtManageChild(fileLabel);

  n = 0;
  RC = XmCreateRowColumn(diamFrame, (char *)"diamRC", args, n);
  XtManageChild(RC);


  n = 0;
  probeRC = XmCreateRadioBox(RC, (char *)"probeRC", args, n);
  XtManageChild(probeRC);


  /* Probe Toggle Buttons.
   */
  for (size_t i = 0; i < MAX_PROBES; ++i)
    {
    n = 0;
    probeB[i] = XmCreateToggleButton(probeRC, (char *)"none      ", NULL, 0);
    XtAddCallback(probeB[i], XmNvalueChangedCallback,
                  (XtCallbackProc)SetDiams, (XtPointer)i);
    }

  XtManageChildren(probeB, MAX_PROBES);



  n = 0;
  drFrame = XmCreateFrame(RC, (char *)"drFrame", args, n);
  XtManageChild(drFrame);
  innerRC = XmCreateRowColumn(drFrame, (char *)"innerRC", args, n);
  XtManageChild(innerRC);
  plRC = XmCreateRowColumn(innerRC, (char *)"plRC", args, n);
  XtManageChild(plRC);

  n = 0;
  probeLabel = XmCreateLabel(plRC, (char *)"test", args, n);
  XtManageChild(probeLabel);

  n = 0;
  XtManageChild(XmCreateLabel(plRC, (char *)"Starting bin #", args, n));
  text[txtCnt] = XmCreateTextField(plRC, (char *)"startBin", args, n);
  XtManageChild(text[txtCnt++]);
  XtManageChild(XmCreateLabel(plRC, (char *)"Ending bin #", args, n));
  text[txtCnt] = XmCreateTextField(plRC, (char *)"startBin", args, n);
  XtManageChild(text[txtCnt++]);

  n = 0;
  for (; txtCnt < 6; ++txtCnt)
    {
    text[txtCnt] = XmCreateTextField(innerRC, (char *)"diamTxt", args, n);
    XtManageChild(text[txtCnt]);
    }

  n = 0;
  for (; txtCnt < 12; ++txtCnt)
    {
    plRC = XmCreateRowColumn(innerRC, (char *)"plRC", args, n);
    XtManageChild(plRC);

    miscLabel[txtCnt] = XmCreateLabel(plRC, (char *)"miscLabel", args, n);
    XtManageChild(miscLabel[txtCnt]);

    text[txtCnt] = XmCreateTextField(plRC, (char *)"miscTxt", args, n);
    XtManageChild(text[txtCnt]);
    }


  n = 0;
  drFrame = XmCreateFrame(Window(), (char *)"buttonFrame", args, n);
  XtManageChild(drFrame);

  n = 0;
  drRC = XmCreateRowColumn(drFrame, (char *)"buttonRC", args, n);
  XtManageChild(drRC);

  n = 0;
  b[0] = XmCreatePushButton(drRC, (char *)"applyButton", args, n);

  n = 0;
  b[1] = XmCreatePushButton(drRC, (char *)"resetButton", args, n);

  n = 0;
  b[2] = XmCreatePushButton(drRC, (char *)"dismissButton", args, n);

  XtManageChildren(b, 3);

  XtAddCallback(b[0],XmNactivateCallback, ApplyDiams, (XtPointer)NULL);
  XtAddCallback(b[1],XmNactivateCallback, SetDiams, (XtPointer)NULL);
  XtAddCallback(b[2],XmNactivateCallback, DismissWindow, (XtPointer)Window());

}	/* END CONSTRUCTOR */

/* -------------------------------------------------------------------- */
void EditDiameters::SetProbeNames(DataFile *currFile)
{
  size_t	i;
  XmString      label;
  Arg           args[2];

  if (currFile == 0)
    return;

  for (i = 0; i < currFile->NumberOfProbes(); ++i)
    {
    XtSetSensitive(probeB[i], True);

    label = XmStringCreate((char *)currFile->probe[i]->Name().c_str(),
					XmFONTLIST_DEFAULT_TAG);
    XtSetArg(args[0], XmNlabelString, label);
    XtSetValues(probeB[i], args, 1);
    XmStringFree(label);

    XmToggleButtonSetState(probeB[i], False, False);
    }

  for (; i < MAX_PROBES; ++i)
    {
    XtSetSensitive(probeB[i], False);

    label = XmStringCreate((char *)"none    ", XmFONTLIST_DEFAULT_TAG);
    XtSetArg(args[0], XmNlabelString, label);
    XtSetValues(probeB[i], args, 1);
    XmStringFree(label);

    XmToggleButtonSetState(probeB[i], False, False);
    }

  XmToggleButtonSetState(probeB[0], True, True);

}	/* END SETPROBENAMES */

/* -------------------------------------------------------------------- */
void EditDiameters::SetDiameters(Probe *probe)
{
  size_t	i, j, cnt, nTxt;
  Arg		args[1];
  XmString	label;

  label = XmStringCreate((char *)probe->Name().c_str(), XmFONTLIST_DEFAULT_TAG);
  XtSetArg(args[0], XmNlabelString, label);
  XtSetValues(probeLabel, args, 1);
  XmStringFree(label);

  cnt = 0;

  snprintf(buffer, BUFFSIZE, "%lu", probe->FirstBin());
  XmTextFieldSetString(text[cnt++], buffer);
  snprintf(buffer, BUFFSIZE, "%lu", probe->LastBin());
  XmTextFieldSetString(text[cnt++], buffer);

  nTxt = probe->VectorLength() / 16;
  if (probe->Type() == Probe::FSSP)
    nTxt *= 4;

  for (i = 0; i < nTxt+1; ++i)
    {
    buffer[0] = '\0';

    XtSetSensitive(text[cnt], True);

    for (j = 0; j < 16 && (i*16)+j < probe->VectorLength(); ++j)
      snprintf(&buffer[strlen(buffer)], 15, "%5g ", probe->CellSize((i*16)+j));

    XmTextFieldSetString(text[cnt++], buffer);
    }

  for (; cnt < 6; ++cnt)
    {
    XtSetSensitive(text[cnt], False);
    XmTextFieldSetString(text[cnt], (char *)"");
    }

  cnt = 6;

  // Set up misc stuff.
  switch (probe->Type())
    {
    case Probe::FSSP:
    case Probe::S100:
    case Probe::CDP:
    case Probe::HDC:
      setSpex("DBZ Factor", cnt++, ((Probe100 *)probe)->_DBZfac);
      setSpex("Liquid Water Content Factor", cnt++, ((Probe100 *)probe)->_PLWfac);
      setSpex("Density of Water", cnt++, ((Probe100 *)probe)->_DENS);
      setSpex("Depth of Field", cnt++, ((Probe100 *)probe)->_DOF);
      setSpex("Beam Diameter", cnt++, ((Probe100 *)probe)->_beamDiameter);
      break;

    case Probe::X260:
    case Probe::TWODP:
    case Probe::TWODC:
    case Probe::TWODS:
      setSpex("DBZ Factor", cnt++, ((Probe200 *)probe)->_DBZfac);

    case Probe::X200:
    case Probe::Y200:
      setSpex("Liquid Water Content Factor", cnt++,((Probe200 *)probe)->_PLWfac);
      setSpex("Density of Water", cnt++, ((Probe200 *)probe)->_DENS);
      setSpex("Number of Diodes", cnt++, (float)((Probe200 *)probe)->_nDiodes);
      setSpex("Arm Distance", cnt++, ((Probe200 *)probe)->_armDistance);
      setSpex("Response Time", cnt++, ((Probe200 *)probe)->_responseTime);

      break;

    case Probe::NoProbe:
    default:
      break;
    }

  for (; cnt < 12; ++cnt)
    {
    label = XmStringCreate((char *)"" , XmFONTLIST_DEFAULT_TAG);
    XtSetArg(args[0], XmNlabelString, label);
    XtSetValues(miscLabel[cnt], args, 1);
    XmStringFree(label);

    XtSetSensitive(text[cnt], False);
    XmTextFieldSetString(text[cnt], (char *)"");
    }


}	/* END SETDIAMETERS */

/* -------------------------------------------------------------------- */
void EditDiameters::ApplyDiameters(Probe *probe)
{
  int	k, l, cnt, nTxt, first, last;
  char	*p, *p1;
  float	cells[256];

  cnt = 0;

  first = GetTextInt(text[cnt++]);
  last = GetTextInt(text[cnt++]);

  nTxt = probe->VectorLength() / 16;
  if (probe->Type() == Probe::FSSP)
    nTxt *= 4;

  for (k = 0; k < nTxt; ++k)
    {
    p = XmTextFieldGetString(text[cnt++]);
    p1 = strtok(p, ", ");

    for (l = 0; l < 16; ++l)
      {
      cells[(k*16)+l] = atof(p1);
      p1 = strtok(NULL, ", ");
      }

    XtFree(p);
    }

  probe->UpdateCellDiams(first, last, cells);

  for (; cnt < 6; ++cnt)
    ;


  // Set up misc stuff.
  switch (probe->Type())
    {
    case Probe::FSSP:
      ((FSSP *)probe)->_DBZfac = GetTextFloat(text[cnt++]);
      ((FSSP *)probe)->_PLWfac = GetTextFloat(text[cnt++]);
      ((FSSP *)probe)->_DENS = GetTextFloat(text[cnt++]);
      ((FSSP *)probe)->_DOF = GetTextFloat(text[cnt++]);
      ((FSSP *)probe)->_beamDiameter = GetTextFloat(text[cnt++]);
      break;

    case Probe::X260:
      ((Probe200 *)probe)->_DBZfac = GetTextFloat(text[cnt++]);

    case Probe::X200:
    case Probe::Y200:
      ((Probe200 *)probe)->_PLWfac = GetTextFloat(text[cnt++]);
      ((Probe200 *)probe)->_DENS = GetTextFloat(text[cnt++]);
      ((Probe200 *)probe)->_nDiodes = GetTextInt(text[cnt++]);
      ((Probe200 *)probe)->_armDistance = GetTextFloat(text[cnt++]);
      ((Probe200 *)probe)->_responseTime = GetTextFloat(text[cnt++]);
      break;

    case Probe::NoProbe:
    default:
      break;
    }

}	/* END APPLYDIAMETERS */

/* -------------------------------------------------------------------- */
void EditDiameters::setSpex(const char *labelTxt, int cnt, float value)
{
  XmString	label;
  Arg		args[2];
  char		buff[32];

  label = XmStringCreate((char *)labelTxt, XmFONTLIST_DEFAULT_TAG);
  XtSetArg(args[0], XmNlabelString, label);
  XtSetValues(miscLabel[cnt], args, 1);
  XmStringFree(label);

  XtSetSensitive(text[cnt], True);
  snprintf(buff, 32, "%g", value);
  XmTextFieldSetString(text[cnt], buff);

}	/* END SETSPEX */

/* END EDITDIAMETERS.CC */
