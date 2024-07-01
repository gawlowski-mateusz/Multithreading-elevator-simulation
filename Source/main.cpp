#include <ncurses.h>
#include <string>
#include <unistd.h>
#include <thread>
#include <vector>
#include <condition_variable>
#include <fstream>
#include <mutex>
#include <algorithm>

#include "../Scene/Scene.h"
#include "../Elevator/Elevator.h"
#include "../Client/Client.h"

using namespace std;

Scene *scene;
Elevator *elevator;

vector<Client *> clients;
vector<Client *> clients_elevator_queue;
vector<thread> client_threads;

mutex mtx;
condition_variable cv;

bool runFlag = true;
int counterClient = 0;

void printQueueToElevator() {
    for (int i = 0; i < clients_elevator_queue.size(); i++) {
        mvprintw(scene->getHeight() - 1, i + 1, "%1c", clients_elevator_queue[i]->getClientSymbol());
    }
}

void moveElevator(Elevator *elevator) {
    while (runFlag) {
        elevator->moveElevator();

        {
            unique_lock lock(mtx);
            if (elevator->canClientEnterElevator()) {
                cv.notify_all();
            }

            if (elevator->y_position == 0) {
                cv.notify_all();
            }
        }

        usleep(1000000);
    }
}

void moveClient(Client *client) {
    while (runFlag) {
        if (client->isInElevator) {
            if (client->floor_destination == elevator->getFloor()) {
                client->getOutOfElevator();
                client->x_position += 1;
                client->x_vector_move = 1;
                elevator->releaseClient();
            }

            usleep(1000000);
        } else {
            if (client->x_position == (scene->getWidth() / 2) - 7 && !client->isInQueueToElevator) {
                {
                    unique_lock lock(mtx);
                    client->isInQueueToElevator = true;
                    clients_elevator_queue.push_back(client);
                }

                // cv.notify_all();

                {
                    unique_lock lock(mtx);

                    cv.wait(lock, [&] {
                        return !runFlag || (elevator->canClientEnterElevator() && !clients_elevator_queue.empty() &&
                                            any_of(clients_elevator_queue.begin(), clients_elevator_queue.begin() + elevator->getCapacity(), [client](const auto& c)
                                                { return c->client_id == client->client_id; }));
                    });

                    if (any_of(clients_elevator_queue.begin(), clients_elevator_queue.begin() + elevator->getCapacity(), [client](const auto& c)
                        { return c->client_id == client->client_id; })) {
                        client->isInElevator = true;
                        elevator->capacity -= 1;

                        clients_elevator_queue.erase(find(clients_elevator_queue.begin(), clients_elevator_queue.end(), client));
                        client->x_position = elevator->x_position + (elevator->getCapacity()) + 1;
                        client->y_position = elevator->y_position;
                        client->x_vector_move = 0;
                        client->y_vector_move = elevator->y_vector_move;
                    }
                }
            }
        }

        client->moveClient();
        usleep(10000 * client->getSpeed());
    }
}

void makeNewElevator() {
    const int x_position = scene->getWidth();
    const int y_position = scene->getHeight();

    elevator = new Elevator(x_position, y_position);
    moveElevator(elevator);
}

void makeNewClient() {
    const int x_position = scene->getWidth();
    const int y_position = scene->getHeight();

    while (runFlag) {
        const int floor_destination = rand() % 4 + 1;
        const int speed = rand() % 5 + 1;
        const int time = rand() % 7 + 1;

        auto *client = new Client(floor_destination, speed, x_position, y_position, counterClient);
        clients.push_back(client);

        client_threads.push_back(thread(moveClient, clients.back()));

        sleep(time);
        counterClient++;
    }
}

void windowRefresh() {
    while (runFlag) {
        clear();

        elevator->printElevator();

        for (const auto &client : clients) {
            attron(COLOR_PAIR(client->getColor()));
            client->printClient();
            attroff(COLOR_PAIR(client->getColor()));
        }

        printQueueToElevator();
        elevator->printFloor();
        scene->printScene();

        refresh();
        usleep(1000);
    }

    clear();
    endwin();
}

void exitProgram() {
    while (runFlag) {
        if (const int inputChar = getch(); inputChar == ' ') {
            runFlag = false;

            {
                unique_lock lock(mtx);
                cv.notify_all();
            }
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

    thread generateNewElevator(makeNewElevator);
    thread generateClientThread(makeNewClient);
    thread windowRefreshThread(windowRefresh);
    thread exitProgramThread(exitProgram);

    generateNewElevator.join();
    generateClientThread.join();
    windowRefreshThread.join();
    exitProgramThread.join();

    for (auto &client_thread : client_threads) {
        client_thread.join();
    }

    endwin();

    return 0;
}
