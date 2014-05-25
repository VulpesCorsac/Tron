#ifndef FUNCTIONS_SEGMENT2D_HPP_INCLUDED
#define FUNCTIONS_SEGMENT2D_HPP_INCLUDED

template < class T >
bool Point_in_segment(const Point2D < T > &Point, const Segment2D < T > &_Segment) {
	return Point_in_box(_Segment.A, _Segment.B, Point);
}

template < class T >
Segment2D < T > Turn(const Segment2D < T > &_Segment, const T &alpha) {
    return Segment2D < T > (turn(_Segment.A, alpha), turn(_Segment.B, alpha));
}

template < class T >
Segment2D < T > Turn(const Segment2D < T > &_Segment, const Point2D < T > &_Point, const T &alpha) {
    return Segment2D < T > (turn(_Segment.A, _Point, alpha), turn(_Segment.A, _Point, alpha));
}

template < class T >
bool Cross_segment(const Segment2D < T > &Segment1, const Segment2D < T > &Segment2, Point2D < T > &Cross_Point) {
	Line2D < T > Line1(Segment1.A, Segment1.B);
	Line2D < T > Line2(Segment2.A, Segment2.B);
	if (!Cross_line(Line1, Line2, Cross_Point))
		return false;
	if (Line1 == Line2) {
		if (Point_in_box(Segment1.A, Segment1.B, Segment2.A)) {
			Cross_Point = Segment2.A;
			return true;
		}
		if (Point_in_box(Segment1.A, Segment1.B, Segment2.B)) {
			Cross_Point = Segment2.B;
			return true;
		}
		if (Point_in_box(Segment2.A, Segment2.B, Segment1.A)) {
			Cross_Point = Segment1.A;
			return true;
		}
		if (Point_in_box(Segment2.A, Segment2.B, Segment1.B)) {
			Cross_Point = Segment1.B;
			return true;
		}
	}
	return (Point_in_box(Segment1.A, Segment1.B, Cross_Point) && Point_in_box(Segment2.A, Segment2.B, Cross_Point));
}

template < class T >
T dist(const Point2D < T > &Point, const Segment2D < T > &_Segment) {
	Point2D < T > CP = Closest_point(Line2D(_Segment.A, _Segment.B), Point);
	if (Point_in_segment(CP, _Segment))
		return dist(CP, Point)
	else
		return min(dist(Point, _Segment.A), dist(Point, _Segment.B));
}

template < class T >
bool Cross_segment_line(const Segment2D < T > &Segment, const Line2D < T > &Line, Point2D < T > &Cross_Point) {
	Line2D < T > Temp(Segment.A, Segment.B);
	if (!Cross_line(Temp, Line, Cross_Point))
		return false;
	if (Temp == Line)
		return true;
	return Point_in_Segment(Cross_Point, Segment);
}

#endif // FUNCTIONS_SEGMENT2D_HPP_INCLUDED
