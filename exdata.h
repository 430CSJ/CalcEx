#ifndef EXDATA_H
#define EXDATA_H

#include <QFile>
#include <QIODevice>
#include <QTime>
#include <QMap>
#include <QtGlobal>

#define EX_NUM 3

class ExData
{
public:
    bool isExloaded[EX_NUM], isExSelected[EX_NUM];
    int loadedExCnt, selectedExCnt, exDelLine[2];
    unsigned timeLeft;
    qlonglong ex1Data[3][51], ex2Data[3][51], ex1Input[3][51], ex2Input[3][51];
    QList<QString> ex3BuyInput, ex3SellInput, ex3BuyAnswer, ex3SellAnswer;
    QList<QList<QByteArray>> ert;
    QMap<int, double> buyRates, sellRates;
    QMap<int, QByteArray> codeNames;
    QList<int> buyCodes, sellCodes;
    QList<double> buyCnts, sellCnts;
    ExData();
    void readyForNewEx();
    void readyToStart(unsigned time);
    bool importEx12Data(int k, QString dataFilePath);
    bool importEx3Data(QString dataFilePath);
};

#endif // EXDATA_H
