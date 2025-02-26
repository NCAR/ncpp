# ncpp
Display program for viewing size-distributions from aircraft netCDF files.

ncpp is a X11-Motif based GUI program for looking at counts and size-distributions from RAF aircraft netCDF files.


## Documentation

[User's Manual](https://www.eol.ucar.edu/raf/Software/ncpp.html).  
[RAF netCDF file conventions](https://www.eol.ucar.edu/raf/Software/netCDF.html).  
[MacOS build environment](https://github.com/ncar/aircraft_oap/wiki/MacOS-Build-Environment).

## Build


### MacOS

ncpp is available via [MacPorts](https://www.macports.org/) or follow the [MacOS build environment](https://github.com/ncar/aircraft_oap/wiki/MacOS-Build-Environment) directions to build from source.

### Dependencies

Redhat / CentOS / Alma
```
openmotif-devel (motif-devel CentOS 8 & later)
netcdf-devel
netcdf-cxx4-devel
xorg-x11-fonts-ISO8859-1-75dpi
xorg-x11-fonts-ISO8859-1-100dpi
```

Ubuntu Focal (20.04)
```
libnetcdf-cxx4-dev
libmotif-dev
libnetcdf-dev
```


ncpp can be built on any Unix platform, including MacOS.  Motif GUI toolkit is the limiting factor.

```
git clone --recursive https://github.com/ncar/ncpp
cd ncpp
```
Edit the SConstruct file and uncomment this line (remove the '#') for Ubuntu:
```
#env.Append(CPPDEFINES=['UBUNTU'])
```
and build:
```
scons
```
