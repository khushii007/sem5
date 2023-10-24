#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define ROWS 3
#define COLS 3

// Structure to hold the game board
struct GameBoard {
    char board[ROWS][COLS];
};

// Function to initialize the shared memory
int init_shared_memory(key_t key, size_t size) {
    int shmid = shmget(key, size, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }
    return shmid;
}

// Function to attach the shared memory
struct GameBoard* attach_shared_memory(int shmid) {
    struct GameBoard *gameboard = shmat(shmid, (void *)0, 0);
    if ((void *)gameboard == (void *)-1) {
        perror("shmat");
        exit(1);
    }
    return gameboard;
}

// Function to display the game board
void display_board(struct GameBoard *gameboard) {
    printf("  1 2 3\n");
    for (int i = 0; i < ROWS; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < COLS; j++) {
            printf("%c ", gameboard->board[i][j]);
        }
        printf("\n");
    }
}

// Function to check if the game is over
int is_game_over(struct GameBoard *gameboard) {
    // Check for a win in rows
    for (int i = 0; i < ROWS; i++) {
        if (gameboard->board[i][0] == gameboard->board[i][1] && gameboard->board[i][1] == gameboard->board[i][2] && gameboard->board[i][0] != ' ') {
            return 1;  // A player has won
        }
    }

    // Check for a win in columns
    for (int j = 0; j < COLS; j++) {
        if (gameboard->board[0][j] == gameboard->board[1][j] && gameboard->board[1][j] == gameboard->board[2][j] && gameboard->board[0][j] != ' ') {
            return 1;  // A player has won
        }
    }

    // Check for a win in diagonals
    if ((gameboard->board[0][0] == gameboard->board[1][1] && gameboard->board[1][1] == gameboard->board[2][2] && gameboard->board[0][0] != ' ') ||
        (gameboard->board[0][2] == gameboard->board[1][1] && gameboard->board[1][1] == gameboard->board[2][0] && gameboard->board[0][2] != ' ')) {
        return 1;  // A player has won
    }

    // Check for a draw (all cells are filled)
    int draw = 1;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (gameboard->board[i][j] == ' ') {
                draw = 0;
                break;
            }
        }
        if (draw == 0) {
            break;
        }
    }

    if (draw) {
        return 1;  // The game is a draw
    }

    return 0;  // The game is not over yet
}

// Function for player's turn
void play_turn(struct GameBoard *gameboard, char player) {
    int row, col;

    while (1) {
        printf("Player %c, enter row (1-3) and column (1-3): ", player);
        scanf("%d %d", &row, &col);

        if (row >= 1 && row <= ROWS && col >= 1 && col <= COLS && gameboard->board[row - 1][col - 1] == ' ') {
            gameboard->board[row - 1][col - 1] = player;
            break;
        } else {
            printf("Invalid move. Try again.\n");
        }
    }
}

int main() {
    key_t key = 1234;
    size_t size = sizeof(struct GameBoard);

    int shmid = init_shared_memory(key, size);
    struct GameBoard *gameboard = attach_shared_memory(shmid);

    // Initialize the game board
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            gameboard->board[i][j] = ' ';
        }
    }

    char currentPlayer = 'X';

    while (1) {
        display_board(gameboard);
        play_turn(gameboard, currentPlayer);

        if (is_game_over(gameboard)) {
            display_board(gameboard);
            printf("Player %c wins!\n", currentPlayer);
            break;
        }

        // Toggle players
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    // Detach and remove shared memory
    shmdt(gameboard);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
