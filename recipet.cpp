#include "recipet.h"
#include "ui_recipet.h"

Recipet::Recipet(Global &global,QWidget *parent)
   : QWidget(parent, Qt::Window)
   , ui(new Ui::Recipet)
   , global(global)
{
    ui->setupUi(this);
}

Recipet::~Recipet()
{
    delete ui;
}
