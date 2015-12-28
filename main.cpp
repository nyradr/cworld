#include <iostream>

#include <SDL/SDL.h>
#include <GL/glut.h>

#include "map/map.h"
#include "map/Planet.h"

#include "freeFlyCam.h"
#include "crea/crea.h"

using namespace std;

#define ECRX 1500
#define ECRY 900

#define SX 100
#define SY 100
#define MAX 30

SDL_Surface *init() {
    SDL_WM_SetCaption("SDL GL Application", NULL);
    SDL_Surface *sur = SDL_SetVideoMode(ECRX, ECRY, 32, SDL_OPENGL);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70, (double)ECRX / ECRY, 1, 1000);
    glEnable(GL_DEPTH_TEST);

    return sur;
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface *scr = init();

    Map *map = new Map(SX, SX, 0, MAX);
    map->generate();
    
    Crea crea = Crea(map);
    crea.spawn();
    
    Planet *pl = new Planet(50, 30, 30);
    pl->generate();
    

    FreeFlyCam *cam = new FreeFlyCam(Vector3<double>(0, 0, 0));

    gluLookAt(SX / 2, SY / 2, SX, SX / 2, SY / 2, 0, 0, 1, 0);

    GLuint ltime = SDL_GetTicks();

    bool ctn = true;
    SDL_Event event;
    while (ctn) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                ctn = false;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    ctn = false;
                    break;

                case SDLK_a:
                    pl->generate();
                    break;
                    
                case SDLK_m:
                    crea.move(rand() % 4);
                    break;

                default:
                    cam->OnKeyboard(event.key);
                    break;
                }
                break;

            case SDL_KEYUP:
                cam->OnKeyboard(event.key);
                break;

            case SDL_MOUSEMOTION:
                cam->OnMouseMotion(event.motion);
                break;

            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEBUTTONDOWN:
                cam->OnMouseButton(event.button);
            }
        }
        GLuint ctime = SDL_GetTicks();
        GLuint elapsed = ctime - ltime;
        ltime = ctime;

        cam->animate(elapsed);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        cam->look();
        
        pl->draw();
        
        //map->draw();
        //crea.draw();

        glFlush();
        SDL_GL_SwapBuffers();
    }
    
    delete pl;
    delete cam;
    delete map;
    SDL_Quit();

    return 0;
}
