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

    void resizeEvent(QResizeEvent *event) override;

    void createOverlay();

private:
    Ui::MainWindow *ui;
    int wordCounter = 0;
    int typedLettersCounter = 0;
    int correctLettersCounter = 0;
    bool isStarted = false;

protected:
    void keyPressEvent(QKeyEvent *event) override;

    void loadWords();

    void setRandomWord();

private slots:
    void on_pushButton_clicked();
};
#endif // MAINWINDOW_H
