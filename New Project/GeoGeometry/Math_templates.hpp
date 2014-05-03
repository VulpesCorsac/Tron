#ifndef MATH_TEMPLATES_HPP_INCLUDED
#define MATH_TEMPLATES_HPP_INCLUDED

// Helpful Functions

template < class T >
T _ABS(const T &x) {
    if (x < 0)
        return -x;
    return x;
}

template < class T >
T _SQR(const T &x) {
    return x * x;
}

template < class T >
T PI(void) {
    return 3.141592653589793238462633832795088693993;
}

template < class T >
T GCD(T a, T b) {
    a = (a < 0 ? -a : a);
    b = (b < 0 ? -b : b);
    while (a > 0 && b > 0) {
        if (a > b)
            a %= b;
        else
            b %= a;
    }
    return a + b;
}

template < class T >
T SIGN(T a)
{
    if (a == 0)
        return 0;
    if (a > 0)
        return 1;
    else
        return -1;
}

#endif // MATH_TEMPLATES_HPP_INCLUDED
