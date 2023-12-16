#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QKeyEvent>
#include <QDebug>
#include <QLabel>
#include <QTextDocument>
#include <QTextCursor>

#include "timer.h"

namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();

    int getWordCounter() const{
        return wordCounter;
    }

    void increaseWordCounter();

    void countAccuracy(const int typedLetters, const int correctLetters);

    void increaseTypedLettersCounter(){
        typedLettersCounter++;
    }

    int getTypedLettersCounter() const{
        return typedLettersCounter;
    }

    void increaseCorrectLettersCounter(){
        correctLettersCounter++;
    }

    int getCorrectLettersCounter() const{
        return correctLettersCounter;
    }

    bool getIsStarted() const{
        return isStarted;
    }

    void changeStatusOfIsStarted(){
        if(isStarted){
            isStarted = false;
        }else{
            isStarted = true;
        }
    }

    Timer* getTimer() const;

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void loadWords();
    void setRandomWord();
    void updateLabelSlot(QString remainingTime);
    void startTimer();
    void stopTimer();

private:
    Ui::Game *ui;
    int wordCounter = 0;
    int typedLettersCounter = 0;
    int correctLettersCounter = 0;
    bool isStarted = true;
};

#endif // GAME_H
