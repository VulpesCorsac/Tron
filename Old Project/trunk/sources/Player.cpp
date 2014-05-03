#include "..\stdafx.h"
#include "..\Headers\Player.h"

// �������� ���������� ������
bool Player::Check() {
    if (position.x < 1)
        return false;
    if (position.y < 1)
        return false;
    if (abs(sqr(direction.dx) + sqr(direction.dy) - 1) > Eps)
        return false;
    if (abs(sqr(direction.dx) + sqr(direction.dy)) < Eps)
        return false;

    return true;
}

// ������ �����������
Player::Player() {
    alive = true;
    ID = -1;
    team = 0;
    speed = Speed0;
    turns.clear();
    direction.dx = 0;
    direction.dy = 0;
    position.x = -1;
    position.y = -1;
}

// ����������� �� ��������� ����� � ���������� �����������
Player::Player(Point starting_point, Direction starting_direction, int including_team, int _ID, bool bot) {
    is_bot = bot;
    alive = true;
    ID = _ID;
    team = including_team;
    speed = Speed0;
    turns.clear();
    direction.dx = starting_direction.dx;
    direction.dy = starting_direction.dy;
    position.x = starting_point.x;
    position.y = starting_point.y;
    turns.push_back(position);

    assert(Check());
}

// ������� ������
void Player::Turn_Right() {
    type old_dx = direction.dx;
    direction.dx = direction.dy;
    direction.dy = -old_dx;

    turns.push_back(position);
    return;
}

// ������� �����
void Player::Turn_Left() {
    type old_dx = direction.dx;
    direction.dx = -direction.dy;
    direction.dy = old_dx;

    turns.push_back(position);
    return;
}

// ����������
void Player::Update(type dt) {
    if (alive) {
        position.x += direction.dx*dt*speed;
        position.y += direction.dy*dt*speed;
    }

    return;
}

// ����������
Player::~Player() {
    alive = false;
    ID = -1;
    team = 0;
    speed = Speed0;
    turns.clear();
    direction.dx = 0;
    direction.dy = 0;
    position.x = -1;
    position.y = -1;
}
