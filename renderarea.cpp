#include "renderarea.h"

#include <cmath>
#include <iostream>
#include "function.h"

float RATIO = 5;
int NB_TAB = 2;
float TAB[] = { /*.2f,*/ .25f, .5f, 1.f };

Function* c = nullptr;



RenderArea::RenderArea(QWidget *parent) : QWidget(parent),
    pen(nullptr),
    center(500, 300),
    pix_unite(100,100),
    unite(1.f , 1.f),
    base(1.f , 1.f),
    current_tab(2,2),
    drag(false),
    old_cursor(-1,-1),
    pos_label(nullptr)
{
    setBackgroundRole(QPalette::Base);
    setFixedSize(QSize(1000,600));
    setAutoFillBackground(true);
    setCursor(Qt::CrossCursor);
    setMouseTracking(true);


    QPalette pal = this->palette();
    pal.setColor(this->backgroundRole(), Qt::white);
    setPalette(pal);

    pos_label = new QLabel("x:        y:       :::::",this);
    pos_label->setFixedSize(200,25);
    pos_label->move(width()-150, height() - 25);
    pos_label->raise();




    c = new Function("id", "x");


}

RenderArea::~RenderArea()
{
    delete pen;
}


void RenderArea::wheelEvent(QWheelEvent *event)
{

    QPoint mouse_pos(event->pos());
    QPointF log_mouse_pos( (mouse_pos.x() - center.x()) * unite_per_pix.x(),
                          (center.y() - mouse_pos.y() ) * unite_per_pix.y()  );


    float delta = float(event->angleDelta().y())/380.f;
    QPoint new_mouse_pos = QPoint(int(pix_unite.x() + delta *  RATIO), int(pix_unite.y() + delta * RATIO));

    if ( new_mouse_pos.x()  < 50 ) { // DEZOOM

        if (current_tab.x() == NB_TAB ) {
            base.setX(base.x() * 10);
            current_tab.setX(0);
        } else {
            current_tab.setX(current_tab.x()+1);
        }

        pix_unite.setX(    pix_unite.x() + 1.5f * pix_unite.x()  );
        unite.setX( base.x() * TAB[current_tab.x()] );



     } else if ( new_mouse_pos.x()  > 150 ) { //ZOOM

        if (current_tab.x() == 0 ) {
            base.setX(base.x() / 10);
            current_tab.setX(NB_TAB);
        } else {
            current_tab.setX(current_tab.x() - 1);
        }


        pix_unite.setX(    pix_unite.x() - .5f * pix_unite.x()  );
        unite.setX( base.x() * TAB[current_tab.x()] );

    } else if (new_mouse_pos.y()  > 150 ) { // ZOOM

        if (current_tab.y() == 0 ) {
            base.setY( base.y() / 10);
            current_tab.setY(NB_TAB);
        } else {
            current_tab.setY( current_tab.y() -1);
        }

        pix_unite.setY(    pix_unite.y() - .5f * pix_unite.y()  );
        unite.setY( base.y() * TAB[current_tab.y()] );

    } else if(new_mouse_pos.y()  < 50 ) { //DEZOOM

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

    //unite_per_pix = QPointF( unite.x()/pix_unite.x(),  unite.y()/pix_unite.y() );

    // On calcule ou se trouve les coordonnée logique du curseur avec les nouvelles variables
   /* QPointF n_mouse_pos( (mouse_pos.x() - center.x()) * unite_per_pix.x(),
                        (center.y() - mouse_pos.y() ) * unite_per_pix.y() );

    QPoint distance( (log_mouse_pos.x() - n_mouse_pos.x())* pix_unite.x() /unite.x(),
                      (n_mouse_pos.y() - log_mouse_pos.y())* pix_unite.y() /unite.y());



    center.setX( center.x() - distance.x() );
    center.setY( center.y() -  distance.y() );
    QCursor::setPos(event->globalX() + distance.x(), event->globalY() + distance.y());*/

    //QCursor::setPos( (event->globalX()/2 + width()) - distance.x(), event->globalY()/* + distance.y() */);

    std::cerr << unite.x() << " - " << unite.y() << std::endl;


    update();

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

    pos_label->setText(  QString("x:")
                       + QString::number((event->pos().x() - center.x() ) * unite_per_pix.x(), 10, 4)
                       + QString(" y:")
                       + QString::number((center.y()-event->pos().y() )* unite_per_pix.y(), 10, 4)
                      );


    update();
    pos_label->update();

}




void RenderArea::move_up()
{
    center.setY(center.y()-10);
    update();
}

void RenderArea::move_down()
{
     center.setY(center.y()+10);
     update();
}

void RenderArea::move_right()
{
     center.setX(center.x()+10);
     update();
}

void RenderArea::move_left()
{
     center.setX(center.x()-10);
     update();
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


void RenderArea::drawFunctions()
{
    pen->setPen(QPen(Qt::blue,1));
    QPainterPath path;
    bool path_begin = false;

    for(float i = -center.x()*unite_per_pix.x(); i <= (width()-center.x())*unite_per_pix.x(); i += unite_per_pix.x() ) {
        float y = c->get_image(i);
        int coord_y = -y * pix_unite.y() /unite.y();

        if (!path_begin && y == y) {
            path.moveTo(i * pix_unite.x() /unite.x() , coord_y);
            path_begin = true;
        } else if ( path_begin &&  !( coord_y > -center.y() && coord_y  < height() - center.y() ) ) {
            pen->drawPath(path);
            path = QPainterPath();
            path_begin = false;
        } else
            path.lineTo(i * pix_unite.x() /unite.x() , -y * pix_unite.y() /unite.y() );
    }

    pen->drawPath(path);


}


void RenderArea::paintEvent(QPaintEvent * /* event */)
{

    pen = new QPainter(this);

    pen->setPen(QPen(Qt::black,1));
    pen->translate(center);

    unite_per_pix = QPointF( unite.x()/pix_unite.x(),  unite.y()/pix_unite.y() );
    drawAxes();
    drawFunctions();



    pen->end();

    delete pen;


}

