#ifndef SEGMENT2D_HPP_INCLUDED
#define SEGMENT2D_HPP_INCLUDED

template < class T >
class Segment2D {
public:
    Point2D < T > A;
    Point2D < T > B;

    Segment2D(const Point2D < T > &_A, const Point2D < T > &_B) {
        this->A = _A;
        this->B = _B;
    }

	Segment2D() {
		this->A = Point2D < T > (0, 0);
		this->B = Point2D < T > (0, 0);
	}

    ~Segment2D () {

    }

    T length() const {
        return sqrt(_SQR(B.x - A.x) + _SQR(B.y - A.y) + _SQR(B.z - A.z));
    }

    Segment2D &operator = (const Segment2D &Segment) {
        if (this == &Segment)
            return *this;
        this->A = Segment.A;
        this->B = Segment.B;
        return *this;
    }

    friend bool operator == (const Segment2D &Segment1, const Segment2D &Segment2) {
        return (Segment1.A == Segment2.A && Segment1.B == Segment2.B);
    }

    friend bool operator != (const Segment2D &Segment1, const Segment2D &Segment2) {
        return (!(Segment1 == Segment2));
    }

    friend std::ostream& operator << (std::ostream& outputstream, const Segment2D &Segment) {
        outputstream << "[" << Segment.A << "," << Segment.B << "]";
        return outputstream;
    }

    friend std::istream& operator >> (std::istream& inputstream, Segment2D &Segment) {
        inputstream >> Segment.A >> Segment.B;
        return inputstream;
    }

};

#endif // SEGMENT2D_HPP_INCLUDED
