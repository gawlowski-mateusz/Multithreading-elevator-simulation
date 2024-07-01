#include "Elevator.h"
#include <ncurses.h>
#include <unistd.h>

#include "../Client/Client.h"

Elevator::Elevator(const int x_initialise_position, const int y_initialise_position) {
    windowPosX = x_initialise_position;
    windowPosY = y_initialise_position;

    x_position = windowPosX / 2 - 6;
    y_position = windowPosY;

    x_vector_move = 0;
    y_vector_move = 1;

    capacity = 5;
    floor = -1;
}

Elevator::~Elevator() = default;

void Elevator::moveElevator() {
    x_position += x_vector_move;
    y_position += y_vector_move;

    setFlor();

    if (y_position == 1 || y_position == windowPosY * 0.75 || y_position == windowPosY * 0.5 || y_position == windowPosY
        * 0.25 || y_position == windowPosY - 1) {
        // pauseElevator();
    }

    if (y_position >= windowPosY) {
        y_position = 0;
    }
}

void Elevator::printElevator() const {
    move(y_position, x_position);
    printw("[     ]");
}

void Elevator::setFlor() {
    if (y_position == 1) {
        floor = 0;
    } else if (y_position == windowPosY * 0.25) {
        floor = 1;
    } else if (y_position == windowPosY * 0.50) {
        floor = 2;
    } else if (y_position == windowPosY * 0.75) {
        floor = 3;
    } else if (y_position == windowPosY - 1) {
        floor = 4;
    } else {
        floor = -1;
    }
}

int Elevator::getFloor() const {
    return floor;
}

int Elevator::getCapacity() const {
    return capacity;
}

void Elevator::printFloor() const {
    mvprintw(windowPosY - 1, 1, "%.3d", floor);
}

void Elevator::pauseElevator() {
    sleep(3);
}

void Elevator::releaseClient() {
    this->capacity += 1;
}

bool Elevator::isClientNerbyElevator(const Client *client) const {
    return (this->floor == 0) &&
           (client->x_position >= this->x_position && client->x_position <= this->x_position + 10);
}
