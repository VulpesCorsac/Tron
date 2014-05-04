#ifndef FUNCTIONS_LINE2D_HPP_INCLUDED
#define FUNCTIONS_LINE2D_HPP_INCLUDED

template < class T >
bool Are_parallel_lines(const Line2D < T > &Line1, const Line2D < T > &Line2) {
    return (_ABS(Line1.A*Line2.B - Line2.A*Line1.B) <= EPS);
}

template < class T >
bool Cross_line(const Line2D < T > &Line1, const Line2D < T > &Line2, Point2D < T > &Point) {
    if (Are_parallel_lines(Line1, Line2))
        return false;
    Point.x = (Line2.B*Line1.C - Line1.B*Line2.C) / (Line2.A*Line1.B - Line1.A*Line2.B);
    Point.y = (Line1.B != 0 ? (-Line1.C - Line1.A*Point.x) / Line1.B : (-Line2.C - Line2.A*Point.x) / Line2.B);
    return true;
}

template < class T >
Line2D < T > Perp_line(const Line2D < T > &Line, const Point2D < T > &Point) {
    return Line2D < T > (Line.B, -Line.A, -Line.B*Point.x + Line.A*Point.y);
}

template < class T >
Point2D < T > Closest_point(const Line2D < T > &Line, const Point2D < T > &Point) {
    T k = (Point_in_line(Point, Line)) / (_SQR(Line.A) + _SQR(Line.B));
    return Point2D < T > (Point.x - Line.A*k, Point.y - Line.B*k);
}

template < class T >
Line2D < T > Parallel_line_of_dist(const Line2D < T > &Line, const T &Dist) {
    return Line2D < T > (Line.A, Line.B, Line.C - Dist*sqrt(_SQR(Line.A) + _SQR(Line.B)));
}

#endif // FUNCTIONS_LINE2D_HPP_INCLUDED