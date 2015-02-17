#ifndef GRAPH_H
#define GRAPH_H
/*this class uses OPenGL to graph the board with colors, creatures are represented as squares*/

#include "grid.h"
#include <QGLWidget>
#include <QTimer>
class Graph : public QGLWidget
{
public:
    Graph(QWidget *parent = 0);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    void draw(int xy); //different creatures are given different colors.
    Grid g;
    QTimer *time;

};

#endif // GRAPH_H
