#include "keypad.h"

Keypad::Keypad()
{
    gpioCfgClock(5,1,0);
    gpioSetMode(rowPin[0], PI_INPUT);
    gpioSetMode(rowPin[1], PI_INPUT);
    gpioSetMode(rowPin[2], PI_INPUT);
    gpioSetMode(rowPin[3], PI_INPUT);

    for (int row = 0; row < ROWS; row++) {
        gpioWrite(rowPin[row],1 );
    }
    for (int i = 0; i < COLS; i++) {
        gpioSetMode(colPin[i],PI_INPUT);
        gpioSetPullUpDown(colPin[i], PI_PUD_UP);
    }
}
Keypad::~Keypad()
{
    stop();
}

void Keypad::start() {
    thread_ = std::thread([this]() {
        while (true) {
            char key = readKey();

            if (key != '\0') {
                std::cout << "Key pressed: " << key << std::endl;
            }
        }
    });
}

void Keypad::stop() {
    if (thread_.joinable()) {
        thread_.join();
    }
}

char Keypad::readKey() {
    char key = '\0';

    for (int row = 0; row < ROWS; row++) {
        gpioWrite(rowPin[row], 0);

        for (int col = 0; col < COLS; col++) {
            if (gpioRead(colPin[col]) == 0) {
                key = keys[row][col];
                break;
            }
        }

        gpioWrite(rowPins_[row], 1);

        if (key != '\0') {
            break;
        }
    }

    return key;
}