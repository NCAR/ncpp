/*
 * Resource file for ncpp.
 */
 
static String fallback_resources[] =
  {
  "*defaultFontList:	-adobe-courier-bold-r-*-*-14-140-75-75-m-90-*-*",
  "*foreground:         black",

  "*font24:		-adobe-courier-bold-r-*-*-24-240-75-75-*-*-*-*",
  "*font18:		-adobe-courier-bold-r-*-*-18-180-75-75-*-*-*-*",
  "*font14:		-adobe-courier-bold-r-*-*-14-140-75-75-*-90-*-*",
  "*font12:		-adobe-courier-bold-r-*-*-12-120-75-75-*-70-*-*",
  "*font10:		-adobe-courier-bold-r-*-*-10-100-75-75-*-60-*-*",

  "*plRC*fontList:	-adobe-courier-bold-r-*-*-12-120-75-75-*-70-*-*",
  "*controlRC*fontList:	-adobe-courier-bold-r-*-*-12-120-75-75-*-70-*-*",
  "*movieRC*fontList:	-adobe-courier-bold-r-*-*-12-120-75-75-*-70-*-*",
  "*printParmsRC*fontList: -adobe-courier-bold-r-*-*-12-120-75-75-*-70-*-*",
  "*diamRC*fontList:	-adobe-courier-bold-r-*-*-12-120-75-75-*-70-*-*",

  "*XmPushButton.height:		32",
  "*XmTextField.background:		Burlywood",
  "*XmTextField.foreground:		black",
  "*XmForm.horizontalSpacing:		4",
  "*XmForm.verticalSpacing:		4",
  "*canvasShell.title:			ncpp 2.2.1",
  "*canvasShell.iconName:		ncpp",
  "*canvasShell.allowShellResize:	True",
  "*canvasShell.x:			0",
  "*canvasShell.y:			50",
  "*controlShell.title:			Plot",
  "*controlShell.x:			800",
  "*controlShell.y:			50",
  "*buttonFrame.shadowType:		SHADOW_IN",
  "*buttonRC.XmPushButton.recomputeSize:	False",
  "*buttonRC.XmPushButton.width:	120",
  "*buttonRC.entryAlignment:		ALIGNMENT_CENTER",
  "*buttonRC.isAligned:			True",
  "*buttonRC.orientation:		HORIZONTAL",

  "*drawForm.XmPushButton.recomputeSize:	False",
  "*drawForm.XmPushButton.width:	32",
  "*drawForm.XmPushButton.height:	32",

  "*canvas.background:			grey",
  "*canvas.height:			600",
  "*canvas.width:			780",

  "*headerShell.title:			netCDF Header",
  "*titlesShell.title:			Variable Titles",
  "*titlesShell.x:			275",
  "*titlesShell.y:			150",
  "*asciiShell.title:			ASCII cell data",
  "*asciiShell.x:			125",
  "*asciiShell.y:			125",
  "*varsShell.title:			Probe Variables",
  "*varsShell.x:			550",
  "*varsShell.y:			600",

  "*headerText.background:		Gray",
  "*headerText.columns:			80",
  "*headerText.editable:		False",
  "*headerText.editMode:		MULTI_LINE_EDIT",
  "*headerText.fontList:  -adobe-courier-bold-r-*-*-12-120-75-75-*-70-*-*",
  "*headerText.rows:			42",

  "*titlesText.background:		Gray",
  "*titlesText.columns:			80",
  "*titlesText.editable:		False",
  "*titlesText.editMode:		MULTI_LINE_EDIT",
  "*titlesText.fontList:  -adobe-courier-bold-r-*-*-12-120-75-75-*-70-*-*",
  "*titlesText.rows:			42",

  "*asciiText.background:		Gray",
  "*asciiText.columns:			132",
  "*asciiText.editable:			False",
  "*asciiText.editMode:			MULTI_LINE_EDIT",
  "*asciiText.fontList:   -adobe-courier-bold-r-*-*-12-120-75-75-*-70-*-*",
  "*asciiText.rows:			25",

  "*varsText.background:		Gray",
  "*varsText.columns:			20",
  "*varsText.editable:			False",
  "*varsText.editMode:			MULTI_LINE_EDIT",
  "*varsText.fontList:    -adobe-courier-bold-r-*-*-12-120-75-75-*-70-*-*",
  "*varsText.rows:			25",

  "*menuBar*newFile.labelString:	Open netCDF File",
  "*menuBar*newFile.mnemonic:		O",
  "*menuBar*newFile.accelerator:	Ctrl<Key>O",
  "*menuBar*newFile.acceleratorText:	Ctrl-O",
  "*menuBar*addFile.labelString:	Add Data File",
  "*menuBar*addFile.mnemonic:		A",
  "*menuBar*addFile.accelerator:	Ctrl<Key>A",
  "*menuBar*addFile.acceleratorText:	Ctrl-A",
  "*menuBar*readParms.labelString:	Read Parms File",
  "*menuBar*readParms.mnemonic:		R",
  "*menuBar*writeParms.labelString:	Write Parms File",
  "*menuBar*writeParms.mnemonic:	W",
  "*menuBar*printSetup.labelString:	Printer Setup",
  "*menuBar*savePS.labelString:		Save PostScript",
  "*menuBar*savePS.mnemonic:		S",
  "*menuBar*savePS.accelerator:		Ctrl<Key>S",
  "*menuBar*savePS.acceleratorText:	Ctrl-S",
  "*menuBar*print.labelString:		Print",
  "*menuBar*print.mnemonic:		P",
  "*menuBar*print.accelerator:		Ctrl<Key>P",
  "*menuBar*print.acceleratorText:	Ctrl-P",
  "*menuBar*savePNG.labelString:	Save PNG",
  "*menuBar*savePNG.mnemonic:		G",
  "*menuBar*quit.labelString:		Quit",
  "*menuBar*quit.mnemonic:		Q",
  "*menuBar*quit.accelerator:		Ctrl<Key>Q",
  "*menuBar*quit.acceleratorText:	Ctrl-Q",

  "*menuBar*editXYparms.labelString:	XY Parameters",
  "*menuBar*editXYparms.mnemonic:	Y",
  "*menuBar*editXYparms.accelerator:	Ctrl<Key>E",
  "*menuBar*editXYparms.acceleratorText:	Ctrl-E",

  "*menuBar*editXYZparms.labelString:	XYZ Parameters",
  "*menuBar*editXYZparms.mnemonic:	Z",

  "*menuBar*editDiams.labelString:	Cell Diameters",
  "*menuBar*editDiams.mnemonic:		D",
  "*menuBar*editDiams.accelerator:	Ctrl<Key>D",
  "*menuBar*editDiams.acceleratorText:	Ctrl-D",

  "*menuBar*viewASCII.labelString:	ASCII cell data",
  "*menuBar*viewASCII.mnemonic:		A",
  "*menuBar*viewVars.labelString:	Probe Variables",
  "*menuBar*viewVars.mnemonic:		V",
  "*menuBar*viewHeader.labelString:	netCDF Header",
  "*menuBar*viewHeader.mnemonic:	H",
  "*menuBar*viewTitles.labelString:	Variable Titles",
  "*menuBar*viewTitles.mnemonic:	T",
  "*menuBar*viewStats.labelString:	Statistics",
  "*menuBar*viewStats.mnemonic:		S",

  "*menuBar*autoScale.labelString:	Scale Y Axis",
  "*menuBar*autoScale.mnemonic:		A",
  "*menuBar*autoScale.accelerator:	Ctrl<Key>A",
  "*menuBar*autoScale.acceleratorText:	Ctrl-A",
  "*menuBar*clearPlot.labelString:	Clear current plot",
  "*menuBar*clearPlot.mnemonic:		C",
  "*menuBar*clearPlot.accelerator:	Ctrl<Key>C",
  "*menuBar*clearPlot.acceleratorText:	Ctrl-C",
  "*menuBar*unZoom.labelString:		Un-Zoom",
  "*menuBar*unZoom.mnemonic:		U",
  "*menuBar*unZoom.accelerator:		Ctrl<Key>U",
  "*menuBar*unZoom.acceleratorText:	Ctrl-U",
  /*
   * Generic horizontal RC.
   */
  "*plRC*XmLabel.recomputeSize:		False",
  "*plRC*XmLabel.width:			100",
  "*plRC*XmLabel.alignment:		ALIGNMENT_END",
  "*plRC.orientation:			HORIZONTAL",
  "*pnRC.orientation:			HORIZONTAL",
  "*plRC.marginHeight:			1",
  /*
   * Control window
   */
  "*controlRC*XmFrame.shadowType:	SHADOW_IN",
  "*movieRC*XmFrame.shadowType:		SHADOW_IN",

  "*controlRC.width:			300",
  "*controlRC.resizeWidth:		False",

  "*controlRC*XmRowColumn.spacing:	0",
  "*movieRC*XmRowColumn.spacing:	0",

  "*XmFrame.XmLabel.childHorizontalAlignment: ALIGNMENT_CENTER",
  "*XmFrame.XmLabel.childVerticalAlignment:   ALIGNMENT_BASELINE_BOTTOM",
  "*XmFrame.XmLabel.childHorizontalSpacing:   5",
  "*XmFrame.XmLabel.childType:                FRAME_TITLE_CHILD",

  "*plotRC.orientation:			HORIZONTAL",
  "*probeRC.numColumns:			3",
  "*probeRC.packing:			PACK_COLUMN",

  "*dataRC.numColumns:			2",
  "*dataRC.packing:			PACK_COLUMN",

  "*plRC*rtText.columns:		6",
  "*plRC*rtText.maxLength:		6",
  "*timeText.columns:			8",
  "*timeText.maxLength:			10",
  "*averageText.columns:		5",
  "*averageText.maxLength:		5",
  /*
   * Movie Control Window
   */
  "*movieShell.title:			Movie Control",
  "*movieShell.x:			800",
  "*movieShell.y:			550",

  "*movieRC*XmScale.orientation:	HORIZONTAL",
  "*movieRC*timeScale.titleString:	Start            Time warp           Finish",
  "*movieRC*delayScale.titleString:	0          Frame delay (seconds)          4",
  "*movieRC*delayScale.decimalPoints:	3",
  "*movieRC*delayScale.maximum:		2000",
  "*movieRC*delayScale.scaleMultiple:	250",
  "*movieRC*delayScale.showValue:	True",

  "*pgButtRC.entryAlignment:		ALIGNMENT_CENTER",
  "*pgButtRC.orientation:		HORIZONTAL",
  "*pgButtRC.XmPushButton.recomputeSize:	False",
  "*movieRC*pgButtRC.XmPushButton.width:	75",

  "*pageRC.entryAlignment:		ALIGNMENT_CENTER",
  "*pageFwd.labelString:		Page Fwd",
  "*pageBkd.labelString:		Page Bkd",

  "*nPanMenu.labelString:		Panels",
  "*normPanMenu.labelString:		Normalization",
  /*
   * Printer Setup Window
   */
  "*printShell.title:			Printer Setup",
  "*prOpMenu.labelString:		Printer",
  "*printParmsRC*lbl0.labelString:	Print command",
  "*printParmsRC*txt0.columns:		40",
  "*printParmsRC*txt0.maxLength:	40",
  "*printParmsRC*lbl1.labelString:	Plot Width",
  "*printParmsRC*txt1.columns:		10",
  "*printParmsRC*txt1.maxLength:	10",
  "*printParmsRC*lbl2.labelString:	Plot Height",
  "*printParmsRC*txt2.columns:		10",
  "*printParmsRC*txt2.maxLength:	10",
  /*
   * Edit Parameter Window
   */
  "*editXYShell.title:			Edit Movie Parameters",
  "*editXYShell.x:			350",
  "*editXYShell.y:			270",
  /*
   * Edit Diameters
   */
  "*editDiamsShell.title:		Edit Cell Diameters",
  "*diamRC.width:			700",
  "*diamRC*diamTxt.columns:		96",
  "*diamRC*diamTxt.maxLength:		120",
  "*diamRC*startBin.columns:		4",
  "*diamRC*startBin.maxLength:		4",
  "*diamRC*endBin.columns:		4",
  "*diamRC*endBin.maxLength:		4",
  "*diamRC*miscLabel.width:		200",
  "*diamRC*miscTxt.columns:		15",
  "*diamRC*miscTxt.maxLength:		15",
  "*diamRC*XmFrame.shadowType:		SHADOW_IN",

  "*minMaxRC*plRC*XmLabel.width:	90",
  "*ticsRC*plRC*XmLabel.width:		110",
  "*plRC*titleTxt.columns:		40",
  "*plRC*titleTxt.maxLength:		80",
  "*plRC*subTitleTxt.columns:		40",
  "*plRC*subTitleTxt.maxLength:		80",
  "*plRC*labelTxt.columns:		40",
  "*plRC*labelTxt.maxLength:		40",
  "*plRC*xMax.width:			75",
  "*plRC*yMax.width:			75",
  "*plRC*zMax.width:			75",
  "*plRC*minMaxTxt.columns:		13",
  "*plRC*minMaxTxt.maxLength:		15",
  "*plRC*ticTxt.columns:		10",
  "*plRC*ticTxt.maxLength:		10",

  "*applyButton.labelString:		Apply",
  "*dismissButton.labelString:		Dismiss",
  "*printButton.labelString:		Print",
  "*resetButton.labelString:		Reset",
  "*saveButton.labelString:		Save",
  "*searchButton.labelString:		Search",
  "*searchTxt.columns:			12",
  "*searchTxt.maxLength:		32",
  "*parmsButton.labelString:		Edit Parms",
  /*
   *       Dialog Boxes
   */
  "*fileBox.defaultPosition:            FALSE",
  "*fileBox.x:                          130",
  "*fileBox.y:                          200",
  "*fileBox*textColumns:                50",
  "*fileBox*dialogTitle:                Select a File",
  "*errorBox.defaultPosition:           FALSE",
  "*errorBox.x:                         350",
  "*errorBox.y:                         300",
  "*errorBox*background:                DarkSlateGray",
  "*errorBox*dialogStyle:               DIALOG_FULL_APPLICATION_MODAL",
  "*errorBox*dialogTitle:               Error Message",
  "*errorBox*foreground:                Red",
  "*errorBox*XmLabel.alignment:         ALIGNMENT_CENTER",
  "*queryBox*dialogStyle:               DIALOG_FULL_APPLICATION_MODAL",
  "*queryBox*dialogTitle:               Need input",
  "*queryBox*alignment:                 ALIGNMENT_CENTER",
  "*warnBox.defaultPosition:            FALSE",
  "*warnBox.x:                          350",
  "*warnBox.y:                          300",
  "*warnBox*background:                 DarkSlateGray",
  "*warnBox*dialogStyle:		DIALOG_FULL_APPLICATION_MODAL",
  "*warnBox*dialogTitle:                Warning Message",
  "*warnBox*foreground:                 Yellow",
  "*warnBox*XmLabel.alignment:          ALIGNMENT_CENTER",
  NULL
  };
