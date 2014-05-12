#ifndef A_IN_B3D_HPP_INCLUDED
#define A_IN_B3D_HPP_INCLUDED

template < class T >
bool Point_in_box(const Point3D < T > &Point1, const Point3D < T > &Point2, const Point3D < T > &Point) {
    return  (abs(Point.x - std::min(Point1.x, Point2.x)) <= EPS || std::min(Point1.x, Point2.x) <= Point.x) &&
            (abs(std::max(Point1.x, Point2.x) - Point.x) <= EPS || std::max(Point1.x, Point2.x) >= Point.x) &&
            (abs(Point.y - std::min(Point1.y, Point2.y)) <= EPS || std::min(Point1.y, Point2.y) <= Point.y) &&
            (abs(std::max(Point1.y, Point2.y) - Point.y) <= EPS || std::max(Point1.y, Point2.y) >= Point.y) &&
            (abs(Point.z - std::min(Point1.z, Point2.z)) <= EPS || std::min(Point1.z, Point2.z) <= Point.z) &&
            (abs(std::max(Point1.z, Point2.z) - Point.z) <= EPS || std::max(Point1.z, Point2.z) >= Point.z);
}

template < class T >
bool Point_in_line(const Point3D < T > &Point, const Line3D < T > &Line) {
    return (Vector_mul(Line.Vector, Vector3D < T > (Point, Line.Point)) == Vector3D < T > (0, 0, 0));
}

template < class T >
bool Point_in_plane(const Point3D < T > &Point, const Plane3D < T > &Plane) {
    return (ABS(Point_to_plane(Point, Plane)) < EPS);
}

template < class T >
bool Point_in_segment(const Point3D < T > &Point, const Segment3D < T > &Segment) {
    return (Point_in_box(Segment.A, Segment.B, Point) && Point_in_line_3D(Point, Line3D < T > (Segment.A, Segment.B)));
}

template < class T >
bool Point_in_sphere(const Point3D < T > &Point, const Sphere < T > &Sphere) {
    return (dist(Point, Sphere) <= EPS);
}

template < class T >
bool Segment_cross_sphere(const Segment3D < T > &Segment, const Sphere < T > &Sphere) {
    return (dist(Segment, Sphere) <= EPS);
}

template < class T >
bool Sphere_cross_plane(const Sphere < T > &Sphere, const Plane3D < T > &Plane) {
    return (dist(Sphere.Centre, Plane) <= Sphere.R);
}

template < class T >
bool Line_cross_sphere(const Line3D < T > &Line, const Sphere < T > &Sphere) {
    return (dist(Sphere.Centre, Line) <= Sphere.R);
}

template < class T >
bool Line_in_plane(const Line3D < T > &Line, const Plane3D < T > &Plane) {
    return (Point_in_plane(Line.Point, Plane) && Point_in_plane(Line.Point + Line.Vector, Plane));
}

#endif // A_IN_B3D_HPP_INCLUDED
