#include "pdfdebugitemtextbox.h"

#include <QPainter>

PdfDebugItemTextBox::PdfDebugItemTextBox(PDFTextBox *textBox, QGraphicsItem *parent)
    : QGraphicsItem(parent), _textBox(textBox)
{
    foreach (PDFTextBox *textBox, _textBox->subBoxes())
        new PdfDebugItemTextBox(textBox, this);
}

PDFTextBox *PdfDebugItemTextBox::textBox() const
{
    return _textBox;
}

QRectF PdfDebugItemTextBox::boundingRect() const
{
    return textBox()->boundingRect().adjusted(-2, -2, 2, 2);
}

void PdfDebugItemTextBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    switch (_textBox->type())
    {
    case PDFTextBox::Text:
        painter->setPen(QPen(Qt::yellow, 1));
        break;
    case PDFTextBox::SubText:
        painter->setPen(QPen(Qt::green, 0.5));
        break;
    case PDFTextBox::Pad:
        painter->setPen(QPen(Qt::red, 1));
        break;
    }
    painter->drawRect(textBox()->boundingRect());
}
