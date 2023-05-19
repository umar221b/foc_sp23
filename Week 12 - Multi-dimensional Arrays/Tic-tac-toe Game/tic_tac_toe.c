#include <stdio.h>

void printBoard(char board[3][3]);
int isGameOver(char board[3][3]);
int noMorePlaces(char board[3][3]);
char someoneWon(char board[3][3]);
char checkRow(char board[3][3], int row);
char checkCol(char board[3][3], int col);
char checkMainDiag(char board[3][3]);
char checkAntiDiag(char board[3][3]);
int invalidMove(char board[3][3], int move);
void makeMove(char board[3][3], int move, int turn);

int main() {
    char board[3][3] = { { '1', '2', '3' }, { '4', '5', '6' }, { '7', '8', '9' }};
    // variable to decide the turn. 0 means X and 1 means O
    int turn = 0;
    printf("Game has started\n");
    while (isGameOver(board) == 0) {
        printBoard(board);
        
        printf("Please play:\n");
        if (turn == 0)
            printf("It is X's turn.\n");
        else
            printf("It is O's turn.\n");
        
        // variable to hold the player's move location
        int move;
        scanf("%d", &move);
        
        // check if the move is valid, if not, continue to prompt the player for another move
        if (invalidMove(board, move) == 1)
            continue;
        
        // change the board according to the new move
        makeMove(board, move, turn);
        
        // switch turn to the next player
        if (turn == 0)
            turn = 1;
        else
            turn = 0;
    }

    // print the final board
    printBoard(board);
    
    // find the winner or whether the game ended in a tie
    char winner = someoneWon(board);
    if (winner == 'T')
        printf("It is a Tie.\n");
    else if (winner == 'X')
        printf("The winner is: X.\n");
    else
        printf("The winner is: O.\n");

    return 0;
}


// prints the game board
void printBoard(char board[3][3]) {
    printf("The board looks like this now:\n");
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (j != 0)
                printf(" ");
            
            printf("%c", board[i][j]);

            if (j < 2)
                printf(" |");
        }
        printf("\n");
        if (i < 2)
            printf("-- --- --\n");
    }
}

// checks whether the game is over yet
// game will be over in one of 2 cases:
// 1) There are no more places to play in
// 2) Someone has won
int isGameOver(char board[3][3]) {
    // Case 1: No more places to play
    int case1 = noMorePlaces(board);
    
    // Case 2: Someone won
    int case2 = someoneWon(board);
    
    // If case1 is 1, or case 2 is T, then game is over
    if (case1 == 1 || case2 != 'T')   
        return 1;
    return 0;
}

// check if any place on the board is not yet filled with X or O
// if there is one such place, return 0, meaning there are still places to play in
// if there is no such place, return 1, meaning that the game is over
int noMorePlaces(char board[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return 0;
        }
    }
    return 1;
}

// find if someone has won the game and who
// if any of the columns, rows, main-diagonal, or anti-diagonal have 3 matching elements
// then the game is over
// return 'X' if X won, 'O' if O won, and 'T if it is a tie (no one won)
char someoneWon(char board[3][3]) {
    char result;
    for (int i = 0; i < 3; ++i) {
        // check rows
        result = checkRow(board, i);
        if (result != 'T')
            return result;
        
        // check columns
        result = checkCol(board, i);
        if (result != 'T')
            return result;
    }

    // check main-diagonal
    result = checkMainDiag(board);
    if (result != 'T')
        return result;
    
    // check anti-diagonal
    result = checkAntiDiag(board);

    // return this regardless of what it is, if it is T then all
    // the above checks returned T too and it is a tie
    return result;
}

// checks one row for a winner, row is decided by the value passed in the parameter "row"
// return 'X' if X won, 'O' if O won, and 'T if no one won this row (yet)
char checkRow(char board[3][3], int row) {
    if (board[row][0] == board[row][1] && board[row][1] == board[row][2])
        return board[row][0];
    return 'T';
}

// checks one column for a winner, column is decided by the value passed in the parameter "col"
// return 'X' if X won, 'O' if O won, and 'T if no one won this column (yet)
char checkCol(char board[3][3], int col) {
    if (board[0][col] == board[1][col] && board[1][col] == board[2][col])
        return board[0][col];
    return 'T';
}

// checks the main-diagonal for a winner
// return 'X' if X won, 'O' if O won, and 'T if no one won this diagonal (yet)
char checkMainDiag(char board[3][3]) {
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return board[0][0];
    return 'T';
}

// checks the anti-diagonal for a winner
// return 'X' if X won, 'O' if O won, and 'T if no one won this diagonal (yet)
char checkAntiDiag(char board[3][3]) {
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return board[0][2];
    return 'T';
}

// check whether the move is valid or not
// a move is invalid if it is less than 1 or more than 9
// or is placed in a location that already contains an X or an O
// returns 1 if the move is invalid, or 0 if it is valid
int invalidMove(char board[3][3], int move) {
    if (move < 1 || move > 9)
        return 1;

    // subtract 1 to make the range from 0 to 8
    // this makes it easier to map 0-8 to the row and column indices - see below
    --move;
    
    
    //  0   1   2
    //  =   =   =
    //  3   3   3
    //  %   %   %
    //  ^   ^   ^
    //  |   |   |
    //  0 | 1 | 2  -> / 3 = 0
    //  -- --- --
    //  3 | 4 | 5  -> / 3 = 1
    //  -- --- --
    //  6 | 7 | 8  -> / 3 = 2

    int row = move / 3; // 0, 1, and 2 divided by 3 are 0, similar behaviour for the other rows
    int col = move % 3; // 0, 3, and 6 mod 3 are 0, similar behaviour for the other columns
    
    // if the place is already played in this is an invalid move
    if (board[row][col] == 'X' || board[row][col] == 'O')
        return 1;
    
    // if not, it is a valid move
    return 0;
}

// adds the player's move to the board
void makeMove(char board[3][3], int move, int turn) {
    char c = 'X';
    if (turn == 1)
        c = 'O';
    
    // similar to what we did when checking the invalid move
    --move;
    int row = move / 3;
    int col = move % 3;
    board[row][col] = c;
}