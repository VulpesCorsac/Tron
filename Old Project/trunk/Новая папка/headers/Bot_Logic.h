#ifndef BOT_LOGIC_INCLUDED
#define BOT_LOGIC_INCLUDED

#include "..\stdafx.h"
#include "Main.h"
#include "Player.h"

const float MIN_ALLOWED_DIST = 1.088;
const int TURN_LEFT = -1;
const int TURN_RIGHT = 1;

struct lightLine
{
    Point begin, end;
	const bool operator < (const lightLine &other) const {
		return begin < other.begin || (begin == other.begin && end < other.end);
	}
};



class CLogic
{
    private:
        //������ ������ ������
        int * enemy;

        //������ ����������
        int * psychoTypes;

        //������ �������������� �����
        vector < lightLine > hLine;

        //��������� ����������� ��������� �� �����������
        int getMinSideDist(int number, Player *playerList, Direction direction);

        //������ ������������ �����
        vector < lightLine > vLine;

        //���������� ����� ������
        set    < lightLine > uniq;

        //���������� �������� �����
        void  updateLine(Player * playerList, int numberOfPlayers);

        //�������� ���������� �������
        int getMinDist(int number, Player *playerList);

        //����������� ����������� ��������� ����� � ������
        int getMinSideDist(int number, Player *playerList, int side);

        //����� ���������� �����
        void findYourEnemy( Player * playerList, int numberOfPlayers);

        //����� ���������
        void choosePsychoTypes( Player * playerList, int numberOfPlayers);

        CLogic();

        //����� ������� � ����������� �� �����������
        int getTurn(Direction preferedDir, Direction curDirection);

    public:

        CLogic(int numberOfPlayers);

        vector <int> updateTurn(Player * playerList, int numberOfPlayers);

        CLogic(Player *playerList ,int numberOfPlayers);
};

#endif
