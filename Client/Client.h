#ifndef CLIENT_H
#define CLIENT_H


#include <thread>
using namespace std;

class Client {
public:
    int x_position, y_position;
    int x_window_size, y_window_size;
    int x_vector_move, y_vector_move;
    int speed;
    int client_id;
    int floor_destination;
    int color{};
    bool isInElevator;
    bool isInQueueToElevator;
    bool threadRunning;
    char c{};
    thread thread_id;

    Client(int, int, int, int, int);

    ~Client();

    [[nodiscard]] int getFloorDestination() const;

    [[nodiscard]] int getSpeed() const;

    [[nodiscard]] int getID() const;

    [[nodiscard]] int getColor() const;

    [[nodiscard]] char getClientSymbol() const;

    void moveClient();

    void goToQueue();

    void printClient() const;

    void setRandomChar();

    void getOutOfElevator();

    void correctOutOfElevatorPosition();

    void setRandomColor();
};


#endif //CLIENT_H
