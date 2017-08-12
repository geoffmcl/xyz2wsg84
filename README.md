xyz2wsg project
---------------

**Overview**

Wanted a simple program to convert geocentric X Y Z coordinates to lat lon height... and the **reverse**...

Found an `old`, circa 2003-2005, source here - https://www.ngs.noaa.gov/PC_PROD/XYZWIN/ - the original zip, is stored in zip/xyzwin.org.zip, in case the above `disappears`....

It was not too difficult to construct a CMakeLists.txt to build it, as **xyz2wsg.exe**, and it works ok, but seems to have some problems... did not give the expected result in some specific cases. Not sure why... Also did not particularly like the UI... you have to pipe the values into it...

So another search found [geographiclib](https://geographiclib.sourceforge.io/). I had previously downloaded the 1.47 revision, built and installed it, but had **not** noted at the time it also includes such a `converter`...

This time I `forked` the sf git source to - https://sourceforge.net/u/geoffmc/geographiclib/ci/master/tree/ - cloned to X:\geographiclib-code, built the `release` **1.48** branch, and installed to X:\3rdParty.x64.

Copied the given `FindGeographicLib.cmake` to a CMakeModules folder, added a small change to also find the Debug library version if MSVC, and created and built an `xyz2wsg.cxx`, as **xyz2wsg84.exe**, using the geographiclib, and it gives the expected results...

**Building**

As with all my projects, this is a [CMake](https://cmake.org/) project, to be able to generate cross-port build files in most systems, so the build process is -

For Unix, assuming the native makefile tools chosen -

```
$ cd build
$ cmake .. [options]
$ make
$ [sudo] make install (if desired)
```

For Windows, assuming say a relatively recent MSVC has been installed -

```
> cd build
> cmake .. [options]
> cmake --build . --config Release
> copy the binaries to a folder in your PATH
```

**License**

Released under GNU GPL version 2. See LICENCE.txt

The original `xygwin` source does **not** appear to have a licence document...

Have fun...  
Geoff 20170812

; eof
