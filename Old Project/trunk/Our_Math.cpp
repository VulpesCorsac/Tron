#include "stdafx.h"
#include "Main.h"

type abs(type a) {
    if (a < 0)
        return -a;
    return a;
}

int area(Point a, Point b, Point c) {
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool intersect_1(int a, int b, int c, int d) {
	if (a > b)
        swap (a, b);
	if (c > d)
        swap (c, d);
	return max(a,c) <= min(b,d);
}

bool intersect(Point a, Point b, Point c, Point d) {
	return intersect_1 (a.x, b.x, c.x, d.x)
		&& intersect_1 (a.y, b.y, c.y, d.y)
		&& area(a,b,c) * area(a,b,d) <= Eps
		&& area(c,d,a) * area(c,d,b) <= Eps;
}
