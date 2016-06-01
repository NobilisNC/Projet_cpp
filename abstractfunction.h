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

#include <QDebug>
#include <iostream>

//#include "function.h"
//#include "parametricfunction.h"

class AbstractFunction : public QPushButton
{
    Q_OBJECT
public:
    explicit AbstractFunction(const QString& _id, QWidget* parent = nullptr);
    virtual ~AbstractFunction();


    virtual QPoint* getPoints(QPoint min_max) = 0;

    inline bool isDrawable() const { return check->isChecked(); }
    inline QString getID() const {return id;}
    inline void setID(const QString& _id) {id=_id;}


    static AbstractFunction* loadFunction(const QString&, QWidget* parent = nullptr) ;

protected :
    QString id;

    QHBoxLayout* layout;
    QCheckBox* check;
    QComboBox* box;
    QLabel* id_func;


};

#endif // ABSTRACTFUNCTION_H
