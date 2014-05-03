#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include "main.h"
#include "player.h"

struct PlayerRender
{
    GLuint v_buff, i_buff, c_buff;
    GLuint dv_buff, di_buff, dc_buff;
    int nTris, d_nTris;
    bool alive;
    int team;
    int cmp_trn;
    Point p_lturn, p_end;
    Direction dir;

    PlayerRender();
//  void
};

class Render
{
private:
    vector <PlayerRender> plrs;
    void updPlrBuff(int id, Player* p, bool dyn);
    float resX, resY;
    float cam_x, cam_y, cam_z;
    float cp_x, cp_y, cp_z;
    float up_x, up_y, up_z;
    float fld_x, fld_z;
    float frl_x, frl_z, frl_h;
    bool lPressSwL, lPressSwR;

    void getTeamColor(int tId, float& r, float& g, float& b);
    void setTeamColor(int tId);

    int cView;
    GLuint grid_buff;
    void makeGrid( int sz, float brd );
    bool spectating;
    int c_specId;
    int c_winner, c_countdown;

    void removePlayer(int i);
    void renderPlList();
public:
    Render();
    ~Render();
    void setCountdown(int v);
    void reset();
    void setWinner(int team);
    void control(bool prLeft, bool prRight, bool prUp, bool prDown, bool zoomIn, bool zoomOut,
                  bool switchL, bool switchR);
    void setFieldSize(float x, float z);
    void toggleView();
    void updPlayerState(Player *pl);
    bool initialize(float aResX, float aResY);
    void draw();

};

#endif // RENDER_H_INCLUDED
