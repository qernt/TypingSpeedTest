#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QDebug>
#include <QLabel>
#include <QTextDocument>
#include <QTextCursor>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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

private:
    Ui::MainWindow *ui;
    int wordCounter = 0;
    int typedLettersCounter = 0;
    int correctLettersCounter = 0;

protected:
    void keyPressEvent(QKeyEvent *event) override;

    void loadWords();

    void setRandomWord();
};
#endif // MAINWINDOW_H
