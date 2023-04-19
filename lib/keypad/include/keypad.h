#ifndef KEYPAD_H
#define KEYPAD_H




#include <iostream>
#include <pigpio.h>
#include <thread>
#include <QThread>

#define ROWS 4
#define COLS 3

int rowPin[ROWS] = { 7, 9, 11, 13 };
int colPin[COLS] = { 15, 17, 19 };

char keys[ROWS][COLS] = {
    { '1', '2', '3' },
    { '4', '5', '6' },
    { '7', '8', '9' },
    { '*', '0', '#' }
};

class KeypadThread : public QThread {
    Q_OBJECT
    public:
    KeypadThread(QObject *parent = 0)
        : QThread(parent) {}
        ~KeypadThread() {}

        signals:
            void keyPressed(char key);

    protected:
        void run() override {
        int rowPin[ROWS] = { 7, 9, 11, 13 };
        int colPin[COLS] = { 15, 17, 19 };

        char keys[ROWS][COLS] = {
                { '1', '2', '3' },
                { '4', '5', '6' },
                { '7', '8', '9' },
                { '*', '0', '#' }
            };

            Keypad keypad(rowPin, colPin, keys);
            keypad.start();

            while(!isInterruptionRequested()) {
                char key = keypad.readKey();
                if (key != '\0') {
                    emit keyPressed(key);
                }
                QThread::msleep(10);
            }

            keypad.stop();
            
        }
    
    };

class Keypad {
public:
    Keypad();
    ~Keypad();

    void start(); // start the keypad thread

    void stop(); // stop the keypad thread

private:
    std::thread keypadThread;

    char readKey(); // read the key pressed

    int main(); // main function of the keypad thread

};