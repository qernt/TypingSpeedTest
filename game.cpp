#include "game.h"
#include "ui_game.h"

#include "timer.h"
#include "mainwindow.h"


#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

#include <QWidget>
#include <QThread>

std::vector<std::string> words;

const int TIMER_DURATION = 2;

QThread *timerThread;
Timer *timer;

Game::Game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
    setFocusPolicy(Qt::StrongFocus);

    ui->label_timer->setText(QString::number(TIMER_DURATION));

    loadWords();
    setRandomWord();
    startTimer();

    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);

    connect(timerThread, &QThread::started, timer, &Timer::start);
    connect(timer, &Timer::updateLabel, this, &Game::updateLabelSlot);
    connect(timer, &Timer::finished, mainWindow, &MainWindow::endGame);
}

Game::~Game()
{
    stopTimer();
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

Timer* Game::getTimer() const
{
    return timer;
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

void Game::updateLabelSlot(QString remainingTime)
{
    ui->label_timer->setText(remainingTime);
}

void Game::startTimer()
{
    timerThread = new QThread(this);
    timer = new Timer(TIMER_DURATION);
    timer->moveToThread(timerThread);
    timerThread->start();
}

void Game::stopTimer()
{
    if (timerThread->isRunning()) {
        timerThread->quit();
        timerThread->wait();
    }
    delete timerThread;
}
