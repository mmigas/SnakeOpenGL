

#ifndef SNAKEOPENGL_COORDINATES_H
#define SNAKEOPENGL_COORDINATES_H


class Coordinates {
private:
    int x;
    int y;
public:
    Coordinates(int x = 0, int y = 0);

    ~Coordinates();


    void setX(int x);

    int getX();

    void setY(int y);

    int getY();
};


#endif //SNAKEOPENGL_COORDINATES_H
