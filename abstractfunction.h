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

    inline bool isDrawable() const { return check->isChecked(); }
    inline QString getID() const {return id;}
    inline void setID(const QString& _id) {id=_id;}
    inline int getColor() const { return COLOR[box->currentIndex()]; }
    inline bool isSelected() const {return is_selected;}


    static AbstractFunction* loadFunction(const QString&, QWidget* parent = nullptr) ;

protected :
    QString id;
    bool is_selected;

    QVBoxLayout* main_layout;
    QHBoxLayout* top_layout;
    QCheckBox* check;
    QComboBox* box;
    QLabel* id_func;
    QVBoxLayout* bottom_layout;



    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;

    void mouseReleaseEvent(QMouseEvent*);


public slots :


signals :
    void selected(AbstractFunction* );





};

#endif // ABSTRACTFUNCTION_H
