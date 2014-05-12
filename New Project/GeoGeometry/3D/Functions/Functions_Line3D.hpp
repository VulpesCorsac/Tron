#ifndef FUNCTIONS_LINE3D_HPP_INCLUDED
#define FUNCTIONS_LINE3D_HPP_INCLUDED

template < class T >
bool Are_parallel_lines(const Line3D < T > &Line1, const Line3D < T > &Line2) {
    return (Vector_mul(Line1.Vector, Line2.Vector) == Vector3D < T > (0, 0, 0));
}

template < class T >
Point3D < T > Point_in_line_by_X(const Line3D < T > &Line, const T &X) {
    T t = (X - Line.Point.x) / Line.Vector.x;
    return Point3D < T > (Line.Point.x + t*Line.Vector.x,
                          Line.Point.y + t*Line.Vector.y,
                          Line.Point.z + t*Line.Vector.z);
}

template < class T >
Point3D < T > Point_in_line_by_Y(const Line3D < T > &Line, const T &Y) {
    T t = (Y - Line.Point.y) / Line.Vector.y;
    return Point3D < T > (Line.Point.x + t*Line.Vector.x,
                          Line.Point.y + t*Line.Vector.y,
                          Line.Point.z + t*Line.Vector.z);
}

template < class T >
Point3D < T > Point_in_line_by_Z(const Line3D < T > &Line, const T &Z) {
    T t = (Z - Line.Point.z) / Line.Vector.z;
    return Point3D < T > (Line.Point.x + t*Line.Vector.x,
                          Line.Point.y + t*Line.Vector.y,
                          Line.Point.z + t*Line.Vector.z);
}

#endif // FUNCTIONS_LINE3D_HPP_INCLUDED
