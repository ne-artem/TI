#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButExec_clicked();     // Для работы с текстом в окне
    void on_pushButExecFile_clicked(); // Для работы с файлами

private:
    Ui::MainWindow *ui;

    // Основная логика распределения
    QString processText(const QString &input);
};
#endif // MAINWINDOW_H
