#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#define sqr(a) ((a)*(a))

// �������� ��
const double Eps = 1e-5;
const double Sur = 1e-2;

typedef float type;

// �����������
struct Direction {
    type dx;
    type dy;

    Direction () {} ;
    Direction (type ax, type ay) : dx(ax), dy(ay) {} ;
};

// �����
struct Point {
    type x;
    type y;
    Point() {};
    Point( type ax, type ay) : x(ax), y(ay) {} ;

    bool normalize() {
        type cf = sqrtf(x*x + y*y);
        if (cf < Eps)
            return false;
        cf = 1.0f / cf;
        x *= cf;
        y *= cf;
        return true;
    }

	Point & operator += (const Point& other) {
		x += other.x; y += other.y;
		return *this;
	}

	Point & operator -= (const Point& other) {
		x -= other.x; y -= other.y;
		return *this;
	}

	const Point operator + (const Point& other) const {
		return Point(x + other.x, y + other.y);
	}

	const Point operator - (const Point& other) const {
		return Point(x - other.x, y - other.y);
	}

	const Point operator * (const type other) const {
		return Point(x * other, y * other);
	}

	const Point operator / (const type other) const {
		return Point(x / other, y / other);
	}
	const bool operator < (const Point& other) const {
		return x < other.x || (x == other.x && y < other.y);
	}
	const bool operator == (const Point& other) const {
		return (x == other.x && y == other.y);
	}
};

// ������
class Line
{
public:
    type a, b, c;
    // �������� ������ ax + by + c = 0
	Line(type _a = 0, type _b = 0, type _c = 0)
    {
        a = _a;
        b = _b;
        c = _c;
    }
};

// ���������� ��������
type abs(type a);

// ��������� ��������
const type Speed0 = 10.0;

// ����������� ��������
bool intersect(Point a, Point b, Point c, Point d);

// ����� �����������
bool cross_segment(Point p1, Point p2, Point p3, Point p4, Point &t);

// ���������������
double dist(Point a, Point b);
int area(Point a, Point b, Point c);
bool intersect_1(int a, int b, int c, int d);
bool point_in_box(Point t, Point p1, Point p2);

Line toline(Point p1,Point p2);
int cross_line(Line l1, Line l2, Point &p);
bool is_equal_line(Line l1, Line l2);
bool is_parallel_line (Line l1, Line l2);

#endif // MAIN_H_INCLUDED
