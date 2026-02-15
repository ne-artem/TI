#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vigenere.h"
#include "playfair.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::processText(const QString &input) {
    int algorithmIdx = ui->comBoxAlgorithm->currentIndex();
    int modeIdx = ui->comBoxMode->currentIndex();
    QString key = ui->lineEditKey->text();

    if (key.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите ключ!");
        return QString();
    }

    // !!! ПРЕОБРАЗУЕМ ВХОДНОЙ ТЕКСТ В ВЕРХНИЙ РЕГИСТР !!!
    QString processedInput = input.toUpper();
    QString processedKey = key.toUpper();
    if (algorithmIdx == 0) { // Плейфейр (English)
        return (modeIdx == 0) ? Playfair::encryptPlayfair(processedInput, processedKey) : Playfair::decryptPlayfair(processedInput, processedKey);
    } else { // Виженер (Russian)
        return (modeIdx == 0) ? Vigenere::encryptVigenere(processedInput, processedKey) : Vigenere::decryptVigenere(processedInput, processedKey);
    }
}

void MainWindow::on_pushButExec_clicked() {
    // 1. Получаем входные данные из интерфейса
    QString input = ui->textEdit->toPlainText();
    if (input.isEmpty()) {
        QMessageBox::warning(this, "Внимание", "Введите текст в поле ввода!");
        return;
    }

    QString result = processText(input);

    if (!result.isNull()) {

        ui->textEditRes->setPlainText(result);


        QString outPath = QFileDialog::getSaveFileName(this, "Сохранить результат", "", "Text (*.txt)");

        if (outPath.isEmpty()) return;

        QFile fileOut(outPath);
        if (!fileOut.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::critical(this, "Ошибка", "Не удалось создать файл для записи!");
            return;
        }

        QTextStream out(&fileOut);
        out.setEncoding(QStringConverter::Utf8);
        out << result;
        fileOut.close();

        QMessageBox::information(this, "Успех", "Результат сохранен в файл.");
    }
}

void MainWindow::on_pushButExecFile_clicked() {

    QString inPath = QFileDialog::getOpenFileName(this, "Выберите файл", "", "Text (*.txt);;All Files (*)");
    if (inPath.isEmpty()) return;

    QString outPath = QFileDialog::getSaveFileName(this, "Сохранить результат", "", "Text (*.txt)");
    if (outPath.isEmpty()) return;

    QFile fileIn(inPath);
    if (!fileIn.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл для чтения!");
        return;
    }
    QTextStream in(&fileIn);
    in.setEncoding(QStringConverter::Utf8);
    QString inputData = in.readAll();
    fileIn.close();
    ui->textEdit->setPlainText(inputData);

    QString resultData = processText(inputData);
    if (resultData.isNull()) return;

    QFile fileOut(outPath);
    if (!fileOut.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось создать файл для записи!");
        return;
    }
    QTextStream out(&fileOut);
    in.setEncoding(QStringConverter::Utf8);
    out << resultData;
    fileOut.close();

    ui->textEditRes->setPlainText(resultData);
    QMessageBox::information(this, "Успех", "Файл обработан, результат сохранен и выведен на экран.");
}
