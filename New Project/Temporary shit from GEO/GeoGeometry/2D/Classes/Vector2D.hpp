#ifndef VECTOR2D_H_INCLUDED
#define VECTOR2D_H_INCLUDED

template < class T >
class Vector2D {
public:
    T x;
    T y;

    Vector2D(const T &_x = 0, const T &_y = 0) {
        this->x = _x;
        this->y = _y;
    }

    Vector2D(const Point2D < T > &A) {
        this->x = A.x;
        this->y = A.y;
    }

    Vector2D(const Point2D < T > &A, const Point2D < T > &B) {
        this->x = B.x - A.x;
        this->y = B.y - A.y;
    }

    ~Vector2D() {

    }

    double Norm() const {
        return sqrt(_SQR(this->x) + _SQR(this->y));
    }

    Vector2D &operator = (const Vector2D &Vector) {
        if (this == &Vector)
            return *this;
        this->x = Vector.x;
        this->y = Vector.y;
        return *this;
    }

    friend bool operator == (const Vector2D &Vector1, const Vector2D &Vector2) {
        return (_ABS(Vector1.x - Vector2.x) < EPS &&
                _ABS(Vector1.y - Vector2.y) < EPS);
    }

    friend bool operator != (const Vector2D &Vector1, const Vector2D &Vector2) {
        return (!(Vector1 == Vector2));
    }

    friend const Vector2D& operator + (const Vector2D &Vector) {
        return Vector;
    }

    friend const Vector2D operator - (const Vector2D &Vector) {
        return Vector2D(-Vector.x, -Vector.y);
    }

    friend Vector2D operator + (const Vector2D &Vector1, const Vector2D &Vector2) {
        return Vector2D(Vector1.x + Vector2.x, Vector1.y + Vector2.y);
    }

    friend Vector2D operator += (Vector2D &Vector1, const Vector2D &Vector2) {
        Vector1.x += Vector2.x;
        Vector1.y += Vector2.y;
        return Vector1;
    }

    friend Point2D < T > operator + (const Point2D < T > &Point, const Vector2D &Vector) {
        return Point2D < T > (Point.x + Vector.x, Point.y + Vector.y);
    }

    friend Point2D < T > operator += (Point2D < T > &Point, const Vector2D &Vector) {
        Point.x += Vector.x;
        Point.y += Vector.y;
        return Point;
    }

    friend Vector2D operator - (const Vector2D &Vector1, const Vector2D &Vector2) {
        return Vector2D(Vector1.x - Vector2.x, Vector1.y - Vector2.y);
    }

    friend Vector2D operator -= (Vector2D &Vector1, const Vector2D &Vector2) {
        Vector1.x -= Vector2.x;
        Vector1.y -= Vector2.y;
        return Vector1;
    }

    friend Point2D < T > operator - (const Point2D < T > &Point, const Vector2D &Vector) {
        return Point2D < T > (Point.x - Vector.x, Point.y - Vector.y);
    }

    friend Point2D < T > operator -= (Point2D < T > &Point, const Vector2D &Vector) {
        Point.x -= Vector.x;
        Point.y -= Vector.y;
        return Point;
    }

    friend Vector2D operator * (const T &m, const Vector2D &Vector) {
        return Vector2D(Vector.x * m, Vector.y * m);
    }

    friend Vector2D& operator *= (Vector2D &Vector, const T &m) {
        Vector.x *= m;
        Vector.y *= m;
        return Vector;
    }

    friend Vector2D operator / (const Vector2D &Vector, const T &m) {
        return Vector2D(Vector.x / m, Vector.y / m);
    }

    friend Vector2D& operator /= (Vector2D &Vector, const T &m) {
        Vector.x /= m;
        Vector.y /= m;
        return Vector;
    }

    friend std::ostream& operator << (std::ostream& outputstream, const Vector2D &Vector) {
        outputstream << "(" << Vector.x << "," << Vector.y << ")";
        return outputstream;
    }

    friend std::istream& operator >> (std::istream& inputstream, Vector2D &Vector) {
        inputstream >> Vector.x >> Vector.y;
        return inputstream;
    }

};

#endif // VECTOR2D_H_INCLUDED

