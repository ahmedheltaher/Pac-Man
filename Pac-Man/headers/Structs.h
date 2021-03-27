#ifndef STRUCTS_H
#define STRUCTS_H

enum struct Direction {
    LEFT = -2,
    UP = -1,
    NONE = 0,
    DOWN = 1,
    RIGHT = 2
};


struct Position {
	float x;
	float y;
};

struct Size {
	int width;
	int height;
};

struct Padding {
    int left;
    int top;
};

#endif // !STRUCTS
