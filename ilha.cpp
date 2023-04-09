#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>


float posCameraX, posCameraY, posCameraZ;

void init(void) 
{
   glClearColor (1.0, 1.0, 1.0, 0.0);
   //inicializa posição da câmera
    posCameraX = 0.3;
    posCameraY = 0.1;
    posCameraZ = 0;

}

void specialKeys(int key, int x, int y)
{
   float angulo = 2*M_PI/180;
   switch (key) {
	   //gira em torno de y
		case GLUT_KEY_RIGHT : 
            posCameraX =  posCameraX*cos(angulo) + posCameraZ*sin(angulo);
            posCameraZ = -posCameraX*sin(angulo) + posCameraZ*cos(angulo);                   
            break; 

      case GLUT_KEY_LEFT : 
            posCameraX =  posCameraX*cos(-angulo) + posCameraZ*sin(-angulo);
            posCameraZ = -posCameraX*sin(-angulo) + posCameraZ*cos(-angulo);                      
            break; 
            
       //gira em torno de x    
       case GLUT_KEY_UP : 
            posCameraY =  posCameraY*cos(angulo) - posCameraZ*sin(angulo);
            posCameraZ =  posCameraY*sin(angulo) + posCameraZ*cos(angulo);                      
            break;    
        case GLUT_KEY_DOWN : 
            posCameraY =  posCameraY*cos(-angulo) - posCameraZ*sin(-angulo);
            posCameraZ =  posCameraY*sin(-angulo) + posCameraZ*cos(-angulo);                      
            break;    
        
        
		break;
			
   }
   
   glutPostRedisplay();
}
/*
void mouse(int button, int state, int x, int y) {

switch(button){
		case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		zoomCamera(-0.1f, posCameraX, posCameraY, posCameraZ);
		
}
}*/

// Função que desenha o plano
void desenhaAgua() {
    // Define a cor do plano
    

    // Define a posição dos vértices do quadrilátero
	
    
   glBegin(GL_QUAD_STRIP);
   
	glColor3f(0.0, 0.0, 1.0);
	glVertex3d(-5.0, 0.0, -4.0);
	glVertex3d(-5.0, 0.0, 4.0);
	glVertex3d(5.0, 0.0, -4.0);
	glVertex3d(5.0, 0.0, 4.0);
	
	
     
   glEnd();
   glutSwapBuffers();
}

void desenhaTerra(){
	
	glBegin(GL_QUAD_STRIP);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3d(-4.0, 0.0, -3.2);
	glVertex3d(-4.0, 0.0, 3.2);
	glVertex3d(4.0, 0.0, -3.2);
	glVertex3d(4.0, 0.0, 3.2);
	
	glEnd();
   glutSwapBuffers();
	
	}

// Função que exibe a cena
void display() {
	
	
	
    glClear (GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt (posCameraX, posCameraY, posCameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   
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

void reshape(int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

// Função principal
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow("Plano da Cena");
    
   init ();
  
   glutDisplayFunc(display); 
   glutSpecialFunc(specialKeys);
   //glutMouseFunc(mouse);
   glutReshapeFunc(reshape);
   
   glutMainLoop();
   
   return 0;
}
