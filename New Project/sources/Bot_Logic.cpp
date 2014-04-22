#include "stdafx.h"
#include "..\Headers\Bot_Logic.h"
#include "..\Headers\Player.h"
#include "..\Headers\Main.h"
#include "..\Headers\Game.h"


//создание линии из двух точек

lightLine createLine(Point a, Point b)
{
    lightLine line;
    line.begin = a;
    line.end = b;
    return line;
}


//получение расстояния до точки пересечения между двумя прямыми

float getDistanceLines(lightLine a,lightLine b)
{
    float dirX, dirY;
    dirX=a.begin.x-a.end.x;
    dirY=a.begin.y-a.end.y;

    if (a.begin.x == b.begin.x && a.begin.y == b.begin.y) return 1488288;
    if (a.begin.x == b.end.x && a.begin.y == b.end.y) return 1488288;

    float gap = 0.3f;

    if ( fabsf(dirX) <= 0.0001f )
    {   if (( a.end.x < max( b.begin.x + gap, b.end.x + gap ) ) && ( a.end.x > min( b.begin.x - gap, b.end.x - gap )))
        return b.end.y-a.begin.y;
        else return 1488228;
    }
    if  ( fabsf(dirY) <= 0.0001f )
    {   if (( a.end.y < max( b.begin.y + gap, b.end.y + gap ) ) && ( a.end.y > min( b.begin.y - gap, b.end.y - gap )))
        return b.end.x-a.begin.x;
        else return 1488228;
    }
    return 1488;
    //условие пересечения пямой по у
}

int  CLogic :: getTurn(Direction preferedDir, Direction curDirection)
{

    if(fabsf(curDirection.dy) <= 0.0001){
        if((fabsf(preferedDir.dy) <= 0.0001) && (preferedDir.dx * curDirection.dx > 0))
            return 0;
        if((fabsf(preferedDir.dy) <= 0.0001) && (preferedDir.dx * curDirection.dx < 0))
            return TURN_RIGHT;
        if((fabsf(preferedDir.dx) <= 0.0001) && (preferedDir.dy * curDirection.dx > 0))
            return TURN_LEFT;
        if((fabsf(preferedDir.dx) <= 0.0001) && (preferedDir.dy * curDirection.dx < 0))
            return TURN_RIGHT;
    }
    if(fabsf(curDirection.dx) <= 0.0001){
        if((fabsf(preferedDir.dx) <= 0.0001) && (preferedDir.dy * curDirection.dy > 0))
        return 0;
        if((fabsf(preferedDir.dx) <= 0.0001) && (preferedDir.dy * curDirection.dy < 0))
        return TURN_LEFT;
        if((fabsf(preferedDir.dy) <= 0.0001) && (preferedDir.dx * curDirection.dy > 0))
        return TURN_RIGHT;
        if((fabsf(preferedDir.dy )<= 0.0001) && (preferedDir.dx * curDirection.dy < 0))
        return TURN_LEFT;
    }
    return 0;
}
//основная функция

vector <int> CLogic :: updateTurn( Player * playerList, int numberOfPlayers)
 {
    vector <int> solutions;
    float curDist;
    Direction curDir;
    int *preferedSolution;
    Direction enemyDir;
    Direction preferedDir;
    Point enemyPos;
    preferedSolution = new int[numberOfPlayers];
    findYourEnemy(playerList, numberOfPlayers);
    updateLine( playerList, numberOfPlayers);

  /*  for(int i = 1; i < numberOfPlayers; i++){
            curDir = playerList[i].direction;
            if (getMinSideDist( i, playerList, curDir) < MIN_ALLOWED_DIST)
            preferedSolution[i] = 0;
            else preferedSolution[i] = 1;
    }
*/
    solutions.resize(numberOfPlayers);

    for( int i = 1; i< numberOfPlayers; i++){
            if(playerList[i].is_bot == 1 && playerList[i].alive){
                if (playerList[enemy[i]].alive == 0){
                    findYourEnemy(playerList, numberOfPlayers);
                }
                curDir = playerList[i].direction;
                enemyDir = playerList[enemy[i]].direction;
                enemyPos = playerList[enemy[i]].position;
                if(psychoTypes[i] == 0){

                    /*if ((fabsf(enemyDir.dx) <= 0.001488) && ((enemyPos.y - playerList[i].position.y) * (enemyDir.dy)) < 0){ // условие невозможности "подрезки"
                        preferedDir.dx = (enemyPos.x - playerList[i].position.x) / (abs(enemyPos.x - playerList[i].position.x) + 0.001f);
                         if(fabsf(preferedDir.dx) >= 0.0001)
                            preferedDir.dy = 0;
                        else  preferedDir.dy = enemyPos.y- playerList[i].position.y> 0 ? 1 : -1;
                    }*/
                    preferedDir = curDir;

                    if ((fabsf(enemyDir.dx) <= 0.001488) && ((enemyPos.y - playerList[i].position.y)*(enemyDir.dy) < 0)){     //условие  возможности "подрезки"
                        preferedDir.dx = enemyPos.x - playerList[i].position.x > 0 ? 1 : -1;
                        if (fabsf(enemyPos.x - playerList[i].position.x) <= 0.0001f) preferedDir.dx = 0;
                        if(fabsf(preferedDir.dx) >= 0.0001)
                            preferedDir.dy = 0;
                        else  preferedDir.dy = enemyPos.y- playerList[i].position.y> 0 ? 1 : -1;
                    }
                   /* if ((fabsf(enemyDir.dy) <= 0.001488) && ((enemyPos.x - playerList[i].position.x) * (enemyDir.dx)) > 0){   //условие невозможности "подрезки"
                        preferedDir.dy = (enemyPos.y - playerList[i].position.y) / abs(enemyPos.y - playerList[i].position.y);
                        if(fabsf(preferedDir.dy) >= 0.0001)
                            preferedDir.dx = 0;
                        else  preferedDir.dx = enemyPos.x - playerList[i].position.x > 0 ? 1 : -1;
                    }*/

                    if ((fabsf(enemyDir.dy) <= 0.001488) && ((enemyPos.x - playerList[i].position.x) * (enemyDir.dx)) < 0){    //условие возможности "подрезки"

                        preferedDir.dy = enemyPos.y- playerList[i].position.y> 0 ? 1 : -1;
                        if (fabsf(enemyPos.y - playerList[i].position.y) <= 0.0001f) preferedDir.dy = 0;
                        if(fabsf(preferedDir.dy) >= 0.0001)
                            preferedDir.dx = 0;
                        else  preferedDir.dx = enemyPos.x - playerList[i].position.x > 0 ? 1 : -1;
                    }

                    float md = getMinSideDist(i, playerList, preferedDir);
                    if (md < MIN_ALLOWED_DIST)
                    {
                        Direction dir1, dir2;
                        dir1.dx = -preferedDir.dy;
                        dir1.dy = preferedDir.dx;
                        dir2.dx = preferedDir.dy;
                        dir2.dy = -preferedDir.dx;
                        float d1 = getMinSideDist(i, playerList, dir1);
                        float d2 = getMinSideDist(i, playerList, dir2);
                        if (d1 < d2 && md < d2) {
                            preferedDir = dir2;
                        } else if (d2 < d1 && md < d1) {
                            preferedDir = dir1;
                        }
                    }
                    solutions[i] = getTurn(preferedDir, playerList[i].direction);
                }
                if (psychoTypes[i] == 1){
                    if ((fabsf(enemyDir.dx) <= 0.0001) && ((enemyPos.x - playerList[i].position.x) < 0) && (fabsf(curDir.dy) <= 0.0001) && (curDir.dx > 0))
                    solutions[i] = TURN_LEFT;
                    if ((fabsf(enemyDir.dx) <= 0.0001) && ((enemyPos.x - playerList[i].position.x) > 0) && (fabsf(curDir.dy) <= 0.0001) && (curDir.dx > 0))
                    solutions[i] = TURN_RIGHT;
                    if ((fabsf(enemyDir.dy) <= 0.0001) && ((enemyPos.y - playerList[i].position.y) < 0) && (fabsf(curDir.dx) <= 0.0001) && (curDir.dy > 0))
                    solutions[i] = TURN_LEFT;
                    if ((fabsf(enemyDir.dy) <= 0.0001) && ((enemyPos.y - playerList[i].position.y) > 0) && (fabsf(curDir.dx) <= 0.0001) && (curDir.dy > 0))
                    solutions[i] = TURN_RIGHT;
                }

                if(psychoTypes[i] == 2){

                    /*if ((fabsf(enemyDir.dx) <= 0.001488) && ((enemyPos.y - playerList[i].position.y) * (enemyDir.dy)) < 0){ // условие невозможности "подрезки"
                        preferedDir.dx = (enemyPos.x - playerList[i].position.x) / (abs(enemyPos.x - playerList[i].position.x) + 0.001f);
                         if(fabsf(preferedDir.dx) >= 0.0001)
                            preferedDir.dy = 0;
                        else  preferedDir.dy = enemyPos.y- playerList[i].position.y> 0 ? 1 : -1;
                    }*/
                    preferedDir = curDir;

                    float md = getMinSideDist(i, playerList, preferedDir);
                    if (md < MIN_ALLOWED_DIST)
                    {
                        Direction dir1, dir2;
                        dir1.dx = -preferedDir.dy;
                        dir1.dy = preferedDir.dx;
                        dir2.dx = preferedDir.dy;
                        dir2.dy = -preferedDir.dx;
                        float d1 = getMinSideDist(i, playerList, dir1);
                        float d2 = getMinSideDist(i, playerList, dir2);
                        if (d1 < d2 && md < d2) {
                            preferedDir = dir2;
                        } else if (d2 < d1 && md < d1) {
                            preferedDir = dir1;
                        }
                    }
                    solutions[i] = getTurn(preferedDir, playerList[i].direction);
                }
            }
    }
    return solutions;

 }

//поиск ближайших врагов
 void CLogic :: findYourEnemy( Player * playerList, int numberOfPlayers)
 {
     int curTeam;
     int curNumber;
  for(int i=0; i<numberOfPlayers; i++)
  {
      curTeam= playerList[i].team;

     double minDistance=320000;
      for(int j=0; j<numberOfPlayers; j++){
          if ( (dist( playerList[i].position, playerList[j].position)<minDistance) && (playerList[j].team!=curTeam) && (i != j) && (playerList[j].alive == 1))
            {
                minDistance=dist( playerList[i].position, playerList[j].position);
                enemy[i] = j;
        }
      }
  }
 }

//получение минимальной дистанции по направлению

int CLogic :: getMinSideDist(int number, Player *playerList, Direction direction)
{
    lightLine directVector;
    vector <lightLine> :: iterator curLine;
    float minDist, curDist;
    minDist = 100000;
    Point side;
    side.x = playerList[number].position.x + direction.dx * 0.1f;
    side.y = playerList[number].position.y + direction.dy * 0.1f;
    directVector = createLine( playerList[number].position, side);
    if ( fabsf( directVector.begin.x - directVector.end.x) <= 0.001f)
    {
        curLine = hLine.begin();
        while(curLine != hLine.end())
        {
            curDist = getDistanceLines(directVector, *curLine) * direction.dy;
            if ((curDist < minDist) && (curDist>0))
            minDist = curDist;
            curLine++;
        }
    }
    else
    {
        curLine = vLine.begin();
        while(curLine != vLine.end())
        {
            curDist = getDistanceLines(directVector, *curLine) * direction.dx;
            if ((curDist < minDist) && (curDist>0))
            minDist = curDist;
            curLine++;
        }
    }
    return minDist;
}

//получение минимальной дистанции слева для текущего игрока.

int CLogic :: getMinSideDist(int number, Player *playerList, int side)
{
    lightLine directVector;
    vector <lightLine> :: iterator  curLine;
    int minDist, curDist;
    minDist = 10000;
    directVector = createLine(playerList[number].position, playerList[number].turns.back());
    if (fabsf( directVector.begin.x - directVector.end.x) <= 0.001f)
    {
        curLine = hLine.begin();
        while(curLine != hLine.end())
        {
            curDist = getDistanceLines(directVector, *curLine);
            if ((curDist < minDist) && (curDist>0))
            minDist = curDist;
            curLine++;
        }
    }
    else
    {
        curLine=vLine.begin();
        while(curLine!=vLine.end())
        {
            curDist=getDistanceLines(directVector, *curLine);
            if ((curDist < minDist) && (curDist>0))
            minDist=curDist;
            curLine++;
        }
    }
    return minDist;
}

//получение минимальной дистанции для текущего игрока.

int CLogic :: getMinDist(int number, Player * playerList)
{
    lightLine directVector;
    vector <lightLine> :: iterator  curLine;
    int minDist, curDist;
    minDist=0;

    directVector = createLine(playerList[number].position, playerList[number].turns.back());
    if (fabsf( directVector.begin.x - directVector.end.x) <= 0.0001)
    {
        curLine = hLine.begin();
        while(curLine != hLine.end())
        {
            curDist = getDistanceLines(directVector, *curLine);
            if ((curDist < minDist) && (curDist>0))
            minDist = curDist;
            curLine++;
        }
    }
    else
    {
        curLine=vLine.begin();
        while(curLine!=vLine.end())
        {
            curDist=getDistanceLines(directVector, *curLine);
            if ((curDist < minDist) && (curDist>0))
            minDist=curDist;
            curLine++;
        }
    }
    return minDist;
}

//Добавление линий в вектор

void  CLogic :: updateLine( Player * playerList, int numberOfPlayers)
  {
    hLine.clear();
    vLine.clear();
    lightLine curLine;
    vector < Point > :: iterator  curPoint;
    vector < Point > :: iterator  nextPoint;

    vLine.push_back(createLine(Point(0,0),Point(0,Game::M)));
    vLine.push_back(createLine(Point(Game::N,0),Point(Game::N,Game::M)));

    hLine.push_back(createLine(Point(0,0),Point(Game::N,0)));
    hLine.push_back(createLine(Point(0,Game::M),Point(Game::N,Game::M)));


    for(int i = 0; i < numberOfPlayers; i++)
    {
        if (!playerList[i].alive) continue;
        curPoint = playerList[i].turns.end();
        nextPoint = curPoint-1;
        curLine = createLine(playerList[i].position, (*nextPoint));

        Direction plDir = playerList[i].direction;
        if (fabsf(plDir.dx) <= 0.0001)
        {
            hLine.push_back(createLine(playerList[i].position - Point(0.0f, 0.0f), playerList[i].position + Point(0.35f, 0.0f)));
        } else {
            vLine.push_back(createLine(playerList[i].position - Point(0.0f, 0.0f), playerList[i].position + Point(0.0f, 0.35f)));
        }



        do
        {
            if (fabsf(curLine.begin.x - curLine.end.x ) <= 0.0001)
                vLine.push_back(curLine);
                else hLine.push_back(curLine);

            curPoint--;
            if (nextPoint == playerList[i].turns.begin()) break;
            nextPoint--;
            curLine = createLine((*curPoint) , (*nextPoint) );
        }
        while (curPoint != playerList[i].turns.begin());
    }
  }


//Конструктор главного класса - очищает контейнеры
CLogic :: CLogic()
 {
     hLine.clear();
     vLine.clear();
     uniq.clear();
  //   psychoTypes = new int[numberOfPlayers];
 }

 //Конструктор главного класса - добавляет игроков, их врагов, определяет психотипы
 CLogic :: CLogic(Player *playerList ,int numberOfPlayers)
 {
     hLine.clear();
     vLine.clear();
     uniq.clear();
     psychoTypes = new int[numberOfPlayers];
     enemy = new int[numberOfPlayers];
     findYourEnemy(playerList, numberOfPlayers);
     choosePsychoTypes( playerList, numberOfPlayers);
 }

 void CLogic :: choosePsychoTypes(Player * playerList, int numberOfPlayers)
 {
     for(int i=0; i<numberOfPlayers; i++){
        psychoTypes[i]=0;
     }
 }
