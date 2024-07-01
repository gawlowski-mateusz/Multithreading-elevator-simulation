#include <ncurses.h>
#include <string>
#include <unistd.h>
#include <thread>
#include <vector>
#include <fstream>
#include "../Scene/Scene.h"
#include "../Elevator/Elevator.h"
#include "../Client/Client.h"

using namespace std;

Scene *scene;
Elevator *elevator;

vector<Client *> clients;
vector<thread> client_threads;

bool runFlag = true;
int counterClient = 0;

void moveElevator(Elevator *elevator) {
    while ((runFlag)) {
        elevator->moveElevator();
        usleep(1000000);
    }
}

void moveClient(Client *client) {
    while ((runFlag)) {
        if (client->isInElevator) {
            if (client->floor_destination == elevator->getFloor()) {
                client->getOutOfElevator();
                client->x_position += 1;
                client->x_vector_move = 1;
                elevator->releaseClient();
            }

            usleep(1000000);
        } else {
            if (elevator->isClientNerbyElevator(client)) {
                client->isInElevator = true;
                elevator->capacity -= 1;

                client->x_position = elevator->x_position + (elevator->getCapacity()) + 1;
                client->y_position = elevator->y_position ;
                client->x_vector_move = 0;
                client->y_vector_move = elevator->y_vector_move;

                if (elevator->getCapacity() < 0) {
                    elevator->releaseClient();
                    client->getOutOfElevator();
                    client->y_position = 1;
                    client->x_position -= (elevator->getCapacity() + 2);
                }
            }
        }

        client->moveClient();
        usleep(10000 * client->getSpeed());
    }
}

void makeNewLift() {
    int x_position = scene->getWidth();
    int y_position = scene->getHeight();

    elevator = new Elevator(x_position, y_position);
    moveElevator(elevator);

    usleep(80000);
}

void makeNewClient() {
    const int x_position = scene->getWidth();
    const int y_position = scene->getHeight();

    while (runFlag) {
        const int floor_destination = rand() % 4 + 1;
        const int speed = rand() % 5 + 1;
        const int time = rand() % 10 + 1;

        Client *client = new Client(floor_destination, speed, x_position, y_position, counterClient);
        clients.push_back(client);

        client_threads.push_back(thread(moveClient, clients.back()));

        sleep(time);
        counterClient++;
    }
}

void windowRefresh() {
    while (runFlag) {
        // erase();
        clear();

        elevator->printElevator();

        for (int i = 0; i < clients.size(); i++) {
            attron(COLOR_PAIR(clients[i]->getColor()));
            clients[i]->printClient();
            attroff(COLOR_PAIR(clients[i]->getColor()));
        }

        elevator->printFloor();
        scene->printScene();

        refresh();
        usleep(2000);
    }

    // erase();
    clear();
    endwin();
}

void exitProgram() {
    while (runFlag) {
        if (const int inputChar = getch(); inputChar == ' ') {
            runFlag = false;
        }
    }
}

int main() {
    srand(time(nullptr));
    scene = new Scene();

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);

    thread generateNewElevator(makeNewLift);
    thread generateClientThread(makeNewClient);
    thread windowRefreshThread(windowRefresh);
    thread exitProgramThread(exitProgram);

    generateNewElevator.join();
    generateClientThread.join();
    windowRefreshThread.join();
    exitProgramThread.join();

    for (int i = 0; i < client_threads.size(); i++) {
        client_threads[i].join();
    }

    endwin();

    return 0;
}