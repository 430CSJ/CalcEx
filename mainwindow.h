#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include "ex1dialog.h"
#include "ex2dialog.h"
#include "ex3dialog.h"
#include "resultdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(ExData *exD, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void openAboutWindow();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_start_clicked();

private:
    Ui::MainWindow *ui;

    ExData *exData;

    void refreshStartButton();

    QString getFilePath(QString fileWindowTitle);

    QString versionStr;
};
#endif // MAINWINDOW_H
