# ncpp
Display program for viewing size-distributions from aircraft netCDF files.

ncpp is a X11-Motif based GUI program for looking at counts and size-distributions from RAF aircraft netCDF files.


## Documentation

[User's Manual](https://www.eol.ucar.edu/raf/Software/ncpp.html).\
[RAF netCDF file conventions](https://www.eol.ucar.edu/raf/Software/netCDF.html).\
[MacOS build environment](https://github.com/ncar/aircraft_oap/wiki/MacOS-Build-Environment).


## Build

ncpp can be built on any Unix platform, including MacOS.  Motif GUI toolkit is the limiting factor.

```
git clone --recursive https://github.com/ncar/ncpp
cd ncpp
scons
```

    
