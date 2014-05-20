#ifndef FUNCTIONS_CIRCLE_HPP_INCLUDED
#define FUNCTIONS_CIRCLE_HPP_INCLUDED

template < class T >
bool Point_in_circle(const Point2D < T > &Point, const Circle < T > &_Circle) {
	return (dist(Point, _Circle) <= EPS);
}

template < class T >
bool Point_on_circle(const Point2D < T > &Point, const Circle < T > &_Circle) {
	return (ABS(dist(Point, _Circle.Centre) - _Circle.R) <= EPS);
}

template < class T >
T dist(const Point2D < T > &Point, const Circle < T > &_Circle) {
	if (dist(Point, _Circle.Centre) <= _Circle.R)
		return 0;
	return (dist(Point, _Circle.Centre) - _Circle.R);
}

template < class T >
int Cross_line_circle(const Line2D < T > &Line, const Circle < T > &_Circle, Point2D < T > &P1, Point2D < T > &P2) {
	Point2D < T > P = Closest_point(Line, _Circle.Centre);
	int flag = 0;
	T d = dist(P, _Circle.Centre);
	if (ABS(d - _Circle.R) <= EPS)
		flag = 1;
	else if (_Circle.R > d)
		flag = 2;
	else
		return 0;

	T k = SQRT(SQR(_Circle.R) - SQR(d));
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

#endif // FUNCTIONS_CIRCLE_HPP_INCLUDED
