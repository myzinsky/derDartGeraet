#include "darts.h"
#include "ui_darts.h"
#include <QGraphicsEllipseItem>
#include <QMessageBox>
#include <QDebug>
#include <QGraphicsTextItem>
#include <cmath>

Darts::Darts(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Darts)
{
    ui->setupUi(this);

    // Initialize fields:
    for(unsigned int i=0; i < 20; i++)
    {
        Item *s = new Item(1,values[i]);
        singles.push_back(s);
        QObject::connect(s, &Item::callback, this, &Darts::clicked);

        Item *s2 = new Item(1,values[i]);
        singles2.push_back(s2);
        QObject::connect(s2, &Item::callback, this, &Darts::clicked);

        Item *d = new Item(2,values[i]);
        doubles.push_back(d);
        QObject::connect(d, &Item::callback, this, &Darts::clicked);

        Item *t = new Item(3,values[i]);
        triples.push_back(t);
        QObject::connect(t, &Item::callback, this, &Darts::clicked);
    }

    bull = new Item(1,25);
    QObject::connect(bull, &Item::callback, this, &Darts::clicked);

    bullseye = new Item(2,25);
    QObject::connect(bullseye, &Item::callback, this, &Darts::clicked);

    // Draw Board
    drawBoard();
}

void Darts::resizeEvent(QResizeEvent *event __attribute__((unused)))
{
    drawBoard();
}

void Darts::drawBoard()
{
    scene = new QGraphicsScene(this);
    scene->setBackgroundBrush(Qt::white);

    int startAngle;
    int spanAngle;

    unsigned int size = ui->dartBoard->height()*0.8;

    for(unsigned int i=0; i < 20; i++)
    {
        startAngle = 90*16 - 5760/20/2 + i*5760/20;
        spanAngle  = 5760/20;

        // Draw Doubles:
        Item *d = doubles[i];

        d->setRect(0, 0, size, size);
        d->setStartAngle(startAngle);
        d->setSpanAngle(spanAngle);

        (i%2==0) ? d->setBrush(Qt::red) : d->setBrush(Qt::green);

        scene->addItem(d);

        // Draw Outer Singles:
        Item *s = singles[i];

        s->setRect(0.033*size,0.033*size, size-0.066*size, size-0.066*size);
        s->setStartAngle(startAngle);
        s->setSpanAngle(spanAngle);

        (i%2==0) ? s->setBrush(Qt::black) : s->setBrush(Qt::lightGray);

        scene->addItem(s);

        // Draw Triples:
        Item *t = triples[i];

        t->setRect(0.183*size, 0.183*size, size-0.366*size, size-0.366*size);
        t->setStartAngle(startAngle);
        t->setSpanAngle(spanAngle);

        (i%2==0) ? t->setBrush(Qt::red) : t->setBrush(Qt::green);

        scene->addItem(t);

        // Draw Inner Singles:
        Item *s2 = singles2[i];

        s2->setRect(0.216*size, 0.216*size, size-0.433*size, size-0.433*size);
        s2->setStartAngle(startAngle);
        s2->setSpanAngle(spanAngle);

        (i%2==0) ? s2->setBrush(Qt::black) : s2->setBrush(Qt::lightGray);

        scene->addItem(s2);

        QGraphicsTextItem *h = new QGraphicsTextItem(QString("%1").arg(values[i]));
        const double pi = 3.14159265;
        double x = size/2 + (size/2*1.1) * cos(-pi/2-i*2*pi/20) - h->boundingRect().width()/2;
        double y = size/2 + (size/2*1.1) * sin(-pi/2-i*2*pi/20) - h->boundingRect().height()/2;
        h->setPos(x,y);
        scene->addItem(h);
    }

    // Draw Bulls:
    bull->setRect(size/2.0-0.066*size, size/2.0-0.066*size, 0.133*size, 0.133*size);
    bull->setBrush(Qt::green);

    scene->addItem(bull);

    // Draw Bulls Eye:
    bullseye->setRect(size/2.0-0.033*size, size/2.0-0.033*size, 0.066*size, 0.066*size);
    bullseye->setBrush(Qt::red);

    scene->addItem(bullseye);

    // Commit:
    ui->dartBoard->setScene(scene);
    ui->dartBoard->show();
}

Darts::~Darts()
{
    delete ui;
}

void Darts::clicked(int m, int v)
{
    qDebug() << m*v;
    int erg = ui->label->text().toInt() - m*v;

    if(erg > 0)
    {
        ui->label->setText(QString("%1").arg(erg));

        if(erg <= 170)
        {
            ui->listWidget->clear();
            ui->listWidget->addItem(calculate(erg));
        }
    }
    else if ( erg == 0)
    {
        ui->label->setText(QString("WON"));
    }
}

QString Darts::calculate(int erg)
{
    // TODO: repace with algorithm ...
    switch(erg)
    {
        case 60  : return "S20 D20"       ;
        case 61  : return "25 D18"        ;
        case 62  : return "T10 D16"       ;
        case 63  : return "T13 D12"       ;
        case 64  : return "T16 D8"        ;
        case 65  : return "25 D20"        ;
        case 66  : return "T10 D18"       ;
        case 67  : return "T17 D8"        ;
        case 68  : return "T20 D4"        ;
        case 69  : return "T13 D15"       ;
        case 70  : return "T10 D20"       ;
        case 71  : return "T17 D10"       ;
        case 72  : return "T12 D18"       ;
        case 73  : return "T19 D8"        ;
        case 74  : return "T18 D10"       ;
        case 75  : return "T17 D12"       ;
        case 76  : return "T20 D8"        ;
        case 77  : return "T19 D10"       ;
        case 78  : return "T18 D12"       ;
        case 79  : return "T13 D20"       ;
        case 80  : return "T20 D10"       ;
        case 81  : return "T15 D18"       ;
        case 82  : return "T14 D20"       ;
        case 83  : return "T17 D16"       ;
        case 84  : return "T20 D12"       ;
        case 85  : return "T15 D20"       ;
        case 86  : return "T18 D16"       ;
        case 87  : return "T17 D18"       ;
        case 88  : return "T16 D20"       ;
        case 89  : return "T19 D16"       ;
        case 90  : return "T18 D18"       ;
        case 91  : return "T17 D20"       ;
        case 92  : return "T20 D16"       ;
        case 93  : return "T19 D18"       ;
        case 94  : return "T18 D20"       ;
        case 95  : return "T19 D19"       ;
        case 96  : return "T20 D18"       ;
        case 97  : return "T19 D20"       ;
        case 98  : return "T20 D19"       ;
        case 99  : return "T20 S7 D16"    ;
        case 100 : return "T20 D20"       ;
        case 101 : return "T17 Bull"      ;
        case 102 : return "T20 S10 D16"   ;
        case 103 : return "T20 S3 D20"    ;
        case 104 : return "T18 Bull"      ;
        case 105 : return "T20 S13 D16"   ;
        case 106 : return "T20 S10 D18"   ;
        case 107 : return "T19 Bull"      ;
        case 108 : return "T20 S16 D16"   ;
        case 109 : return "T20 S17 D16"   ;
        case 110 : return "T20 S18 D16"   ;
        case 111 : return "T20 S19 D16"   ;
        case 112 : return "T20 S20 D16"   ;
        case 113 : return "T20 S13 D20"   ;
        case 114 : return "T20 S14 D20"   ;
        case 115 : return "T20 S15 D20"   ;
        case 116 : return "T20 S16 D20"   ;
        case 117 : return "T20 S17 D20"   ;
        case 118 : return "T20 S18 D20"   ;
        case 119 : return "T20 S19 D20"   ;
        case 120 : return "T20 S20 D20"   ;
        case 121 : return "T20 T7 D20"    ;
        case 122 : return "T18 T12 D16"   ;
        case 123 : return "T19 T10 D18"   ;
        case 124 : return "T20 S14 Bull"  ;
        case 125 : return "25 T20 D20"    ;
        case 126 : return "T19 S19 Bull"  ;
        case 127 : return "T20 T17 D8"    ;
        case 128 : return "T18 T14 D16"   ;
        case 129 : return "T19 T12 D18"   ;
        case 130 : return "T20 S20 Bull"  ;
        case 131 : return "T20 T17 D10"   ;
        case 132 : return "T20 T12 D18"   ;
        case 133 : return "T20 T11 D20"   ;
        case 134 : return "T20 T14 D16"   ;
        case 135 : return "T17 T20 D12"   ;
        case 136 : return "T20 T20 D8"    ;
        case 137 : return "T19 T20 D10"   ;
        case 138 : return "T20 T18 D12"   ;
        case 139 : return "T19 T14 D20"   ;
        case 140 : return "T20 T20 D10"   ;
        case 141 : return "T17 T18 D18"   ;
        case 142 : return "T20 T14 D20"   ;
        case 143 : return "T20 T17 D16"   ;
        case 144 : return "T18 T18 D18"   ;
        case 145 : return "T20 T15 D20"   ;
        case 146 : return "T20 T18 D16"   ;
        case 147 : return "T19 T18 D18"   ;
        case 148 : return "T20 T16 D20"   ;
        case 149 : return "T20 T19 D16"   ;
        case 150 : return "T20 T18 D18"   ;
        case 151 : return "T20 T17 D20"   ;
        case 152 : return "T20 T20 D16"   ;
        case 153 : return "T20 T19 D18"   ;
        case 154 : return "T20 T18 D20"   ;
        case 155 : return "T20 T19 D19"   ;
        case 156 : return "T20 T20 D18"   ;
        case 157 : return "T20 T19 D20"   ;
        case 158 : return "T20 T20 D19"   ;
        case 160 : return "T20 T20 D20"   ;
        case 161 : return "T20 T17 Bull"  ;
        case 164 : return "T20 T18 Bull"  ;
        case 167 : return "T20 T19 Bull"  ;
        case 170 : return "T20 T20 Bull"  ;
        default  : return "";
    }
}

void Darts::on_pushButton_clicked()
{
    ui->label->setText(QString("501"));
}
