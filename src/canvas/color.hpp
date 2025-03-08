#ifndef COLOR_HPP
#define COLOR_HPP

using namespace std ; 

using namespace std;
struct RGBA {
    float r, g, b, a;
    RGBA() : r(255), g(255), b(255), a(255) {}
    RGBA(float _r, float _g, float _b, float _a)
      : r(_r), g(_g), b(_b), a(_a) {}

    RGBA operator+(const RGBA& other) const {
        return {r + other.r, g + other.g, b + other.b, a + other.a};
    }

    RGBA operator-(const RGBA& other) const {
        return {r - other.r, g - other.g, b - other.b, a - other.a};
    }

    RGBA operator*(float f) const {
        return {r*f, g*f, b*f, a*f};
    }

    RGBA operator/(float f) const {
        return {r/f, g/f, b/f, a*f};
    }
};


// // mocha theme 
// const RGBA Rosewater(245, 224, 220, 255);
// const RGBA Flamingo(242, 205, 205, 255);
// const RGBA Pink(245, 194, 231, 255);
// const RGBA Mauve(203, 166, 247, 255);
// const RGBA Red(243, 139, 168, 255);
// const RGBA Maroon(235, 160, 172, 255);
// const RGBA Peach(250, 179, 135, 255);
// const RGBA Yellow(249, 226, 175, 255);
// const RGBA Green(166, 227, 161, 255);
// const RGBA Teal(148, 226, 213, 255);
// const RGBA Sky(137, 220, 235, 255);
// const RGBA Sapphire(116, 199, 236, 255);
// const RGBA Blue(137, 180, 250, 255);
// const RGBA Lavender(180, 190, 254, 255);
// const RGBA White(205, 214, 244, 255);
// const RGBA Subtext1(186, 194, 222, 255);
// const RGBA Subtext0(166, 173, 200, 255);
// const RGBA Overlay2(147, 153, 178, 255);
// const RGBA Overlay1(127, 132, 156, 255);
// const RGBA Overlay0(108, 112, 134, 255);
// const RGBA Surface2(88, 91, 112, 255);
// const RGBA Surface1(69, 71, 90, 255);
// const RGBA Surface0(49, 50, 68, 255);
// const RGBA Base(30, 30, 46, 255);
// const RGBA Black(24, 24, 37, 255);
// const RGBA Crust(17, 17, 27, 255);


// Macchiato theme 
// const RGBA Rosewater(244, 219, 214, 255);
// const RGBA Flamingo(240, 198, 198, 255);
// const RGBA Pink(245, 189, 230, 255);
// const RGBA Mauve(198, 160, 246, 255);
// const RGBA Red(237, 135, 150, 255);
// const RGBA Maroon(238, 153, 160, 255);
// const RGBA Peach(245, 169, 127, 255);
// const RGBA Yellow(238, 212, 159, 255);
// const RGBA Green(166, 218, 149, 255);
// const RGBA Teal(139, 213, 202, 255);
// const RGBA Sky(145, 215, 227, 255);
// const RGBA Sapphire(125, 196, 228, 255);
// const RGBA Blue(138, 173, 244, 255);
// const RGBA Lavender(183, 189, 248, 255);
// const RGBA White(202, 211, 245, 255);
// const RGBA Subtext1(184, 192, 224, 255);
// const RGBA Subtext0(165, 173, 203, 255);
// const RGBA Overlay2(147, 154, 183, 255);
// const RGBA Overlay1(128, 135, 162, 255);
// const RGBA Overlay0(110, 115, 141, 255);
// const RGBA Surface2(91, 96, 120, 255);
// const RGBA Surface1(73, 77, 100, 255);
// const RGBA Surface0(54, 58, 79, 255);
// const RGBA Base(36, 39, 58, 255);
// const RGBA Black(30, 32, 48, 255);
// const RGBA Crust(24, 25, 38, 255);

// Frappé theme 

const RGBA Rosewater(242, 213, 207, 255);
const RGBA Flamingo(238, 190, 190, 255);
const RGBA Pink(244, 184, 228, 255);
const RGBA Mauve(202, 158, 230, 255);
const RGBA Red(231, 130, 132, 255);
const RGBA Maroon(234, 153, 156, 255);
const RGBA Peach(239, 159, 118, 255);
const RGBA Yellow(229, 200, 144, 255);
const RGBA Green(166, 209, 137, 255);
const RGBA Teal(129, 200, 190, 255);
const RGBA Sky(153, 209, 219, 255);
const RGBA Sapphire(133, 193, 220, 255);
const RGBA Blue(140, 170, 238, 255);
const RGBA Lavender(186, 187, 241, 255);
const RGBA White(198, 208, 245, 255);
const RGBA Subtext1(181, 191, 226, 255);
const RGBA Subtext0(165, 173, 206, 255);
const RGBA Overlay2(148, 156, 187, 255);
const RGBA Overlay1(131, 139, 167, 255);
const RGBA Overlay0(115, 121, 148, 255);
const RGBA Surface2(98, 104, 128, 255);
const RGBA Surface1(81, 87, 109, 255);
const RGBA Surface0(65, 69, 89, 255);
const RGBA Base(48, 52, 70, 255);
const RGBA Black(41, 44, 60, 255);
const RGBA Crust(35, 38, 52, 255);

// // Latte theme 


// const RGBA Rosewater(220, 138, 120, 255);
// const RGBA Flamingo(221, 120, 120, 255);
// const RGBA Pink(234, 118, 203, 255);
// const RGBA Mauve(136, 57, 239, 255);
// const RGBA Red(210, 15, 57, 255);
// const RGBA Maroon(230, 69, 83, 255);
// const RGBA Peach(254, 100, 11, 255);
// const RGBA Yellow(223, 142, 29, 255);
// const RGBA Green(64, 160, 43, 255);
// const RGBA Teal(23, 146, 153, 255);
// const RGBA Sky(4, 165, 229, 255);
// const RGBA Sapphire(32, 159, 181, 255);
// const RGBA Blue(30, 102, 245, 255);
// const RGBA Lavender(114, 135, 253, 255);
// const RGBA White(76, 79, 105, 255);
// const RGBA Subtext1(92, 95, 119, 255);
// const RGBA Subtext0(108, 111, 133, 255);
// const RGBA Overlay2(124, 127, 147, 255);
// const RGBA Overlay1(140, 143, 161, 255);
// const RGBA Overlay0(156, 160, 176, 255);
// const RGBA Surface2(172, 176, 190, 255);
// const RGBA Surface1(188, 192, 204, 255);
// const RGBA Surface0(204, 208, 218, 255);
// const RGBA Base(239, 241, 245, 255);
// const RGBA Black(230, 233, 239, 255);
// const RGBA Crust(220, 224, 232, 255);


#endif // COLOR_HPP


