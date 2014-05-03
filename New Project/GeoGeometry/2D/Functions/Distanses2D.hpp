#ifndef DISTANSES2D_HPP_INCLUDED
#define DISTANSES2D_HPP_INCLUDED

template < class T >
T dist(const Point2D < T > &Point1, const Point2D < T > &Point2) {
    return sqrt(_SQR(Point1.x - Point2.x) + _SQR(Point1.y - Point2.y));
}

template < class T >
T dist(const Line2D < T > &Line, const Point2D < T > &Point) {
    return _ABS(Point_in_line(Point, Line) / (_SQR(Line.A) + _SQR(Line.B)));
}

template < class T >
T dist(const Line2D < T > &Line1, const Line2D < T > &Line2) {
    if (Line1 == Line2 || !Are_parallel_lines(Line1, Line2))
        return 0;
    return _ABS(Line1.C - Line2.C) / (_SQR(Line1.A) + _SQR(Line2.B));
}

#endif // DISTANSES2D_HPP_INCLUDED
