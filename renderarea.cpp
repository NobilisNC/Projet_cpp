#include "renderarea.h"

#include <cmath>
#include <iostream>
#include "function.h"

float RATIO = 5;
int NB_TAB = 2;
float TAB[] = { /*.2f,*/ .25f, .5f, 1.f };


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
    setMinimumSize(QSize(1000,600));
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





}

RenderArea::~RenderArea()
{
    delete pen;
    for (auto i : intern_func)
        delete i;
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

    /* Axes synchronisés */
    unite.setY(unite.x());
    pix_unite.setY(pix_unite.x());
    unite_per_pix.setY(unite_per_pix.y());
    base.setY(base.x());
    current_tab.setY(current_tab.x());



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


void RenderArea::drawFunction(AbstractFunction* f)
{
    if (f->isDrawable()) {


        pen->setPen( QPen( QBrush(f->getColor()) , 1 ,  (f->isSelected() ? Qt::DashLine : Qt::SolidLine) ));
        QPainterPath path;
        bool path_begin = false;

        std::pair<unsigned, QPointF*>  pair = f->getPoints(-center.x()*unite_per_pix.x(), (width()-center.x())*unite_per_pix.x());

        QPointF* tab = pair.second;


        for(unsigned i = 0; i < pair.first; i++ ) {
;

            int coord_y = -tab[i].y() * pix_unite.y() /unite.y();

            if (!path_begin && tab[i].y() == tab[i].y()) {
                path.moveTo(tab[i].x() * pix_unite.x() /unite.x() , coord_y);
                path_begin = true;
            } else if ( path_begin &&  !( coord_y >= -center.y() && coord_y  <= height() - center.y()) ) {
                pen->drawPath(path);
                path = QPainterPath();
                path_begin = false;
            } else
                path.lineTo(tab[i].x() * pix_unite.x() /unite.x() , -tab[i].y() * pix_unite.y() /unite.y() );
        }

        pen->drawPath(path);
    }




}


void RenderArea::paintEvent(QPaintEvent * /* event */)
{

    pen = new QPainter(this);

    pen->setPen(QPen(Qt::black,1));
    pen->translate(center);

    unite_per_pix = QPointF( unite.x()/pix_unite.x(),  unite.y()/pix_unite.y() );
    drawAxes();

    for (auto i : ext_function)
        drawFunction(i);

    for(auto i : intern_func)
        drawFunction(i);



    pen->end();

    delete pen;



}

