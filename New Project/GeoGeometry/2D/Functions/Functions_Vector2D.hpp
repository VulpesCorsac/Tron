#ifndef FUNCTIONS_VECTOR2D_HPP_INCLUDED
#define FUNCTIONS_VECTOR2D_HPP_INCLUDED

template < class T >
Vector2D < T > Norm(const Vector2D < T > &Vector) {
    return Vector2D < T > (Vector.x / Vector.Norm(), Vector.y / Vector.Norm());
}

template < class T >
Vector2D < T > turn(const Vector2D < T > &Vector, const T &alpha) {
    T cosalpha = cos(alpha);
    T sinalpha = sin(alpha);
    return Vector2D < T > (Vector.x*cosalpha - Vector.y*sinalpha, Vector.x*sinalpha + Vector.y*cosalpha);
}

template < class T >
Vector2D < T > turn(const Vector2D < T > &Vector, const Point2D < T > &Of, const T &alpha) {
	Point2D < T > Tmp = turn(Point2D < T >(-Of.x + Vector.x, -Of.y + Vector.y), alpha);
    return Vector2D < T > (Of.x + Tmp.x, Of.y + Tmp.y);
}

#endif // FUNCTIONS_VECTOR2D_HPP_INCLUDED
