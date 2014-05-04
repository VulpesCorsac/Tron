#ifndef FUNCTIONS_SEGMENT2D_HPP_INCLUDED
#define FUNCTIONS_SEGMENT2D_HPP_INCLUDED

template < class T >
Segment2D < T > Turn(const Segment2D < T > &_Segment, const T &alpha) {
    return Segment2D < T > (turn(_Segment.A, alpha), turn(_Segment.B, alpha));
}

template < class T >
Segment2D < T > Turn(const Segment2D < T > &_Segment, const Point2D < T > &_Point, const T &alpha) {
    return Segment2D < T > (turn(_Segment.A, _Point, alpha), turn(_Segment.A, _Point, alpha));
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

#endif // FUNCTIONS_SEGMENT2D_HPP_INCLUDED
