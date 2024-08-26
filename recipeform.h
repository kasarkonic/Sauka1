#ifndef RECIPEFORM_H
#define RECIPEFORM_H

#include <QWidget>

namespace Ui {
class RecipeForm;
}

class RecipeForm : public QWidget
{
    Q_OBJECT

public:
    explicit RecipeForm(QWidget *parent = nullptr);
    ~RecipeForm();

private:
    Ui::RecipeForm *ui;
};

#endif // RECIPEFORM_H
