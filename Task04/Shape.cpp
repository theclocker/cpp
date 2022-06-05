#include "Shape.h"
#include "Circle.h"
#include "Quad.h"
#include <string.h>

// CTORs / DTOR

Shape::Shape(const char *sn) {
    m_shapeName = new char[strlen(sn) + 1];
    strcpy(m_shapeName, sn);
    s_totalNumOfShapes++;
    m_centerPoint = Point(0, 0);
}

Shape::Shape(const Shape &other) {
    m_shapeName = new char[strlen(other.m_shapeName) + 1];
    strcpy(m_shapeName, other.getName());
    m_centerPoint = Point(other.m_centerPoint);
//    *this = other;
    s_totalNumOfShapes++;
}

Shape::~Shape() {
    if (m_shapeName != nullptr) {
        delete [] m_shapeName;
        s_totalNumOfShapes--;
    }
}

// Assignment Operator
const Shape& Shape::operator=(const Shape &otherShape) {
    if (this != &otherShape) {
        delete [] m_shapeName;
        m_shapeName = new char[strlen(otherShape.m_shapeName) + 1];
        strcpy(m_shapeName, otherShape.m_shapeName);
        m_centerPoint = otherShape.m_centerPoint;
//        Circle* c = dynamic_cast<Circle*>(this);
/*        const Circle* oc = dynamic_cast<const Circle*>(&otherShape);
        const Quad* oq = dynamic_cast<const Quad*>(&otherShape);
        if (oc) {
            *this = *oc;
        }
        if (oq) {
            *this = *oq;
        }*/
    }
    return *this;
}

// Public Methods

//sets the shape's name
void Shape::setName( const char* name ) {
    if (name == nullptr) return;
    delete [] m_shapeName;
    m_shapeName = new char[strlen(name) + 1];
    strcpy(m_shapeName, name);
}

//sets the center point
void Shape::setCenter( const Point& p ) {
    m_centerPoint = p;
}

//returns the shape's name
const char* Shape::getName() const {
    return m_shapeName;
}

//returns the center point
Point Shape::getCenter() const {
    return m_centerPoint;
}

//set the shape's name and the center point
void Shape::setShape( const char* sn, const Point& other ) {
    setName(sn);
    setCenter(other);
}

// returns the total number of shapes
int Shape::numOfShapes() {
    return Shape::s_totalNumOfShapes;
}
