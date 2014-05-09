#ifndef FUNCTIONS_POINT2D_HPP_INCLUDED
#define FUNCTIONS_POINT2D_HPP_INCLUDED

template < class T >
bool Point_in_box(const Point2D < T > &Point1, const Point2D < T > &Point2, const Point2D < T > &Point) {
	return  ((ABS(Point.x - min(Point1.x, Point2.x)) <= EPS || min(Point1.x, Point2.x) <= Point.x) &&
		     (ABS(max(Point1.x, Point2.x) - Point.x) <= EPS || max(Point1.x, Point2.x) >= Point.x) &&
		     (ABS(Point.y - min(Point1.y, Point2.y)) <= EPS || min(Point1.y, Point2.y) <= Point.y) &&
		     (ABS(max(Point1.y, Point2.y) - Point.y) <= EPS || max(Point1.y, Point2.y) >= Point.y));
}

template < class T >
T dist(const Point2D < T > &Point1, const Point2D < T > &Point2) {
	return SQRT(SQR(Point1.x - Point2.x) + SQR(Point1.y - Point2.y));
}

template < class T >
T polar_angle(const Point2D < T > &Point) {
    T alpha = atan2(Point.y, Point.x);
    if (alpha < 0)
        alpha += 2 * PI < T > ();
    return alpha;
}

template < class T >
Point2D < T > turn(const Point2D < T > &Point, const T &alpha) {
    T cosalpha = cos(alpha);
    T sinalpha = sin(alpha);
    return Point2D < T > (Point.x*cosalpha - Point.y*sinalpha, Point.x*sinalpha + Point.y*cosalpha);
}

template < class T >
Point2D < T > turn(const Point2D < T > &Point, const Point2D < T > &Of, const T &alpha) {
    Point2D < T > Tmp = turn(Point2D < T > (Point.x - Of.x, Point.y - Of.y), alpha);
    return Point2D < T > (Tmp.x + Of.x, Tmp.y + Of.y);
}

#endif // FUNCTIONS_POINT2D_HPP_INCLUDED
