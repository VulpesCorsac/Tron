#ifndef FUNCTIONS_POLYGON2D_H_INCLUDED
#define FUNCTIONS_POLYGON2D_H_INCLUDED

template < class T >
Polygon2D < T > turn(const Polygon2D < T > &_Polygon, const T &alpha) {
    Polygon2D < T > ans = _Polygon;
    for (size_t i = 0; i < _Polygon.Polygon.size(); i++)
        ans.Polygon[i] = turn(_Polygon.Polygon[i], alpha);
    return ans;
}

template < class T >
Polygon2D < T > turn(const Polygon2D < T > &_Polygon, const Point2D < T > &_Point, const T &alpha) {
    Polygon2D < T > ans = _Polygon;
    for (size_t i = 0; i < _Polygon.Polygon.size(); i++)
        ans.Polygon[i] = turn(_Polygon.Polygon[i], _Point, alpha);
    return ans;
}

#endif // FUNCTIONS_POLYGON2D_H_INCLUDED
