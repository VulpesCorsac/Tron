#ifndef PLANE3D_H_INCLUDED
#define PLANE3D_H_INCLUDED

template < class T >
class Plane3D {
public:
    T A;
    T B;
    T C;
    T D;

    Plane3D(const T &_A, const T &_B, const T &_C, const T &_D) {
        this->A = _A;
        this->B = _B;
        this->C = _C;
        this->D = _D;
    }

    Plane3D(const Point3D < T > &Point1, const Point3D < T > &Point2, const Point3D < T > &Point3) {
        Vector3D < T > N = Vector_mul(Vector3D < T > (Point1, Point2), Vector3D < T > (Point1, Point3));
        this->A = N.x;
        this->B = N.y;
        this->C = N.z;
        this->D = -this->A*Point1.x - this->B*Point1.y - this->C*Point1.z;
    }

    Plane3D(const Point3D < T > &Point, const Vector3D < T > &Vector1, const Vector3D < T > &Vector2) {
        Vector3D < T > N = Vector_mul(Vector3D < T > (Point, Point + Vector1), Vector3D < T > (Point, Point + Vector2));
        this->A = N.x;
        this->B = N.y;
        this->C = N.z;
        this->D = -this->A*Point.x - this->B*Point.y - this->C*Point.z;
    }

    Plane3D &operator = (const Plane3D &Plane) {
        if (this == &Plane)
            return *this;
        this->A = Plane.A;
        this->B = Plane.B;
        this->C = Plane.C;
        this->D = Plane.D;
        return *this;
    }

    friend bool operator == (const Plane3D &Plane1, const Plane3D &Plane2) {
        return (ABS(Plane1.A*Plane2.B - Plane2.A*Plane1.B) < EPS &&
                ABS(Plane1.B*Plane2.C - Plane2.B*Plane1.C) < EPS &&
                ABS(Plane1.C*Plane2.D - Plane2.C*Plane1.D) < EPS &&
                ABS(Plane1.D*Plane2.A - Plane2.D*Plane1.A) < EPS);
    }

    friend bool operator != (const Plane3D &Plane1, const Plane3D &Plane2) {
        return (!(Plane1 == Plane2));
    }

    friend std::ostream& operator << (std::ostream& outputstream, const Plane3D &Plane) {
        outputstream << Plane.A << "*x";
        if (Plane.B >= 0)
            outputstream << "+";
        outputstream << Plane.B << "*y";
        if (Plane.C >= 0)
            outputstream << "+";
        outputstream << Plane.C << "*z";
        if (Plane.D >= 0)
            outputstream << "+";
        outputstream << Plane.D << "=0";

        return outputstream;
    }

    friend std::istream& operator >> (std::istream& inputstream, Plane3D &Plane) {
        inputstream >> Plane.A >> Plane.B >> Plane.C >> Plane.D;
        return inputstream;
    }

};

#endif // PLANE3D_H_INCLUDED
