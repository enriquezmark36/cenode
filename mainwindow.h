#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollBar>
#include <QTextCursor>
#include <QPlainTextEdit>
#include <QLabel>
#include <QSize>

namespace Ui {
class MainWindow;
}

class Solutions{
    public:

};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int gcdExtended(int a, int b, int *x, int *y);
    int modInverse(int a, int m);
    void Inverter();
    void encoder ();
    void write_to_solution(QString string);
    void solbox_clear();
    void ScrollDown(QPlainTextEdit * TE);
    void Aboutwidget_init();
    void cenode();
    void SeparateFive();

private slots:
    void on_actionSolution_triggered();

    void on_soldock_destroyed();

    void on_Input_textChanged();

    void on_Inverse_clicked();

    void on_B_currentTextChanged(const QString &arg1);

    void on_A_currentTextChanged(const QString &arg1);

    void on_actionAll_Caps_triggered();

    void on_actionAll_Lower_triggered();

    void on_actionAutomatic_Encode_triggered();

    void on_actencode_clicked();

    void on_actionME_triggered();

    void on_actionSplit_by_five_triggered();

    void on_actionIgnore_Punctuation_triggered();

private:
    Ui::MainWindow *ui;
    bool automatic_translation = true;
    static MainWindow* instance;
    int modadd = 1;
    int modmul = 1;
    QDockWidget *Aboutfloating = NULL;
    QWidget *AbtfloatingContents;
    QLabel *Abtlabel;
    QLabel *Abtlabel2;

};

#endif // MAINWINDOW_H
