#include <stdio.h>
#include <stdbool.h>

enum Cell {
    EMPTY = 0,
    PLAYER1 = 1,
    PLAYER2 = 2,
};

char convert(enum Cell cell) {
   switch (cell) {
       case EMPTY:
            return ' ';
       case PLAYER1:
            return 'x'; 
       case PLAYER2:
            return 'o';
   }
}

void display(enum Cell grid[3][3])  {
   printf("-------\n");
   for (size_t i = 0; i < 3; i++) {
        printf("|%c|%c|%c|\n", convert(grid[i][0]), convert(grid[i][1]), convert(grid[i][2]));
   }
   printf("-------\n");
} 

int player_input(bool player, enum Cell grid[3][3]) {   
    bool is_valid = false;
    while (!is_valid){
        printf("player %i: ", player + 1);
    
        int x = getchar() - '0';
        if (x == 'q') {
            getchar();
            return -1;
        }
        int y = getchar() - '0';
        // \n
        getchar();
        
        enum Cell *grid_pos = &grid[y - 1][x - 1];
        if (*grid_pos == EMPTY && !(x > 3 || x < 1) && !(y > 3 || y < 1)){
            *grid_pos = (!player) ? PLAYER1 : PLAYER2;
            is_valid = true;
        }
    }
    return 0;
}

int main(void) {
    enum Cell grid[3][3] = {
        {EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY},
    };
    
    while (true) {
        display(grid);
        int player1 = player_input(0, grid);
        display(grid);
        int player2 =  player_input(1, grid);
        if (player2 == -1 || player1 == -1) {
            break;
        }
    }

    return 0;
}