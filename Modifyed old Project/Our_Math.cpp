#include "..\stdafx.h"
#include "..\Headers\Main.h"

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

bool cross_segment(Point p1, Point p2, Point p3, Point p4, Point &t) {
    t.x = t.y = -100;

    // Строим прямые проходящие через эти отрезки и пересекаем их
    Line l1 = toline(p1, p2);
    Line l2 = toline(p3, p4);

    int flag = cross_line(l1, l2, t);
    if (flag == 0)
        return false;

    // Если прямые совпадают, проверяем каждый конец отрезка на принадлежность другому отрезку
    if (flag == 2)
    {
        if (point_in_box (p1, p3, p4)) {
            t = p1;
            return true;
        }
        if (point_in_box (p2, p3, p4)) {
            t = p2;
            return true;
        }
        if (point_in_box (p3, p1, p2)) {
            t = p3;
            return true;
        }
        if (point_in_box (p4, p1, p2)) {
            t = p4;
            return true;
        }
        return false;
    }

    // Если прямые пересекаются, проверяем принадлежит ли точка пересечения обоим отрезкам
    return point_in_box (t, p1, p2) && point_in_box (t, p3, p4);
}

Line toline(Point p1,Point p2) {
    double a = p2.y - p1.y;
    double b = p1.x - p2.x;
    return Line(a, b, - a * p1.x - b * p1.y);
}

bool is_parallel_line (Line l1, Line l2) {
    return abs (l1.a * l2.b - l2.a * l1.b) <= Eps;
}

int cross_line(Line l1, Line l2, Point &p) {
    if (is_equal_line (l1, l2))
		return 2;
    if (is_parallel_line (l1, l2))
		return 0;

    p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
    p.y = (l1.b != 0 ? (- l1.c - l1.a * p.x) / l1.b : (- l2.c - l2.a * p.x) / l2.b);
    return 1;
}

bool is_equal_line(Line l1, Line l2) {
    return abs (l1.a * l2.b - l2.a * l1.b) <= Eps &&
            abs (l1.a * l2.c - l2.a * l1.c) <= Eps &&
            abs (l1.b * l2.c - l2.b * l1.c) <= Eps;
}

bool point_in_box(Point t, Point p1, Point p2) {
    return  (abs (t.x - min(p1.x, p2.x)) <= Eps || min(p1.x, p2.x) <= t.x) &&
            (abs (max(p1.x, p2.x) - t.x) <= Eps || max(p1.x, p2.x) >= t.x) &&
            (abs (t.y - min(p1.y, p2.y)) <= Eps || min(p1.y, p2.y) <= t.y) &&
            (abs (max(p1.y, p2.y) - t.y) <= Eps || max(p1.y, p2.y) >= t.y);
}

double dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

