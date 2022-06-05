#include "Point.h"

// CTORs / DTOR

Point::Point(int x, int y): m_x(x), m_y(y) {}

Point::Point(const Point &other): m_x(other.m_x), m_y(other.m_y) {}

Point::~Point() {}

// Public Methods

int Point::getX() const {
    return m_x;
}

int Point::getY() const {
    return m_y;
}

void Point::setX( int x ) {
    m_x = x;
}

void Point::setY( int y ) {
    m_y = y;
}

void Point::setPoint( int x, int y ) {
    m_x = x;
    m_y = y;
}

void Point::setPoint( const Point & other ) {
    m_x = other.getX();
    m_y = other.getY();
}

// Operators

// Used as friend method in class declaration
// returns a new point with (x,y)*num
Point operator*( int num, const Point& other ) {
    Point resultPoint(other);
    resultPoint.setX(resultPoint.getX() * num);
    resultPoint.setY(resultPoint.getY() * num);
    return resultPoint;
}

//returns true if and only if the two points are equal
bool Point::operator==( const Point& other ) const {
    return m_x == other.m_x && m_y == other.m_y;
}

//returns true if and only if the two points are not equal
bool Point::operator!=( const Point& other ) const {
    return m_x != other.m_x || m_y != other.m_y;
}

// returns a new point with updated x(x+num) and y(y+num)
Point Point::operator+( int num ) const {
    Point resultPoint(*this);
    resultPoint.setX(resultPoint.getX() + num);
    resultPoint.setY(resultPoint.getY() + num);
    return resultPoint;
}

// updates the point with x(x+num) and y(y+num) and returns the updated point
const Point& Point::operator+=( int num ) {
    setX(m_x + num);
    setY(m_y + num);
    return *this;
}

// returns the sum of x and y
Point::operator int() const {
    return getX() + getY();
}

// Add coordinates (x,y) from other Point and returns a new point
Point Point::operator+( const Point& other ) const {
    Point resultPoint(*this);
    resultPoint.setX(other.getX() + getX());
    resultPoint.setY(other.getY() + getY());
    return resultPoint;
}

// adds 1 to x and y and returns the updated point - postfix
Point Point::operator++( int ) {
    Point resultPoint(*this);
    setX(getX() + 1);
    setY(getY() + 1);
    return resultPoint;
}

// adds 1 to x and y and returns the updated point - prefix
const Point& Point::operator++() {
    setX(getX() + 1);
    setY(getY() + 1);
    return *this;
}
