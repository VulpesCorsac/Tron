#ifndef SPHERE_HPP_INCLUDED
#define SPHERE_HPP_INCLUDED

template < class T >
class Sphere {
public:
    Point3D < T > Centre;
    T R;

    Sphere (const T &_X = 0, const T &_Y = 0, const T &_Z = 0, const T &_R = 0) {
        this->Centre.x = _X;
        this->Centre.y = _Y;
        this->Centre.z = _Z;
        this->R = _R;
    }

    Sphere(const Point3D < T > &_C, const T &_R = 0) {
        this->R = _R;
        this->Centre = _C;
    }

    Sphere(const Point3D < T > &Point, const Vector3D < T > &Vector) {
        this->Centre = Point;
        this->R = Vector.Norm();
    }

    ~Sphere() {

    }

    Sphere &operator = (const Sphere &Sphere) {
        if (this == &Sphere)
            return *this;
        this->Centre = Sphere.Centre;
        this->R = Sphere.R;
        return *this;
    }

    friend bool operator == (const Sphere &Sphere1, const Sphere &Sphere2) {
        return (ABS(Sphere1.R - Sphere2.R) < EPS && Sphere1.Centre == Sphere2.Centre);
    }

    friend bool operator != (const Sphere &Sphere1, const Sphere &Sphere2) {
        return (!(Sphere1 == Sphere2));
    }

    friend std::ostream& operator << (std::ostream& outputstream, const Sphere &Sphere) {
        outputstream << "[" << Sphere.Centre << "," << Sphere.R << "]";
        return outputstream;
    }

    friend std::istream& operator >> (std::istream& inputstream, Sphere &Sphere) {
        inputstream >> Sphere.Centre >> Sphere.R;
        return inputstream;
    }

};

#endif // SPHERE_HPP_INCLUDED
