#ifndef FUNCTIONS_LINE2D_HPP_INCLUDED
#define FUNCTIONS_LINE2D_HPP_INCLUDED

template < class T >
T Point_to_line(const Point2D < T > &Point, const Line2D < T > &Line) {
	return Line.A*Point.x + Line.B*Point.x + Line.C;
}

template < class T >
bool Point_in_line(const Point2D < T > &Point, const Line2D < T > &Line) {
	return (ABS(Point_to_line(Point, Line)) <= EPS);
}

template < class T >
T dist(const Line2D < T > &Line, const Point2D < T > &Point) {
	return ABS(Point_in_line(Point, Line) / (SQR(Line.A) + SQR(Line.B)));
}

template < class T >
T dist(const Line2D < T > &Line1, const Line2D < T > &Line2) {
	if (Line1 == Line2 || !Are_parallel_lines(Line1, Line2))
		return 0;
	return ABS(Line1.C - Line2.C) / (SQR(Line1.A) + SQR(Line2.B));
}

template < class T >
bool Are_parallel_lines(const Line2D < T > &Line1, const Line2D < T > &Line2) {
    return (ABS(Line1.A*Line2.B - Line2.A*Line1.B) <= EPS);
}

template < class T >
Line2D < T > Perp_line(const Line2D < T > &Line, const Point2D < T > &Point) {
    return Line2D < T > (Line.B, -Line.A, -Line.B*Point.x + Line.A*Point.y);
}

template < class T >
Line2D < T > Parallel_line_of_dist(const Line2D < T > &Line, const T &Dist) {
    return Line2D < T > (Line.A, Line.B, Line.C - Dist*SQRT(SQR(Line.A) + SQR(Line.B)));
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
Point2D < T > Closest_point(const Line2D < T > &Line, const Point2D < T > &Point) {
	T k = (Point_to_line(Point, Line)) / (SQR(Line.A) + SQR(Line.B));
	return Point2D < T >(Point.x - Line.A*k, Point.y - Line.B*k);
}

#endif // FUNCTIONS_LINE2D_HPP_INCLUDED
