#ifndef A_TO_B2D_HPP_INCLUDED
#define A_TO_B2D_HPP_INCLUDED

template < class T >
T Point_to_line(const Point2D < T > &Point, const Line2D < T > &Line) {
    return Line.A*Point.x + Line.B*Point.x + Line.C;
}

#endif // A_TO_B2D_HPP_INCLUDED
