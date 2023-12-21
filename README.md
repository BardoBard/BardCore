[![nuget-downloads](https://img.shields.io/nuget/dt/Bardcore.svg)](https://www.nuget.org/packages/Bardcore/)
[![issues](https://img.shields.io/github/issues/bardobard/bardcore.svg)](https://github.com/bardobard/bardcore/issues)

[![nuget](https://img.shields.io/nuget/v/Bardcore.svg)](https://www.nuget.org/packages/Bardcore/)
[![nuget-github](https://img.shields.io/nuget/vpre/Bardcore.svg?label=nuget-github)](https://github.com/bardobard/bardcore/pkgs/nuget/BardCore)

# Bardcore

---

[![build-and-test](https://github.com/bardobard/bardcore/actions/workflows/Build-Test-Windows.yml/badge.svg)](https://github.com/bardobard/bardcore/actions?query=workflow%3Build-Test-Windows.yml)

#### C++ 14/17/20 compatible [^flag]

Bardcore is a simple 3D mathematics library that is primarily designed for use in raytracing applications.
It includes vectors, points, quaternion rotation and some useful math functions.

The goal is to provide a simple, easy to use library that is fast and efficient. One of the future ideas is to make an
opengl wrapper around it.

I've tried to make everything constexpr where possible, so that the compiler can do as much work as possible at compile
time.

Please refer to the [wiki](https://github.com/BardoBard/BardCore/wiki/Introduction) for more information.

[^flag]: *In order to use the c++ 14/17/20 you have to use the /Zc:__cplusplus flag, it's automatically included (.target) but it might not be [compatible](https://learn.microsoft.com/en-us/cpp/build/reference/zc-cplusplus?view=msvc-170#remarks) with other packages, keep that in mind.*
