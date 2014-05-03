#ifndef CIRCLE_HPP_INCLUDED
#define CIRCLE_HPP_INCLUDED

template < class T >
class Circle {
public:
    Point2D < T > Centre;
    T R;

    Circle(const T &_x, const T &_y, const T &_R) {
        this->Centre.x = _x;
        this->Centre.y = _y;
        this->R = _R;
    }

    Circle(const Point2D < T > &Point, const Vector2D < T > &Vector) {
        this->Centre = Point;
        this->R = Vector.Norm();
    }

    ~Circle() {

    }

    Circle &operator = (const Circle &Circle) {
        if (this == &Circle)
            return *this;
        this->Centre = Circle.Centre;
        this->R = Circle.R;
        return *this;
    }

    friend bool operator == (const Circle &Circle1, const Circle &Circle2) {
        return (_ABS(Circle1.R - Circle2.R) < EPS && Circle1.Centre == Circle2.Centre);
    }

    friend bool operator != (const Circle &Circle1, const Circle &Circle2) {
        return (!(Circle1 == Circle2));
    }

    friend std::ostream& operator << (std::ostream& outputstream, const Circle &Circle) {
        outputstream << "[" << Circle.Centre << "," << Circle.R << "]";
        return outputstream;
    }

    friend std::istream& operator >> (std::istream& inputstream, Circle &Circle) {
        inputstream >> Circle.Centre >> Circle.R;
        return inputstream;
    }

};

#endif // CIRCLE_HPP_INCLUDED
