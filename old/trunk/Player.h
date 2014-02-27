#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Main.h"

// �����
class Player {
public:
    // ��������
    type speed;

    // ����� ���������
    vector < Point > turns;

    // ������� �����������
    Direction direction;

    // ������� �������
    Point position;

    // ����� �������
    int team;

    // �������� ���������� ������
    bool Check();

    // ������ �����������
    Player();

    // ����������� �� ��������� ����� � ���������� �����������
    Player(Point starting_point, Direction starting_direction, int including_team);

    // ������� ������
    void Turn_Right();

    // ������� �����
    void Turn_Left();

    // ����������
    void Update(type dt);

    // ����������
    ~Player();

};

#endif // PLAYER_H_INCLUDED
