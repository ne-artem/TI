#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QFileDialog>
#include <QFileInfo>
#include <QFile>
#include "lfsr_generator.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

QString MainWindow::prepareSessionKey()
{
    QString rawInput = ui->textEditKey->toPlainText();

    QString filteredKey = rawInput.remove(QRegularExpression("[^01]"));

    if (filteredKey.length() < 32) {
        QMessageBox::critical(this, "Ошибка ключа",
                              QString("Длина ключа должна быть не менее 32 бит. Текущая длина: %1")
                                  .arg(filteredKey.length()));
        return QString();
    }

    if (filteredKey.length() > 32) {
        filteredKey = filteredKey.left(32);
    }

    return filteredKey;
}

void MainWindow::on_butExec_clicked()
{
    QString sessionKey = prepareSessionKey();
    if (sessionKey.isEmpty()) return;

    QString inputFilePath = QFileDialog::getOpenFileName(this,
                                                         tr("Выберите файл"), "", tr("Все файлы (*.*)"));
    if (inputFilePath.isEmpty()) return;

    QString outputFilePath = inputFilePath + ".result";

    LFSRGenerator generator;
    if (!generator.setSeed(sessionKey)) {
        QMessageBox::warning(this, "Ошибка", "Некорректный Seed");
        return;
    }

    QFile inFile(inputFilePath);
    QFile outFile(outputFilePath);

    if (!inFile.open(QIODevice::ReadOnly) || !outFile.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть файлы.");
        return;
    }

    ui->textEditKeySequence->clear();
    ui->textEditSrc->clear();
    ui->textEditRes->clear();

    const int blockSize = 4096; // Увеличим буфер для скорости
    long long bitsPrinted = 0;   // Счетчик выведенных бит
    const int maxBitsToPrint = 128;

    while (!inFile.atEnd()) {
        QByteArray dataBlock = inFile.read(blockSize);
        QByteArray resultBlock;
        resultBlock.reserve(dataBlock.size());

        for (int i = 0; i < dataBlock.size(); ++i) {
            uint8_t byteFromFile = static_cast<uint8_t>(dataBlock[i]);
            uint8_t keyByte = 0;
            //сборка ключа
            for (int b = 0; b < 8; ++b) {
                uint8_t bit = generator.getNextBit();
                // вывод
                if (bitsPrinted < maxBitsToPrint) {
                    ui->textEditKeySequence->insertPlainText(QString::number(bit));
                    bitsPrinted++;
                    if (bitsPrinted % 8 == 0) ui->textEditKeySequence->insertPlainText(" ");
                }

                keyByte = (keyByte << 1) | bit;
            }

            resultBlock.append(static_cast<char>(byteFromFile ^ keyByte));
        }

        // Выводим Src и Res
        if (bitsPrinted <= maxBitsToPrint) {
            ui->textEditSrc->insertPlainText(byteArrayToBinaryString(dataBlock.left(16)));
            ui->textEditRes->insertPlainText(byteArrayToBinaryString(resultBlock.left(16)));
        }

        outFile.write(resultBlock);

        // Обновляем GUI
        if (bitsPrinted % 1024 == 0) QCoreApplication::processEvents();
    }

    inFile.close();
    outFile.close();

    QMessageBox::information(this, "Успех", "Файл обработан. Первые 128 бит выведены на экран.");
}

QString MainWindow::byteArrayToBinaryString(const QByteArray &data) {
    QString res;
    for (int i = 0; i < data.size(); ++i) {
        res += QString("%1").arg(static_cast<uint8_t>(data[i]), 8, 2, QChar('0')) + " ";
    }
    return res;
}

MainWindow::~MainWindow()
{
    delete ui;
}
