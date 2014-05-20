#ifndef MATH_TEMPLATES_HPP_INCLUDED
#define MATH_TEMPLATES_HPP_INCLUDED

// Helpful Functions

#define M_SQR(x) ((x) * (x))
#define M_ABS(a) ((a) > 0 ? (a) : -(a))
#define M_MIN(a, b) ((a) < (b) ? (a) : (b))
#define M_MAX(a, b) ((a) > (b) ? (a) : (b))

template < class T >
T ABS(const T &x) {
    if (x < 0)
        return -x;
    return x;
}

template < class T >
T SQR(const T &x) {
    return x * x;
}

template < class T >
T SQRT(const T &x) {
	return sqrt(x);
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
T SIGN(T a) {
    if (a == 0)
        return 0;
    if (a > 0)
        return 1;
    else
        return -1;
}

template < class T >
T Heaviside(T a) {
	if (a < 0)
		return 0;
	else
		return 1;
}

#endif // MATH_TEMPLATES_HPP_INCLUDED
