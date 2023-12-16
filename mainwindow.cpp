#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "game.h"
#include "overlay.h"
#include "timer.h"

Game *game;
Overlay *startOverlay;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    startOverlay = new Overlay(this);
    ui->verticalLayout->addWidget(startOverlay);

    connect(startOverlay->getPushButton(), &QPushButton::clicked, this, &MainWindow::startGame);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startGame()
{
    if(game != nullptr){
        return;
    }
    startOverlay->hide();
    game = new Game(this);
    ui->verticalLayout->addWidget(game);
}

void MainWindow::endGame()
{
    delete game;
    game = nullptr;

    startOverlay->show();
}

