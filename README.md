# MPML -- Multi-Purpose Math Library

## Purpose of MPML

MPML is a Multi-Purpose Math Library (hence the acronym) with a special emphasis on **Graphics Mathematics**; as such, the library is meant to be used with *OpenGL*, *DirectX*, and *Vulkan*. 
MPML was mainly written as part of my own ecosystem (along with many more libraries) which are all meant to be used with my forthcoming **Graphics Engine**; MPML aspires to be at its core.

## Features

MPML shall feature a wide range of *mathematical operations* but is for now limited to what is necessary:

- **Constants**
- **Ranges** (in developement)
- **Angles**
- **Vectors**
  - 2D
  - 3D
  - 4D (operates like 3D)
- **Matrices**
  - 2x2
  - 3x3
  - 4x4
- **Quaternions**
- **Utility Functions**
  - Tensors

### Specialized Types

MPML is designed to be Multi-Purpose (even though its current state may say otherwise), thereby possessing generalized types. As such, generalized *vectors*, *matrices*, and *quaternions* are indexed types and can be accessed via `operator[]`. While less intuitive than an *anonymous struct*, this allows for more flexibility when accessing multi-dimensional matrices/vectors.
(As of the day of writing no such type is yet availble).

## Design Goals

- Provide a consistant interface across various types and mathematical concepts.
- Maintain balance between flexibility and performances.
- Remain:
  - Dependency-free
  - Header-only
  - Easy to integrate and use
- Provide suitability for modern C++ as the library is *constexpr friendly*.

#### Last words

The library is free to use as per its [license](https://github.com/Allosker/MPML/blob/master/LICENSE.txt). Note: this is subject to changes.




