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
    void recipeFormSetComponents(QList<Global::recipeT> recKomp);
    void setRecipeName(QString name);

private:
    Ui::RecipeForm *ui;
    Global& global;
    void initUi();

    struct  tPtr {
        QLabel *label_komp;
        QLabel *label_var1;
        QLabel *label_var2;
    };
    QList<tPtr>tabPtr;
};

#endif // RECIPEFORM_H
