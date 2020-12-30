#include <vector>
#include "../controller/Coordinates.h"

class Snake {
private:
    Coordinates *position;
    Coordinates *direction;

    std::vector<Coordinates *> *segments;
    std::vector<Coordinates *> *changeQueue;

    bool change;
public:
    Snake(int x, int y);

    ~Snake();

    void changeDirection();

    void grow();

    void moveSnake();

    Coordinates *getPosition();

    std::vector<Coordinates *> *getSegments();

    Coordinates *getDirection();

    std::vector<Coordinates *> *getChangeQueue() ;
};


