#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stack>
#include <math.h>
#include <string>
#include <unordered_map>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->num0, SIGNAL(clicked()), this, SLOT(numberButtonClicked()));
    connect(ui->num1, SIGNAL(clicked()), this, SLOT(numberButtonClicked()));
    connect(ui->num2, SIGNAL(clicked()), this, SLOT(numberButtonClicked()));
    connect(ui->num3, SIGNAL(clicked()), this, SLOT(numberButtonClicked()));
    connect(ui->num4, SIGNAL(clicked()), this, SLOT(numberButtonClicked()));
    connect(ui->num5, SIGNAL(clicked()), this, SLOT(numberButtonClicked()));
    connect(ui->num6, SIGNAL(clicked()), this, SLOT(numberButtonClicked()));
    connect(ui->num7, SIGNAL(clicked()), this, SLOT(numberButtonClicked()));
    connect(ui->num8, SIGNAL(clicked()), this, SLOT(numberButtonClicked()));
    connect(ui->num9, SIGNAL(clicked()), this, SLOT(numberButtonClicked()));

    connect(ui->plus, SIGNAL(clicked()), this, SLOT(operationButtonClicked()));
    connect(ui->min, SIGNAL(clicked()), this, SLOT(operationButtonClicked()));
    connect(ui->mult, SIGNAL(clicked()), this, SLOT(operationButtonClicked()));
    connect(ui->div, SIGNAL(clicked()), this, SLOT(operationButtonClicked()));

    connect(ui->brc1, SIGNAL(clicked()), this, SLOT(Bracket1Clicked()));
    connect(ui->brc2, SIGNAL(clicked()), this, SLOT(Bracket2Clicked()));

    connect(ui->clear1, SIGNAL(clicked()), this, SLOT(removeLastChar()));
    connect(ui->dot, SIGNAL(clicked()), this, SLOT(dotButtonClicked()));
    connect(ui->equal, SIGNAL(clicked()), this, SLOT(evaluate()));

    connect(ui->clear_all, SIGNAL(clicked()), this, SLOT(acButtonClicked()));


}




MainWindow::~MainWindow()
{
    delete ui;
}

deque<QString> reverse_polish_notation(QString s){
    deque<QString> result;
    stack<QString> tmp;
    tmp.push("b");
    unordered_map<string, int> d =
    {{"bb", 4}, {"b+", 1}, {"b*", 1}, {"b/", 1}, {"b(", 1}, {"b)", 5}, {"++", 2}, {"+*", 1}, {"+/", 1},
     {"+b", 2}, {"+(", 1}, {"+)", 2}, {"*b", 2}, {"*+", 2}, {"**", 2}, {"*/", 2}, {"*(", 1}, {"*)", 2},
     {"/b", 2}, {"/+", 2}, {"/*", 2}, {"//", 2}, {"/(", 1}, {"/)", 2}, {"(b", 5}, {"(+", 1}, {"(*", 1},
     {"(/", 1}, {"((", 1}, {"()", 3}, {"-b", 2}, {"-+", 2}, {"--", 2}, {"-*", 1}, {"-/", 1}, {"-(", 1},
     {"-)", 2}, {"b-", 1}, {"+-", 2}, {"*-", 2}, {"/-", 2}, {"(-", 1}};
    s.replace("(","( ");
    s.replace(")"," )");
    s.append(" b");
    auto sl = s.split(" ");
    bool stop = false;
    while (!stop){
        auto i = sl.front();
        sl.pop_front();
        bool is_number;
        i.toDouble(&is_number);
        if (is_number){
            result.push_back(i);
        }
        else{
            auto com = tmp.top();
            tmp.pop();
            auto t = d.find((com + i).toStdString());
            switch (t->second) {
            case 1:
                tmp.push(com);
                tmp.push(i);
                break;
            case 2:
                result.push_back(com);
                sl.push_front(i);
                break;
            case 4:
                stop = true;
                break;
            case 5:
                throw std::invalid_argument("Не коректный ввод");
            }
        }
    }
    return result;
}




void MainWindow::numberButtonClicked()
{
     if (answered == false)
    {
        QPushButton* button = (QPushButton*)sender();
        QString numString = ui->expression->text() + button->text();
        ui->expression->setText(numString);
        operation_is_entered = false;
        space_is_entered = false;
    }
}

void MainWindow::operationButtonClicked()
{
       if (answered == false)
       {
            QPushButton* button = (QPushButton*)sender();
            QString oprString = ui->expression->text() + button->text();
            ui->expression->setText(oprString);
            operation_is_entered = true;
        }
}

void MainWindow::Bracket1Clicked()
{
    if (!answered)
    {
        ui->expression->setText(ui->expression->text() + "(");
        n_of_bracket++;
        n_of_bracket1++;
    }
}

void MainWindow::Bracket2Clicked(){
    if (n_of_bracket>0 && !answered){
        ui->expression->setText(ui->expression->text()+")");
        n_of_bracket--;
    }
}

void MainWindow::removeLastChar()
{
    QString exprStr = ui->expression->text();
    exprStr.remove(exprStr.length()-1, 1);
    ui->expression->setText(exprStr);
    if(operation_is_entered == true)
    {
        operation_is_entered = false;
    }
    else if(space_is_entered == true)
    {
        space_is_entered = false;
    }
    else if(dot == true)
    {
        dot = false;
    }
}

void MainWindow::acButtonClicked()
{
    dot = false;
    answered = false;
    operation_is_entered = true;
    space_is_entered = false;
    ui->expression->clear();
    ui->result->setText("");
}


void MainWindow::dotButtonClicked()
{
    if((dot == false) && (answered == false)){
        QPushButton* button = (QPushButton*)sender();
        QString point = ui->expression->text() + button->text();
        ui->expression->setText(point);
        dot = true;
}
}

void MainWindow::evaluate()
{
    QString r = ui->expression->text();
    if(!r.isEmpty())
    {
            if(answered == false && operation_is_entered == false){
            stack<QString> tmp;
            r.replace("+"," + ");
            r.replace("-"," - ");
            r.replace("*"," * ");
            r.replace("/"," / ");
            auto s1 = reverse_polish_notation(r);
            int n = s1.size();
            for(int i = 0; i < n; i++)
            {
                auto t = s1.front();
                s1.pop_front();
                bool is_number;
                t.toDouble(&is_number);
                if(is_number)
                {
                    tmp.push(t);
                }
                else {
                    QString n1, n2;
                    switch (t.toStdString().back()) {
                    case '+':
                        n1 = tmp.top(); tmp.pop();
                        n2 = tmp.top(); tmp.pop();
                        tmp.push(QString::number(n2.toDouble() + n1.toDouble()));
                        break;
                     case '-':
                        n1 = tmp.top(); tmp.pop();
                        n2 = tmp.top(); tmp.pop();
                        tmp.push(QString::number(n2.toDouble() - n1.toDouble()));
                        break;
                     case '/':
                        n1 = tmp.top(); tmp.pop();
                        n2 = tmp.top(); tmp.pop();
                        if (n1.toDouble() == 0)
                        {
                            ui->result->setText("Error!, You cant divide on zero!");
                            answered = true;
                            return;
                        }
                        tmp.push(QString::number(n2.toDouble() / n1.toDouble()));
                        break;
                     case '*':
                        n1 = tmp.top(); tmp.pop();
                        n2 = tmp.top(); tmp.pop();
                        tmp.push(QString::number(n2.toDouble() * n1.toDouble()));
                        break;
                    }
                }
            }
            ui->result->setText(tmp.top());
            answered = true;
        }
    }
}
