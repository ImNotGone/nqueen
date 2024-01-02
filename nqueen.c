#include <stdio.h>
#include <stdlib.h>

enum {QUEEN = 'Q', EMPTY='_'};

#define FALSE 0
#define TRUE !FALSE

int nqueen(char ** board, int n);
void print_board(char ** board, int n);

int main(int argc, char * argv[]) {
    int n;
    if(argc != 2 || (n = atoi(argv[1])) <= 0) {
        printf("Usage \"%s <n>\"\n", argv[0]);
        printf("n beeing a number > 0\n");
        return 1;
    }

    printf("Trying to solve N queen problem for a board of %dx%d\n", n, n);

    char ** board = malloc(n*sizeof(char *));
    for (int i = 0; i < n; i++) {
        board[i] = malloc(n*sizeof(char));
    }
    
    for(int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = EMPTY;
        }
        
    }

    int solved = nqueen((char **)board, n);

    if (!solved) {
        printf("No solution was found for board of %dx%d\n", n, n);
        goto free;
    }
    printf("The following board represents a solution for %dx%d\n", n, n);
    print_board((char **)board, n);

free:
    for (int i = 0; i < n; i++) {
        free(board[i]);
    }
    
    free(board);
    return 0;
}

int queen_in_direction(char ** board, int n, int i, int j, int dir[2]) {
    while (i >= 0 && i < n && j >= 0 && j < n){
        if (board[i][j] == QUEEN) {
            return TRUE;
        }
        i += dir[0];
        j += dir[1];
    }
    return FALSE;
}

#define CANT_DIR 3
int can_place_queen(char ** board, int n, int i, int j) {
    int directions[CANT_DIR][2] = {{-1, 0}, {-1, -1}, {-1, 1}};
    for (int dir = 0; dir < CANT_DIR; dir++) {
        if(queen_in_direction(board, n, i, j, directions[dir])) {
            return FALSE;
        }
    }
    return TRUE;
}

int nqueen_rec(char ** board, int n, int i, int j) {
    if(i == n) {
        return TRUE;
    }
    for (; j < n; j++) {
        if(can_place_queen(board, n, i, j)) {
            board[i][j] = QUEEN;
            if(nqueen_rec(board, n, i+1, 0)) {
                return TRUE;
            }
            board[i][j] = EMPTY;
        }
    }
    return FALSE;
}

int nqueen(char ** board, int n) {
    return nqueen_rec(board, n, 0, 0);
}

void print_board(char ** board, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            putchar(board[i][j]);            
        }
        putchar('\n');
    }
}
