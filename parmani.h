#ifndef PARMANI_H
#define PARMANI_H

#include <QMainWindow>
#include"global.h"

namespace Ui {
class ParMani;
}

class ParMani : public QMainWindow
{
    Q_OBJECT

public:
    explicit ParMani(Global &global, QWidget *parent = nullptr);
    ~ParMani();

private slots:
    void on_pushButtonExit_clicked();
protected:
    void    timerEvent(QTimerEvent *event) override;
private:
    Ui::ParMani *ui;
    Global &global;
    int att;
   /* Dyno *dynoA;
    int timerIdUpd;
    int attX = 1;
    int attY = 1;
    int currX = 0;
    int currY = 0;
*/
};

#endif // PARMANI_H
