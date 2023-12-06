
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
Ось приклад секції "Code Specification" для вашого файлу README.md, яка описує структуру та логіку коду вашого проекту:


## Code Specification

### Project Structure
This project, being compact in nature, adopts a straightforward and streamlined approach to its codebase structure. We have chosen to use `.hpp` files exclusively for several reasons:

1. **Simplicity**: Given the project's small scale, the separation into header and source files (`.h` and `.cpp`) is deemed unnecessary. This decision simplifies the file structure and makes the code easier to navigate and maintain.

2. **All-in-One Headers**: All class definitions, including their implementations, are encapsulated within `.hpp` files. This approach aligns well with the project's focus on simplicity and quick integration.

3. **Encapsulation**: Although encapsulation is a key principle in object-oriented programming, for this small-scale project, we have prioritized ease of access and readability over strict encapsulation. This choice is reflected in the way classes and functions are structured within the `.hpp` files.

### Include Guards
To prevent multiple inclusions of the same header file, traditional include guards are used in the format:

```cpp
#ifndef HITTABLE_H
#define HITTABLE_H
// Class or function declarations
#endif // HITTABLE_H
```

This conventional method of using `#ifndef`, `#define`, and `#endif` directives is effective and sufficient for guarding against multiple inclusions in our project. This choice supports the project's emphasis on keeping things simple and efficient without the need for more complex solutions.

### Emphasis on Practicality
In summary, the project's code specification is tailored to meet the demands of a small-scale project. Our decisions regarding the file structure and coding practices reflect a focus on practicality, ease of use, and the ability to quickly understand and modify the codebase.

### Code Convention

In this project, we adhere to a C-style coding convention for most internal implementations. This decision is rooted in the following reason:

- **Performance Optimization**: C-style coding conventions are known for their focus on performance. By keeping the code close to the lower-level operations, we aim to maximize efficiency and optimize resource usage.

## Output
The output image is saved in the PPM format. PPM files can be viewed with various image viewers or converted to other formats using image processing tools.

## Future Enhancements
- Adding support for multiple objects and complex scenes.
- Implementing advanced lighting and shading techniques.
- Adding texture and material properties to objects.
