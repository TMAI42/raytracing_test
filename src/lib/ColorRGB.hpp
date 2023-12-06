//
// Created by tmai42 on 12/5/23.
//

#ifndef COLOR_HPP
#define COLOR_HPP

#include "Vector3D.hpp"

using ColorRGB = Vector3D;

// This function does not implement new line switching, so you need to add it manually
// it simply writes ColorRGB to std::ostream &out ColorRGB in format "R G B"
void write_color(std::ostream &out, ColorRGB pixel_color) {
    // Write the translated [0,255] value of each ColorRGB component.
    out << static_cast<int>(255.999 * pixel_color.X()) << ' '
        << static_cast<int>(255.999 * pixel_color.Y()) << ' '
        << static_cast<int>(255.999 * pixel_color.Z());
}
#endif // COLOR_HPP

