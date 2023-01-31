#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->plainTextEdit);
    setWindowTitle("Notepad");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->plainTextEdit->setPlainText(QString());
}


void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open a file");
    QFile file(fileName);
    currentFile = fileName;
    if(!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString());
        return;
    }
    // else, assume file is open
    setWindowTitle(fileName);
    QTextStream is(&file);
    QString text = is.readAll();
    ui->plainTextEdit->setPlainText(text);
    file.close();
}


void MainWindow::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as", "", "Text files (*.txt)");
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file : " + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream os(&file);
    QString text = ui->plainTextEdit->toPlainText();
    os << text;
    file.close();
}


void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->plainTextEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->plainTextEdit->paste();
}


void MainWindow::on_actionCut_triggered()
{
    ui->plainTextEdit->cut();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->plainTextEdit->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->plainTextEdit->redo();
}

