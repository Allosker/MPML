# MPML -- Multi-Purpose Math Library

## Purpose of MPML

MPML is a Multi-Purpose Math Library (hence the acronym) with a special emphasis on **Graphics Mathematics**; as such, the library is meant to be used with *OpenGL*, *DirectX*, and *Vulkan*. 
The library is being tested and updated regularly as it is part of my *Voxel Engine* which utilizes MPML at its core.

## Features

MPML features a wide range of *mathematical operations*:

- **Angles**
  - Single abstraction class
- **Vectors**
  - 2D
  - 3D
  - 4D
- **Matrices**
  - 2x2
  - 3x3
  - 4x4
- **Quaternions**
- **Utility Functions**
  - Tensors

### Data Organization

Matrices are ordered following the Row-Major convention.

## Design Goals

- Provide a consistant interface across various types and mathematical concepts.
- Maintain balance between flexibility and performances:
    - All operations for all threee matrices/vector types are hardcoded, which performs better.
- Remain:
  - Dependency-free
  - Cmake compatible
  - Easy to integrate and use
- Provide suitability for modern C++ as the library is *constexpr friendly*.
- Provide a large range of utility functions for *tensors*.

#### Last words

The library is currently under maintenance — new updates may come at any time.

The library is free to use as per its [license](https://github.com/Allosker/MPML/blob/master/LICENSE.txt).




