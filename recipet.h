#ifndef RECIPET_H
#define RECIPET_H

#include <QMainWindow>
#include"global.h"
namespace Ui {
class Recipet;
}

class Recipet : public QWidget
{
    Q_OBJECT

public:
    explicit Recipet(Global &global, QWidget *parent = nullptr);
    ~Recipet();

private:
    Ui::Recipet *ui;
    Global &global;
};

#endif // RECIPET_H
