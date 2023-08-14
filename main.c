#include <stdio.h>

// #####################
// #      @            #  
// #                   #  
// #                   #  
// #                   #  
// #                   #  
// #                   #  
// #                   #  
// #                   #  
// #                   #  
// #                   #  
// #####################
// Ange vad du vill göra:u + ENTER           
        
#define ROWS 10 //
#define COLS 30 //
#define WALL '#'

 

typedef struct{    
    unsigned char X; // 0.-255
    unsigned char Y; //
}Position;

// snake = dynamisk datastruktur 
// malloc?
typedef struct{
    Position pos[ROWS*COLS]; // 0 huvudet  size-1 svansen
    int size;
}Snake;

typedef enum {
    Snake_Direction_Left,    
    Snake_Direction_Right,
    Snake_Direction_Up,
    Snake_Direction_Down,
}Snake_Direction;

#define clrscr() printf("\e[1;1H\e[2J")
char getch(){
    char c;
    c= getchar();
    return(c);
}

void gotoxy(int x,int y){
    printf("%c[%d;%df",0x1B,y,x);
}

void drawBoundaries(){
    for(int row = 0; row < ROWS+2;row++){
        for(int col = 0; col < COLS+2; col++){
            if(row == 0 || row == ROWS+1 || col == 0 || col == COLS+1){
                printf("%c",WALL);         
            }
            else{
                printf(" ");
            }
        }
        printf("\n");
        
    }
}

void drawSnake(Snake *snake){
    for(int segment = 0; segment <= snake->size; segment++){
        gotoxy(snake->pos[segment].X, snake->pos[segment].Y);
        if(segment == 0)
            printf("@");
        else 
            printf("&");
    }

}

Snake_Direction getNextSnakeDirection(Snake_Direction currentSnakeDirection){
    gotoxy(0,ROWS+3);
    printf("Ange vad den ska göra:");
    char ch = getch(); // 
    fflush(stdin);
    if(ch == 'u') return Snake_Direction_Up;
    if(ch == 'd') return Snake_Direction_Down;
    if(ch == 'l') return Snake_Direction_Left;
    if(ch == 'r') return Snake_Direction_Right;
    return currentSnakeDirection;

}


void moveSnake(Snake *snake,Snake_Direction direction){
    // if(direction == Snake_Direction_Up){
    //     if(snake->Y == 2) snake->Y = ROWS+1;
    //     else snake->Y--;
    // }
    // if(direction == Snake_Direction_Down){
    //     if(snake->Y == ROWS+1) snake->Y = 2;
    //     else snake->Y++;
    // }
    // if(direction == Snake_Direction_Left){
    //     if(snake->X == 2) snake->X = COLS+1;
    //     else snake->X--;
    // }
    // if(direction == Snake_Direction_Right){
    //     if(snake->X == COLS+1) snake->X = 2;
    //     else snake->X++;
    // }

}


void snake_init(Snake *snake){
    // snake->size = 1;
    // snake->pos[0].X = 5;
    // snake->pos[0].Y = 5;    
    snake->size = 3;
    snake->pos[0].X = 5;
    snake->pos[0].Y = 5;    
    snake->pos[1].X = 4;
    snake->pos[1].Y = 5;    
    snake->pos[2].X = 3;
    snake->pos[2].Y = 5;    


}

int main(){
    Snake snake; // snake är en array med kroppsdelar - varje kroppsdel har en X och en Y
                    //   arrayen[0] = huvudet  12,10   array[1] = 11,10 array[2]=9,10
                        //           @@@
                        //             @@@@@  
    snake_init(&snake);


    Snake_Direction currentDirection = Snake_Direction_Right;

    while(1){
        clrscr();    // Motsvarar SLÄCK ALLA LEDS
        drawBoundaries();   // BEHÖVS INTE MNED LED MATRISEN
        drawSnake(&snake); // Tänd LEDDEN där den är
        // om tryckt på u snake.Y = snake.Y - 1
        gotoxy(0,0);
        currentDirection = getNextSnakeDirection(currentDirection);
        moveSnake(&snake,currentDirection);

        // sleep
    }

    return 0;
}