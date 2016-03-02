#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::gcdExtended(int a, int b, int *x, int *y)
{
    if (a == 0)
    {
        *x = 0, *y = 1;
        return b;
    }

    int x1, y1;
    int gcd = gcdExtended(b%a, a, &x1, &y1);

    *x = y1 - (b/a) * x1;
    *y = x1;

    return gcd;
}

int MainWindow::modInverse(int a, int m)
{
    int x, y;
    int res = 0;
    int gcd = gcdExtended(a, m, &x, &y);
    if (gcd == 1)
        res = (x%m + m) % m;
    return res;
}

void MainWindow::Inverter()
{
    int modmul = modInverse(ui->A->currentText().toInt(), 26);
    int modadd = 26 - ((ui->B->currentText().toInt() * modmul) % 26);
    ui->A->setCurrentText(QString::number(modmul));
    ui->B->setCurrentText(QString::number(modadd));
}

void MainWindow::encoder()
{
    int initcunt = ui->Input->toPlainText().size();
    QString text(ui->Input->toPlainText());
    ui->Output->clear();
    solbox_clear();
    write_to_solution("Coding equation: y = " +
                           QString::number(modmul) +
                           " \u2299 x \u2295 " + QString::number(modadd) + '\n');
    for (int initcont = 0; initcont != initcunt; initcont++)
    {
        char character = text.at(initcont).toUpper().unicode();
        char encrypted = character;
        char first_step;
        char second_step;
        if (character >= 'A' && character <= 'Z')
        {
            bool isLower = (bool)(text.at(initcont).unicode() / 91);
            if (character == 'Z')
                character = (char) 0;
            else
                character -= '@' ;
            first_step = (char)  ((modmul * character) % 26);
            encrypted = second_step = (char) (( first_step + modadd) % 26);
            if (encrypted == 0)
                encrypted = 'Z';
            else
                encrypted += '@';

            encrypted += (isLower * 32);
            write_to_solution(QString(encrypted) + "    =    " +
                              QString::number(second_step) + "    =    " +
                              QString::number(first_step) + " ⊕ " +
                              QString::number(modadd) + "    =    " +
                              QString::number(modmul) + " ⊙ " +
                              QString::number(character) + " ⊕ " +
                              QString::number(modadd) + '\n');
        }
        else
        {
            if (encrypted == ' ')
                ;
            else if(encrypted == '\n')
                write_to_solution("--------------------LINE END-------------------- \n\n");
            else if (ui->actionIgnore_Punctuation->isChecked() == true)
                continue;
            else
            write_to_solution(QString(encrypted) + "    =    copied, nothing done\n");
        }
        ui->Output->moveCursor (QTextCursor::End);
        ui->Output->insertPlainText (QChar(encrypted));
    }
    ScrollDown(ui->Output);
    return;
}

void MainWindow::SeparateFive(){
    if(ui->actionSplit_by_five->isChecked() == true){
        QString text(ui->Output->toPlainText());
        text.replace(" ", "");
        for (int x = (int) (text.length() / 5); x != 0; x--)
            text.insert(x * 5, " ");
        ui->Output->setPlainText(text);
    }
}

void MainWindow::write_to_solution(QString string)
{
    if (ui->soldock->isEnabled() == true) {
            ui->solutionbx->insertPlainText(string);
            ScrollDown(ui->solutionbx);
    }
}

void MainWindow::ScrollDown(QPlainTextEdit * TE){
    TE->verticalScrollBar()->setValue(TE->verticalScrollBar()->maximum());
}

void MainWindow::solbox_clear()
{
    if (ui->soldock->isVisible() == true) {
            ui->solutionbx->clear();
    }
}

void MainWindow::on_actionSolution_triggered()
{
    if (ui->actionSolution->isChecked() == true)
    {
        ui->soldock->setEnabled(true);
        ui->solutionbx->setEnabled(true);
        this->setFixedWidth(700);
    }
    else
    {
        ui->soldock->setEnabled(false);
        ui->solutionbx->setEnabled(false);
        this->setFixedWidth(370);
    }
    cenode();
}

void MainWindow::on_soldock_destroyed()
{
    ui->actionSolution->setChecked(false);
    ui->soldock->toggleViewAction()->toggle();
}

void MainWindow::on_Input_textChanged()
{
    if (automatic_translation == true)
        cenode();
}

void MainWindow::on_Inverse_clicked()
{
    Inverter();
    cenode();
}

void MainWindow::on_B_currentTextChanged(const QString &arg1)
{
    modadd = arg1.toInt();
    cenode();
}

void MainWindow::on_A_currentTextChanged(const QString &arg1)
{
    modmul = arg1.toInt();
    cenode();
}

void MainWindow::cenode(){
    encoder();
    SeparateFive();
}

void MainWindow::on_actionAll_Caps_triggered()
{
    ui->Input->setPlainText(ui->Input->toPlainText().toUpper());
    cenode();
}

void MainWindow::on_actionAll_Lower_triggered()
{
    ui->Input->setPlainText(ui->Input->toPlainText().toLower());
    cenode();
}

void MainWindow::on_actionAutomatic_Encode_triggered()
{
    ui->actencode->setEnabled(!ui->actencode->isEnabled());
    automatic_translation = ui->actionAutomatic_Encode->isChecked();
    if (automatic_translation == false)
        ui->actencode->setText("Encode!");
    else
        ui->actencode->setText("It's Automatic!");
    cenode();
}

void MainWindow::on_actencode_clicked()
{
    cenode();
}

void MainWindow::Aboutwidget_init(){
    Aboutfloating = new QDockWidget(this);
    Aboutfloating->setObjectName(QStringLiteral("Aboutfloating"));
    Aboutfloating->setGeometry(QRect(20, 170, 320, 121));
    Aboutfloating->setFixedSize(320,121);
    Aboutfloating->setAllowedAreas(Qt::NoDockWidgetArea);
    Aboutfloating->setAutoFillBackground(true);
    Aboutfloating->setFloating(true);
    Aboutfloating->setFeatures(QDockWidget::DockWidgetClosable|QDockWidget::DockWidgetMovable|
                               QDockWidget::DockWidgetFloatable );
    Aboutfloating->findChild<QAbstractButton*>("qt_dockwidget_floatbutton")->hide();
    AbtfloatingContents = new QWidget();
    AbtfloatingContents->setObjectName(QStringLiteral("AbtfloatingContents"));
    Abtlabel = new QLabel(AbtfloatingContents);
    Abtlabel->setObjectName(QStringLiteral("Abtlabel"));
    Abtlabel->setGeometry(QRect(10, 10, 280, 45));
    Abtlabel2 = new QLabel(AbtfloatingContents);
    Abtlabel2->setObjectName(QStringLiteral("Abtlabel2"));
    Abtlabel2->setGeometry(QRect(10, 60, 271, 21));
    Aboutfloating->setWidget(AbtfloatingContents);
    Aboutfloating->setWindowTitle(QApplication::translate("MainWindow", "About", 0));
    Abtlabel->setText(QApplication::translate("MainWindow", "Check out the View->Solutions and the Edit menu\n"
                                                            "Used Qt5.5 C++ and Yes, nakakabaliw yung C++", 0));
    Abtlabel2->setText(QApplication::translate("MainWindow", "ME - https://github.com/enriquezmark36/cenode", 0));
}

void MainWindow::on_actionME_triggered()
{
    if (Aboutfloating == NULL)
        Aboutwidget_init();
    if (Aboutfloating->isVisible() == true){
        Aboutfloating->deleteLater();
        Aboutfloating->close();
        Aboutfloating = NULL;
    }
    else{
        Aboutfloating->move(this->x() + ((this->width() - Aboutfloating->width()) / 2),
                            this->y() + (this->height() - Aboutfloating->height()) / 2);
        Aboutfloating->show();
    }
}

void MainWindow::on_actionSplit_by_five_triggered()
{
    cenode();
}

void MainWindow::on_actionIgnore_Punctuation_triggered()
{
    cenode();
}
