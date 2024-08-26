#include "recipeform.h"
#include "ui_recipeform.h"

RecipeForm::RecipeForm(Global& global, QWidget *parent)
    : QWidget(parent)
    , global(global)
    , ui(new Ui::RecipeForm)
{
    ui->setupUi(this);
}

RecipeForm::~RecipeForm()
{
    delete ui;
}

//void RecipeForm::recipeFormSetComponents(QList<recipeT> recKomp)
//{

//}
