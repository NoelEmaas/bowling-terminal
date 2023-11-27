#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define NUM_ROWS 50
#define NUM_COLS 35
#define NUM_PINS 10

typedef struct {
    bool is_knocked_down;
    int row;
    int col;
} Pin;

typedef struct {
    int row;
    int col;
    float speed;
    float spin;
} Ball;

typedef struct {
    Pin pins[NUM_PINS];
    Ball ball;
    int score;
} Frame;

typedef struct {
    char name[20];
    Frame frame;
} Player;

typedef struct {
    Player players[2];
} Game;

// Pin
Pin create_pin(int row, int col);
bool is_pins_at(int row, int col, Pin pins[NUM_PINS]);
void knock_down_pin(int row, int col, Pin *pin);
int get_pin_index_at(Pin pins[NUM_PINS], int row, int col);

// Ball
Ball create_ball(int row, int col, float speed, float spin);
bool is_ball_at(int row, int col, Ball ball);
void update_ball(Ball *ball);

// Frame
Frame create_frame();
void display_frame(Frame *frame);

// Player
Player create_player(char name[20], Frame frame);

// Game
Game create_game();

int main() {
    Game game = create_game();
    
    while (1) {
        // Update ball
        update_ball(&game.players[0].frame.ball);

        // Display game
        display_frame(&game.players[0].frame);

        // Sleep
        usleep(10000);
        system("clear");
    }

    return 0;
}

Pin create_pin(int row, int col) {
    return (Pin) {false, row, col};
}

Ball create_ball(int row, int col, float speed, float spin) {
    return (Ball) {row, col, speed, spin};
}

Frame create_frame() {
    Frame frame;

    // Initialize pins
    for (int i = 0; i < NUM_PINS; ++i) {
        // Place pins in triangle formation
        if (i < 4) {
            frame.pins[i] = create_pin(1, 2 + i * 10);
        } else if (i < 7) {
            frame.pins[i] = create_pin(4, 7 + (i - 4) * 10);
        } else if (i < 9) {
            frame.pins[i] = create_pin(7, 12 + (i - 7) * 10);
        } else {
            frame.pins[i] = create_pin(10, 17);
        }
    }

    // Initialize ball
    frame.ball = create_ball(NUM_ROWS - 1, NUM_COLS / 2 , 1, 0);

    // Initialize score
    frame.score = 0;

    return frame;
}

Player create_player(char name[20], Frame frame) {
    Player player;
    
    for (int i = 0; i < 20; ++i) {
        player.name[i] = name[i];
    }

    player.frame = frame;

    return player;
}

Game create_game() {
    Frame frame = create_frame();
    Player player1 = create_player("Player 1", frame);
    Player player2 = create_player("Player 2", frame);

    return (Game) {player1, player2};
}

void display_frame(Frame *frame) {
    for (int i = 0; i < NUM_ROWS; ++i) {
        for (int j = 0; j < NUM_COLS; ++j) {
            if (j % 5 == 0) {
                printf("|");
            }

            bool is_ball = is_ball_at(i, j, frame->ball);
            bool is_pin = is_pins_at(i, j, frame->pins);

            if (is_ball && is_pin) {
                // Get pin
                int pin_index = get_pin_index_at(frame->pins, i, j);
                knock_down_pin(i, j, &frame->pins[pin_index]);

                printf("O");
            } else if (is_ball) {
                printf("O");
            } else if (is_pin) {
                printf("X");
            } else {
                printf(" ");
            }

            if (j % 5 == 4 && j == NUM_COLS - 1) {
                printf("|");
            }
        }
        printf("\n");
    }
}

bool is_pins_at(int row, int col, Pin pins[NUM_PINS]) {
    for (int i = 0; i < NUM_PINS; ++i) {
        if (pins[i].row == row && pins[i].col == col && !pins[i].is_knocked_down) {
            return true;
        }
    }
    return false;
}

bool is_ball_at(int row, int col, Ball ball) {
    return ball.row == row && ball.col == col;
}

void knock_down_pin(int row, int col, Pin *pin) {
    pin->is_knocked_down = true;
}

int get_pin_index_at(Pin pins[NUM_PINS], int row, int col) {
    for (int i = 0; i < NUM_PINS; ++i) {
        if (pins[i].row == row && pins[i].col == col && !pins[i].is_knocked_down) {
            return i;
        }
    }
    return -1;
}

void update_ball(Ball *ball) {
    printf("%d\n", ball->row);
    ball->row -= ball->speed;
}