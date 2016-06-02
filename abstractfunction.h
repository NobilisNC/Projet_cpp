#ifndef ABSTRACTFUNCTION_H
#define ABSTRACTFUNCTION_H

#include <QWidget>
#include <QObject>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QComboBox>
#include <QString>
#include <QCheckBox>
#include <QVector>
#include <QPainter>
#include <QColorDialog>

#include <QDebug>
#include <iostream>
#include "defines.h"


class AbstractFunction : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractFunction(const QString& _id, QWidget* parent = nullptr);
    virtual ~AbstractFunction();


    virtual std::pair<unsigned, QPointF*>  getPoints(float min, float max) = 0;
    void new_select(AbstractFunction* new_func);
    virtual float getOnePoint(float x) = 0;

    inline bool isDrawable() const { return check->isChecked(); }
    inline QString getID() const {return id;}
    inline void setID(const QString& _id) {id=_id;}
    inline QColor getColor() const { return color; }
    inline bool isSelected() const {return is_selected;}


    static AbstractFunction* loadFunction(const QString&, QWidget* parent = nullptr) ;

protected :
    QString id;
    bool is_selected;
    QColor color;

    QVBoxLayout* main_layout;
    QHBoxLayout* top_layout;
    QCheckBox* check;
    QPushButton* color_button;
    QIcon* icon_color;
    QPixmap* pix_color;
    QLabel* id_func;
    QVBoxLayout* bottom_layout;



    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;

    void mouseReleaseEvent(QMouseEvent*);


public slots :
    void choseColor();


signals :
    void selected(AbstractFunction* );





};

#endif // ABSTRACTFUNCTION_H
