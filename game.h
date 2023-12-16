#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QKeyEvent>
#include <QDebug>
#include <QLabel>
#include <QTextDocument>
#include <QTextCursor>

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

protected:
    void keyPressEvent(QKeyEvent *event) override;

    void loadWords();

    void setRandomWord();

private:
    Ui::Game *ui;
    int wordCounter = 0;
    int typedLettersCounter = 0;
    int correctLettersCounter = 0;
    bool isStarted = false;
};

#endif // GAME_H
