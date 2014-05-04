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

template < class T >
bool Cross_polygon(const Polygon2D < T > &Polygon1, const Polygon2D < T > &Polygon2) {
    std::vector < Point2D < T > > Vector1 = Polygon1.Polygon;
    Vector1.push_back(Vector1[0]);
    std::vector < Point2D < T > > Vector2 = Polygon2.Polygon;
    Vector2.push_back(Vector2[0]);
    for (size_t i = 0; i < Vector1.size() - 1; i++)
        for (size_t j = 0; j < Vector2.size() - 1; j++) {
            if (Cross_segment(Segment2D < T > (Vector1[i], Vector1[i+1]), Segment2D < T > (Vector2[j], Vector2[j+1])))
                return true;
        }

    return false;
}


#endif // FUNCTIONS_POLYGON2D_H_INCLUDED
