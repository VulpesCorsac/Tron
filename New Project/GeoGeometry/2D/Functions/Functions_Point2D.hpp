#ifndef FUNCTIONS_POINT2D_HPP_INCLUDED
#define FUNCTIONS_POINT2D_HPP_INCLUDED

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
