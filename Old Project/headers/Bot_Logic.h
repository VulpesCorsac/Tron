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
        //¬ектор личных врагов
        int * enemy;

        //¬ектор психотипов
        int * psychoTypes;

        //¬ектор горизонтальных линий
        vector < lightLine > hLine;

        //получение минимальной дистанции по направлению
        int getMinSideDist(int number, Player *playerList, Direction direction);

        //¬ектор вертикальных линий
        vector < lightLine > vLine;

        //”никальный набор пр€мых
        set    < lightLine > uniq;

        //ќбновление векторов линий
        void  updateLine(Player * playerList, int numberOfPlayers);

        //получаем конкретное решение
        int getMinDist(int number, Player *playerList);

        //определение минимальной дистанции слева и справа
        int getMinSideDist(int number, Player *playerList, int side);

        //поиск ближайшего врага
        void findYourEnemy( Player * playerList, int numberOfPlayers);

        //выбор психотипа
        void choosePsychoTypes( Player * playerList, int numberOfPlayers);

        CLogic();

        //выбор стороны в зависимости от направлени€
        int getTurn(Direction preferedDir, Direction curDirection);

    public:

        CLogic(int numberOfPlayers);

        vector <int> updateTurn(Player * playerList, int numberOfPlayers);

        CLogic(Player *playerList ,int numberOfPlayers);
};

#endif
