#include "allShapes.h"
#include "Circle.h"
#include "Quad.h"
#include "Square.h"
#include <typeinfo>


// CTORs / DTOR
int Shape::s_totalNumOfShapes;

allShapes::allShapes() {
    m_size = 0;
    m_arr = new Shape*;
}

allShapes::allShapes(const allShapes &other) {
    m_size = 0;
    m_arr = new Shape*;
    for (int i = 0; i < other.m_size; i++) {
//        addShape(other.m_arr[i]);
        m_arr[i] = other.m_arr[i];
        m_size++;
    }
}

allShapes::~allShapes() {
    if (m_arr == nullptr) return;
    for (int i = 0; i < m_size; i++) {
         delete m_arr[i];
    }
//    delete [] m_arr;
}

// Public methods

int allShapes::getSize() const {
    return m_size;
}

// add a new shape (deep copy) to the end of array
void allShapes::addShape( Shape* newShape ) {
    Circle* c = dynamic_cast<Circle*>(newShape);
    if (c) {
        *this += new Circle(*c);
        return;
    }
    Quad* q = dynamic_cast<Quad*>(newShape);
    if (q) {
        *this += new Quad(*q);
    }
}

// remove shape by index
void allShapes::removeShape( int index ) {
    if (index >= m_size) return;
    delete m_arr[index];
    for (int i = index, n = index + 1; n < m_size; i++, n++) {
        m_arr[i] = m_arr[n];
    }
    --m_size;
//    if (index != --m_size) {
//        delete m_arr[m_size];
//    }
//    --m_size;
}

// returns the total area of all the shapes (rounded to int)
int allShapes::totalArea() const {
    int totalArea = 0;
    for (int i = 0; i < m_size; i++) {
        totalArea += (int) m_arr[i]->calcArea();
    }
    return totalArea;
}

// returns the total Perimeter of all the shapes (rounded to int)
int allShapes::totalPerimeter() const {
    int totalPerimeter = 0;
    for (int i = 0; i < m_size; i++) {
        totalPerimeter += (int) m_arr[i]->calcPerimeter();
    }
    return totalPerimeter;
}

// returns the total sum of circle areas (rounded to int)
int allShapes::totalCircleArea() const {
    int totalCircleArea = 0;
    for (int i = 0; i < m_size; i++) {
        if (typeid(*m_arr[i]) != typeid(Circle)) continue;
        totalCircleArea += m_arr[i]->calcArea();
    }
    return totalCircleArea;
}

// returns the total sum of squar Perimeter (rounded to int)
int allShapes::totalSquarePerimeter() const {
    int totalSquarePerimeter = 0;
    for (int i = 0; i < m_size; i++) {
        if (typeid(*m_arr[i]) != typeid(Square)) continue;
        totalSquarePerimeter += (int) m_arr[i]->calcPerimeter();
    }
    return totalSquarePerimeter;
}

// Operators
// Add a new shape
const allShapes& allShapes::operator+=( Shape* newShape ){
    Shape* shapeToCreate = newShape;
    m_arr[m_size++] = shapeToCreate; // Problem (?) -> will use Shape assignment operator
    return *this;
}

// returns the shape located at index ind
Shape* allShapes::operator[]( int index ) const {
    if (m_arr == nullptr) return nullptr;
    return m_arr[index];
}

// returns a new allShape with all elements located at this and other
allShapes allShapes::operator+( const allShapes& other ) const {
    allShapes resultShape;
    for (int i = 0; i < m_size; i++) {
        resultShape.addShape(m_arr[i]);
    }
    for (int i = 0; i < other.m_size; i++) {
        resultShape.addShape(other.m_arr[i]);
    }
    for (int i = 0; i < resultShape.m_size; i++) cout << resultShape.m_arr[i] << endl;
    return resultShape;
}

// returns the number of elements
allShapes::operator int() const {
    return m_size;
}
