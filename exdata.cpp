#include "exdata.h"

ExData::ExData()
{
    readyForNewEx();
}

void ExData::readyForNewEx()
{
    loadedExCnt = 0;
    selectedExCnt = 0;
    timeLeft = 0;
    for (int i = 0; i < EX_NUM; ++i)
    {
        isExloaded[i] = false;
        isExSelected[i] = false;
    }
}

void ExData::readyToStart(unsigned int time)
{
    timeLeft = time;
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    exDelLine[0] = qrand() % 51;
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    exDelLine[1] = qrand() % 51;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 51; ++j)
        {
            ex1Input[i][j] = 0;
            ex2Input[i][j] = 0;
        }
    ex3BuyInput.clear();
    for (int i = 0; i < buyCodes.size(); ++i)
        ex3BuyInput.push_back("");
    ex3SellInput.clear();
    for (int i = 0; i < sellCodes.size(); ++i)
        ex3SellInput.push_back("");
}

bool ExData::importEx12Data(int k, QString dataFilePath)
{
    QFile dataFile;
    dataFile.setFileName(dataFilePath);
    if (dataFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        int i = 0;
        QString exDataStr[3][51];
        qlonglong exDataTmp[3][51];
        while (!dataFile.atEnd() && i < 51)
        {
            for (int j = 0; j < 3; ++j)
                exDataStr[j][i] = "0";
            QByteArray lineBytes = dataFile.readLine();
            QList<QByteArray> data = lineBytes.split('\t');
            if (data.size() < 3)
            {
                dataFile.close();
                return false;
            }
            else
            {
                for (int j = 0; j < 3; ++j)
                    exDataStr[j][i] = data.at(j);
            }
            ++i;
        }
        if (i < 51)
        {
            dataFile.close();
            return false;
        }
        bool isOk = true;
        if (k == 1)
        {
            for (int l = 0; l < 3; ++l)
                for (int m = 0; m < 51; ++m)
                {
                    exDataTmp[l][m] = exDataStr[l][m].toLongLong(&isOk);
                    if (!isOk)
                    {
                        dataFile.close();
                        return false;
                    }

                }
            for (int l = 0; l < 3; ++l)
                for (int m = 0; m < 51; ++m)
                    ex1Data[l][m] = exDataTmp[l][m];
        }
        else if (k == 2)
        {
            for (int l = 0; l < 3; ++l)
                for (int m = 0; m < 51; ++m)
                {
                    exDataTmp[l][m] = exDataStr[l][m].toLongLong(&isOk);
                    if (!isOk)
                    {
                        dataFile.close();
                        return false;
                    }
                }
            for (int l = 0; l < 3; ++l)
                for (int m = 0; m < 51; ++m)
                    ex2Data[l][m] = exDataTmp[l][m];
        }
        else
        {
            dataFile.close();
            return false;
        }
        dataFile.close();
        return true;
    }
    dataFile.close();
    return false;
}

bool ExData::importEx3Data(QString dataFilePath)
{
    QFile dataFile;
    dataFile.setFileName(dataFilePath);
    if (dataFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QList<QList<QByteArray>> erttmp;
        QMap<int, double> bm, sm;
        QMap<int, QByteArray> nm;
        QList<int> bcl, scl;
        QList<double> bdl, sdl;
        while (!dataFile.atEnd())
        {
            QByteArray lineBytes = dataFile.readLine();
            if (lineBytes.size() <= 0 || lineBytes.at(0) == '*')
                break;
            QList<QByteArray> data = lineBytes.split('\t');
            if (data.size() < 7)
            {
                dataFile.close();
                return false;
            }
            bool isOK = true;
            int code = data.at(0).toInt(&isOK);
            if (!isOK)
            {
                dataFile.close();
                return false;
            }
            double br = data.at(3).toDouble(&isOK);
            if (!isOK)
            {
                dataFile.close();
                return false;
            }
            double sr = data.at(5).toDouble(&isOK);
            if (!isOK)
            {
                dataFile.close();
                return false;
            }
            erttmp.push_back(data);
            bm.insert(code, br);
            sm.insert(code, sr);
            nm.insert(code, data.at(6));
        }
        if (erttmp.size() <= 0)
        {
            dataFile.close();
            return false;
        }
        while (!dataFile.atEnd())
        {
            QByteArray lineBytes = dataFile.readLine();
            if (lineBytes.size() <= 0 || lineBytes.at(0) == '*')
                break;
            QList<QByteArray> data = lineBytes.split('\t');
            if (data.size() < 2)
            {
                dataFile.close();
                return false;
            }
            bool isOK = true;
            int code = data.at(0).toInt(&isOK);
            if (!isOK || !nm.contains(code))
            {
                dataFile.close();
                return false;
            }
            double bd = data.at(1).toDouble(&isOK);
            if (!isOK)
            {
                dataFile.close();
                return false;
            }
            bcl.push_back(code);
            bdl.push_back(bd);
        }
        while (!dataFile.atEnd())
        {
            QByteArray lineBytes = dataFile.readLine();
            if (lineBytes.size() <= 0 || lineBytes.at(0) == '*')
                break;
            QList<QByteArray> data = lineBytes.split('\t');
            if (data.size() < 2)
            {
                dataFile.close();
                return false;
            }
            bool isOK = true;
            int code = data.at(0).toInt(&isOK);
            if (!isOK || !nm.contains(code))
            {
                dataFile.close();
                return false;
            }
            double sd = data.at(1).toDouble(&isOK);
            if (!isOK)
            {
                dataFile.close();
                return false;
            }
            scl.push_back(code);
            sdl.push_back(sd);
        }
        dataFile.close();
        ert.clear();
        ert.append(erttmp);
        buyRates.clear();
        buyRates.swap(bm);
        sellRates.clear();
        sellRates.swap(sm);
        codeNames.clear();
        codeNames.swap(nm);
        buyCodes.clear();
        buyCodes.append(bcl);
        sellCodes.clear();
        sellCodes.append(scl);
        buyCnts.clear();
        buyCnts.append(bdl);
        sellCnts.clear();
        sellCnts.append(sdl);
        ex3BuyAnswer.clear();
        for (int i = 0; i < buyCnts.size(); ++i)
            ex3BuyAnswer.push_back(QString::number(buyCnts.at(i) * buyRates.value(buyCodes.at(i), 0) / 100.0, 'f', 2));
        ex3SellAnswer.clear();
        for (int i = 0; i < sellCnts.size(); ++i)
            ex3SellAnswer.push_back(QString::number(sellCnts.at(i) / sellRates.value(sellCodes.at(i), 0) * 100, 'f', 2));
        return true;
    }
    dataFile.close();
    return false;
}
