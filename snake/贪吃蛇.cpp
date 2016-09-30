
// *************************** 
// 罗晓峰 软工六班  中山大学 
// ************************** 

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<ctype.h>
#include<windows.h>

#define SNAKE_MAX_LENGTH 80
#define SNAKE_HEAD 'H'
#define SNAKE_BODY 'X'
#define BLANK_CELL ' '
#define SNAKE_FOOD '$'
#define WALL_CELL '*'
#define MAP_SIZE 20
#define MAX_restCounter ((snakeLength/2))

//snake stepping: dy = -1(up),1(down); dx = -1(left),1(right),0(no move)
void snakeMove(int, int);
//put a food randomized on a blank cell
void put_money(void);
//out cells of the grid
void output(void);
//outs when gameover
void gameover(void);
// auto go to the food
void autogo (void);
// check whethe the road can go
int IsAvailable(int , int );
//turn direction to coordinate
int tranX(int x, char dir);
int tranY(int y, char dir);
// initilize the map
void drawmap(void);
//the way to food
char route[MAP_SIZE * MAP_SIZE] = {'0'};
int routeCounter = 0;
char firstStep = 0;
// used to find road
int restLength = 0; 

char map[MAP_SIZE + 1][MAP_SIZE + 1] = 
    {"************",    
     "*XXXXH      ",
     "*           ",
     "*           ",
     "*           ",
     "*           ",
     "*           ",
     "*           ",
     "*           ",
     "*           ",
     "*           "};

//deside whether the point has been searched
char searched[MAP_SIZE + 1][MAP_SIZE + 1] = 
    {"************",    
     "*           ",
     "*           ",
     "*           ",
     "*           ",
     "*           ",
     "*           ",
     "*           ",
     "*           ",
     "*           ",
     "*           "};

//define vars for snake, notice name of vars in C
int snakeX[SNAKE_MAX_LENGTH] = {1,1,1,1,1};
int snakeY[SNAKE_MAX_LENGTH] = {1,2,3,4,5};
int snakeLength = 5;
int alive = 1;
char direction = 'D';
int foodX = 0;
int foodY = 0;

int main() {
  char ch = '0';
  int mode = 0;
  printf("please select mode: 0 for player, 1 for auto\n");
  do {
    scanf("%d", &mode);    
  } while ((mode != 0) && (mode != 1));
  drawmap();
  put_money(); 
  output();
  while (alive != 0) {
    if(mode == 0) {
      Sleep(200);
      if(kbhit()) {
        ch = getch();
        switch(ch) {
        case 'a':
        case 'A': if (direction == 'D') break; snakeMove(0, -1); direction = toupper(ch); break;
        case 's':
        case 'S': if (direction == 'W') break; snakeMove(1, 0); direction = toupper(ch);break;
        case 'd':
        case 'D': if (direction == 'A') break; snakeMove(0, 1); direction = toupper(ch);break;
        case 'w':
        case 'W': if (direction == 'S') break; snakeMove(-1, 0); direction = toupper(ch);break;
        }
      } else {
        switch(direction) {
        case 'A': snakeMove(0, -1); break;
        case 'S': snakeMove(1, 0); break;
        case 'D': snakeMove(0, 1); break;
        case 'W':  snakeMove(-1, 0) ;break;
      }
      output();
    }
      output();
    } else {
      Sleep(100);
      autogo();
    }
  }

  system("pause");
  gameover();
  return 0;
}

void snakeMove(int x, int y) {
  int i = 0;
  int tempX = 0;
  tempX = snakeX[snakeLength - 1] + x;
  int tempY = 0;
  tempY = snakeY[snakeLength - 1] + y;
  if ((map[tempX][tempY] == SNAKE_HEAD) || (map[tempX][tempY] == SNAKE_BODY) || (map[tempX][tempY] == WALL_CELL)) {
    alive = 0;
  } else if ((map[tempX][tempY] == SNAKE_FOOD) && (snakeLength < SNAKE_MAX_LENGTH)) {
    snakeLength++;
    snakeX[snakeLength - 1] = tempX;
    snakeY[snakeLength - 1] = tempY;
    map[tempX][tempY] = SNAKE_HEAD;
    map[snakeX[snakeLength - 2]][snakeY[snakeLength - 2]] = SNAKE_BODY;
    put_money();
  } else {
    if (map[tempX][tempY] == SNAKE_FOOD) put_money();
  map[snakeX[0]][snakeY[0]] = BLANK_CELL;
    for (i = 0; i < snakeLength - 1; i++) {
      snakeX[i] = snakeX[i + 1];
      snakeY[i] = snakeY[i + 1];
    }
    snakeX[snakeLength - 1] = snakeX[snakeLength - 1] + x;
    snakeY[snakeLength - 1] = snakeY[snakeLength - 1] + y;
    map[snakeX[snakeLength - 1]][snakeY[snakeLength - 1]] = SNAKE_HEAD;
    map[snakeX[snakeLength - 2]][snakeY[snakeLength - 2]] = SNAKE_BODY;
  }
}

void output(void) {
  int i ,j = 0;
  system("cls");
  for (i = 0; i < MAP_SIZE; i++) {
    for (j = 0; j < MAP_SIZE; j++) {
      printf("%c", map[i][j]);
    }
    printf("\n");
  }
  printf("current length : %d\n", snakeLength);
}

void gameover(void) {
  system("cls");
  printf("Gameover!\n");
  alive = 0;
}

void put_money(void) {
  srand(time(0));
  int x, y = 0;
  do {
    x = rand() % MAP_SIZE + 1;
    y = rand() % MAP_SIZE + 1;
  } while (map[x][y] != BLANK_CELL);
  map[x][y] = SNAKE_FOOD;
  foodX = x;
  foodY = y;
}

void autogo (void) {
  int i, j = 0;
  double ihold = 0;
  char chold = 0;
  char dir[5] = {'A', 'S', 'D',  'W'};
  int movable[5] = {0};
  double distance[5] = {0};
  map[snakeX[0]][snakeY[0]] = BLANK_CELL;
  
  distance[0] = abs((snakeX[snakeLength - 1]) - foodX) + abs((snakeY[snakeLength - 1] - 1) - foodY) - (abs(((snakeX[snakeLength - 1]) - foodX))?0:0.4) ;//- (abs((snakeY[snakeLength - 1] - 1 - foodY))?0:0.4);
  distance[1] = abs((snakeX[snakeLength - 1] + 1) - foodX) + abs((snakeY[snakeLength - 1]) - foodY) - (abs(((snakeX[snakeLength - 1] + 1) - foodX))?0:0.4);// - (abs((snakeY[snakeLength - 1] - foodY))?0:0.4);
  distance[2] = abs((snakeX[snakeLength - 1]) - foodX) + abs((snakeY[snakeLength - 1] + 1) - foodY) - (abs(((snakeX[snakeLength - 1] ) - foodX))?0:0.4) ;//- (abs((snakeY[snakeLength - 1] +1 - foodY))?0:0.4);
  distance[3] = abs((snakeX[snakeLength - 1] - 1) - foodX) + abs(snakeY[snakeLength - 1] - foodY) - (abs(((snakeX[snakeLength - 1] - 1) - foodX))?0:0.4) ;//- (abs((snakeY[snakeLength - 1] - foodY))?0:0.4);
  
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 3; j++) {    
      if (distance[j] > distance[j+1]) {
        ihold = distance[j];
        distance[j] = distance[j+1];
        distance[j+1] = ihold;
        
        chold = dir[j];
        dir[j] = dir[j+1];
        dir[j+1] = chold;
      }
    }   
  }

  for (i = 0; i < 4; i++) {     
    switch(dir[i]) { 
      case 'A':  movable[i] = IsAvailable(snakeX[snakeLength - 1], snakeY[snakeLength - 1] - 1); firstStep = 'A'; break;
      case 'S':  movable[i] = IsAvailable(snakeX[snakeLength - 1] + 1, snakeY[snakeLength - 1]); firstStep = 'S'; break;
      case 'D':  movable[i] = IsAvailable(snakeX[snakeLength - 1], snakeY[snakeLength - 1] + 1); firstStep = 'D'; break;
      case 'W':  movable[i] = IsAvailable(snakeX[snakeLength - 1] - 1, snakeY[snakeLength - 1]); firstStep = 'W'; break;
    }
    if (movable[i] == 1) {
        switch(firstStep) {
        case 'A': snakeMove(0, -1); break;
        case 'S': snakeMove(1, 0); break;
        case 'D': snakeMove(0, 1); break;
        case 'W':  snakeMove(-1, 0) ;break;
        }
        while (routeCounter != 0) {
          Sleep(100);
          switch(route[--routeCounter]) {
          case 'A': snakeMove(0, -1); break;
          case 'S': snakeMove(1, 0); break;
          case 'D': snakeMove(0, 1); break;
          case 'W':  snakeMove(-1, 0) ;break;
          }
         output();
        }
        break;
    }
  }
}

int IsAvailable(int x, int y) {
  int ok = 0;
  int used = 0;
  if (restLength < MAX_restCounter - 1) {
  used = 1;
  map[snakeX[restLength]][snakeY[restLength]] = BLANK_CELL;
  restLength++;
  }
  if (searched[x][y] == '*') {
    return 0;
  } else {
    searched[x][y] = '*';
    if ((map[x][y] == SNAKE_HEAD) || (map[x][y] == SNAKE_BODY) || (map[x][y] == WALL_CELL)) {
      ok = 0;
    } else if (map[x][y] == SNAKE_FOOD) {
      ok = 1;
    } else {
        int i = 0, j = 0;
        double ihold = 0;
        char chold = 0;
        char dir[5] = {'A', 'S', 'D',  'W'};
        int movable[5] = {0};
        double distance[5] = {0};
        distance[0] = abs(x - foodX) + abs((y - 1) - foodY) - (abs(x - foodX)?0:0.4) - (abs((y - 1) - foodY)?0:0.4);
        distance[1] = abs((x + 1) - foodX) + abs(y - foodY) - (abs(x + 1 - foodX)?0:0.4) - (abs((y) - foodY)?0:0.4);
        distance[2] = abs(x - foodX) + abs((y + 1) - foodY) - (abs(x - foodX)?0:0.4) - (abs((y + 1) - foodY)?0:0.4);
        distance[3] = abs((x - 1) - foodX) + abs(y - foodY) - (abs(x - 1 - foodX)?0:0.4) - (abs((y) - foodY)?0:0.4);
  
  
        for (i = 0; i < 4; i++) {
          for (j = 0; j < 3; j++) {    
            if (distance[j] >= distance[j+1]) {
              ihold = distance[j];
              distance[j] = distance[j+1];
              distance[j+1] = ihold;
          
              chold = dir[j];
              dir[j] = dir[j+1];
              dir[j+1] = chold;
            }
          }   
        }
          if (IsAvailable(tranX(x, dir[0]), tranY(y, dir[0]))) {
            route[routeCounter++] = dir[0];
            ok = 1;
          } else if (IsAvailable(tranX(x, dir[1]), tranY(y, dir[1]))) {
            route[routeCounter++] = dir[1];
            ok = 1;
          }else if (IsAvailable(tranX(x, dir[2]), tranY(y, dir[2]))) {
            route[routeCounter++] = dir[2];
            ok = 1;
          }else if ( IsAvailable(tranX(x, dir[3]), tranY(y, dir[3]))) {
            route[routeCounter++] = dir[3];
            ok = 1;
          } else {
          ok = 0;
          }
    }
  }
  if (used == 1) {
   restLength--;
   map[snakeX[restLength]][snakeY[restLength]] = SNAKE_BODY;
   used = 1;
 }
  searched[x][y] = ' ';
  return ok;
}

int tranX(int x, char dir) {
 switch(dir) { 
      case 'A': return x; break;
      case 'S': return x+1; break;
      case 'D': return x; break;
      case 'W': return x-1; break;
    } 
}

int tranY(int y, char dir) {
 switch(dir) { 
      case 'A': return y-1; break;
      case 'S': return y; break;
      case 'D': return y+1; break;
      case 'W': return y; break;
    } 
}

void drawmap(void) {
  srand(time(0));
  int i = 0;
  int j = 0;
  for (i = 0; i < MAP_SIZE; i++) {
    for (j = 0; j < MAP_SIZE; j++) {
      if ((i == 0) ||( j == 0) || (i == MAP_SIZE - 1) || (j == MAP_SIZE - 1)) {
        map[i][j] = '*';
        searched[i][j] = '*';
      } else {
        if ((rand() % 11)/10){
          map[i][j] = '*';
        } else {  
        map[i][j] = ' ';
        }  
        searched[i][j] = ' ' ;
      }
    }
  }
  map[1][1] = 'X';
  map[1][2] = 'X';
  map[1][3] = 'X';
  map[1][4] = 'X';
  map[1][5] = 'H';
  output();
} 
