#ifndef VECTOR3D_H_INCLUDED
#define VECTOR3D_H_INCLUDED

template < class T >
class Vector3D {
public:
    T x;
    T y;
    T z;

    Vector3D(const T &_x = 0, const T &_y = 0, const T &_z = 0) {
        this->x = _x;
        this->y = _y;
        this->z = _z;
    }

    Vector3D(const Point3D < T > &A) {
        this->x = A.x;
        this->y = A.y;
        this->z = A.z;
    }

    Vector3D(const Point3D < T > &A, const Point3D < T > &B) {
        this->x = B.x - A.x;
        this->y = B.y - A.y;
        this->z = B.z - A.z;
    }

    ~Vector3D() {

    }

    double Norm() const {
        return SQRT(SQR(this->x) + SQR(this->y) + SQR(this->z));
    }

    Vector3D &operator = (const Vector3D &Vector) {
        if (this == &Vector)
            return *this;
        this->x = Vector.x;
        this->y = Vector.y;
        this->z = Vector.z;
        return *this;
    }

    friend bool operator == (const Vector3D &Vector1, const Vector3D &Vector2) {
        return (ABS(Vector1.x - Vector2.x) < EPS &&
                ABS(Vector1.y - Vector2.y) < EPS &&
                ABS(Vector1.z - Vector2.z) < EPS);
    }

    friend bool operator != (const Vector3D &Vector1, const Vector3D &Vector2) {
        return (!(Vector1 == Vector2));
    }

    friend const Vector3D& operator + (const Vector3D &Vector) {
        return Vector;
    }

    friend const Vector3D operator - (const Vector3D &Vector) {
        return Vector3D(-Vector.x, -Vector.y, -Vector.z);
    }

    friend Vector3D operator + (const Vector3D &Vector1, const Vector3D &Vector2) {
        return Vector3D(Vector1.x + Vector2.x, Vector1.y + Vector2.y, Vector1.z + Vector2.z);
    }

    friend Vector3D operator += (Vector3D &Vector1, const Vector3D &Vector2) {
        Vector1.x += Vector2.x;
        Vector1.y += Vector2.y;
        Vector1.z += Vector2.z;
        return Vector1;
    }

    friend Point3D < T > operator + (const Point3D < T > &Point, const Vector3D &Vector) {
        return Point3D < T > (Point.x + Vector.x, Point.y + Vector.y, Point.z + Vector.z);
    }

    friend Point3D < T > operator += (Point3D < T > &Point, const Vector3D &Vector) {
        Point.x += Vector.x;
        Point.y += Vector.y;
        Point.z += Vector.z;
        return Point;
    }

    friend Vector3D operator - (const Vector3D &Vector1, const Vector3D &Vector2) {
        return Vector3D(Vector1.x - Vector2.x, Vector1.y - Vector2.y, Vector1.z - Vector2.z);
    }

    friend Vector3D operator -= (Vector3D &Vector1, const Vector3D &Vector2) {
        Vector1.x -= Vector2.x;
        Vector1.y -= Vector2.y;
        Vector1.z -= Vector2.z;
        return Vector1;
    }

    friend Point3D < T > operator - (const Point3D < T > &Point, const Vector3D &Vector) {
        return Point3D < T > (Point.x - Vector.x, Point.y - Vector.y, Point.z - Vector.z);
    }

    friend Point3D < T > operator -= (Point3D < T > &Point, const Vector3D &Vector) {
        Point.x -= Vector.x;
        Point.y -= Vector.y;
        Point.z -= Vector.z;
        return Point;
    }

    friend Vector3D operator * (const T &m, const Vector3D &Vector) {
        return Vector3D(Vector.x * m, Vector.y * m, Vector.z * m);
    }

    friend Vector3D& operator *= (Vector3D &Vector, const T &m) {
        Vector.x *= m;
        Vector.y *= m;
        Vector.z *= m;
        return Vector;
    }

    friend Vector3D operator / (const Vector3D &Vector, const T &m) {
        return Vector3D(Vector.x / m, Vector.y / m, Vector.z / m);
    }

    friend Vector3D& operator /= (Vector3D &Vector, const T &m) {
        Vector.x /= m;
        Vector.y /= m;
        Vector.z /= m;
        return Vector;
    }

    friend std::ostream& operator << (std::ostream& outputstream, const Vector3D &Vector) {
        outputstream << "(" << Vector.x << "," << Vector.y << "," << Vector.z << ")";
        return outputstream;
    }

    friend std::istream& operator >> (std::istream& inputstream, Vector3D &Vector) {
        inputstream >> Vector.x >> Vector.y >> Vector.z;
        return inputstream;
    }

};

#endif // VECTOR3D_H_INCLUDED
