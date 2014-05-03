#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Main.h"

// �����
class Player {
public:
    // � � ��� ���?
    bool alive;

    // � � ���?
    bool is_bot;

    // ��������
    type speed;

    // ID
    int ID;

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

    // ����������� �� ��������� ����� � ���������� ����������� � �.�.
    Player(Point starting_point, Direction starting_direction, int including_team, int _ID, bool bot);

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
