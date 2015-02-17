#include "graph.h"
#include <iostream>
#include "Constant.h"
#include "grid.h"
#include "random.h"
#include "display.h"
#include <cmath>
using namespace std;

Graph::Graph(QWidget *parent):QGLWidget(parent)
{
    time=new QTimer(this);
    connect(time, SIGNAL(timeout()), this, SLOT(update()));
    time->start(10);
}
void Graph::draw(int xy)
{
    g.snapShot();
    char **temp=g.GetSnap();

    for(int i = 0; i < xy; i++)
    {
        for(int j = 0; j < xy; j++)
        {
            if(temp[j][i]=='.')
                glColor3f(0.0f, 0.2f, 0.5f);
            if(temp[j][i]=='X')
                glColor3f(1.0f, 0.0f, 0.0f);
            if(temp[j][i]=='o')
                glColor3f(0.5f, 1.0f, 1.0f);
            if(temp[j][i]=='B')
                glColor3f(1.0f, 0.5f, 0.0f);
            if(temp[j][i]=='T')
                glColor3f(0.0f, 0.5f, 0.5f);

            glVertex2f(     i*xy,    j*xy); // BOTTOM LEFT
            glVertex2f((i+1)*xy ,    j*xy); // BOTTOM RIGHT
            glVertex2f((i+1)*xy ,(j+1)*xy); // TOP RIGHT
            glVertex2f(     i*xy,(j+1)*xy); // TOP LEFT
        }
    }
}

void Graph::initializeGL()
{
    glClearColor(0,0,0,0);
}

void Graph::resizeGL(int w, int h)
{
    double Aspect;
    if(h==0)
        h=1;

    glViewport(0,0, w, h);
    Aspect=(double)w/(double)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Graph::paintGL()
{
    double xy = MAXX;

    g.Move();
    g.Breed();
    g.Armor();
    g.Die();
    g.Boom();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glOrtho(0, xy*xy, 0, xy*xy, -1.0, 1.0);

    glBegin(GL_QUADS);
    draw(xy);
    glEnd();
}
