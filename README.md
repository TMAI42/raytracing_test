
# Simple Ray Tracing Renderer

## Overview
This project is a basic ray tracing renderer implemented in C++. It's designed as an initial framework for more complex ray tracing applications. The program currently renders images in the PPM (Portable Pixmap) format when executed and redirected to a file.

## Building the Project
Ensure you have CMake installed and a C++ compiler that supports C++23.

### Prerequisites
- C++23 compatible compiler
- CMake (version 3.26 or higher)

### Compilation
1. Clone the repository.
2. Navigate to the project directory.
3. Run the following commands:

```bash
mkdir build
cd build
cmake ..
make
```

This will compile the source code and generate an executable.

### Running the Renderer
To generate a .ppm image, run the executable and redirect the output to a file:

```bash
./raytracing_test > image.ppm
```

## Code Structure
- `main.cpp`: The main driver of the program. It sets up the rendering parameters and initiates the rendering process.
- `lib/ray.hpp`: Defines the `ray` class, which represents rays in the ray tracing algorithm.
- `lib/color.hpp`: Handles color representations and color utility functions.
- `hit_sphere()`: A function in `main.cpp` that checks if a ray hits a given sphere.
- `ray_color()`: Determines the color of a pixel based on the ray's interaction with objects in the scene.

## Output
The output image is saved in the PPM format. PPM files can be viewed with various image viewers or converted to other formats using image processing tools.

## Future Enhancements
- Adding support for multiple objects and complex scenes.
- Implementing advanced lighting and shading techniques.
- Adding texture and material properties to objects.
