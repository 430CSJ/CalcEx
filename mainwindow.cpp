#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(ExData *exD, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    versionStr = "0.1";
    exData = exD;
    ui->setupUi(this);
    menuBar()->addAction("关闭", this, SLOT(close()));
    menuBar()->addAction("关于...", this, SLOT(openAboutWindow()));
    ui->label->setWordWrap(true);
    ui->label_2->setWordWrap(true);
    ui->label_3->setWordWrap(true);
    ui->pushButton_start->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString filePath = getFilePath("选择翻打数据文件");
    if (QString::compare(filePath, "") != 0)
    {
        if (exData->importEx12Data(1, filePath))
        {
            ui->label->setText(filePath);
            ui->label->adjustSize();
            ui->groupBox->setCheckable(true);
            ui->groupBox->setChecked(true);
        }
        else
        {
            QString errMsg = "无法载入翻打数据文件“";
            QMessageBox::critical(this, "错误", errMsg.append(filePath).append("”。"), QMessageBox::Ok, QMessageBox::Ok);
        }
    }
}

QString MainWindow::getFilePath(QString fileWindowTitle)
{
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(fileWindowTitle);
    fileDialog->setDirectory(".");
    fileDialog->setNameFilter(MainWindow::tr("File(*.*)"));
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    fileDialog->setViewMode(QFileDialog::Detail);
    QStringList fileNames;
    if (fileDialog->exec())
        return fileDialog->selectedFiles().front();
    return "";
}

void MainWindow::openAboutWindow()
{
    QString aboutMsg = "计算器练习v";
    aboutMsg.append(versionStr);
    aboutMsg.append(" by ZYH. <a href=\"https://github.com/430CSJ/CalcEx\">项目地址");
    QMessageBox::about(this, "关于", aboutMsg);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString filePath = getFilePath("选择平打数据文件");
    if (QString::compare(filePath, "") != 0)
    {
        if (exData->importEx12Data(2, filePath))
        {
            ui->label_2->setText(filePath);
            ui->label_2->adjustSize();
            ui->groupBox_2->setCheckable(true);
            ui->groupBox_2->setChecked(true);
        }
        else
        {
            QString errMsg = "无法载入平打数据文件“";
            QMessageBox::critical(this, "错误", errMsg.append(filePath).append("”。"), QMessageBox::Ok, QMessageBox::Ok);
        }
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QString filePath = getFilePath("选择外汇折算数据文件");
    if (QString::compare(filePath, "") != 0)
    {
        if (exData->importEx3Data(filePath))
        {
            ui->label_3->setText(filePath);
            ui->label_3->adjustSize();
            ui->groupBox_3->setCheckable(true);
            ui->groupBox_3->setChecked(true);
        }
        else
        {
            QString errMsg = "无法载入外汇折算数据文件“";
            QMessageBox::critical(this, "错误", errMsg.append(filePath).append("”。"), QMessageBox::Ok, QMessageBox::Ok);
        }
    }
}

void MainWindow::on_pushButton_start_clicked()
{
    exData->isExSelected[0] = false;
    exData->isExSelected[1] = false;
    exData->isExSelected[2] = false;
    exData->selectedExCnt = 0;
    if (ui->groupBox->isChecked())
    {
        exData->isExSelected[0] = true;
        ++exData->selectedExCnt;
    }
    if (ui->groupBox_2->isChecked())
    {
        exData->isExSelected[1] = true;
        ++exData->selectedExCnt;
    }
    if (ui->groupBox_3->isChecked())
    {
        exData->isExSelected[2] = true;
        ++exData->selectedExCnt;
    }
    if (exData->selectedExCnt <= 0)
        QMessageBox::question(this, "提示", tr("请选择至少一个部分。"), QMessageBox::Yes, QMessageBox::Yes);
    else
    {
        exData->readyToStart(ui->spinBox->value() * 60);
        int dialogRes = QDialog::Accepted;
        if (exData->isExSelected[0] && exData->timeLeft > 0)
        {
            Ex1Dialog *ex1Dialog = new Ex1Dialog(exData, this);
            dialogRes = ex1Dialog->exec();
        }
        if (dialogRes == QDialog::Accepted && exData->isExSelected[1] && exData->timeLeft > 0)
        {
            Ex2Dialog *ex2Dialog = new Ex2Dialog(exData, this);
            dialogRes = ex2Dialog->exec();
        }
        if (dialogRes == QDialog::Accepted && exData->isExSelected[2] && exData->timeLeft > 0)
        {
            Ex3Dialog *ex3Dialog = new Ex3Dialog(exData, this);
            dialogRes = ex3Dialog->exec();
        }
        ResultDialog *resultDialog = new ResultDialog(exData, this);
        resultDialog->exec();
    }
}
