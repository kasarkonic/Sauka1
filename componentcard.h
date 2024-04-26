#ifndef COMPONENTCARD_H
#define COMPONENTCARD_H

#include <QMainWindow>
#include"global.h"

namespace Ui {
class ComponentCard;
}

class ComponentCard : public QWidget //QMainWindow
{
    Q_OBJECT

public:

    explicit ComponentCard(Global &global, QWidget *parent = nullptr);
   // Ui::ComponentCard *ui;
    ~ComponentCard();

private:
    Ui::ComponentCard *ui;
    Global &global;
};

#endif // COMPONENTCARD_H
