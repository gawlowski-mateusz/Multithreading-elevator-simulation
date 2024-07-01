#include "Client.h"
#include <cstdlib>
#include <mutex>
#include <ncurses.h>
#include <unistd.h>
using namespace std;

mutex floor_1_client_1, floor_1_client_2, floor_1_client_3, floor_1_client_4, floor_1_client_5;
mutex floor_2_client_1, floor_2_client_2, floor_2_client_3, floor_2_client_4, floor_2_client_5;
mutex floor_3_client_1, floor_3_client_2, floor_3_client_3, floor_3_client_4, floor_3_client_5;
mutex floor_4_client_1, floor_4_client_2, floor_4_client_3, floor_4_client_4, floor_4_client_5;

Client::Client(const int floor_destination, const int speed, const int x_initialise_position,
               const int y_initialise_position, const int client_id) {
    this->speed = speed;
    this->client_id = client_id;
    this->floor_destination = floor_destination;

    x_window_size = x_initialise_position;
    y_window_size = y_initialise_position;

    x_vector_move = 1;
    y_vector_move = 0;

    x_position = 1;
    y_position = 1;

    threadRunning = true;
    isInElevator = false;
    isInQueueToElevator = false;

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
    correctOutOfElevatorPosition();
    this->isInElevator = false;
    this->moveClient();
}

void Client::correctOutOfElevatorPosition() {
    if (this->getFloorDestination() == 1) {
        this->y_position = y_window_size * 0.25 - 1;
    } else if (this->getFloorDestination() == 2) {
        this->y_position = y_window_size * 0.50 - 1;
    } else if (this->getFloorDestination() == 3) {
        this->y_position = y_window_size * 0.75 - 1;
    } else {
        this->y_position = y_window_size - 2;
    }

    this->x_vector_move = -1;
    this->y_vector_move = 0;
}

void Client::moveClient() {
    if (x_position == (x_window_size / 2) - 7) {
        x_vector_move = 0;
        y_vector_move = 0;
    }

    if (x_position == x_window_size - 6) {
        goToQueue();
    }

    x_position += x_vector_move;
    y_position += y_vector_move;
}

void Client::goToQueue() {
    x_vector_move = 0;
    y_vector_move = 0;

    if (floor_destination == 1) {
        // position 5
        floor_1_client_5.lock();
        x_position++;

        // position 4
        floor_1_client_4.lock();
        floor_1_client_5.unlock();
        x_position++;

        // position 3
        floor_1_client_3.lock();
        floor_1_client_4.unlock();
        x_position++;

        // position 2
        floor_1_client_2.lock();
        floor_1_client_3.unlock();
        x_position++;

        // position 1 - finish
        floor_1_client_1.lock();
        floor_1_client_2.unlock();
        x_position++;
        sleep(3);
        floor_1_client_1.unlock();
        c = ' ';
        y_position++;
    } else if (floor_destination == 2) {
        // position 5
        floor_2_client_5.lock();
        x_position++;

        // position 4
        floor_2_client_4.lock();
        floor_2_client_5.unlock();
        x_position++;

        // position 3
        floor_2_client_3.lock();
        floor_2_client_4.unlock();
        x_position++;

        // position 2
        floor_2_client_2.lock();
        floor_2_client_3.unlock();
        x_position++;

        // position 1 - finish
        floor_2_client_1.lock();
        floor_2_client_2.unlock();
        x_position++;
        sleep(3);
        floor_2_client_1.unlock();
        c = ' ';
        y_position++;
    } else if (floor_destination == 3) {
        // position 5
        floor_3_client_5.lock();
        x_position++;

        // position 4
        floor_3_client_4.lock();
        floor_3_client_5.unlock();
        x_position++;

        // position 3
        floor_3_client_3.lock();
        floor_3_client_4.unlock();
        x_position++;

        // position 2
        floor_3_client_2.lock();
        floor_3_client_3.unlock();
        x_position++;

        // position 1 - finish
        floor_3_client_1.lock();
        floor_3_client_2.unlock();
        x_position++;
        sleep(3);
        floor_3_client_1.unlock();
        c = ' ';
        y_position++;
    } else if (floor_destination == 4) {
        // position 5
        floor_4_client_5.lock();
        x_position++;

        // position 4
        floor_4_client_4.lock();
        floor_4_client_5.unlock();
        x_position++;

        // position 3
        floor_4_client_3.lock();
        floor_4_client_4.unlock();
        x_position++;

        // position 2
        floor_4_client_2.lock();
        floor_4_client_3.unlock();
        x_position++;

        // position 1 - finish
        floor_4_client_1.lock();
        floor_4_client_2.unlock();
        x_position++;
        sleep(3);
        floor_4_client_1.unlock();
        c = ' ';
        y_position++;
    }
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

char Client::getClientSymbol() const {
    return c;
}

void Client::setRandomColor() {
    color = rand() % 6 + 1;
}

int Client::getColor() const {
    return color;
}