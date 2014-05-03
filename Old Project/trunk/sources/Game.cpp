#include "..\stdafx.h"
#include "..\Headers\Game.h"
#include "..\Headers\Bot_logic.h"

Game* g_game;

void g_specialKeyPress(int key, int x, int y) {
    if (g_game) g_game->OnKey(key, true);
}

void g_keyPress(unsigned char key, int x, int y) {
    if (g_game) g_game->OnKey(key, false);
}

void g_cycle(void) {
    g_game->Cycle();
}

// пустой конструктор
Game::Game() {
    number_of_players = 0;
    players.clear();
    were_crashed.clear();
    pressedLeft = false;
    pressedRight = false;
    botLogic = NULL;
    QueryPerformanceCounter((PLARGE_INTEGER) &lTimePC);
}

// добавление дового игрока
void Game::Add_Player(Player new_player) {
    number_of_players++;
    players.push_back(new_player);
    return;
}

//нажатие клавиши
void Game::OnKey(int key, bool special) {
    if (special && key == GLUT_KEY_LEFT) {
        players[0].Turn_Right();
    } else if (special &&  key == GLUT_KEY_RIGHT) {
        players[0].Turn_Left();
    } else if (!special &&  (key == 'V' || key == 'v' || key == 236)) { //236 - small russian m x_x
        render->toggleView();
    } else if (!special && key == 0x1B) { //escape key
        ExitProcess(0);
    }
    return;
}

//игровой цикл
void Game::Cycle() {
    /*
    variable framestep, using GLUT time counter. i didn't like the results.
    int nFrameTime = glutGet(GLUT_ELAPSED_TIME);

    float dt = float(nFrameTime - lFrameTime) / 1000;

    if (dt == 0) {
        Sleep(0);
        return;
    }
    lFrameTime = nFrameTime;
    */

    //platform - specific fixed framestep using performance counter

    long long int pFreq, cTime;
    QueryPerformanceFrequency((PLARGE_INTEGER) (&pFreq));
    QueryPerformanceCounter((PLARGE_INTEGER) (&cTime));
    while ((cTime - lTimePC) < (pFreq / 60)) {
        Sleep(0);
        QueryPerformanceCounter((PLARGE_INTEGER) (&cTime));
    }

    lTimePC = cTime;

    if (!gameOver)
    {
        float dt = 1.0f / 60.0f;

        if (gameStartCountdown <= 0 || gameStartCountdown >= 177) {
            if (gameStartCountdown > 0) gameStartCountdown--;

            vector<int> bot_turns = botLogic->updateTurn(&players[0], number_of_players);

            forvec(int, bot_turns, i)
            {
                int j = i-bot_turns.begin();
                if (!players[j].is_bot) continue;
                if (*i == TURN_LEFT) players[j].Turn_Left();
                if (*i == TURN_RIGHT) players[j].Turn_Right();
            }

            Update(dt);
            Find_Crashes(were_crashed);
            Delete_Crashed(were_crashed);

            number_of_teams = Set_number_of_teams();
            if (number_of_teams <= 1) {
                int winner_team = -2;
                forvec(Player, players, i)
                    if (i->alive) {
                        cout << "Team " << i->team << " won!" << endl;
                        winner_team = i->team;
                        break;
                    }
                gameOver = true;
                gameOverCountdown = 60*2;
                render->setWinner(winner_team);
            }
        } else {
            gameStartCountdown--;
        }
        render->setCountdown(gameStartCountdown);

     //   bool hasAlive = false;
        forvec(Player, players, i) {
            render->updPlayerState(&(*i));
       //     if ( i->alive ) hasAlive = true;
        }
        //if (!hasAlive) ExitProcess(0);


        bool prLeft = (GetKeyState(VK_LEFT) & 0x8000) != 0;
        bool prRight = (GetKeyState(VK_RIGHT) & 0x8000) != 0;
        bool prUp = (GetKeyState(VK_UP) & 0x8000) != 0;
        bool prDown = (GetKeyState(VK_DOWN) & 0x8000) != 0;
        bool swL = (GetKeyState('Q') & 0x8000) != 0;
        bool swR = (GetKeyState('W') & 0x8000) != 0;
        bool zIn = (GetKeyState('E') & 0x8000) != 0;
        bool zOut = (GetKeyState('D') & 0x8000) != 0;
        render->control(prLeft, prRight, prUp, prDown, zIn, zOut, swL, swR);
    } else {
        if (gameOverCountdown-- <= 0) Restart();
    }
   // Player testPl(Point(1, 1), Direction(1, 0), 0, 1);
   // testPl.turns.push_back(Point(-5, -5));
   // testPl.turns.push_back(Point(0, -5));
   // render->updPlayerState(&testPl);

   // render->draw();

   glutPostRedisplay();
   return;
}

// обновление всех игроков
void Game::Update(type dt) {
    for (int player_number = 0; player_number < number_of_players; player_number++)
        players[player_number].Update(dt);
    return;
}

// поиск столкновений
int Game::Find_Crashes(vector < int > &crashed) {
    crashed.clear();
    int number_of_crashes = 0;
    number_of_players = players.size();
    Point t;

    for (int player_number = 0; player_number < number_of_players; player_number++) {
        if (!players[player_number].alive)
            continue;
        for (int turn_number = 0; turn_number < int(players[player_number].turns.size()) - 2; turn_number++)
            if (cross_segment(players[player_number].position,
                              players[player_number].turns[players[player_number].turns.size() - 1],
                              players[player_number].turns[turn_number],
                              players[player_number].turns[turn_number + 1], t)) {
                assert(t.x != -100 && t.y != -100);
                crashed.push_back(player_number);
                number_of_crashes++;
                cerr << "Player: " << players[player_number].ID << " - self-crashed" << endl;
                players[player_number].alive = false;
                break;
            }

        if (!players[player_number].alive)
            continue;
        if (players[player_number].position.x >= N || players[player_number].position.y >= M ||
            players[player_number].position.x <= 0 || players[player_number].position.y <= 0) {
            crashed.push_back(player_number);
            number_of_crashes++;
            cerr << "Player: " << players[player_number].ID << " - out of board" << endl;
            players[player_number].alive = false;
        }

        if (!players[player_number].alive)
            continue;
        for (int competitor_number = 0; competitor_number < number_of_players; competitor_number++)
            if (competitor_number != player_number && players[competitor_number].alive) {
                if (cross_segment(players[player_number].position,
                                  players[player_number].turns[players[player_number].turns.size() - 1],
                                  players[competitor_number].position,
                                  players[competitor_number].turns[players[competitor_number].turns.size() - 1], t) &&
                    dist(players[player_number].position, t) < Sur) {
                        assert(t.x != -100 && t.y != -100);
                        crashed.push_back(player_number);
                        number_of_crashes++;
                        cerr << "Player: " << players[player_number].ID <<  " - crashed-in-track of: " << players[competitor_number].ID << endl;
                        On_Crash(player_number, competitor_number, 1);
                        break;
                    }

                for (int turn_number = 0; turn_number < int(players[competitor_number].turns.size()) - 1; turn_number++)
                        if (cross_segment(players[player_number].position,
                                          players[player_number].turns[players[player_number].turns.size() - 1],
                                          players[competitor_number].turns[turn_number],
                                          players[competitor_number].turns[turn_number + 1], t)) {
                            assert(t.x != -100 && t.y != -100);
                            crashed.push_back(player_number);
                            number_of_crashes++;
                            On_Crash(player_number, competitor_number, 0);
                            cerr << "Player: " << players[player_number].ID << " - crashed-in-tail of: " << players[competitor_number].ID << endl;
                            players[player_number].alive = false;
                            break;
                        }
            }
    }

    return number_of_crashes;
}

// удаление игрока
void Game::Delete_Player(int i) {
    number_of_players--;
    players.erase(players.begin() + i);
    return;
}

// удаление всех, кто сталкивался
void Game::Delete_Crashed(vector < int > &crashed) {
//    cerr << "in function - " << crashed.size() << endl;
    for (int current_number = int(crashed.size()) - 1; current_number >= 0; current_number--) {
//        cerr << "deleting crashed "; // why it starts?!?! WTF?!
//        cerr << current_number << " " << crashed[current_number] << endl;
//        Delete_Player(crashed[current_number]);
        players[crashed[current_number]].alive = false;
    }
    crashed.clear();
    return;
}

// выставление кол-ва команд
int Game::Set_number_of_teams() {
    number_of_players = (int) players.size();
    set < int > teams;
    teams.clear();
    for (int current_player_number = 0; current_player_number < number_of_players; current_player_number++)
        if (players[current_player_number].alive)
            teams.insert(players[current_player_number].team);
    return teams.size();
}

// создание игрока
Player Game::Get_player(int team, int _ID, bool bot) {
    Point temp_position;
    Direction temp_dir;
    temp_position.x = rand() % (N - 10) + 10;
    temp_position.y = rand() % (N - 10) + 10;
    int dir = rand() % 4;
    if (dir == 0)
        temp_dir.dx = 1;
    if (dir == 1)
        temp_dir.dx = -1;
    if (dir == 2)
        temp_dir.dy = 1;
    if (dir == 3)
        temp_dir.dy = -1;
    Player new_player(temp_position, temp_dir, team, _ID, bot);
    return new_player;
}

void Game::resetTeams()
{
    players.clear();
    gameOver = false;
    number_of_players = 0;
}

//установка игроков с настройками из консоли
void Game::ManualSetup() {
    resetTeams();

    cout << "Enter teams ammount: ";
    cin >> number_of_teams;
    s_number_of_teams = number_of_teams;

    for (int i = 1; i <= number_of_teams; i++) {
        int number_of_players_in_team = 0;
        cout << "Enter the ammount of players in team " << i << ": ";
        cin >> number_of_players_in_team;
        for (int j = 0; j < number_of_players_in_team; j++) {
            Player new_player = Get_player(i, (int) players.size());
            Add_Player(new_player);
            cerr << "Player " << (int) players.size() << ", position (" << new_player.position.x << ", " << new_player.position.y << ")" << endl;
        }
    }
    players[0].is_bot = false;

    gameStartCountdown = 3*60;

    delete botLogic;
    botLogic = new CLogic(&players[0], number_of_players);
}

void Game::Restart() {
    vector<int> team_size;

    forvec(Player, players, i)
    {
        int t = i->team;
        if (t >= int(team_size.size())) team_size.resize(t+1, 0);
        team_size[t]++;
    }

    resetTeams();
    number_of_teams = s_number_of_teams;

    for (int i = 1; i <= number_of_teams; i++) {
        int number_of_players_in_team = team_size[i];
        for (int j = 0; j < number_of_players_in_team; j++) {
            Player new_player = Get_player(i, (int) players.size());
            Add_Player(new_player);
        }
    }
    players[0].is_bot = false;

    delete botLogic;
    botLogic = new CLogic(&players[0], number_of_players);

    Set_number_of_teams();
    gameStartCountdown = 3*60;
    render->reset();
}

// инициализация
void Game::Init() {
    srand(time(NULL));


    ManualSetup();
    Set_number_of_teams();

    render = new Render();
    render->initialize(800, 600);
    render->setFieldSize(N, M);

    render->reset();
    lFrameTime = glutGet(GLUT_ELAPSED_TIME);
    g_game = this;
    glutIdleFunc(&g_cycle);
    glutSpecialFunc(&g_specialKeyPress);
    glutKeyboardFunc(&g_keyPress);
    return;
}

// запуск игры
void Game::Run() {

    Init();
    glutMainLoop();
/*
    while (number_of_teams > 1) {
        cout << "New Round" << endl;
        Set_number_of_teams();
    }*/
    return;
}

// Отладка
void Game::On_Crash(int player, int competitor, int mode) {
    if (players[player].ID == 0 && mode == 1) {
        cerr << "Player crashed in " << players[competitor].ID << endl;
        cerr << "Player position - " << players[player].position.x << ", " << players[player].position.y << endl;
        cerr << "Last turn position - " << players[player].turns[players[player].turns.size() - 1].x << ", " << players[player].turns[players[player].turns.size() - 1].y << endl;
        cerr << "Competitor position - " << players[competitor].position.x << ", " << players[competitor].position.y << endl;
        cerr << "Competitor last turn position - " << players[competitor].turns[players[competitor].turns.size() - 1].x << ", " << players[competitor].turns[players[competitor].turns.size() - 1].y << endl;
        if (intersect(players[player].position, players[player].turns[players[player].turns.size() - 1],
                    players[competitor].position, players[competitor].turns[players[competitor].turns.size() - 1]))
            cerr << "Well..." << endl;
        else
            cerr << "Fuck!!!" << endl;
    }
    return;
}

// деструктор
Game::~Game() {
    number_of_players = 0;
    players.clear();
    were_crashed.clear();
}
