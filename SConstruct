#!python

import eol_scons


def ncpp(env):
    if env['PLATFORM'] == 'darwin' and env['HOST_ARCH'] == 'arm64':
        env['DEFAULT_OPT_PREFIX']='/opt/homebrew'

    env.Require(['default', 'prefixoptions'])

env = Environment(GLOBAL_TOOLS = [ncpp])

env.Require(['openmotif', 'netcdfcxx4', 'raf'])

env.Append(CXXFLAGS='-std=c++20 -g -Wall -Wno-write-strings -Wstrict-aliasing -Wno-deprecated-register')

env.Append(CPPDEFINES=['PNG'])

# Change default fonts for Ubuntu as the adobe courier is not available.
#env.Append(CPPDEFINES=['UBUNTU'])

env.Prepend(CPPPATH=['#/class'])

env.Append(LIBS=['png'])
env.Append(LIBS=['z'])

#env.Append(LIBPATH=['#/raf'])
env['PUBLISH_PREFIX'] = '/net/www/docs/raf/Software'


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
class/hdc.cc
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


ncpp = env.Program(target = 'src/ncpp', source = sources)
env.Default(ncpp)

#env.Alias('install', env.Install([$INSTALL_PREFIX + '/bin'], 'src/ncpp'))
env.Install('$INSTALL_PREFIX/bin', 'src/ncpp')

#env = Environment(tools=['default'])

if "publish" in COMMAND_LINE_TARGETS:
   pub = env.Install('$PUBLISH_PREFIX', ["src/ncpp.html"])
   env.Alias('publish', pub)

#env.SetHelp()
#env.AddHelp("""
#Targets:
#publish:  Copy html documentation to EOL web space : $PUBLISH_PREFIX.
#""")
