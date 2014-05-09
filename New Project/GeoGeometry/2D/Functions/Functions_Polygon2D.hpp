#ifndef FUNCTIONS_POLYGON2D_HPP_INCLUDED
#define FUNCTIONS_POLYGON2D_HPP_INCLUDED

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
	assert(Polygon1.Polygon.size() >= 2 && Polygon2.Polygon.size() >= 2 && "One of polygons contain less than 2 points - that's not enough for intersecting!");
	std::vector < Point2D < T > > Vector1 = Polygon1.Polygon;
	Vector1.push_back(Vector1[0]);
	std::vector < Point2D < T > > Vector2 = Polygon2.Polygon;
	Vector2.push_back(Vector2[0]);
	for (size_t i = 0; i < Vector1.size() - 1; i++)
	for (size_t j = 0; j < Vector2.size() - 1; j++) {
		if (Cross_segment(Segment2D < T >(Vector1[i], Vector1[i + 1]), Segment2D < T >(Vector2[j], Vector2[j + 1])))
			return true;
	}

	return false;
}

template < class T >
bool Cross_polygon_in_turning(const Polygon2D < T > &Turning, const Polygon2D < T > &Static, const T &alpha, const long long &n) {
	Polygon2D < T > Turned = Turning;
	T d_alpha = alpha / n;
	for (int i = 0; i <= n; i++) {
		if (Cross_polygon(Turned, Static))
			return true;
		Turned = turn(Turning, i*d_alpha);
	}
	return false;
}

template < class T >
bool Cross_polygon_in_turning(const Polygon2D < T > &Turning, const Point2D < T > TurnOf, const Polygon2D < T > &Static, const T &alpha, const long long &n) {
	Vector2D < T > Vector(TurnOf);
	return Cross_polygon_in_turning(Turning - Vector, Static - Vector, alpha, n);
}

#endif // FUNCTIONS_POLYGON2D_HPP_INCLUDED
