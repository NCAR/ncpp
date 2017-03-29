#!python

import os
import eol_scons

env = Environment(tools = ['default', 'openmotif', 'netcdf'], ENV= os.environ)

try: env['JLOCAL'] = os.environ['JLOCAL']
except KeyError:
    env.Append(CPPPATH=['#/libraf'])
    env.Append(LIBPATH=['#/libraf'])
else:
    env.Append(CPPPATH=['$JLOCAL/include'])
    env.Append(LIBPATH=['$JLOCAL/lib'])

env.Append(CPPPATH=['#/class'])

env.Append(CCFLAGS=['-Wall'])
env.Append(CCFLAGS=['-Wno-write-strings'])
env.Append(CCFLAGS=['-Wstrict-aliasing'])

env.Append(CPPDEFINES=['-DPNG'])
if env['PLATFORM'] == 'darwin':
  env.Append(CPPDEFINES=['-DPNG15'])


env.Append(LIBS=['raf'])
env.Append(LIBS=['png'])
env.Append(LIBS=['z'])

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
class/ncHeader.cc
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

env.Alias('install', env.Install([env['JLOCAL'] + '/bin'], 'src/ncpp'))
