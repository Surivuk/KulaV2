#include "buslov.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QInputDialog>
#include <QLineEdit>


BUslov::BUslov(QString ime, QPoint lokacija)
{
    this->_tip="Uslov";
    this->_ime=ime;
    this->_tekst=" <podaci> ";

    this->_tekstBoja=QColor(0,0,0,255);
    this->_pozadinaBoja=QColor(255,102,255,255);
    this->_linijaBoja=QColor(153,0,153,255);

    this->setPos(lokacija);
}

QPainterPath BUslov::shape() const
{
    QRectF rect = outlineRect();
    QPainterPath path;
    QPolygon _poligon;

    _poligon.append(rect.topLeft().toPoint()+QPoint(0,rect.height()/2));
    _poligon.append(rect.topLeft().toPoint()+QPoint(10,0));
    _poligon.append(rect.topRight().toPoint()-QPoint(10,0));
    _poligon.append(rect.topRight().toPoint()+QPoint(0,rect.height()/2));
    _poligon.append(rect.bottomRight().toPoint()-QPoint(10,0));
    _poligon.append(rect.bottomLeft().toPoint()+QPoint(10,0));


    path.addPolygon(_poligon);

    return path;
}

void BUslov::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QString text = QInputDialog::getText(0,"Blok uslov", "Unesi podatke:",QLineEdit::Normal);
       if (!text.isEmpty())
           setText(text);
}

void BUslov::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QPen pen(_linijaBoja,2);

       if (option->state & QStyle::State_Selected) {
           pen.setColor(Qt::black);
           pen.setStyle(Qt::DotLine);
           pen.setWidth(2);
       }

       painter->setPen(pen);
       painter->setBrush(_pozadinaBoja);

       QRectF rect = outlineRect();

       QPolygon _poligon;

       _poligon.append(rect.topLeft().toPoint()+QPoint(0,rect.height()/2));
       _poligon.append(rect.topLeft().toPoint()+QPoint(10,0));
       _poligon.append(rect.topRight().toPoint()-QPoint(10,0));
       _poligon.append(rect.topRight().toPoint()+QPoint(0,rect.height()/2));
       _poligon.append(rect.bottomRight().toPoint()-QPoint(10,0));
       _poligon.append(rect.bottomLeft().toPoint()+QPoint(10,0));

       painter->drawPolygon(_poligon,Qt::OddEvenFill);

       painter->setPen(_tekstBoja);

       painter->drawText(rect, Qt::AlignCenter, _tekst);
}
