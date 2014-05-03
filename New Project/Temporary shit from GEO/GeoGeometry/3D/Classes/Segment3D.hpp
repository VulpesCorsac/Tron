#ifndef SEGMENT3D_HPP_INCLUDED
#define SEGMENT3D_HPP_INCLUDED

template < class T >
class Segment3D {
public:
    Point3D < T > A;
    Point3D < T > B;

    Segment3D(const Point3D < T > &_A, const Point3D < T > &_B) {
        this->A = _A;
        this->B = _B;
    }

    ~Segment3D () {

    }

    T length() const {
        return sqrt(_SQR(B.x - A.x) + _SQR(B.y - A.y) + _SQR(B.z - A.z));
    }

    Segment3D &operator = (const Segment3D &Segment) {
        if (this == &Segment)
            return *this;
        this->A = Segment.A;
        this->B = Segment.B;
        return *this;
    }

    friend bool operator == (const Segment3D &Segment1, const Segment3D &Segment2) {
        return (Segment1.A == Segment2.A && Segment1.B == Segment2.B);
    }

    friend bool operator != (const Segment3D &Segment1, const Segment3D &Segment2) {
        return (!(Segment1 == Segment2));
    }

    friend std::ostream& operator << (std::ostream& outputstream, const Segment3D &Segment) {
        outputstream << "[" << Segment.A << "," << Segment.B << "]";
        return outputstream;
    }

    friend std::istream& operator >> (std::istream& inputstream, Segment3D &Segment) {
        inputstream >> Segment.A >> Segment.B;
        return inputstream;
    }

};

#endif // SEGMENT3D_HPP_INCLUDED
