#ifndef CLIENT_H
#define CLIENT_H


#include <thread>
using namespace std;

class Client {
public:
    int x_position, y_position;
    int windowPosX, windowPosY;
    int x_vector_move, y_vector_move;
    int speed;
    int client_id;
    int floor_destination;
    bool isInElevator;
    bool threadRunning;
    int color{};
    char c{};
    thread thread_id;

    Client(int, int, int, int, int);

    ~Client();

    void moveClient();

    void printClient() const;

    int getFloorDestination() const;

    int getSpeed() const;

    int getID() const;

    void setRandomChar();

    void stopThread();

    bool isThreadRunning();

    thread runThread();

    void getOutOfElevator();

    void setRandomColor();

    int getColor() const;
};


#endif //CLIENT_H
