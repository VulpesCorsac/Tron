#ifndef A_TO_B3D_H_INCLUDED
#define A_TO_B3D_H_INCLUDED

template < class T >
T Point_to_plane(const Point3D < T > &Point, const Plane3D < T > &Plane) {
    return Plane.A*Point.x + Plane.B*Point.y + Plane.C*Point.z + Plane.D;
}

#endif // A_TO_B3D_H_INCLUDED
