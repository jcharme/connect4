/* Julia Ducharme 02/22/24

Play a game of connect 4 in the terminal. Alternates players, 
taking moves as input until the game has ended.
*/
#include <stdio.h>
#include <string.h>

// Constant variables to make program easily modified
#define ROWS 6
#define COLS 7

void printGrid(char grid[ROWS][COLS]); // Prints the game board
int addMove(char grid[ROWS][COLS], int col, char player); // Adds move to board
char* checkGameStatus(char grid[ROWS][COLS]); // Checks the game status

int main (void){
    // Initialize grid filled with .
    char grid[ROWS][COLS] = {0};

    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            grid[i][j] = '.';
        }
    }

    // Initialize the game status to "Ongoing game"
    char* gameStatus = "Ongoing game";

    // Initialize the player to 'X'
    char player = 'X';

    // Print the initial game board
    printf("Initial game board:\n");
    printGrid(grid);

    // Game loop
    while (strcmp(gameStatus, "Ongoing game") == 0) {
        // Get the move as input
        int col;
        printf("Player %c, enter your move (column number): ", player);
        scanf("%d", &col);

        // Add the move to the grid and print if it is illegal
        if (addMove(grid, col, player) == -1) {
            printf("Illegal move\n");
            continue;
        }

        // Print the updated game board
        printf("Updated game board:\n");
        printGrid(grid);

        // Check the game status
        gameStatus = checkGameStatus(grid);
        printf("%s\n", gameStatus);

        // Switch player
        player = (player == 'X') ? 'O' : 'X';
    }
}

// Function to print the game board
void printGrid(char grid[ROWS][COLS]) {
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }
}

// Function to add a move to the grid
// addMove(grid[][], col, player) returns 0 if the move is added to the grid 
//  successfully and -1 if there was an error
int addMove(char grid[ROWS][COLS], int col, char player) {
    if (col < 0 || col >= COLS) {
        return -1; // Invalid column
    }

    for (int i = ROWS-1; i >= 0; i--) {
        if (grid[i][col] == '.') {
            grid[i][col] = player;
            return 0; // Move added successfully
        }
    }
    return -1; // Column is full
}

// Function to check the game status
// checkGameStatus(grid[][]) returns the game status as a string
// requires: a grid filled with . or X or O
char* checkGameStatus(char grid[ROWS][COLS]){
    // Check for a win
    int full = 1; // board is full until proven wrong
    for (int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++){
            char player = grid[i][j];
            // Check for 4 in a row
            if (player == 'X' || player == 'O'){
                    // Horizontal
                if ((j + 3 < COLS && grid[i][j+1] == player && grid[i][j+2] == player && grid[i][j+3] == player) ||
                    // Vertical
                    (i + 3 < ROWS && grid[i+1][j] == player && grid[i+2][j] == player && grid[i+3][j] == player) ||
                    // Diagonal right (\)
                    (i + 3 < ROWS && j + 3 < COLS && grid[i+1][j+1] == player && grid[i+2][j+2] == player && grid[i+3][j+3] == player) ||
                    // Diagonal left (/)
                    (i - 3 >= 0 && j + 3 < COLS && grid[i-1][j+1] == player && grid[i-2][j+2] == player && grid[i-3][j+3] == player)){
                    return player == 'X' ? "X wins" : "O wins";
                }
            }
            // If there is a . in the grid, the grid isn't full
            else if (player == '.'){
                full = 0;
            }
        }
    }
    
    // Tie if the board is full
    if (full) {
        return "Tie game";
    }

    // If nothing returned, the game is ongoing
    return "Ongoing game";
}