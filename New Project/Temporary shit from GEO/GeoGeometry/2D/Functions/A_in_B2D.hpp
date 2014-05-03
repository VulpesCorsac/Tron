#ifndef A_IN_B2D_HPP_INCLUDED
#define A_IN_B2D_HPP_INCLUDED

template < class T >
bool Point_in_box(const Point2D < T > &Point1, const Point2D < T > &Point2, const Point2D < T > &Point) {
    return  (abs(Point.x - std::min(Point1.x, Point2.x)) <= EPS || std::min(Point1.x, Point2.x) <= Point.x) &&
            (abs(std::max(Point1.x, Point2.x) - Point.x) <= EPS || std::max(Point1.x, Point2.x) >= Point.x) &&
            (abs(Point.y - std::min(Point1.y, Point2.y)) <= EPS || std::min(Point1.y, Point2.y) <= Point.y) &&
            (abs(std::max(Point1.y, Point2.y) - Point.y) <= EPS || std::max(Point1.y, Point2.y) >= Point.y);
}

template < class T >
bool Point_in_line(const Point2D < T > &Point, const Line2D < T > &Line) {
    return (_ABS(Point_to_line(Point, Line)) <= EPS);
}

#endif // A_IN_B2D_HPP_INCLUDED
