#include "Client.h"
#include <cstdlib>
#include <ncurses.h>
#include <unistd.h>
using namespace std;

Client::Client(const int floor_destination, const int speed, const int x_initialise_position, const int y_initialise_position, const int client_id) {
    this->speed = speed;
    this->client_id = client_id;
    this->floor_destination = floor_destination;

    windowPosX = x_initialise_position;
    windowPosY = y_initialise_position;

    x_vector_move = 1;
    y_vector_move = 0;

    x_position = 1;
    y_position = 1;

    threadRunning = true;
    isInElevator = false;

    setRandomChar();
    setRandomColor();
}

Client::~Client() = default;

void Client::setRandomChar() {
    srand(time(nullptr));

    int random_ascii = rand() % ('z' - 'a' + 1) + 'a';
    c = static_cast<char>(random_ascii);
}

void Client::getOutOfElevator() {
    this->x_vector_move = -1;
    this->y_vector_move = 0;
    this->isInElevator = false;
    this->moveClient();
}

void Client::moveClient() {
    if (x_position == (windowPosX / 2) - 6) {
        x_vector_move = -1;
        y_vector_move = 0;
    }

    if (x_position == 0) {
        x_vector_move = 1;
    }

    if (x_position >= (windowPosX / 2) + 7) {
        x_vector_move = 1;
        y_vector_move = 0;
    }

    if (x_position == windowPosX - 1) {
        x_vector_move = 0;
        y_vector_move = 0;
        sleep(3);
        c = ' ';
    }

    x_position += x_vector_move;
    y_position += y_vector_move;
}


void Client::printClient() const {
    move(y_position, x_position);
    printw("%c", c);
}

int Client::getFloorDestination() const {
    return floor_destination;
}

int Client::getSpeed() const {
    return this->speed;
}

int Client::getID() const {
    return client_id;
}

void Client::setRandomColor() {
    color = rand() % 6 + 1;
}

int Client::getColor() const {
    return color;
}
