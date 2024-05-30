#ifndef RUNPROCESS_H
#define RUNPROCESS_H

#include <QWidget>
#include"global.h"

namespace Ui {
class Runprocess;
}

class Runprocess : public QWidget
{
    Q_OBJECT

public:
    explicit Runprocess(Global &global,QWidget *parent = nullptr);
    ~Runprocess();

private:
    Ui::Runprocess *ui;
    Global &global;
};

#endif // RUNPROCESS_H
