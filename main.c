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


void snake_move(Snake *snake,Snake_Direction direction){
    Position huvudPosition = snake->pos[0];

    if(direction == Snake_Direction_Up){
        if(huvudPosition.Y == 2) huvudPosition.Y = ROWS+1;
        else huvudPosition.Y--;
    }
    if(direction == Snake_Direction_Down){
        if(huvudPosition.Y == ROWS+1) huvudPosition.Y = 2;
        else huvudPosition.Y++;
    }
    if(direction == Snake_Direction_Left){
        if(huvudPosition.X == 2) huvudPosition.X = COLS+1;
        else huvudPosition.X--;
    }
    if(direction == Snake_Direction_Right){
        if(huvudPosition.X == COLS+1) huvudPosition.X = 2;
        else huvudPosition.X++;
    }
    // huvudposition 2,10
    // snake->pos[0].X/Y = Huvudet             3,10
    // snake->pos[1].X/Y = Segment 1           4,10  
    // snake->pos[2].X/Y = Svansen             5,10
    for(int segment = snake->size - 1; segment > 0; segment--)   {
        snake->pos[segment] = snake->pos[segment-1];
    }
    snake->pos[0] = huvudPosition;

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
        snake_move(&snake,currentDirection);

        // sleep
    }

    return 0;
}