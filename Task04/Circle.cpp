#include "Circle.h"

// CTORs / DTOR

//create a circle with radius=1, name=sn and center=(0,0)
Circle::Circle( double r, const char* sn ): Shape(sn), m_radius(r) {}

//copy constructor
Circle::Circle( const Circle& other ): Shape(other), m_radius(other.m_radius) {}

Circle::~Circle() {}

// Public methods
//returns the circle's radius
double Circle::getRadius() const {
    return m_radius;
}

//set the radius
void Circle::setRadius( double r ) {
    m_radius = r;
}

// Override Virtual Methods
//returns the circle's area (rounded to int)
int Circle::calcArea() const {
    return (int) (PI * (m_radius * m_radius));
}

//returns the circle's Perimeter (rounded to int)
int Circle::calcPerimeter() const {
    return (int) (2 * PI * m_radius);
}

//operator= that copies all
const Circle& Circle::operator=( const Circle& other ) {
    Shape::operator=(other);
    m_radius = other.m_radius;
    return *this;
}

// updates only the name of the shape and returns the updated shape
const Circle& Circle::operator=( const char* name ) {
    setName(name);
    return *this;
}

//returns a new Circle with added radius
Circle operator+( int r, const Circle& other ) {
    Circle newCircle(other);
    newCircle.setRadius(newCircle.getRadius() + r);
//    Circle resultCircle;
//    cout << other.m_radius << endl;
//    resultCircle.setRadius(other.m_radius + r);
    newCircle.setName(other.getName());
    newCircle.setCenter(other.getCenter());
    return newCircle;
}