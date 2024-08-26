#ifndef RECIPEFORM_H
#define RECIPEFORM_H

#include <QWidget>
#include <QList>
#include "global.h"

namespace Ui {
class RecipeForm;
}

class RecipeForm : public QWidget
{
    Q_OBJECT

public:
    explicit RecipeForm(Global& global, QWidget *parent = nullptr);
    ~RecipeForm();
   // void recipeFormSetComponents(QList<recipeT> recKomp);

private:
    Ui::RecipeForm *ui;
    Global& global;
};

#endif // RECIPEFORM_H
