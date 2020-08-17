#include "ex3buylineedit.h"

Ex3BuyLineEdit::Ex3BuyLineEdit(QWidget *parent) : QLineEdit(parent)
{
    firstD = -1;
    QRegExp regx("[0-9,.]+$");
    QValidator *validator = new QRegExpValidator(regx, this);
    setValidator(validator);
    setAlignment(Qt::AlignmentFlag::AlignRight);
}

void Ex3BuyLineEdit::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Asterisk:
        if (QString::compare(text(), "") != 0)
        {
            firstD = text().toDouble();
            setText("");
        }
        break;
    case Qt::Key_Enter:
        if (firstD >= 0 && QString::compare(text(), "") != 0)
            setText(QString::number(firstD * text().toDouble() / 100.0, 'f', 2));
        emit calcB(i);
        break;
    default:
        QLineEdit::keyPressEvent(event);
        break;
    }
}

void Ex3BuyLineEdit::focusInEvent(QFocusEvent *event)
{
    QLineEdit::focusInEvent(event);
    QTimer::singleShot(0, this, &QLineEdit::selectAll);
}

void Ex3BuyLineEdit::focusOutEvent(QFocusEvent *event)
{
    exData->ex3BuyInput.replace(i, text());
    QLineEdit::focusOutEvent(event);
}
