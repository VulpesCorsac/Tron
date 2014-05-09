#ifndef DISTANSES3D_HPP_INCLUDED
#define DISTANSES3D_HPP_INCLUDED

template < class T >
T dist(const Point3D < T > &Point1, const Point3D < T > &Point2) {
    return SQRT(SQR(Point1.x - Point2.x) + SQR(Point1.y - Point2.y) + SQR(Point1.z - Point2.z));
}

template < class T >
T dist(const Point3D < T > &Point, const Line3D < T > &Line) {
    Vector3D < T > Tmp = Vector_mul(Vector3D < T > (Point, Line.Point), Line.Vector);
    return (Tmp.Norm() / Line.Vector.Norm());
}

template < class T >
T dist(const Point3D < T > &Point, const Segment3D < T > &Segment) {
    Vector3D < T > V1(Point, Segment.A), V2(Point, Segment.B);
    Vector3D < T > S = Vector_mul(V1, V2);
    if (SQR(V1.Norm()) >= SQR(V2.Norm()) + SQR(Segment.length()) ||
        SQR(V2.Norm()) >= SQR(V1.Norm()) + SQR(Segment.length()))
        return std::min(dist(Point, Segment.A), dist(Point, Segment.B));
    else
        return (S.Norm() / Segment.length());
}

template < class T >
T dist(const Point3D < T > &Point, const Sphere < T > &Sphere) {
    T ans = dist(Point, Sphere.Centre) - Sphere.R;
    if (ans <= EPS)
        ans = 0;
    return ans;
}

template < class T >
T dist(const Point3D < T > &Point, const Plane3D < T > &Plane) {
    return (ABS(Point_to_plane(Point, Plane))) /(SQRT(SQR(Plane.A) + SQR(Plane.B) + SQR(Plane.C)));
}

template < class T >
T dist (const Line3D < T > &Line, const Plane3D < T > &Plane) {
    if ((Point_in_plane_3D(Line.Point, Plane) && Point_in_plane_3D(Line.Point + Line.Vector, Plane)) ||
        ABS(Plane.A*Line.Vector.x + Plane.B*Line.Vector.y + Plane.C*Line.Vector.z) >= EPS)
        return 0;
    return dist(Line.Point, Plane);
}

template < class T >
T dist(const Segment3D < T > &Segment, const Sphere < T > &Sphere) {
    T ans = dist(Sphere.Centre, Segment) - Sphere.R;
    if (ans < EPS)
        ans = 0;
    return ans;
}

template < class T >
T dist(const Segment3D < T > &Segment, const Plane3D < T > &Plane) {
    if (Point_to_plane(Segment.A, Plane)*Point_to_plane(Segment.B, Plane) <= EPS)
        return 0;
    return std::min(dist(Segment.A, Plane), dist(Segment.B, Plane));
}


#endif // DISTANSES3D_HPP_INCLUDED
