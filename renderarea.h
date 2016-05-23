#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPainter>
#include <QWheelEvent>
#include <QMouseEvent>

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = 0);
    ~RenderArea();

    void move_up();
    void move_down();
    void move_right();
    void move_left();



private :
    void drawAxes();
    void calcCoord();


    QPainter* pen;
    QPoint center;


    // ZOOM/DEZOOM

    QPointF pix_unite;
    QPointF unite;
    QPointF base;
    QPoint current_tab;

    // DEPLACEMENT
    bool drag;
    QPoint old_cursor;





protected:
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent *) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent * ) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *) Q_DECL_OVERRIDE;

};




#endif // RENDERAREA_H
