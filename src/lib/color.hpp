//
// Created by tmai42 on 12/5/23.
//

#ifndef COLOR_HPP
#define COLOR_HPP

#include "vector3D.hpp"

using color = vector3D;

// This function does not implement new line switching, so you need to add it manually
// it simply writes color to std::ostream &out color in format "R G B"
void write_color(std::ostream &out, color pixel_color) {
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(255.999 * pixel_color.x()) << ' '
        << static_cast<int>(255.999 * pixel_color.y()) << ' '
        << static_cast<int>(255.999 * pixel_color.z());
}
#endif // COLOR_HPP

