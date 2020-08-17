#ifndef DIALOG0_H
#define DIALOG0_H

#include <QDialog>

namespace Ui {
class Dialog0;
}

class Dialog0 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog0(QWidget *parent = nullptr);
    ~Dialog0();

private:
    Ui::Dialog0 *ui;
};

#endif // DIALOG0_H
