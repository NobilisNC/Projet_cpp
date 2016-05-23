#include "renderarea.h"

#include <cmath>




float RATIO = 5;
int NB_TAB = 3;
float TAB[] = { .2f, .25f, .5f, 1.f };



RenderArea::RenderArea(QWidget *parent) : QWidget(parent),
    pen(nullptr),
    center(500, 300),
    pix_unite(100,100),
    unite(1.f , 1.f),
    base(1.f , 1.f),
    current_tab(3,3),
    drag(false),
    old_cursor(-1,-1)
{
    setBackgroundRole(QPalette::Base);
    setFixedSize(QSize(1000,600));
    setAutoFillBackground(true);
    setCursor(Qt::CrossCursor);
    setMouseTracking(true);

}

RenderArea::~RenderArea()
{
    delete pen;
}


void RenderArea::wheelEvent(QWheelEvent *event)
{
    float delta = float(event->angleDelta().y())/380.f;
    QPoint new_UNITE = QPoint(int(pix_unite.x() + delta *  RATIO), int(pix_unite.y() + delta * RATIO));

    if ( new_UNITE.x()  < 50 ) { // DEZOOM

        if (current_tab.x() == NB_TAB ) {
            base.setX(base.x() * 10);
            current_tab.setX(0);
        } else {
            current_tab.setX(current_tab.x()+1);
        }
        pix_unite.setX(    pix_unite.x() + 1.5f * pix_unite.x()  );
        unite.setX( base.x() * TAB[current_tab.x()] );
    } else if ( new_UNITE.x()  > 150 ) { //ZOOM

        if (current_tab.x() == 0 ) {
            base.setX(base.x() / 10);
            current_tab.setX(NB_TAB);
        } else {
            current_tab.setX(current_tab.x() - 1);
        }


        pix_unite.setX(    pix_unite.x() - .5f * pix_unite.x()  );
        unite.setX( base.x() * TAB[current_tab.x()] );
    } else if (new_UNITE.y()  > 150 ) { // ZOOM

        if (current_tab.y() == 0 ) {
            base.setY( base.y() / 10);
            current_tab.setY(NB_TAB);
        } else {
            current_tab.setY( current_tab.y() -1);
        }

        pix_unite.setY(    pix_unite.y() - .5f * pix_unite.y()  );
        unite.setY( base.y() * TAB[current_tab.y()] );
    } else if(new_UNITE.y()  < 50 ) { //DEZOOM

        if (current_tab.y() == NB_TAB ) {
            base.setY( base.y() * 10);
            current_tab.setY(0);
        } else {
            current_tab.setY(current_tab.y() + 1);
        }


        pix_unite.setY(    pix_unite.y() + 1.5f * pix_unite.y()  );
        unite.setY(base.y() * TAB[current_tab.y()] );
    } else {
        pix_unite.setX(    pix_unite.x() + delta *  RATIO  );
        pix_unite.setY(    pix_unite.y() + delta *  RATIO  );
    }



    repaint();
}

void RenderArea::mousePressEvent(QMouseEvent * )
{
    drag = true;
    setCursor(Qt::ClosedHandCursor);

}

void RenderArea::mouseReleaseEvent(QMouseEvent *)
{
    drag = false;
    setCursor(Qt::CrossCursor);

}

void RenderArea::mouseMoveEvent(QMouseEvent *event)
{
    QPoint dist( old_cursor.x() - event->pos().x(),old_cursor.y() - event->pos().y() );
    old_cursor = event->pos();

    if (drag) {
        center.setX( center.x() - dist.x() );
        center.setY( center.y() - dist.y() );
    }


    update();

}




void RenderArea::move_up()
{
    center.setY(center.y()-10);
    repaint();
}

void RenderArea::move_down()
{
     center.setY(center.y()+10);
     repaint();
}

void RenderArea::move_right()
{
     center.setX(center.x()+10);
     repaint();
}

void RenderArea::move_left()
{
     center.setX(center.x()-10);
     repaint();
}

void RenderArea::drawAxes()
{
    pen->drawLine(-center.x(),0, -center.x()+width(), 0);
    pen->drawLine(0,-center.y(),0,-center.y()+height());

    // Axe X
    int cpt = 0;
    for (int i = 0; i < width()-center.x() ; i+= pix_unite.x() ) {
        pen->drawLine(i,-3,i,3);
        float num_grad = float(cpt)*unite.y();
        if (num_grad)
            pen->drawText(i-2, -8, QString::number(num_grad));
        else
           pen->drawText(i+8, -8, QString::number(num_grad));
        cpt++;
    }

    cpt = 0;
    for (int i = 0; i > -center.x(); i-= pix_unite.x() ) {
         pen->drawLine(i,-3,i,3);
         float num_grad = float(cpt)*unite.y();
         if (num_grad)
            pen->drawText(i-2, -8, "-" + QString::number(num_grad));
         cpt++;
    }

    // Axe Y
    cpt = 0;
    for (int i = 0; i < height()-center.y(); i += pix_unite.y()) {
        pen -> drawLine(-3,i,3,i);
        float num_grad = float(cpt)*unite.y();
        if (num_grad)
            pen->drawText(5, i, "-" + QString::number(num_grad));
        cpt++;
   }

    cpt = 0;
    for (int i = 0; i > -center.y(); i -= pix_unite.y()) {
        pen -> drawLine(-3,i,3,i);
        float num_grad = float(cpt)*unite.y();
        if (num_grad)
            pen->drawText(5, i, QString::number(num_grad));
        cpt++;
   }


}


void RenderArea::paintEvent(QPaintEvent * /* event */)
{

    pen = new QPainter(this);

    pen->setPen(QPen(Qt::black,1));
    pen->translate(center);

    drawAxes();



    pen->end();

    delete pen;


}

