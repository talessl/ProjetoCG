//Compilar: g++ -o ilha ilha.cpp -lGL -lGLU -lglut
//rodar: ./ilha


#include <SDL2/SDL.h>  
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <cmath>
#include <stdio.h>


bool mouseIn = false;
float posCameraX, posCameraY , posCameraZ ; 
float camYaw = 0.0;
float camPitch = 0.0;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


void lockCamera();
void moveCamera(float, float);
void moveCameraUp(float, float);
//void control();
void updateCamera();

void init(void) 
{
   glClearColor (1.0, 1.0, 1.0, 1.0);
   
        // Habilita a definição da cor do material a partir da cor corrente
        glEnable(GL_COLOR_MATERIAL);
        //Habilita o uso de iluminação
        glEnable(GL_LIGHTING);  
        // Habilita a luz de número 0
        glEnable(GL_LIGHT0);
        // Habilita o depth-buffering
        glEnable(GL_DEPTH_TEST);
 
        // Habilita o modelo de colorização de Gouraud
        glShadeModel(GL_FLAT);
        posCameraX = 0.3;
		posCameraY = 0.1;
		posCameraZ = 0;

}

void DefineIluminacao (void)
{
		
		
        GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0}; 
        GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0}; // "cor" 
        GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0}; //"brilho" 
        GLfloat posicaoLuz[4]={0.0, 50.0, 50.0, 1.0};
 
        // Capacidade de brilho do material
        GLfloat especularidade[4]={1.0,1.0,1.0,1.0}; 
        GLint especMaterial = 60;
 
        // Define a refletância do material 
        glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
        // Define a concentração do brilho
        glMateriali(GL_FRONT,GL_SHININESS,especMaterial);
 
        // Ativa o uso da luz ambiente 
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
 
        // Define os parâmetros da luz de número 0
        glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente); 
        glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
        glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
        glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );   
        }


//camera


	
/*	

void control(float moveVelocity, float mouseVelocity, bool mi){
		if(mi){
		int MidX = 320;
		int MidY = 240;
		SDL_ShowCursor(SDL_DISABLE);
		int tmpX, tmpY;
		SDL_GetMouseState(&tmpX, &tmpY);
		camYaw += mouseVelocity*(MidX-tmpX);
		camPitch += mouseVelocity*(MidY-tmpY);
		lockCamera();
		SDL_WarpMouse(MidX,MidY);
		Uint8* state = SDL_GetKeyState(NULL);
		if(state[SDLK_w]){
			if(camPitch!=90 && camPitch!=-90){
			moveCamera(moveVelocity,0.0);
			moveCameraUp(moveVelocity, 0.0);
			}
			}
			else if(state[SDLK_s]){
				if(camPitch!=90 && camPitch!=-90){
				moveCamera(moveVelocity,180.0);
				moveCameraUp(moveVelocity, 180.0);
				}
				}
				else if(state[SDLK_a]){
					moveCamera(moveVelocity,90.0);
					}
					else if(state[SDLK_d]){
						moveCamera(moveVelocity,270);
						}
					}
		glRotatef(-camPitch,1.0,0.0,0.0);
		glRotated(-camYaw,0.0,1.0,0.0);
	}
*/
void updateCamera(){
		
		glTranslatef(-posCameraX, -posCameraY, -posCameraZ);
}

void moveCamera(float distance, float direction){

	float rad = (camYaw + direction)*M_PI/180.0;
	posCameraX -= sin(rad)*distance;
	posCameraY -= cos(rad)*distance;
}

void moveCameraUp(float distance, float direction){
	
	float rad = (camPitch + direction) * M_PI/180.0;
	posCameraY += sin(rad)*distance;
	}

void lockCamera(){
	if(camPitch>90)
	camPitch=90;
	if(camPitch<-90)
	camPitch=-90;
	if(camYaw<0.0)
	camYaw+=360.0;
	if(camYaw>360.0)
	camYaw>360.0;
	}
//camera

 
// Função responsável pela especificação dos parâmetros de iluminação

void specialKeys(int key, int x, int y)
{
	int moveVelocity = 0.2;
	int mouseVelocity = 0.2;
	
   switch (key) {
	   
		case GLUT_KEY_RIGHT : 
            moveCamera(moveVelocity,270);                 
            break; 

      case GLUT_KEY_LEFT : 
            moveCamera(moveVelocity,90.0);                     
            break; 
            
         
       case GLUT_KEY_UP : 
           if(camPitch!=90 && camPitch!=-90){
			moveCamera(moveVelocity,0.0);
			moveCameraUp(moveVelocity, 0.0);}                    
            break;    
        case GLUT_KEY_DOWN : 
            if(camPitch!=90 && camPitch!=-90){
				moveCamera(moveVelocity,180.0);
				moveCameraUp(moveVelocity, 180.0);}                     
            break;    
		
			
   }
   
    glRotatef(-camPitch,1.0,0.0,0.0);
	glRotated(-camYaw,0.0,1.0,0.0);
	glutPostRedisplay();
}

// Função que desenha o plano
void desenhaAgua() {
	
    
   glBegin(GL_QUAD_STRIP);
   
	glColor3f(0.0, 0.0, 1.0);
	glVertex3d(-1.0, 0.0, -1.0);
	glVertex3d(-1.0, 0.0, 1.0);
	glVertex3d(1.0, 0.0, -1.0);
	glVertex3d(1.0, 0.0, 1.0);
	
	
     
   glEnd();
   
}

void desenhaTerra(){
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_QUADS);			// Face posterior
	glNormal3f(0.0, 0.0, 1.0);	
	glVertex3f(0.8, 0.1, 0.8);
	glVertex3f(-0.8, 0.1, 0.8);
	glVertex3f(-0.8, 0, 0.8);
	glVertex3f(0.8, 0, 0.8);
	glEnd();


	glBegin(GL_QUADS);			// Face frontal
	glNormal3f(0.0, 0.0, -1.0); 	
	glVertex3f(0.8, 0.1, -0.8);
	glVertex3f(0.8, 0, -0.8);
	glVertex3f(-0.8, 0, -0.8);
	glVertex3f(-0.8, 0.1, -0.8);
	glEnd();
	glBegin(GL_QUADS);			// Face lateral esquerda
	glNormal3f(-1.0, 0.0, 0.0); 	
	glVertex3f(-0.8, 0.1, 0.8);
	glVertex3f(-0.8, 0.1, -0.8);
	glVertex3f(-0.8, 0, -0.8);
	glVertex3f(-0.8, 0, 0.8);
	glEnd();
	glBegin(GL_QUADS);			// Face lateral direita
	glNormal3f(1.0, 0.0, 0.0);	
	glVertex3f(0.8, 0.1, 0.8);
	glVertex3f(0.8, 0, 0.8);
	glVertex3f(0.8, 0, -0.8);
	glVertex3f(0.8, 0.1, -0.8);
	glEnd();
	glBegin(GL_QUADS);			// Face superior
	glNormal3f(0.0, 1.0, 0.0);  	
	glVertex3f(-0.8, 0.1, -0.8);
	glVertex3f(-0.8, 0.1, 0.8);
	glVertex3f(0.8, 0.1, 0.8);
	glVertex3f(0.8, 0.1, -0.8);
	glEnd();
	/*glBegin(GL_QUADS);			// Face inferior
	glNormal3f(0.0, -1.0, 0.0); 	
	glVertex3f(-0.8, 0, -0.8);
	glVertex3f(0.8, 0, -0.8);
	glVertex3f(0.8, 0, 0.8);
	glVertex3f(-0.8, 0, 0.8);
	glEnd();*/

	
}
	
	void reshape(int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   DefineIluminacao();
}

//exibe a cena
void display() {
	
	
	
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    DefineIluminacao();	
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	
    
    gluLookAt (posCameraX, posCameraY, posCameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//control(0.2,0.2,mouseIn);
	updateCamera();
    desenhaAgua();
    desenhaTerra();
    glBegin(GL_LINES);
        glColor3f (1.0, 0.0, 0.0);//vermelho x
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, 0.0);
        
        glColor3f (0.0, 1.0, 0.0); //verde y
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 1.0, 0.0);
      
        glColor3f (0.0, 0.0, 1.0);//azul z
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 1.0);    
    glEnd();
    glutSwapBuffers();
}






// Função principal
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow("Plano da Cena");
    
    init ();
	
   glutDisplayFunc(display); 
   glutSpecialFunc(specialKeys);
   glutReshapeFunc(reshape);
   
   
   glutMainLoop();
   
   return 0;
}
