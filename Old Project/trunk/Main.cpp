#include "stdafx.h"
#include "Player.h"

using namespace std;

// игра
class Game {
public:
    // игроки
    vector < Player > players;

    // количествл игроков
    int number_of_players;

    // количество команд
    int number_of_teams;

    // пустой конструктор
    Game() {
        number_of_players = 0;
        players.clear();
    }

    // добавление дового игрока
    void Add_Player(Player new_player) {
        number_of_players++;
        players.push_back(new_player);
        return;
    }

    // обновление всех игроков
    void Update(int dt) {
        for (size_t player_number = 0; player_number < number_of_players; player_number++)
            players[player_number].Update(dt);
        return;
    }

    // поиск столкновений
    int Find_Crashes(vector < int > &crashed) {
        int number_of_crashes = 0;
        for (size_t player_number = 0; player_number < number_of_players; player_number++)
            for (size_t competitor_numer = 0; competitor_numer < number_of_players; competitor_numer++)
                if (competitor_numer != player_number) {
                    if (intersect(players[player_number].position,
                                  players[player_number].turns[players[player_number].turns.size() - 1],
                                  players[competitor_numer].position,
                                  players[competitor_numer].turns[players[player_number].turns.size() - 1])) {
                        crashed.push_back(player_number);
                        number_of_crashes++;
                        break;
                    }
                    for (size_t turn_number = 0; turn_number < players[competitor_numer].turns.size() - 1; turn_number++)
                            if (intersect(players[player_number].position,
                                          players[player_number].turns[players[player_number].turns.size() - 1],
                                          players[competitor_numer].turns[turn_number],
                                          players[competitor_numer].turns[turn_number + 1])) {
                                crashed.push_back(player_number);
                                number_of_crashes++;
                                break;
                            }
                }
        return number_of_crashes;
    }

    // удаление игрока
    void Delete_Player(int i) {
        number_of_players--;
        players.erase(players.begin() + i);
        return;
    }

    // выставление кол-ва команд
    int Set_number_of_teams() {
        set < int > teams;
        teams.clear();
        for (size_t current_player_number = 0; current_player_number < number_of_players; current_player_number++)
            teams.insert(players[current_player_number].team);
        return teams.size();
    }

    // создание игрока
    Player Get_player() {

    }

    // инициализация
    void Init() {

        Set_number_of_teams();
    }

    // запуск игры
    void Run() {
        Init();

        while (number_of_teams > 1) {

            Set_number_of_teams();
        }
    }

    // деструктор
    ~Game() {
        number_of_players = 0;
        players.clear();
    }
};

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Tron");
    glutDisplayFunc(display);
    glutMainLoop();
}
