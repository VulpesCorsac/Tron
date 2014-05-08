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

#endif // FUNCTIONS_SEGMENT2D_HPP_INCLUDED
