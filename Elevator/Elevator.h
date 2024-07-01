#ifndef ELEVATOR_H
#define ELEVATOR_H
#include <vector>


class Client;

class Elevator {
public:
    int x_position{}, y_position{};
    int floor;
    int x_window_size, y_window_size;
    int x_vector_move, y_vector_move;
    int clientInsideIndex = -1;
    int capacity;
    std::vector<int> clients_inside_elevator_id;
    // bool isOnFloor0;

    Elevator(int, int);

    ~Elevator();

    [[nodiscard]] int getFloor() const;

    [[nodiscard]] int getCapacity() const;

    void moveElevator();

    void printElevator() const;

    void setFloor();

    void printFloor() const;

    void releaseClient();

    [[nodiscard]] bool canClientEnterElevator() const;
};


#endif //ELEVATOR_H