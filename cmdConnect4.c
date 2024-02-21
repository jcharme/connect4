/* Julia Ducharme 02/21/24

Takes as input a player's move and the current board and 
prints if the game is ongoing or if the game has ended.
*/
#include <stdio.h>

// Constant variables to make program easily modified
#define ROWS 6
#define COLS 7

int addMove(char grid[ROWS][COLS], int col, char player); // Adds move to board
char* checkGameStatus(char grid[ROWS][COLS]); // Checks the game status

int main (void){
    // Get the move as input
    char player;
    int col;
    scanf(" %c %d", &player, &col);

    // Initialize grid filled with .
    char grid[ROWS][COLS] = {{'.'}};

    // Fill the grid with user input
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            scanf(" %c", &grid[i][j]);
        }
    }

    // Add the move to the grid and print if it is illegal
    if (addMove(grid, col, player) == -1) {
        printf("Illegal move\n");
    } 
    // Print the game status
    else {
        printf("%s\n", checkGameStatus(grid));
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