#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#define sqr(a) ((a)*(a))

typedef double type;

// �����������
struct Direction {
    type dx;
    type dy;
};

// �����
struct Point {
    type x;
    type y;
};

// ���������� ��������
type abs(type a);

// ��������� ��������
const type Speed0 = 1.0;

// �������� ��
const double Eps = 1e-5;

// ����������� ��������
bool intersect(Point a, Point b, Point c, Point d);

// ���������������
int area(Point a, Point b, Point c);
bool intersect_1(int a, int b, int c, int d);

#endif // MAIN_H_INCLUDED
