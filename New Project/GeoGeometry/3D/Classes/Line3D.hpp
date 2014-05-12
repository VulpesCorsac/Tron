#ifndef LINE3D_H_INCLUDED
#define LINE3D_H_INCLUDED

template < class T >
class Line3D {
public:
    Point3D < T > Point;
    Vector3D < T > Vector;

    Line3D(const Point3D < T > &_Point, const Vector3D < T > &_Vector) {
        this->Point = _Point;
        this->Vector = _Vector;
    }

    Line3D(const Point3D < T > &_Point1, const Point3D < T > &_Point2) {
        this->Point = _Point1;
        this->Vector = Vector3D < T > (_Point1, _Point2);
    }

    ~Line3D() {

    }

    Line3D &operator = (const Line3D &Line) {
        if (this == &Line)
            return *this;
        this->Point = Line.Point;
        this->Vector = Line.Vector;
        return *this;
    }
    friend bool operator == (const Line3D &Line1, const Line3D &Line2) {
        return (Point_in_line_3D(Line1.Point, Line2) && Point_in_line_3D(Line1.Point + Line1.Vector, Line2) &&
                Point_in_line_3D(Line2.Point, Line1) && Point_in_line_3D(Line2.Point + Line2.Vector, Line1));
    }

    friend bool operator != (const Line3D &Line1, const Line3D &Line2) {
        return (!(Line1 == Line2));
    }

    friend std::ostream& operator << (std::ostream& outputstream, const Line3D &Line) {
        outputstream << Line.Point << "+t*" << Line.Vector;
        return outputstream;
    }

    friend std::istream& operator >> (std::istream& inputstream, Line3D &Line) {
        inputstream >> Line.Point >> Line.Vector;
        return inputstream;
    }

};

#endif // LINE3D_H_INCLUDED
