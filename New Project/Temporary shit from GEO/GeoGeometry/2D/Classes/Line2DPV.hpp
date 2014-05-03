#ifndef Line2DPV_H_INCLUDED
#define Line2DPV_H_INCLUDED

template < class T >
class Line2DPV {
public:
    Point2D < T > Point;
    Vector2D < T > Vector;

    Line2DPV(const Point2D < T > &_Point, const Vector2D < T > &_Vector) {
        this->Point = _Point;
        this->Vector = _Vector;
    }

    Line2DPV(const Point2D < T > &_Point1, const Point2D < T > &_Point2) {
        this->Point = _Point1;
        this->Vector = Vector2D < T > (_Point1, _Point2);
    }

//    Line2DPV(const Line2D < T > _Line) {
//        if (_Line.A != 0 && _Line.B != 0) {
//            this->Point = Point2D < T > (0, -_Line.C/_Line.B);
//            this->Vector = Vector2D < T > (this->Point, Point2D < T > (-_Line.C/_Line.A, 0));
//        } else {
//            if (_Line.A == 0) {
//                this->Point = Point2D < T > (0, -_Line.C/_Line.B);
//                this->Vector = Vector2D < T > (0, 1);
//            } else {
//                this->Point = Point2D < T > (-_Line.C/_Line.A, 0);
//                this->Vector = Vector2D < T > (1, 0);
//            }
//        }
//    }

    ~Line2DPV() {

    }

    Line2DPV &operator = (const Line2DPV &Line) {
        if (this == &Line)
            return *this;
        this->Point = Line.Point;
        this->Vector = Line.Vector;
        return *this;
    }
    friend bool operator == (const Line2DPV &Line1, const Line2DPV &Line2) {
        return (Point_in_line_2D(Line1.Point, Line2) && Point_in_line_2D(Line1.Point + Line1.Vector, Line2) &&
                Point_in_line_2D(Line2.Point, Line1) && Point_in_line_2D(Line2.Point + Line2.Vector, Line1));
    }

    friend bool operator != (const Line2DPV &Line1, const Line2DPV &Line2) {
        return (!(Line1 == Line2));
    }

    friend std::ostream& operator << (std::ostream& outputstream, const Line2DPV &Line) {
        outputstream << Line.Point << "+t*" << Line.Vector;
        return outputstream;
    }

    friend std::istream& operator >> (std::istream& inputstream, Line2DPV &Line) {
        inputstream >> Line.Point >> Line.Vector;
        return inputstream;
    }
};

#endif // Line2DPV_H_INCLUDED
