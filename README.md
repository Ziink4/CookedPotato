# CookedPotato
## Requirements
- CMake
- Boost (for Wt)
- Wt
- Doxygen (for the Documentation)

## How To Build
1) Configure build with CMake
2) Build
3) Done

*You might need to define `BOOST_ROOT` and `WT_ROOT` for CMake to find the dependencies*

*Please set `POTATO_GENERATE_DOC` to `OFF` if you don't have Doxygen or you don't want to build the documentation*

*If you use Visual Studio with its CMake tools, the CMakeSettings.json should setup the minimal configuration for the project to build*

*Note : Due to a known bug (https://gitlab.kitware.com/cmake/cmake/issues/18738),
Doxygen 1.8.15 is not compatible with CMake <= 3.13.3.
This is especially annoying on Visual Studio because of the old version used by default by the CMake plugin.
To solve this issue : use Doxygen <= 1.8.14 or CMake >= 3.13.4.*

## Frontyard
Default command line : `--docroot . --http-address 127.0.0.1 --http-port 8080`
