#ifndef A_IN_B2D_HPP_INCLUDED
#define A_IN_B2D_HPP_INCLUDED

template < class T >
bool Point_in_box(const Point2D < T > &Point1, const Point2D < T > &Point2, const Point2D < T > &Point) {
	return  ((_ABS(Point.x - min(Point1.x, Point2.x)) <= EPS || min(Point1.x, Point2.x) <= Point.x) &&
		     (_ABS(max(Point1.x, Point2.x) - Point.x) <= EPS || max(Point1.x, Point2.x) >= Point.x) &&
			 (_ABS(Point.y - min(Point1.y, Point2.y)) <= EPS || min(Point1.y, Point2.y) <= Point.y) &&
			 (_ABS(max(Point1.y, Point2.y) - Point.y) <= EPS || max(Point1.y, Point2.y) >= Point.y));
}

template < class T >
bool Point_in_line(const Point2D < T > &Point, const Line2D < T > &Line) {
    return (_ABS(Point_to_line(Point, Line)) <= EPS);
}

template < class T >
bool Point_in_circle(const Point2D < T > &Point, const Circle < T > &_Circle) {
	return (dist(Point, _Circle) <= EPS);
}

#endif // A_IN_B2D_HPP_INCLUDED
