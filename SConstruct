#!python

import os
env = Environment(platform = 'posix',ENV= os.environ)

try: env['JLOCAL'] = os.environ['JLOCAL']
except KeyError:
    print "\n$JLOCAL not found!  Defaulting to '/opt/local'\n"
    env['JLOCAL'] = '/opt/local/'

env['CPPPATH'] = Split("""
    #/libraf
    #/class
    $JLOCAL/include
    /usr/include/netcdf
""")

env['CCFLAGS'] = Split("""
    -Wall -g -Wno-write-strings -Wstrict-aliasing
""")

env['CPPDEFINES'] = Split("""
    -DPNG
""")

env['LIBPATH'] = Split("""
    #/libraf
    $JLOCAL/lib
""")

env['LIBS'] = Split("""
  raf
  Xm Xt X11 Xext
  netcdf_c++ netcdf hdf5_hl hdf5 
  png z
""")


Export('env')

SConscript('libraf/SConscript')

sources = Split("""
class/2D.cc
class/Ascii.cc
class/CanvasWindow.cc
class/Colors.cc
class/DataFile.cc
class/DataSet.cc
class/DataSource.cc
class/EditDiameters.cc
class/EditPlotParms.cc
class/EditWindow.cc
class/FileMgr.cc
class/Header.cc
class/MovieControl.cc
class/Panel.cc
class/PlotInfo.cc
class/PlotMgr.cc
class/Probe.cc
class/Probe100.cc
class/Probe200.cc
class/SetMgr.cc
class/Titles.cc
class/VarsWin.cc
class/cdp.cc
class/f300.cc
class/fssp.cc
class/hvps.cc
class/pcasp.cc
class/s100.cc
class/s200.cc
class/uhsas.cc
class/x200.cc
class/x260.cc
class/y200.cc
src/autoscale.cc
src/cb_canvas.cc
src/cb_control.cc
src/cb_edit.cc
src/cb_menus.cc
src/cb_movie.cc
src/cb_printer.cc
src/cb_text.cc
src/ccb.cc
src/global.cc
src/ncpp.cc
src/ticlabel.cc
""")


env.Program(target = 'src/ncpp', source = sources)