#ifndef DARTS_H
#define DARTS_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <vector>
#include "item.h"

namespace Ui
{
    class Darts;
}

class Darts : public QMainWindow
{
    Q_OBJECT

public:
    explicit Darts(QWidget *parent = 0);
    ~Darts();

public slots:
    void clicked(int m, int v);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Darts *ui;
    QGraphicsScene *scene;
    std::vector<Item*> singles;
    std::vector<Item*> singles2;
    std::vector<Item*> doubles;
    std::vector<Item*> triples;
    Item *bull;
    Item *bullseye;
    const unsigned int values[20] = {20, 5, 12, 9, 14, 11, 8, 16, 7, 19, 3, 17, 2, 15, 10, 6, 13, 4, 18, 1};
    //const unsigned int values[20] = {20, 1, 18, 4,13, 6, 10, 15, 2, 17, 3, 19, 7, 16, 8 , 11, 14, 9, 12, 5};

    void drawBoard();
    QString calculate(int erg);
    void virtual resizeEvent(QResizeEvent *event);
};

#endif // DARTS_H
