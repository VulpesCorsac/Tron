#ifndef CROSSING2D_HPP_INCLUDED
#define CROSSING2D_HPP_INCLUDED

template < class T >
bool Cross_line(const Line2D < T > &Line1, const Line2D < T > &Line2, Point2D < T > &Point) {
	if (Are_parallel_lines(Line1, Line2))
		return false;
	Point.x = (Line2.B*Line1.C - Line1.B*Line2.C) / (Line2.A*Line1.B - Line1.A*Line2.B);
	Point.y = (Line1.B != 0 ? (-Line1.C - Line1.A*Point.x) / Line1.B : (-Line2.C - Line2.A*Point.x) / Line2.B);
	return true;
}

template < class T >
bool Cross_segment(const Segment2D < T > &Segment1, const Segment2D < T > &Segment2) {
	Line2D < T > Line1(Segment1.A, Segment1.B);
	Line2D < T > Line2(Segment2.A, Segment2.B);
	Point2D < T > Cross_Point;
	if (!Cross_line(Line1, Line2, Cross_Point))
		return false;
	if (Point_in_box(Segment1.A, Segment1.B, Cross_Point) && Point_in_box(Segment2.A, Segment2.B, Cross_Point))
		return true;
	return false;
}

template < class T >
int Cross_line_circle(const Line2D < T > &Line, const Circle < T > &_Circle, Point2D < T > &P1, Point2D < T > &P2) {
	Point2D < T > P = Closest_point(Line, _Circle.Centre);
	int flag = 0;
	T d = dist(P, _Circle.Centre);
	if (_ABS(d - _Circle.R) <= EPS)
		flag = 1;
	else if (_Circle.R > d)
		flag = 2;
	else
		return 0;

	T k = sqrt(_SQR(_Circle.R) - _SQR(d));
	T t = dist(Point2D < T >(0, 0), Point2D < T >(Line.B, -Line.A));
	P1 = P + (k / t) * Vector2D < T >(Point2D < T >(-Line.B, Line.A));
	P1 = P + (k / t) * Vector2D < T >(Point2D < T >(Line.B, -Line.A));

	return flag;
}

template < class T >
int Cross_segment_circle(const Segment2D < T > &Segment, const Circle < T > &_Circle, Point2D < T > &P1, Point2D < T > &P2) {
	Line2D < T > Line(Segment.A, Segment.B);
	int flag = Cross_line_circle(Line, _Circle, P1, P2);
	if (!flag)
		return 0;
	flag = 0;
	if (Point_in_box(Segment.A, Segment.B, P1))
		flag++;
	if (Point_in_box(Segment.A, Segment.B, P2))
		flag++;
	return flag;
}

#endif // CROSSING2D_HPP_INCLUDED
