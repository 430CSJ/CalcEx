#ifndef PREPAREDIALOG_H
#define PREPAREDIALOG_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class PrepareDialog;
}

class PrepareDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PrepareDialog(QString notice_str, QWidget *parent, unsigned max_time = 60);
    ~PrepareDialog();

private:
    Ui::PrepareDialog *ui;
    unsigned time_left;
    QTimer *timer;

private slots:
    void showTimeLeft();
};

#endif // PREPAREDIALOG_H
