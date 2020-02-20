# ncpp
Display program for viewing size-distributions from aircraft netCDF files.

ncpp is a X11-Motif based GUI program for looking at counts and size-distributions from RAF aircraft netCDF files.


## Documentation

https://www.eol.ucar.edu/raf/software/ncpp.html User's manual.
https://www.eol.ucar.edu/raf/Software/netCDF.html describes netCDF conventions used.  
https://github.com/ncar/aircraft_oap/wiki/MacOS-Build-Environment for building on MacOS.

## Build

ncpp can be built on any Unix platform, including MacOS.  Motif GUI toolkit is the limiting factor.

```
git clone --recursive https://github.com/ncar/ncpp
cd ncplot
```
    
If you are on MacOS, follow MacOS Environment instructions above and edit the Makefile and uncomment the MacOS section.

```
scons
```

    
