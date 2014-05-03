
#include "..\stdafx.h"
#include "..\headers\render.h"

const float wall_thick = 0.125f;
const float wall_h = 0.35f;
const int grid_lines = 300;

PFNGLGENBUFFERSPROC glGenBuffers;
PFNGLBINDBUFFERPROC glBindBuffer;
PFNGLBUFFERDATAPROC glBufferData;
PFNGLDELETEBUFFERSPROC glDeleteBuffers;


PlayerRender::PlayerRender() {
    v_buff = 0;
    i_buff = 0;
    c_buff = 0;
    dv_buff = 0;
    di_buff = 0;
    dc_buff = 0;

}


Render* g_render;

void r_display(void) {
    g_render->draw();
}

Render::Render() {
    cam_x = 0;  frl_x = 10.0f;
    cam_y = 0;  frl_z = 10.0f;
    cam_z = 0;  frl_h = 10.0f;
    cp_x = 0;
    cp_y = 0;
    cp_z = 0;
    up_x = 0;
    up_y = 0;
    up_z = 0;
    cView = 0;
    spectating = false;
    c_specId = 0;
}

Render::~Render() {
    cam_x = 0;
    cam_y = 0;
    cam_z = 0;
    cp_x = 0;
    cp_y = 0;
    cp_z = 0;
    up_x = 0;
    up_y = 0;
    up_z = 0;
    cView = 0;
}

void Render::makeGrid( int sz, float brd ) {
    glGenBuffers(1, &grid_buff);

    float * vBuff = new float[3 * sz * 6];
    const float g_size = 1.0f;
    fori(cx, sz) {
        *(vBuff++) = cx * g_size - brd;
        *(vBuff++) = 0;
        *(vBuff++) = 0;

        *(vBuff++) = cx * g_size - brd;
        *(vBuff++) = 0;
        *(vBuff++) = sz * g_size;

        *(vBuff++) = cx * g_size + brd;
        *(vBuff++) = 0;
        *(vBuff++) = sz * g_size;

        *(vBuff++) = cx * g_size - brd;
        *(vBuff++) = 0;
        *(vBuff++) = 0;

        *(vBuff++) = cx * g_size + brd;
        *(vBuff++) = 0;
        *(vBuff++) = sz * g_size;

        *(vBuff++) = cx * g_size + brd;
        *(vBuff++) = 0;
        *(vBuff++) = 0;
    }
    vBuff -= sz * 18;

    glBindBuffer(GL_ARRAY_BUFFER, grid_buff);
    glBufferData(GL_ARRAY_BUFFER, 18 * sz * sizeof(float), vBuff, GL_STATIC_DRAW);

    delete vBuff;
}

bool makeBox(const Point &f, const Point &t, float w, float ys, float * trg, int* trgi, int & o_nv, int & o_ni, int iOff) {
    Point dr = t - f;
    if (!dr.normalize()) return false;
    Point sh(dr.y * 0.5f * w, -dr.x * 0.5f * w);

    for (int dx = 0; dx < 2; dx++) {
        for (int dy = 0; dy < 2; dy++) {
            for (int dz = 0; dz < 2; dz++) {
                float fx = dx ? t.x : f.x;
                float fz = dx ? t.y : f.y;

                *(trg++) = dz ? fx + sh.x : fx - sh.x;
                *(trg++) = dy ? ys : 0;
                *(trg++) = dz ? fz + sh.y : fz - sh.y;
            }
        }
    }
    //  0   1   2   3   4   5   6   7
    // --- --+ -+- -++ +-- +-+ ++- +++
    #define mk_quad(v1, v2, v3, v4) *(trgi++) = v1+iOff; *(trgi++) = v2+iOff; *(trgi++) = v3+iOff; *(trgi++) = v1+iOff; *(trgi++) = v3+iOff; *(trgi++) = v4+iOff;

    mk_quad(0,1,3,2);   //YZ l , XY l
    mk_quad(0,2,6,4);

    mk_quad(0,4,5,1);   //XZ l , XZ h
    mk_quad(2,3,7,6);

    mk_quad(4,6,7,5);   //YZ h , XY h
    mk_quad(1,5,7,3);

    o_nv = 8;
    o_ni = 36;
    #undef mk_quad
    return true;
}

void Render::toggleView() {
    cView++;
    if (cView >= 3) cView = 0;
}

void Render::updPlrBuff(int id, Player* p, bool dyn) {

    int nb = 1;
    GLuint * t_vb, *t_ib, *t_cb;

    if (!dyn) {
        if (p->turns.size() <= 1)
            return;
        nb = int(p->turns.size() - 1);
        t_vb = &plrs[id].v_buff;
        t_ib = &plrs[id].i_buff;
        t_cb = &plrs[id].c_buff;
    } else {
        t_vb = &plrs[id].dv_buff;
        t_ib = &plrs[id].di_buff;
        t_cb = &plrs[id].dc_buff;
    }

    if (*t_vb)
    {
        GLuint arr[3];
        arr[0] = *t_vb;
        arr[1] = *t_ib;
        arr[2] = *t_cb;
        glDeleteBuffers(3, arr);
        *t_vb = 0;
        *t_ib = 0;
        *t_cb = 0;
    }


    float* vbData = new float[nb * 8 * 3];
    int* ibData = new int [nb * 36];
    float* clData = new float [nb * 8 * 3];


    int tot_v = 0;
    int tot_i = 0;
    if (!dyn) {
        forvec (Point, p->turns, i) {
            if (i + 1 == p->turns.end())
                break;
            Point np = *(i+1);

            int nv, ni;
            if (makeBox(*i, np, wall_thick, wall_h, vbData, ibData, nv, ni, tot_v)) {
                vbData += nv * 3;
                fori(k, nv) {
                    (*clData++) = 0.0f;
                    (*clData++) = 1.0f;
                    (*clData++) = 0.0f;
                }
                ibData += ni;

                tot_v += nv;
                tot_i += ni;
            }
        }
    } else {
        int nv, ni;
        if (makeBox(p->turns.back(), p->position, wall_thick, wall_h, vbData, ibData, nv, ni, tot_v)) {
            vbData += nv * 3;
            fori(k, nv) {
                (*clData++) = 0.0f;
                (*clData++) = 1.0f;
                (*clData++) = 0.0f;
            }
            ibData += ni;

            tot_v += nv;
            tot_i += ni;
        }
    }
    vbData -= 3 * tot_v;
    ibData -= tot_i;
    clData -= 3 * tot_v;

    if (tot_v) {
        glGenBuffers(1, t_vb);
        glGenBuffers(1, t_ib);
        glGenBuffers(1, t_cb);

        glBindBuffer(GL_ARRAY_BUFFER, *t_vb);
        glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float) * tot_v, vbData, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, *t_cb);
        glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float) * tot_v, clData, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *t_ib);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * tot_i, ibData, GL_STATIC_DRAW);

        fori(i, tot_i) {
         //   printf("%.4f %.4f %.4f\n", vbData[3*ibData[i]], vbData[3*ibData[i]+1], vbData[3*ibData[i]+2]);
        }


        if (dyn) {
            plrs[id].d_nTris = tot_i / 3;
        } else {
            plrs[id].nTris = tot_i / 3;
        }
    }
    delete vbData;
    delete ibData;
    delete clData;
    return;
}

void Render::control(bool prLeft, bool prRight, bool prUp, bool prDown, bool zoomIn, bool zoomOut,
                  bool switchL, bool switchR)
{
    float ncam_x = cam_x, ncam_y = cam_y, ncam_z = cam_z,
        ncp_x = cp_x, ncp_y = cp_y, ncp_z = cp_z;

    if (spectating)
    {
        if (switchL)
        {
            if (c_specId < 0)
            {
                c_specId = int(plrs.size())  - 1;
            } else {
                c_specId--;
            }
            while (c_specId >= 0 && !plrs[c_specId].alive) c_specId--;
        }
        if (switchR)
        {
            c_specId++;
            while (c_specId < int(plrs.size()) && !plrs[c_specId].alive) c_specId++;
            if (c_specId == int(plrs.size())) c_specId = -1;
        }
    }
    if (cView == 2 || c_specId < 0)
    {
        if (zoomIn) frl_h -= 1.0f;
        if (zoomOut) frl_h += 1.0f;
        if (frl_h < 6.0f) frl_h = 6.0f;
        if (frl_h > 60.0f) frl_h = 60.0f;
    }

    if (c_specId >= 0)
    {
        if (spectating)
        {
            if (!plrs[c_specId].alive)
            {
                c_specId = -1;
            }
        }
        if (plrs[c_specId].alive)
        {
            ncp_x = plrs[c_specId].p_end.x;
            ncp_z = plrs[c_specId].p_end.y;
            ncp_y = 0;

            up_x = 0;
            up_y = 1;
            up_z = 0;
            if (cView == 0) {
                ncam_x = plrs[c_specId].p_end.x - plrs[c_specId].dir.dx * 3;
                ncam_z = plrs[c_specId].p_end.y - plrs[c_specId].dir.dy * 3;
                ncam_y = 2;
            } else if (cView == 1) {
                ncam_x = plrs[c_specId].p_end.x - plrs[c_specId].dir.dx * 8;
                ncam_z = plrs[c_specId].p_end.y - plrs[c_specId].dir.dy * 8;
                ncam_y = 6;
            } else if (cView == 2) {
                //up_x = plrs[c_specId].dir.dx;
               // up_y = 0;
               // up_z = plrs[c_specId].dir.dy;

                ncam_x = plrs[c_specId].p_end.x;
                ncam_z = plrs[c_specId].p_end.y;
                ncam_y = frl_h;
            } else assert(false);
        } else {
            if (spectating) c_specId = -1;
        }
    } else {
        float mv_speed = frl_h / 20.0f; ;
        if (prUp) frl_x += mv_speed;
        if (prDown) frl_x -= mv_speed;
        if (prLeft) frl_z -= mv_speed;
        if (prRight) frl_z += mv_speed;

        if (frl_x < 0.0f) frl_x = 0.0f;
        if (frl_z < 0.0f) frl_z = 0.0f;
        if (frl_x > fld_x) frl_x = fld_x;
        if (frl_z > fld_z) frl_z = fld_z;

        ncam_x = frl_x;
        ncam_z = frl_z;
        ncp_x = frl_x;
        ncp_z = frl_z;
        ncam_y = frl_h;

        cam_x = ncam_x;
        cam_z = ncam_z;
        ncp_y = 0.0f;
        up_x = 1;
        up_y = 0;
        up_z = 0;
    }
    float a = 1;
    cp_x = ncp_x * a + (1-a) * cp_x;
    cp_y = ncp_y * a + (1-a) * cp_y;
    cp_z = ncp_z * a + (1-a) * cp_z;

    a = 0.07f;
    cam_x = ncam_x * a + (1-a) * cam_x;
    cam_y = ncam_y * a + (1-a) * cam_y;
    cam_z = ncam_z * a + (1-a) * cam_z;
}

void Render::updPlayerState(Player* pl) {
    int id = pl->ID;
    assert(id >= 0 && id < 256);
    if (int(plrs.size()) <= id)
        plrs.resize(id + 1);

    plrs[id].team = pl->team;
    plrs[id].alive = pl->alive;

    if (!pl->alive) {
        if (id == 0)
        {
            spectating = true;
        }
        if (plrs[id].v_buff || plrs[id].dv_buff){
            GLuint arr[6];
            arr[0] = plrs[id].v_buff;
            arr[1] = plrs[id].i_buff;
            arr[2] = plrs[id].c_buff;
            arr[3] = plrs[id].dv_buff;
            arr[4] = plrs[id].di_buff;
            arr[5] = plrs[id].dc_buff;
            glDeleteBuffers(6, arr);
            plrs[id].v_buff = 0;
            plrs[id].i_buff = 0;
            plrs[id].c_buff = 0;
            plrs[id].dv_buff = 0;
            plrs[id].di_buff = 0;
            plrs[id].dc_buff = 0;
        }
        return;
    }

    if (!pl->turns.size())
        return;

    if (plrs[id].cmp_trn != int(pl->turns.size())) {
        updPlrBuff(id, pl, false);
        plrs[id].cmp_trn = int(pl->turns.size());
    }
    plrs[id].p_lturn = pl->turns.back();
    plrs[id].p_end = pl->position;
    plrs[id].dir = pl->direction;
    updPlrBuff(id, pl, true);
}

bool Render::initialize() {
    ///int argc = 0;

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Tron");
    glutDisplayFunc(r_display);
    g_render = this;

    glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
    glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
    glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
    glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");

    printf("OpenGL vendor string: %s\n", glGetString(GL_VENDOR));
    printf("OpenGL renderer string: %s\n", glGetString(GL_RENDERER));
    printf("OpenGL version string: %s\n", glGetString(GL_VERSION));

    assert(glBindBuffer && glGenBuffers && glBufferData && glDeleteBuffers);


    makeGrid( grid_lines, 0.05f);
    return true;
}

void Render::setFieldSize(float x, float z) {
    fld_x = x;
    fld_z = z;
}
void Render::draw() {
   glShadeModel(GL_SMOOTH);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_CULL_FACE);

   // glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glDepthFunc(GL_LEQUAL);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glViewport(0, 0, (GLsizei)800, (GLsizei)600);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, 4.0f/3.0f, 0.1f, 400.0f);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();




    gluLookAt(cam_x,cam_y, cam_z, cp_x, cp_y, cp_z, up_x, up_y, up_z);

    glColor4f(0.0f, 0.0f, 0.6f, 0.0f);

    glPushMatrix();
    glTranslatef(0.0f, 0.5f, fld_z * 0.5f);
    glScalef(0.1f, 1.0f, fld_z);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(fld_x, 0.5f, fld_z * 0.5f);
    glScalef(0.1f, 1.0f, fld_z);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(fld_x * 0.5f, 0.5f, 0.0f);
    glScalef(fld_x, 1.0f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(fld_x * 0.5f, 0.5f, fld_z);
    glScalef(fld_x, 1.0f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glEnableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_INDEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glPolygonMode( GL_FRONT_AND_BACK, GL_FLAT );

    float gr_lx = floorf(cp_x - grid_lines * 0.5f);
    float gr_lz = floorf(cp_z - grid_lines * 0.5f);

    glColor4f(0.0, 0.0, 0.7, 1.0);
    glBindBuffer(GL_ARRAY_BUFFER, grid_buff);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glTranslatef(gr_lx, cp_y, gr_lz);
    glDrawArrays(GL_TRIANGLES, 0, 6 * grid_lines);
    glTranslatef(-gr_lx, -cp_y, -gr_lz);

    glPushMatrix();
    glTranslatef(gr_lx, cp_y, gr_lz + grid_lines);
    glRotatef(90.0f, 0, 1, 0);
    glDrawArrays(GL_TRIANGLES, 0, 6 * grid_lines);
    glPopMatrix();

    glEnableClientState(GL_INDEX_ARRAY);
    forvec(PlayerRender, plrs, i) {
        if (i->team == 1)
        {
            glColor4f(1.0, 0.5, 0.0, 1.0);
        } else if (i->team == 2 )
        {
            glColor4f(0.0, 0.5, 1.0, 1.0);
        } else if (i->team == 3 )
        {
            glColor4f(0.0, 0.7, 0.0, 1.0);
        } else if (i->team == 4 )
        {
            glColor4f(0.85f, 0.0, 0.0, 1.0);
        }
        if (i->v_buff) {
            glBindBuffer(GL_ARRAY_BUFFER, i->v_buff);
            glVertexPointer(3, GL_FLOAT, 0, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i->i_buff);

            glDrawElements(GL_TRIANGLES, i->nTris*3,  GL_UNSIGNED_INT, 0);
           // glDrawArrays(GL_TRIANGLES, 0, i->nTris);
        }
        if (i->dv_buff) {
            //glBindBuffer(GL_ARRAY_BUFFER_ARB, i->dc_buff);
            //glColorPointer(3, GL_FLOAT, 0, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i->di_buff);
            //glIndexPointer(GL_UNSIGNED_INT, 0, 0);
            glBindBuffer(GL_ARRAY_BUFFER, i->dv_buff);
            glVertexPointer(3, GL_FLOAT, 0, 0);
            glDrawElements(GL_TRIANGLES, i->d_nTris*3,  GL_UNSIGNED_INT, 0);
        }
    }

    //glFlush();
    glutSwapBuffers();
}
