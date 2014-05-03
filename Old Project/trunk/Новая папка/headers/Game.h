#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "main.h"
#include "player.h"
#include "render.h"

class CLogic;

class Game {
private:
    // время последнего кадра от GLUT
    int lFrameTime;

    // нажаты ли клавиши (только что)
    bool pressedLeft, pressedRight;

    // время последнего кадра от QueryPerformanceCounter
    long long int lTimePC;

    //обратный отсчет до перезапуска игры
    int gameOverCountdown;

    //очищает текущих игроков
    void resetTeams();

    CLogic* botLogic;
public:

    //игра закончилась
    bool gameOver;

    // класс отрисовки
    Render* render;

    // игроки
    vector < Player > players;

    // количествл игроков
    int number_of_players;

    // количество команд
    int number_of_teams;

    // изначальное количество команд
    int s_number_of_teams;

    // массив столкнувшихся
    vector < int > were_crashed;

    // размеры поля
    static const int N = 55;
    static const int M = 55;

    // пустой конструктор
    Game();

    // добавление дового игрока
    void Add_Player(Player new_player);

    // обновление всех игроков
    void Update(type dt);

    // поиск столкновений
    int Find_Crashes(vector < int > &crashed);

    // Отладка
    void On_Crash(int player, int competitor, int mode);

    // удаление игрока
    void Delete_Player(int i);

    // удаление всех, кто сталкивался
    void Delete_Crashed(vector < int > &crashed);

    // выставление кол-ва команд
    int Set_number_of_teams();

    // создание игрока
    Player Get_player(int team, int _ID, bool bot = true);

    // инициализация
    void Init();

    // запуск игры
    void Run();

    // игровой цикл
    void Cycle();

    //перезапуск с теми же параметрами
    void Restart();

    //установка игроков с настройками из консоли
    void ManualSetup();

    // нажатие клавиши
    void OnKey(int key, bool special);

    // деструктор
    ~Game() ;
};

#endif // GAME_H_INCLUDED
