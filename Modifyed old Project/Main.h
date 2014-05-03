#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#define sqr(a) ((a)*(a))

typedef double type;

// направление
struct Direction {
    type dx;
    type dy;
};

// точка
struct Point {
    type x;
    type y;
};

// абсолютное значение
type abs(type a);

// начальная скорость
const type Speed0 = 1.0;

// точность до
const double Eps = 1e-5;

// пересечение отрезков
bool intersect(Point a, Point b, Point c, Point d);

// вспомогательное
int area(Point a, Point b, Point c);
bool intersect_1(int a, int b, int c, int d);

#endif // MAIN_H_INCLUDED
