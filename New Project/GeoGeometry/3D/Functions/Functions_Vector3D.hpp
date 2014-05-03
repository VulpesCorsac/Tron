#ifndef FUNCTIONS_VECTOR3D_H_INCLUDED
#define FUNCTIONS_VECTOR3D_H_INCLUDED

template < class T >
T Scalar_mul(const Vector3D < T > &Vector1, const Vector3D < T > &Vector2) {
    return Vector1.x*Vector2.x + Vector1.y*Vector2.y + Vector1.z*Vector2.z;
}

template < class T >
Vector3D < T > Vector_mul(const Vector3D < T > &Vector1, const Vector3D < T > &Vector2) {
    return Vector3D < T > (Vector1.y*Vector2.z - Vector2.y*Vector1.z,
                           Vector2.x*Vector1.z - Vector1.x*Vector2.z,
                           Vector1.x*Vector2.y - Vector2.x*Vector1.y);
}

template < class T >
Vector3D < T > Norm(const Vector3D < T > &Vector) {
    return Vector3D < T > (Vector.x / Vector.Norm(), Vector.y / Vector.Norm(), Vector.z / Vector.Norm());
}


#endif // FUNCTIONS_VECTOR3D_H_INCLUDED
