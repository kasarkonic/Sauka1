#include "componentcard.h"
#include "ui_componentcard.h"

ComponentCard::ComponentCard(Global &global,QWidget *parent)
    //: QMainWindow(parent)
    : QWidget(parent, Qt::Window)
    , ui(new Ui::ComponentCard)
    , global(global)

{
    //QPalette pal = QPalette();
    //pal.setColor(QPalette::Window,global.backgroundColor); //QColor(255, 0, 0, 127)
    //pal.setColor(QPalette::Window, QColor(242, 219, 238, 0.251));
   // this->setAutoFillBackground(true);
   // this->setPalette(pal);
    ui->setupUi(this);
}

ComponentCard::~ComponentCard()
{
    delete ui;
}
