#ifndef POINT2D_HPP_INCLUDED
#define POINT2D_HPP_INCLUDED

template < class T >
class Point2D {
public:
    T x;
    T y;

    Point2D(const T &_x = 0, const T &_y = 0) {
        this->x = _x;
        this->y = _y;
    }

    ~Point2D() {

    }

    Point2D &operator = (const Point2D &Point) {
        if (this == &Point)
            return *this;
        this->x = Point.x;
        this->y = Point.y;
        return *this;
    }

    friend bool operator == (const Point2D &Point1, const Point2D &Point2) {
        return (_ABS(Point1.x - Point2.x) < EPS &&
                _ABS(Point1.y - Point2.y) < EPS);
    }

    friend bool operator != (const Point2D &Point1, const Point2D &Point2) {
        return (!(Point1 == Point2));
    }

    friend const Point2D& operator + (const Point2D &Point) {
        return Point;
    }

    friend const Point2D operator - (const Point2D &Point) {
        return Point2D(-Point.x, -Point.y);
    }

    friend Point2D operator + (const Point2D &Point1, const Point2D &Point2) {
        return Point2D(Point1.x + Point2.x, Point1.y + Point2.y);
    }

    friend Point2D operator += (Point2D &Point1, const Point2D &Point2) {
        Point1.x += Point2.x;
        Point1.y += Point2.y;
        return Point1;
    }

    friend Point2D operator - (const Point2D &Point1, const Point2D &Point2) {
        return Point2D(Point1.x - Point2.x, Point1.y - Point2.y);
    }

    friend Point2D operator -= (Point2D &Point1, const Point2D &Point2) {
        Point1.x -= Point2.x;
        Point1.y -= Point2.y;
        return Point1;
    }

    friend Point2D operator * (const T &m, const Point2D &Point) {
        return Point2D(Point.x * m, Point.y * m);
    }

    friend Point2D& operator *= (Point2D &Point, const T &m) {
        Point.x *= m;
        Point.y *= m;
        return Point;
    }

    friend Point2D operator / (const T &m, const Point2D &Point) {
        return Point2D(Point.x / m, Point.y / m);
    }

    friend Point2D& operator /= (Point2D &Point, const T &m) {
        Point.x /= m;
        Point.y /= m;
        return Point;
    }

    friend std::ostream& operator << (std::ostream& outputstream, const Point2D &Point) {
        outputstream << "(" << Point.x << "," << Point.y << ")";
        return outputstream;
    }

    friend std::istream& operator >> (std::istream& inputstream, Point2D &Point) {
        inputstream >> Point.x >> Point.y;
        return inputstream;
    }

};

#endif // POINT2D_HPP_INCLUDED
