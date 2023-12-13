#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "overlay.h"

#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGraphicsOpacityEffect>

std::vector<std::string> words;
Overlay *overlayWidget;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadWords();
    setRandomWord();

    createOverlay();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::increaseWordCounter(){
    wordCounter++;
    ui->label_wordCounter->setText(QString::number(wordCounter));
}

void MainWindow::countAccuracy(const int typedLetters, const int correctLetters){
    int accuracy = correctLetters * 100 / typedLetters;
    ui->label_accuracy->setText(QString::number(accuracy) + "%");
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    if(overlayWidget != nullptr){
        overlayWidget->setFixedSize(this->size());
    }
}

void MainWindow::createOverlay()
{
    overlayWidget = new Overlay(this);
    overlayWidget->setFixedSize(this->size());
    overlayWidget->setStyleSheet("background-color: black;");

    this->stackUnder(overlayWidget);
}

void MainWindow::loadWords(){
    std::ifstream inputFile("/Users/alexeygolubev/Documents/programming/TypingSpeedTest/words.txt");

    if (!inputFile.is_open()) {
        qDebug() << "File is not oppened!";
        return;
    }

    std::string word;
    while (inputFile >> word) {
        words.push_back(word);
    }

    inputFile.close();
}

void MainWindow::setRandomWord()
{
    if (!words.empty()) {
        int randomIndex = std::rand() % words.size();
        std::string randomWord = words[randomIndex];
        ui->label->setText(QString::fromStdString(randomWord));
    } else {
        qDebug() << "No loaded words!";
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(!getIsStarted()){
        return;
    }

    static QString enteredWord = "";
    static int cursorPosition = 0;
    static QString necessaryWord = ui->label->text();

    QString keyText = event->text();

    increaseTypedLettersCounter();

    if(necessaryWord.at(cursorPosition) == keyText){
        enteredWord = enteredWord + keyText;
        ui->label_2->setText(enteredWord);
        cursorPosition++;
        increaseCorrectLettersCounter();
    }else{
        qDebug() << "Incorrect letter";
    }

    countAccuracy(getTypedLettersCounter(), getCorrectLettersCounter());

    if(cursorPosition >= necessaryWord.length()){
        setRandomWord();
        increaseWordCounter();
        cursorPosition = 0;
        necessaryWord = ui->label->text();
        enteredWord = "";
        ui->label_2->setText(enteredWord);
    }
}

void MainWindow::on_pushButton_clicked()
{
    changeStatusOfIsStarted();
}

