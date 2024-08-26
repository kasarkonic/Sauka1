#include "recipeform.h"
#include "ui_recipeform.h"

RecipeForm::RecipeForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RecipeForm)
{
    ui->setupUi(this);
}

RecipeForm::~RecipeForm()
{
    delete ui;
}
