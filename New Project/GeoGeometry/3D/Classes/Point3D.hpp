#ifndef POINT3D_H_INCLUDED
#define POINT3D_H_INCLUDED

template < class T >
class Point3D {
public:
    T x;
    T y;
    T z;

    Point3D(const T &_x = 0, const T &_y = 0, const T &_z = 0) {
        this->x = _x;
        this->y = _y;
        this->z = _z;
    }

    ~Point3D() {

    }

    Point3D &operator = (const Point3D &Point) {
        if (this == &Point)
            return *this;
        this->x = Point.x;
        this->y = Point.y;
        this->z = Point.z;
        return *this;
    }

    friend bool operator == (const Point3D &Point1, const Point3D &Point2) {
        return (ABS(Point1.x - Point2.x) < EPS &&
                ABS(Point1.y - Point2.y) < EPS &&
                ABS(Point1.z - Point2.z) < EPS);
    }

    friend bool operator != (const Point3D &Point1, const Point3D &Point2) {
        return (!(Point1 == Point2));
    }

    friend const Point3D& operator + (const Point3D &Point) {
        return Point;
    }

    friend const Point3D operator - (const Point3D &Point) {
        return Point3D(-Point.x, -Point.y, -Point.z);
    }

    friend Point3D operator + (const Point3D &Point1, const Point3D &Point2) {
        return Point3D(Point1.x + Point2.x, Point1.y + Point2.y, Point1.z + Point2.z);
    }

    friend Point3D operator += (Point3D &Point1, const Point3D &Point2) {
        Point1.x += Point2.x;
        Point1.y += Point2.y;
        Point1.z += Point2.z;
        return Point1;
    }

    friend Point3D operator - (const Point3D &Point1, const Point3D &Point2) {
        return Point3D(Point1.x - Point2.x, Point1.y - Point2.y, Point1.z - Point2.z);
    }

    friend Point3D operator -= (Point3D &Point1, const Point3D &Point2) {
        Point1.x -= Point2.x;
        Point1.y -= Point2.y;
        Point1.z -= Point2.z;
        return Point1;
    }

    friend Point3D operator * (const T &m, const Point3D &Point) {
        return Point3D(Point.x * m, Point.y * m, Point.z * m);
    }

    friend Point3D& operator *= (Point3D &Point, const T &m) {
        Point.x *= m;
        Point.y *= m;
        Point.z *= m;
        return Point;
    }

    friend Point3D operator / (const T &m, const Point3D &Point) {
        return Point3D(Point.x / m, Point.y / m, Point.z / m);
    }

    friend Point3D& operator /= (Point3D &Point, const T &m) {
        Point.x /= m;
        Point.y /= m;
        Point.z /= m;
        return Point;
    }

    friend std::ostream& operator << (std::ostream& outputstream, const Point3D &Point) {
        outputstream << "(" << Point.x << "," << Point.y << "," << Point.z << ")";
        return outputstream;
    }

    friend std::istream& operator >> (std::istream& inputstream, Point3D &Point) {
        inputstream >> Point.x >> Point.y >> Point.z;
        return inputstream;
    }

};

#endif // POINT3D_H_INCLUDED
