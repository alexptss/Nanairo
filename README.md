# Nanairo #

![cover](https://github.com/byzin/Nanairo/wiki/image/RaytracingCamp4.png)

**Nanairo** is a physically plausible spectral renderer.

Version: 0.0.2

## Description ##

### Demo ###

![Demo](https://github.com/byzin/Nanairo/wiki/image/NanairoDemo.gif)

### Features ###

**Monte calro ray tracing method**

* Path tracing
* Light tracing
* Progressive photon mapping [[paper](http://www.cgg.unibe.ch/publications/2011/progressive-photon-mapping-a-probabilistic-approach)]

**BVH**

* Binary radix tree [[paper](https://research.nvidia.com/publication/maximizing-parallelism-construction-bvhs-octrees-and-k-d-trees)]
* Approximate agglomerative clustering [[paper](http://graphics.cs.cmu.edu/projects/aac/)]
* Agglomerative treelet restructuring [[paper](http://dl.acm.org/citation.cfm?doid=2790060.2790065)]

**Surface**

* Smooth diffuse surface (Lambert BRDF)
* Smooth conductor surface (Fresnel BRDF)
* Smooth dielectric surface (Fresnel BSDF)
* Rough conductor surface (GGX BRDF) [[paper](https://hal.inria.fr/hal-00996995v2)]
* Rough dielectric surface (GGX BSDF) [[paper](https://hal.inria.fr/hal-00996995v2)]
* Layered diffuse surface (Interfaced Lambertian BRDF) [[paper](https://hal-unilim.archives-ouvertes.fr/hal-01246612/)]
* Cloth surface (Microcylinder cloth BRDF) [[paper](http://dl.acm.org/citation.cfm?id=2451240)]

**Camera**

* Pinhole camera

**Color**

* Spectra (point sampling) [[paper](http://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.68.1533)]
* Spectral transport from RGB [[paper](http://dl.acm.org/citation.cfm?id=2853793)]

**Geometry**

* Triangle meshes (support Wavefront .obj file)
* Nagata patch (normal interpolation) [[paper](http://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.129.9689)], ray intersection [[paper](https://www.osapublishing.org/ao/abstract.cfm?uri=ao-49-18-3442)]
* Orthonormal basis [[paper](http://jcgt.org/published/0006/01/01/)]

**Tone mappling**

* Reinhard [[paper](https://www.cs.utah.edu/~reinhard/cdrom/)]
* Filmic
* Uncharted2

## Requirement ##

### Compiler ###

* C++14 support compiler

### Build tools ###

* CMake (version 3.4 or later) [[page](http://www.cmake.org/)]

### Dependency Library ###

* Qt (version 5.6.0 or later) [[page](http://qt-project.org/)]

## Usage ##
Please see [wiki](https://github.com/byzin/Nanairo/wiki/Home "NanairoWiki").

## Installation ##

### Test environments ###
Building step is tested in the following environments  

* Mac Mavericks + Apple Clang 8.0 + Qt 5.9.1 + CMake 3.8.2
* Mac Mavericks + GCC 7.1 + Qt 5.9.1 + CMake 3.8.2
* Ubuntu 16.04 + GCC 5.4 + Qt 5.9.1 + CMake 3.8.2
* Ubuntu 16.04 + Clang 4.0 + Qt 5.9.1 + CMake 3.8.2
* Windows 8 (64bit) + MinGW GCC 7.1 + Qt 5.9.1 + CMake 3.8.2
* Windows 8 (64bit) + Clang 4.0.1 with MSVC (Visual Studio 2015) + Qt 5.9.1 + CMake 3.8.2

### Download source code ###

```
% git clone https://github.com/byzin/Nanairo
% cd Nanairo
% git submodule init
% git submodule update
```

### Setup ###
To build Nanairo, you need to add the Qt qmake path to **$PATH**.  
``% export PATH=${qmake_path}:$PATH``  
For example, on Mac, qmake path is maybe ``${qt_root}/${qt_version}/clang_64/bin``  

#### Python environment setup ####
Please see [wiki](https://github.com/byzin/Nanairo/wiki/Python-environment-setup "Python environment setup") for details.

### Build ###
Please see [wiki](https://github.com/byzin/Nanairo/wiki/Home "NanairoWiki")
for details.

First, You need to move the build directory.  
``% cd ${project_root}/build``

Next, we generate a Makefile using cmake.

#### On Mac or Linux ####

GCC  
```
% CC=gcc CXX=g++ cmake -DCMAKE_BUILD_TYPE=Release ..
% cmake --build .
```

Clang  
```
% CC=clang CXX=clang++ cmake -DCMAKE_BUILD_TYPE=Release -DZ_CLANG_USES_LIBCXX=ON ..
% cmake --build .
```

#### On Windows (MSVC) ####

Visual Studio 2015 64bit
```
% cmake -G"Visual Studio 14 2015 Win64" -TLLVM-vs2014 -DCMAKE_BUILD_TYPE=Release ..
% cmake --build . --config Release
```

#### On Windows (MinGW) ####

```
% cmake -G"MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..
% cmake --build .
```

### Packaging ###

Only **Windows** and **Mac** are supported.

After release building,
```
% cpack -C Release
```

## License ##
[MIT-LICENSE.txt](./MIT-LICENSE.txt)
except for *3d model* (resources/model) and *spectrum* (resources/spectrum) files.

## Acknowledgement ##
Please see [Acknowledgement.md](./Acknowledgement.md).
