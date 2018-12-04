#include <GL/gl.h>
#include <GL/glut.h>
#include <windows.h>
#include <stdlib.h>
#include <ctime>
#include "RGBpixmap.cpp"


#define COLUMNS 70
#define ROWS 70

#define Max 20

#define UP 1
#define DOWN -1
#define RIGHT 2
#define LEFT -2

#define food_counter 4

int foodX,foodY;
bool food=true;




int FPS=30;
int Dir = RIGHT;
int SnakeLen=5;
int headX,headY;
int PosX[ROWS]={25,24,23,22,21};
int PosY[COLUMNS]={25,25,25,25,25};

int score=0;
RGBpixmap pix[6];
int fpst=2000;

bool gameOver=false;
void initGrid(int x,int y);
void drawGrid();
void drawFood();
void drawSnake();
void random(int &x,int &y);

void reshape_callback(int w, int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,COLUMNS,0,ROWS,-1,1);
    glMatrixMode(GL_MODELVIEW);
}

void display_callback()
{
    glClear(GL_COLOR_BUFFER_BIT);
   drawGrid();
    drawFood();
    //drawSnake();





    glBindTexture(GL_TEXTURE_2D,3);
	glEnable(GL_TEXTURE_2D);
    drawSnake();
    glDisable(GL_TEXTURE_2D);


    glutSwapBuffers();
    if(gameOver)
    {
        char _score[10];
        itoa(score,_score,10);
        char text[50]="Score : ";
        strcat(text,_score);
        MessageBox(NULL,text,"Game Over!",0);
        exit(0);
    }

}



void drawGrid()
{
    int x,y;
    glClearColor(1.0,.9,.7,255);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3ub(255,244,111);
    glLineWidth(1);
    glBegin(GL_LINES);

    for(x=0;x<ROWS;x++){
        for(y=0;y<COLUMNS;y++){

//            if(x==0 || y==0 || x==COLUMNS-1 || y==ROWS-1){
//                glLineWidth(1.0);
//                glColor3f(1,1,1);
//            }
//            else{
//                glLineWidth(1.0);
//                glColor3f(1,1,1);
//            }
            //glBegin(GL_LINE_LOOP);
            glVertex2f(x,y);
            glVertex2f(x,y+1);
            glVertex2f(x,y);
            glVertex2f(x+1,y);
        }
    }
    glEnd();


    for(x=0;x<ROWS;x++){
        for(y=0;y<COLUMNS;y++){
                if(x==0 || y==0 || x==ROWS-1 || y==COLUMNS-1){
                     glLineWidth(1.0);
                     glColor3ub(204,0,0);
                     glRectd(x,y,x+1,y+1);
                }
        }



    }
}

void drawFood()
{
    if(food){
        random(foodX,foodY);
        Beep(50000,30);
        FPS=FPS+2;
    }
    food=false;
    glColor3ub(55,155,75);
    if(score<food_counter)
        glRectf(foodX,foodY,foodX+2,foodY+2);

    glRectf(foodX,foodY,foodX+1,foodY+1);
}

void random(int &x,int &y)
{
    int _maxX=ROWS-2, _min=1;
    int _maxY=COLUMNS-2;
    srand(time(NULL));
    x = _min + rand() % (_maxX-_min);
    y = _min + rand() % (_maxY-_min);
}

void timerFunc(int)
{

    glutPostRedisplay();
    glutTimerFunc(2000/FPS,timerFunc,0);

}

void drawSnake()
{

    for(int i=SnakeLen-1;i>0;i--){
        PosX[i]=PosX[i-1];
        PosY[i]=PosY[i-1];
    }
    glColor3ub(153,76,0);
    if(Dir==UP)PosY[0]++;
    else if(Dir==DOWN)PosY[0]--;
    else if(Dir==RIGHT)PosX[0]++;
    else if(Dir==LEFT)PosX[0]--;

    for(int i=0;i<SnakeLen;i++){
        if(i==0)
            glColor3ub(102,51,0);
        else
            glColor3f(255,128,0);

        glRectd(PosX[i],PosY[i],PosX[i]+1,PosY[i]+1);
    }
    if(PosX[0]==1 || PosX[0]==ROWS-2||PosY[0]==1||PosY[0]==COLUMNS-2){
        gameOver=true;
    }
    for(int i=0;i<SnakeLen;i++){
        if(i==0){
            headX=PosX[0];
            headY=PosY[0];
        }
        if(i>0)
            if(headX==PosX[i] && headY==PosY[i])
            gameOver=true;
    }




    if(score>=food_counter)
    if(PosX[0]==foodX && PosY[0]==foodY){
       SnakeLen++;
       score++;
       if(SnakeLen>Max)
          SnakeLen=Max;

       food=true;
   }

   if(score<food_counter)
    if((PosX[0]==foodX && PosY[0]==foodY)||
       (PosX[0]==foodX+1 &&PosY[0]==foodY)||
       (PosX[0]==foodX &&PosY[0]==foodY+1)||
       (PosX[0]==foodX+1 &&PosY[0]==foodY+1))
   {

       SnakeLen++;
       score++;
       if(SnakeLen>Max)
          SnakeLen=Max;

       food=true;
   }




















}
void keyboard_callback(int key,int,int)
{
    switch(key)
    {
    case GLUT_KEY_UP:
        if(Dir!=DOWN)
            Dir=UP;
        break;
    case GLUT_KEY_DOWN:
        if(Dir!=UP)
            Dir=DOWN;
        break;
    case GLUT_KEY_RIGHT:
        if(Dir!=LEFT)
            Dir=RIGHT;
        break;
    case GLUT_KEY_LEFT:
        if(Dir!=RIGHT)
            Dir=LEFT;
        break;
    }
}

void init()
{
    glClearColor(1,1,1,1);
    //initGrid(COLUMNS,ROWS);
    glEnable(GL_TEXTURE_2D);


    pix[0].makeCheckImage();
	pix[0].setTexture(1);	// create texture int parameter as TextureName


    //pix[0].readBMPFile("teapot.bmp");
    //	pix[0].setTexture(1);



	pix[2].readBMPFile("C:\\snake\\snake.bmp");
	pix[2].setTexture(3);



}



int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  //  glutInitWindowPosition(100,100);
    glutInitWindowSize(600,600);
    glutCreateWindow("GameSnake");

    glutDisplayFunc(display_callback);
    glutReshapeFunc(reshape_callback);
    glutTimerFunc(0,timerFunc,0);
    glutSpecialFunc(keyboard_callback);
    init();
    glutMainLoop();
    return 0;
}
