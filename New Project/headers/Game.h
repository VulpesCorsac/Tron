#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "main.h"
#include "player.h"
#include "render.h"

class CLogic;

class Game {
private:
    // ����� ���������� ����� �� GLUT
    int lFrameTime;

    // ������ �� ������� (������ ���)
    bool pressedLeft, pressedRight;

    // ����� ���������� ����� �� QueryPerformanceCounter
    long long int lTimePC;

    //�������� ������ �� ����������� ����
    int gameOverCountdown;

    //������� ������� �������
    void resetTeams();

    CLogic* botLogic;
public:

    //���� �����������
    bool gameOver;

    // ����� ���������
    Render* render;

    // ������
    vector < Player > players;

    // ���������� �������
    int number_of_players;

    // ���������� ������
    int number_of_teams;

    // ����������� ���������� ������
    int s_number_of_teams;

    // ������ �������������
    vector < int > were_crashed;

    // ������� ����
    static const int N = 55;
    static const int M = 55;

    // ������ �����������
    Game();

    // ���������� ������ ������
    void Add_Player(Player new_player);

    // ���������� ���� �������
    void Update(type dt);

    // ����� ������������
    int Find_Crashes(vector < int > &crashed);

    // �������
    void On_Crash(int player, int competitor, int mode);

    // �������� ������
    void Delete_Player(int i);

    // �������� ����, ��� �����������
    void Delete_Crashed(vector < int > &crashed);

    // ����������� ���-�� ������
    int Set_number_of_teams();

    // �������� ������
    Player Get_player(int team, int _ID, bool bot = true);

    // �������������
    void Init();

    // ������ ����
    void Run();

    // ������� ����
    void Cycle();

    //���������� � ���� �� �����������
    void Restart();

    //��������� ������� � ����������� �� �������
    void ManualSetup();

    // ������� �������
    void OnKey(int key, bool special);

    // ����������
    ~Game() ;
};

#endif // GAME_H_INCLUDED
