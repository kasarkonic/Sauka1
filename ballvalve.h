#ifndef BALLVALVE_H
#define BALLVALVE_H

#include <QMainWindow>

class Global;
class BallValve :  public QObject
{
    Q_OBJECT
public:
    explicit BallValve(Global* global,QString name, int outOpen, int outClose, int inOpen, int inClose, QObject* parent = nullptr);

    QString name;
    int outOpen = 0;    // output address
    int outClose = 0;
    int inOpen = 0; // input address
    int inClose = 0;

    void open();
    void close();
    bool isOpen();
    bool isClose();
    QString getName();
    int getOpenTime();
    int getCloseTime();
    int initbattValve( bool stat ); // close/oprn if unknow status 0 close,  1 open.


protected:
    void timerEvent(QTimerEvent* event) ;

private:
    enum valveStatus {
        Open,
        Close,
        Unknow,
    };

    //  QTimer* runTimer;
    Global* global;

    void startTim(int t = 100);
    int startOpenTime = 0;
    int StartCloseTime = 0;

    int openTime = 0;
    int closeTime = 0;
    int startTime = 0;
    int timerId;

    valveStatus status = valveStatus::Unknow;




};

#endif // BALLVALVE_H
