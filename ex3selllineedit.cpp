#include "ex3selllineedit.h"

Ex3SellLineEdit::Ex3SellLineEdit(QWidget *parent) : QLineEdit(parent)
{
    firstD = -1;
    QRegExp regx("[0-9,.]+$");
    QValidator *validator = new QRegExpValidator(regx, this);
    setValidator(validator);
    setAlignment(Qt::AlignmentFlag::AlignRight);
}

void Ex3SellLineEdit::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Slash:
        if (QString::compare(text(), "") != 0)
        {
            firstD = text().toDouble();
            setText("");
        }
        break;
    case Qt::Key_Enter:
        if (firstD >= 0 && QString::compare(text(), "") != 0)
        {
            double newD = text().toDouble();
            if (newD == 0)
                setText("NaN");
            else
                setText(QString::number(firstD / newD * 100.0, 'f', 2));
        }
        emit calcS(i);
        break;
    default:
        QLineEdit::keyPressEvent(event);
        break;
    }
}

void Ex3SellLineEdit::focusInEvent(QFocusEvent *event)
{
    QLineEdit::focusInEvent(event);
    QTimer::singleShot(0, this, &QLineEdit::selectAll);
}

void Ex3SellLineEdit::focusOutEvent(QFocusEvent *event)
{
    exData->ex3SellInput.replace(i, text());
    QLineEdit::focusOutEvent(event);
}
