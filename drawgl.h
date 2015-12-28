#ifndef INC_DRAWGL
#define INC_DRAWGL

#include <GL/gl.h>

/* Classe de base pour les elements dessinable avec openGL
*/
class DrawGl{
    
public:
    
    DrawGl(){
        dl_index = 0;
    }
    ~DrawGl(){
        if(dl_index != 0)
            glDeleteLists(dl_index, 1);
    }
    
    GLuint getDlIndex(){return dl_index;}
    
    void draw(){
        if(dl_index != 0)
            glCallList(dl_index);
    }
    
protected:
    
    GLuint dl_index;
    
    void newList(){
        if(dl_index != 0)
            glDeleteLists(dl_index, 1);
        dl_index = glGenLists(1);
    }
    
    void dglSetColor(int r, int g, int b){
        glColor3ub(r, g, b);
    }
    
};

#endif