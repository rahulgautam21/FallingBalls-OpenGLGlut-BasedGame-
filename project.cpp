#include <stdio.h>
#include <time.h>
#include <GL/glut.h>
#include <unistd.h>
#include <iostream>
using namespace std;

float add1=3;
int points=0;
int points2=0;
GLbyte  lighton = true;
//0 for display 1 for points 2 for game over  
GLint  gameOver = 0;

GLfloat backr,backg,backb;
GLfloat br,bg,bb;
GLfloat br1,bg1,bb1;

int flag=0;
time_t seconds;

//x ranges from -40 to 200
//z ranges from -120 to 200
GLint   ballx[4];     
GLint   ballz[4];
GLint   ballx1[4];     
GLint   ballz1[4];
GLint   mballx;
GLint   mballz;   

// Screen variables
GLint   screeenw       = 800;
GLint   screeenh       = 550;

//Variables for the Camera Angle
static GLfloat camrotx=45.0F ;
static GLfloat camroty=0.0F ;
static GLfloat camrotz=0.0F ;

static GLfloat headRotation=90.0F ;
static GLfloat zoom=-300.0f;

void randx(){
    seconds++;
    time(&seconds);
    srand((unsigned int) seconds);
    //cout<<"$$$$$"<<rand()<<"$$$$$$$";
    for(int i=0;i<4;i++){
            ballx[i]=((rand()%240)-40);
            for(int j=0;j<i;j++){
                if((ballx[j]-ballx[i]) < 20 || (ballx[i]-ballx[j]) <20 )
                    ballx[i]=((rand()%240)-40);
            }
    }
}

void rc(){
    seconds++;
    time(&seconds);
    srand((unsigned int) seconds);
    for(int i=0;i<3;i++){
        if(i==0)
            backr=(rand()%10)*0.1;
        if(i==1)
            backg=(rand()%10)*0.1;
        if(i==2)
            backb=(rand()%10)*0.1;
    }
    glClearColor(backr, backg, backb, 1.0f);
}

void rc1(){
    seconds++;
    time(&seconds);
    srand((unsigned int) seconds);
    for(int i=0;i<6;i++){
        if(i==0)
            br=(rand()%10)*0.1;
        if(i==1)
            bg=(rand()%10)*0.1;
        if(i==2)
            bb=(rand()%10)*0.1;
        if(i==3)
            br1=(rand()%10)*0.1;
        if(i==4)
            bg1=(rand()%10)*0.1;
        if(i==5)
            bb1=(rand()%10)*0.1;
    }
}

void Write(char *string){//Write string on the screen
    while(*string)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string++);
}

void scorescreen(){

    char tmp_str[40];

    // Print the status of the game on the screen
    glColor3f(0, 1, 0);
    glRasterPos2f(0, -10);

    sprintf(tmp_str, "Your Total Points are: %d", points);
    Write(tmp_str);

    glColor3f(0, 0, 0);
    glRasterPos2f(-20, -30);    
    Write("***********To Return to main menu press 'S' or 's' **************");
    
}


void collision(){
    for(int i=0;i<4;i++){
        int x=ballx[i]-mballx;
        int z=ballz[i]-mballz;
        if(x<0)
            x=x*-1;
        if(z<0)
            z=z*-1;
        if( x<10 && z<10){
                gameOver=2;
        }
        x=ballx1[i]-mballx;
        z=ballz1[i]-mballz;
        if(x<0)
            x=x*-1;
        if(z<0)
            z=z*-1;
        if( x<10 && z<10){
                gameOver=2;
        }
    }
}

void randz(){
    seconds++;
    time(&seconds);
    srand((unsigned int) seconds);
    //cout<<"$$$$$"<<rand()<<"$$$$$$$";
    for(int i=0;i<4;i++){
            ballz1[i]=((rand()%120));
            if(i%2)
                ballz1[i]=-1*((rand()%120));
           
    }
}
//Configure window resize
void resize (int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1, 800.0);
}


//initialize the first configurations
void Initialize(void)
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(backr, backg, backb, 1.0f); //Change the background to sky blue
    if(lighton){
        glEnable(GL_COLOR_MATERIAL); //Enable color
        glEnable(GL_LIGHTING); //Enable lighting
        glEnable(GL_LIGHT0); //Enable light #0
        glEnable(GL_LIGHT1); //Enable light #1
        glEnable(GL_NORMALIZE); //Automatically normalize normals
    }
}

//This Function will rotate the object according to the Angles
void ManipulateViewAngle() {
    glRotatef(camrotx,1.0,0.0,0.0);//Rotate Arround X axis
    glRotatef(camroty,0.0,1.0,0.0);//Rotate Arround Y axis
    glRotatef(camrotz,0.0,0.0,1.0);//Rotate Arround Z axis
}


void restart(){
    add1=5;
    gameOver = 1;
    points=0;
    randz();
    randx();
    mballx=50;
    mballz=50;
    for(int i=0;i<4;i++){
        ballz[i]=-120;
        ballx1[i]=-40;
    }
    camrotx=45.0F ;
    camroty=0.0F ;
    camrotz=0.0F ;
    headRotation=90.0F ;
}

void gamestat(){
    char tmp_str[40];

    // Print the status of the game on the screen
    glColor3f(0, 1, 0);
    glRasterPos2f(0, -150);

    sprintf(tmp_str, "Points: %d", points);
    Write(tmp_str);
}

void drawball()
{
    points2++;
    if(points2==10){
        points2=0;
        points++;
    }
    collision();
    for(int i=0;i<4;i++){
        if(ballz[i]>120){
            randx();
            ballz[i]=-120;
        }
        if(ballx[i]>200){
            randx();
        }
        if(ballz1[i]>120){
            randz();
            ballx1[i]=-40;
        }
        if(ballx1[i]>200){
            ballx1[i]=-40;
            randz();
        }
    }
    char tmp_str[40];
    glPushMatrix();
        ManipulateViewAngle();
        glTranslatef(mballx,-10.0,mballz);
        glColor3f(br1, bg1, bb1);
        glScalef(1,1,1);
        glutSolidSphere(5,25,25);
    glPopMatrix();
    for(int i=0;i<4;i++){
        glPushMatrix();
        ManipulateViewAngle();
        glTranslatef(ballx1[i],-10.0,ballz1[i]);
        glColor3f(br, bg, bb);
        glScalef(1,1,1);
        glutSolidSphere(5,25,25);
        glPopMatrix();
    }
    for(int i=0;i<4;i++){
        glPushMatrix();
        ManipulateViewAngle();
        glTranslatef(ballx[i],-10.0,ballz[i]);
        glColor3f(br, bg, bb);
        glScalef(1,1,1);
        glutSolidSphere(5,25,25);
        glPopMatrix();
    }
}

//Configure the lightning
void addlight()
{
    //Add ambient light
    GLfloat ambientColor[] = {0.3f, 0.4f, 0.8f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

    //Add positioned light
    GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f};
    GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

    //Add directed light
    GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f};
    //Coming from the direction (-1, 0.5, 0.5)
    GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
}

//Display a welcome screen
void HomeScreen(){
    
    glColor3f(1, 0, 0);
    glRasterPos2f(-25, 20);
    Write("***************WELCOME TO Falling Balls**************");

    glColor3f(0, 0, 0);
    glRasterPos2f(-20, 0);
    Write("**************Instructions For Playing**************");

    glColor3f(0, 0, 0);
    glRasterPos2f(-20, -10);
    Write("Keys And Their Functions :-");

    glColor3f(0, 0, 0);
    glRasterPos2f(-20, -20);    
    Write("Start Playing = S ");

    glColor3f(0, 0, 0);
    glRasterPos2f(-20, -30);    
    Write("Quit Playing = ESC");
    
    glColor3f(0, 0, 0);
    glRasterPos2f(-20, -40);    
    Write("Arrow Keys For Movement");

    glColor3f(0, 0, 0);
    glRasterPos2f(-20, -50);    
    Write("Background Colour Change = C");

    glColor3f(0, 0, 0);
    glRasterPos2f(-20, -60);    
    Write("Balls Colour Change = B");
    
}

void Run(int value){
    //for(int i=0;i<4;i++)
    //    cout<<"%"<<i<<"&"<<"#"<<ballx[i]<<" "<<ballz[i];
    add1=add1+0.02;
    int x=1+add1;
    //ballx=ballx+1;
    for(int i=0;i<4;i++)
    ballz[i]=ballz[i]+add1;
    for(int i=0;i<4;i++)
    ballx1[i]=ballx1[i]+add1;
    //Set the Timer
    glutTimerFunc(130, Run, 0);
}

void keyboard (unsigned char key, int x, int y)
{
    switch (key) {

      case 'S'    : 
          if(gameOver==2){
            gameOver=0;
            return;
          }
          restart() ;
          glutPostRedisplay();
          break;
    case 's'    : 
          if(gameOver==2){
            gameOver=0;
            return;
          }  
          restart() ;
          glutPostRedisplay();
          break;
    case 'c'    : 
          rc();
          break;
    case 'C'    : 
          rc();
          break;
    case 'b'    : 
          rc1();
          break;
    case 'B'    : 
          rc1();
          break;
      //ESC to Exit
      case 27:
          exit(0);
          break;
      default:
          break;
    }
}

void keyin(int key, int x, int y){

    switch(key){
    case GLUT_KEY_RIGHT     :
            if(mballx<197)
            mballx+=3;
        break;
    case GLUT_KEY_LEFT      :
            if(mballx>-37)
            mballx-=3;
        break;
    case GLUT_KEY_UP        :
            if(mballz>-117)
            mballz-=3;
        break;
    case GLUT_KEY_DOWN      :
            if(mballz<117)
            mballz+=3;
        break;
    }
}

void drawgame(){
    glPushMatrix();
    ManipulateViewAngle();
        //This will draw the plane that the snake will run on.
        glPushMatrix();
        glColor3f(1, 0.7, 0.2);
        glTranslatef(75.0, 50.0, 75.0);
        glScalef(175,5.0,175);
        glutSolidCube(1);
        glPopMatrix();
    glPopMatrix();
}

void Display(void){//Draw Function
    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if(lighton) addlight();

    glTranslatef (-60.0, 40.0, zoom);
    //Check if the value of the Flag "Game Over is not True it will continue the game"
    if(gameOver==1){
        gamestat();
        
        drawgame();
	drawball();
    }
    else if(gameOver == 0)
        HomeScreen();
    else if(gameOver == 2){
        scorescreen();
    }

    // Updates the screen
    glutPostRedisplay();
    glutSwapBuffers();
}

int main(int argc, char **argv) {
	        glutInit(&argc, argv);
    backr=0.1;
    backg=1;
    backb=0.5;
    br=1;
    bg=0;
    bb=0;
    br1=0;
    bg1=0;
    bb1=1;
    randz();
    randx();
    mballx=50;
    mballz=50;
    for(int i=0;i<4;i++){
        ballz[i]=-120;
        ballx1[i]=-40;
    }
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(screeenw,screeenh);
    glutInitWindowPosition(80,80);
    glutCreateWindow("Falling Balls");
    glutSpecialFunc(keyin);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(Display);
    glutReshapeFunc(resize);

  //  newFood();
    Run(0);

    Initialize();
    glutMainLoop();
}