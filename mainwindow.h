#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void numberButtonClicked();
    void operationButtonClicked();
    void Bracket1Clicked();
    void Bracket2Clicked();
    void removeLastChar();
    void acButtonClicked();
    void dotButtonClicked();
    void evaluate();

private:
    Ui::MainWindow *ui;
    bool dot = false;
    bool operation_is_entered = true;
    bool answered = false;
    bool space_is_entered = false;
    int n_of_bracket = 0;
    int n_of_bracket1 = 0;
    double fnum, snum, bnum1, bnum2;

};
#endif // MAINWINDOW_H
