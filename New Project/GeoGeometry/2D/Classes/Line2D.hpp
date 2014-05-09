#ifndef LINE2D_HPP_INCLUDED
#define LINE2D_HPP_INCLUDED

template < class T >
class Line2D {
public:
    T A;
    T B;
    T C;

    Line2D(const T &_A, const T &_B, const T &_C) {
        this->A = _A;
        this->B = _B;
        this->C = _C;
    }

    Line2D(const Point2D < T > &Point1, const Point2D < T > &Point2) {
        this->A = Point2.y - Point1.y;
        this->B = Point1.x - Point2.x;
        this->C = -this->A*Point1.x - this->B*Point1.y;
    }

    ~Line2D() {

    }

    Line2D &operator = (const Line2D &Line) {
        if (this == &Line)
            return *this;
        this->A = Line.A;
        this->B = Line.B;
        this->C = Line.C;
        return *this;
    }

    friend bool operator == (const Line2D &Line1, const Line2D &Line2) {
        return (ABS(Line1.A*Line2.B - Line2.A*Line1.B) < EPS &&
                ABS(Line1.B*Line2.C - Line2.B*Line1.C) < EPS &&
                ABS(Line1.C*Line2.A - Line2.C*Line1.A) < EPS);
    }

    friend bool operator != (const Line2D &Line1, const Line2D &Line2) {
        return (!(Line1 == Line2));
    }

    friend std::ostream& operator << (std::ostream& outputstream, const Line2D &Line) {
        outputstream << Line.A << "*x";
        if (Line.B >= 0)
            outputstream << "+";
        outputstream << Line.B << "*y";
        if (Line.C >= 0)
            outputstream << "+";
        outputstream << Line.C;

        return outputstream;
    }

    friend std::istream& operator >> (std::istream& inputstream, Line2D &Line) {
        inputstream >> Line.A >> Line.B >> Line.C;
        return inputstream;
    }

};

#endif // LINE2D_HPP_INCLUDED
