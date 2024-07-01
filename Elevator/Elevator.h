#ifndef ELEVATOR_H
#define ELEVATOR_H
#include <vector>


class Client;

class Elevator {
public:
    int x_position{}, y_position{};
    int floor;
    int windowPosX, windowPosY;
    int x_vector_move, y_vector_move;
    int clientInsideIndex = -1;
    int capacity;

    std::vector<int> clients_inside_elevator_id;

    Elevator(int, int);

    ~Elevator();

    void moveElevator();

    void printElevator() const;

    void setFlor();

    [[nodiscard]] int getFloor() const;

    [[nodiscard]] int getCapacity() const;

    void printFloor() const;

    static void pauseElevator();

    void releaseClient();

    bool isClientNerbyElevator(const Client *) const;
};


#endif //ELEVATOR_H
