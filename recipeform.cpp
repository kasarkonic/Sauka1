#include "recipeform.h"
#include "ui_recipeform.h"

RecipeForm::RecipeForm(Global& global, QWidget *parent)
    : QWidget(parent)
    , global(global)
    , ui(new Ui::RecipeForm)
{
    ui->setupUi(this);
    initUi();




}

RecipeForm::~RecipeForm()
{
    delete ui;
}

void RecipeForm::recipeFormSetComponents(QList<Global::recipeT> recKomp)
{
    for (int i = 0; i < recKomp.length(); i++){

        QLabel *label_komp = tabPtr[i].label_komp;
        label_komp->setText(recKomp[i].name);

        QLabel *label_var1 = tabPtr[i].label_var1;
        label_var1->setText(recKomp[i].name);

        QLabel *label_var2 = tabPtr[i].label_var2;
        label_var2->setText(recKomp[i].name);

    }
}

void RecipeForm::setRecipeName(QString name)
{
    ui->label_name->setText(name);
}

void RecipeForm::initUi()
{
    tPtr tablePtr;
    for (int i = 0; i < 8; i++){
        QLabel *label_komp = new QLabel(this);
        tablePtr.label_komp = label_komp;
        label_komp->setText(QString::number(i+1) + ". Komponente");
        label_komp->setMinimumSize(20, 20);

        QLabel *label_var1 = new QLabel(this);
        tablePtr.label_var1 = label_var1;
        label_var1->setText(QString::number(i * 10));
        label_var1->setMinimumSize(20, 20);

        QLabel *label_var2 = new QLabel(this);
        tablePtr.label_var2 = label_var2;
        label_var2->setText(QString::number(i * 100));
        label_var2->setMinimumSize(20, 20);


        ui->vl_komp->addWidget(label_komp);
        ui->vl_var1->addWidget(label_var1);
        ui->vl_var2->addWidget(label_var2);


        tabPtr.append(tablePtr);

    }

    QFrame *lineK1;
    lineK1 = new QFrame(this);
    lineK1->setFrameShape(QFrame::HLine);
    lineK1->setFrameShadow(QFrame::Sunken);
    //lineK1->lineWidth(1); //[0-3]

    QFrame *lineV1;
    lineV1 = new QFrame(this);
    lineV1->setFrameShape(QFrame::HLine);
    lineV1->setFrameShadow(QFrame::Sunken);
    QFrame *lineV2;
    lineV2 = new QFrame(this);
    lineV2->setFrameShape(QFrame::HLine);
    lineV2->setFrameShadow(QFrame::Sunken);


    ui->vl_komp->addWidget(lineK1);
    ui->vl_var1->addWidget(lineV1);
    ui->vl_var2->addWidget(lineV2);

    QLabel *label_Sum = new QLabel(this);
    tablePtr.label_komp = label_Sum;
    label_Sum->setText("Kopā");
    label_Sum->setMinimumSize(20, 20);

    QLabel *label_var1 = new QLabel(this);
    tablePtr.label_var1 = label_var1;
    label_var1->setText(QString::number(28* 10));
    label_var1->setMinimumSize(20, 20);

    QLabel *label_var2 = new QLabel(this);
    tablePtr.label_var2 = label_var2;
    label_var2->setText(QString::number(28 * 100));
    label_var2->setMinimumSize(20, 20);

    tabPtr.append(tablePtr);

    ui->vl_komp->addWidget(label_Sum);
    ui->vl_var1->addWidget(label_var1);
    ui->vl_var2->addWidget(label_var2);

}
