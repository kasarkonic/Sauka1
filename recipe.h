#ifndef RECIPE_H
#define RECIPE_H

#include <QWidget>

namespace Ui {
    class Recipe;
}

class Recipe : public QWidget {
    Q_OBJECT

public:
    explicit Recipe(QWidget* parent = nullptr);
    ~Recipe();

private:
    Ui::Recipe* ui;
};

#endif // RECIPE_H
