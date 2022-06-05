#include "Quad.h"
#include <string.h>

// CTORs / DTOR
Quad::Quad( double up, double down, double right, double left, const char* sn):
    m_up(up), m_down(down), m_left(left), m_right(right), Shape(sn) {}

Quad::Quad(const Quad &other): Shape(other) {
    m_up = other.m_up;
    m_down = other.m_down;
    m_left = other.m_left;
    m_right = other.m_right;
}

Quad::~Quad() {}

//returns the quad's area (right*up) (rounded to int)
int Quad::calcArea() const {
    return (int) (m_right * m_up);
}

//returns the quad's Perimeter (the sum of the four ribs) (rounded to int)
int Quad::calcPerimeter() const {
    return (int) (m_right + m_left + m_up + m_down);
}
