#include "game.h"
#include "ui_game.h"

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

Game::Game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
}

Game::~Game()
{
    delete ui;
}

void Game::increaseWordCounter()
{
    wordCounter++;
    ui->label_wordCounter->setText(QString::number(wordCounter));
}

void Game::countAccuracy(const int typedLetters, const int correctLetters)
{
    int accuracy = correctLetters * 100 / typedLetters;
    ui->label_accuracy->setText(QString::number(accuracy) + "%");
}

void Game::keyPressEvent(QKeyEvent *event)
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

void Game::loadWords()
{
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

void Game::setRandomWord()
{
    if (!words.empty()) {
        int randomIndex = std::rand() % words.size();
        std::string randomWord = words[randomIndex];
        ui->label->setText(QString::fromStdString(randomWord));
    }else{
        qDebug() << "No loaded words!";
    }
}
