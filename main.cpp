#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<graphics.h>
#include<time.h>
#define SIZE 77
#define WIDTH SIZE+SIZE/2

double graphicSpeed = 0.000000000000000000001;
char visited = '#',rat = '0',wall = '0',right = 'r',left = 'l',up = 'u',down = 'd';
int ratColor = 14,grassColor = 8,grassHatch = 11,visitedColor = 8,visitedHatch = 0,mazeColor = 2,mazeBackground = 8,pathHatch = 9,x = 1,y = 0,d = 100;
int pixelSize = 10,gap = 0;
struct node{
    int data;
    struct node *link;
};
struct node *pathX;
struct node *pathY;
char maze[SIZE][WIDTH];
char visbinaryMaze[SIZE][WIDTH];
char binaryMaze[SIZE][WIDTH];

void printMaze(char maze[][WIDTH]){
    for(int i=0; i < SIZE;i++){
        for(int j=0; j < WIDTH; j++){printf("%c", maze[i][j]);}
    printf("\n");
    }
}
void initializer(){
    for (int i=0; i < SIZE ;i++){for (int j=0; j < WIDTH; j++){visbinaryMaze[i][j] = maze[i][j];}}
}
int isEmpty(struct node *top){
    if(top == NULL){return 1;}
    else return 0;
}
struct node *push(struct node* top, int data){
    struct node *temp = (node*)malloc(sizeof(struct node));
    if(temp == NULL){printf("Stack Overflow");}
    else{temp->data = data;temp->link = top;}
    return temp;
}
struct node *pop(struct node *top){
    struct node *temp = top;
    top = top->link;
    return top;
}
void createMaze(){
    srand(time(0));
    char walls[] = {'+', '-', '|', ' '};
    for (int i=0; i < SIZE ;i++){
        for (int j=0; j < WIDTH; j++){
            int condition = 0;
            if(i == 0 && j == 0) condition = 0;
            else if(i == 0 && j == WIDTH-1) condition = 0;
            else if(i == 0 && (j & 3) == 0) condition = 0;
            else if(j == 0 && (i & 1) == 0) condition = 0;
            else if(j == WIDTH - 1 && (i & 1) == 0) condition = 0;
            else if(i == SIZE -1 && (j & 3) == 0) condition = 0;
            else if((i & 1) == 0 && (j & 3) == 0) condition = 0;
            else if(i == SIZE - 2 && j == WIDTH-1) condition = 3;
            else if(i == 1 && j ==0) condition = 3;
            else if((i == 0 && (j & 3) != 0)||(i == SIZE - 1 && (j & 3) != 0)) condition = 1;
            else if((j == 0 && (i & 1) != 0)||(j == WIDTH-1 && (i & 1) != 0)) condition = 2;
            else if(rand()%2 == 0 && (j & 3) == 0) condition = 2;
            else if(rand()%2 == 0 && (i & 1) == 0) condition = 1;
            else if((j & 2) != 0) condition = 3;
            else condition = 3;
            maze[i][j] = walls[condition];
        }
    }
}

void createBinaryMaze(){
    for (int i=0; i < SIZE ;i++){
        for (int j=0; j < WIDTH; j++){
            if(maze[i][j] != ' '){binaryMaze[i][j] = '0';}
            else binaryMaze[i][j] = '1';}}
}
bool isSafe(char dir){
    int a = 0;
    int b = 0;
    if(dir == 'r'){a = 0; b = 1;}
    else if(dir == 'l'){a = 0; b = -1;}
    else if(dir == 'u'){a = -1; b = 0;}
    else if(dir  == 'd'){a = 1; b = 0;    }
    if((binaryMaze[x+a][y+b] == '1')&&(visbinaryMaze[x+a][y+b] != visited)){return true;}
    else return false;
}
void backtrack(){
    outtextxy(pixelSize,(SIZE*(pixelSize+gap))+30,"Backtracking...");
    visbinaryMaze[x][y] = visited;
    setfillstyle(visitedHatch, visitedColor);
    bar(pixelSize+(y*(pixelSize+gap)),pixelSize+((x)*(pixelSize+gap)),2*pixelSize+(y*(pixelSize+gap)),2*pixelSize+((x)*(pixelSize+gap)));
    pathX = pop(pathX);
    x = pathX->data;
    pathY = pop(pathY);
    y = pathY->data;
    setfillstyle(1,ratColor);
    bar(pixelSize+(y*(pixelSize+gap)),pixelSize+((x)*(pixelSize+gap)),2*pixelSize+(y*(pixelSize+gap)),2*pixelSize+((x)*(pixelSize+gap)));
}
void moveTo(char dir){
    int a = 0;
    int b = 0;
    if(dir == right){a = 0; b = 1;}
    else if(dir == left){a = 0; b = -1;}
    else if(dir == up){a = -1; b = 0;}
    else if(dir  == down){a = 1; b = 0;}
    pathX = push(pathX,x+a);
    pathY = push(pathY,y+b);
    setfillstyle(1,0);
    bar(0,(SIZE*(pixelSize+gap))+30,650,800);
    setfillstyle(pathHatch,grassColor);
    bar(pixelSize+(y*(pixelSize+gap)),pixelSize+((x)*(pixelSize+gap)),2*pixelSize+(y*(pixelSize+gap)),2*pixelSize+((x)*(pixelSize+gap)));
    setfillstyle(1,ratColor);
    bar(pixelSize+((y+b)*(pixelSize+gap)),pixelSize+((x+a)*(pixelSize+gap)),2*pixelSize+((y+b)*(pixelSize+gap)),2*pixelSize+((x+a)*(pixelSize+gap)));
    binaryMaze[x+a][y+b] = visited;
}
void initGraphics(){
    int gd,gm;
    detectgraph(&gd,&gm);
    initwindow(1200,800,"");
    for(int i = 0; i < SIZE ; i++)
        {for(int j = 0; j < WIDTH ; j++){
            if(binaryMaze[i][j] == '0'){setfillstyle(1,mazeColor);bar(pixelSize+(j*(pixelSize+gap)),pixelSize+(i*(pixelSize+gap)),2*pixelSize+(j*(pixelSize+gap)),2*pixelSize+(i*(pixelSize+gap)));}
            else if(binaryMaze[i][j] == '1'){setfillstyle(grassHatch,mazeBackground);bar(pixelSize+(j*(pixelSize+gap)),pixelSize+(i*(pixelSize+gap)),2*pixelSize+(j*(pixelSize+gap)),2*pixelSize+(i*(pixelSize+gap)));}}}
}
void graphics(char maze1[SIZE][WIDTH]){
    initGraphics();
    pathX = push(pathX,x);
    pathY = push(pathY,y);
    visbinaryMaze[x][y] = visited;
    while(!isEmpty(pathX)){
        if(x == SIZE - 2 && y == WIDTH - 1){outtextxy(pixelSize,(SIZE*(pixelSize+gap))+30,"Found the exit point!");outtextxy(pixelSize,(SIZE*(pixelSize+gap))+50,"Displaying the shortest path!");}
        else if((((binaryMaze[x+1][y] == '0')||(visbinaryMaze[x+1][y] == visited))&&((binaryMaze[x-1][y] == '0')||(visbinaryMaze[x-1][y] == visited))&&((binaryMaze[x][y+1] == '0')||(visbinaryMaze[x][y+1] == visited))&&((binaryMaze[x][y-1] == '0')||(visbinaryMaze[x][y-1] == visited)))){outtextxy(pixelSize,(SIZE*(pixelSize+gap))+30,"Path blocked!");outtextxy(pixelSize,(SIZE*(pixelSize+gap))+50,"Cannot find the exit!");}
        else if(isSafe(down)){moveTo(down);x++;}
        else if(isSafe(right)){moveTo(right);y++;}
        else if(isSafe(up)){moveTo(up);x--;}
        else if(isSafe(left)){moveTo(left);y--;}
        else{backtrack();}
        system("cls");
        delay(graphicSpeed);
    }
    return;
}
int main(){
    while(1){
        createMaze();
        createBinaryMaze();
        initializer();
        int ch;
        printf("\n1. Display the symbolic representation of the maze\n2. Display binary representation of the maze\n3. Start graphic animation\n4. Clear screen\n5. Reset the maze\n6. Exit\n\nEnter your choice: ");
        scanf("%d", &ch);
        switch(ch){
        case 1:
            printf("\n");
            printMaze(maze);
            break;
        case 2:
            printf("\n");
            printMaze(binaryMaze);
            break;
        case 3:
            printf("\n");
            graphics(maze);
            break;
        case 4:
            system("cls");
            break;
        case 5:
            printf("\n");
            createMaze();
            printMaze(maze);
            break;
        case 6:
            exit(0);
        default:
            printf("\n Invalid Input! \n");
        }
    }
    return 0;
}
