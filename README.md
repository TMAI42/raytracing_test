
# Simple Ray Tracing Renderer

## Overview
Basic ray tracing renderer implemented in C++. 
It is done in educational purposes and still in development stage.

![](example.png)

**Warning:** Do not use this code in your production, it is in early WIP stage  

### Prerequisites
- C++23 compatible compiler
- CMake (version 3.26 or higher)


## Quick Start

### Build
```bash
mkdir build
cd build
cmake ..
make
```

### Run
To generate a .ppm image, run the executable and redirect the output to a file:

```bash
./raytracing_test > image.ppm
```

## Code Specification

### Project Structure
- **Header only style**. This project is done in headers only, for simplicity and implementation speed.
- **C-style** is used in most cases for internal calculation, `std` is used only for places speed does not matter 

## Future Enhancements
- Adding support for multiple objects and complex scenes.
- Adding different object materials 
- Adding different reflection distributions 
- Adding lite sources 
- *MB:* Adding UI interface on screen rendering

## Resources 

- [Math for intersection calculates](https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection.html)
- [.PPM format](https://en.wikipedia.org/wiki/Netpbm#File_formats)
- [Ray tracing book](https://raytracing.github.io/books/RayTracingInOneWeekend.html)