#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>


float posCameraX,posCameraY,posCameraZ;
float anguloCamera = 0.0;
float posXteaPot = -0.8, posYteaPot = 0.2, posZteaPot = 0.2;
float velXteaPot = 0.0, velYteaPot = 0.0, velZteaPot = 0.0;
float posXteaPot_2 = -0.8, posYteaPot_2 = 0.2, posZteaPot_2 = -0.2;
float velXteaPot_2 = 0.0, velYteaPot_2 = 0.0, velZteaPot_2 = 0.0;




void init (void) 
{
    glClearColor (1.0, 1.0, 1.0, 0.0);
    
		// Habilita a definição da cor do material a partir da cor corrente
        glEnable(GL_COLOR_MATERIAL);
        //Habilita o uso de iluminação
        glEnable(GL_LIGHTING);  
        // Habilita a luz de número 0
        glEnable(GL_LIGHT0);
        // Habilita o depth-buffering
        glEnable(GL_DEPTH_TEST);
 
        // Habilita o modelo de colorização
        glShadeModel(GL_SMOOTH);

    
    glLoadIdentity();
    posCameraX = 0.3;
	posCameraY = 0.1;
	posCameraZ = 0.0;
	
	//movimento do teaPot
	velXteaPot = 0.1;
	velYteaPot = 0.2;
	velZteaPot = 0.3;
	
	//movimento do teaPot_2
	velXteaPot_2 = 0.1;
	velYteaPot_2 = 0.2;
	velZteaPot_2 = 0.3;
    

   
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



void keyPressed(unsigned char key, int x, int y) 
{
   float angulo = 2*M_PI/180;
   
   switch (key) {
       case 'a': //rotacao em torno de x
             posCameraX =  posCameraX*cos(-angulo) + posCameraZ*sin(-angulo); 
            posCameraZ = -posCameraX*sin(-angulo) + posCameraZ*cos(-angulo);
            break;

      case 'd': 
          case GLUT_KEY_RIGHT : //rotacao em torno de x
            posCameraX =  posCameraX*cos(angulo) + posCameraZ*sin(angulo); 
            posCameraZ = -posCameraX*sin(angulo) + posCameraZ*cos(angulo);                      
            break;

        case 's': //rotacao em torno de z
            posCameraY =  posCameraY*cos(-angulo) + posCameraZ*sin(-angulo); 
            posCameraZ = -posCameraY*sin(-angulo) + posCameraZ*cos(-angulo);
            break;

        case 'w': //rotacao em torno de x
            posCameraY =  posCameraY*cos(angulo) + posCameraZ*sin(angulo); 
            posCameraZ = -posCameraY*sin(angulo) + posCameraZ*cos(angulo);
            break;      
   }
   glutPostRedisplay();
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
	
	/*glBegin(GL_QUADS);		// Face inferior	
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(-0.8, 0, -0.8);
	glVertex3f(0.8, 0, -0.8);
	glVertex3f(0.8, 0, 0.8);
	glVertex3f(-0.8, 0, 0.8);
	glEnd();*/

	
}

void desenhaAgua() {
	
    
   glBegin(GL_QUAD_STRIP);
   
	glColor3f(0.0, 0.0, 1.0);
	glVertex3d(-1.0, 0.0, -1.0);
	glVertex3d(-1.0, 0.0, 1.0);
	glVertex3d(1.0, 0.0, -1.0);
	glVertex3d(1.0, 0.0, 1.0);
	
	
     
   glEnd();
   
}

void desenhaLinhas(){
	glBegin(GL_LINES);
        glColor3f (1.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, 0.0);
        
        glColor3f (0.0, 1.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 1.0, 0.0);
      
        glColor3f (0.0, 0.0, 1.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 1.0);    
    glEnd();
}

void desenhaCubeAzul(){

glTranslatef(-0.4, 0.2, -0.4); 
glColor3f(0.0,0.0,1.0);
glutSolidCube(0.1);

}

void desenhaCubeRosa(){

glTranslatef(0.4, 0.2, 0.4); 
glColor3f(1.0,0.5,0.5);
glutSolidCube(0.1);

}

void desenhaTeaPot(){
glTranslatef(posXteaPot, posYteaPot, posZteaPot); 


glColor3f(1.0,0.0,0.0);
glutSolidTeapot(0.1);
glutWireSphere(0.1,6,6);


}

void desenhaTeaPot_2(){
glTranslatef(posXteaPot_2, posYteaPot_2, posZteaPot_2); 


glColor3f(1.0,1.0,0.0);
glutSolidTeapot(0.1);
glutWireSphere(0.1,6,6);


}



void update(int value) {
    // Atualiza a posição do teapot
    if(posXteaPot < 0.8){
	posXteaPot += velXteaPot;
	posXteaPot_2 += velXteaPot_2;}
	else{
	posXteaPot -= 1.5;
	posXteaPot_2 -= 1.5;
}
    glutTimerFunc(1000, update, 0);
    glutPostRedisplay();
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


void display(void)
{
	
	
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DefineIluminacao();	
	
	
	
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	gluLookAt (posCameraX, posCameraY, posCameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	desenhaAgua();
	desenhaTerra();
	
	glPushMatrix();
	desenhaTeaPot();
	glPopMatrix();
	
	glPushMatrix();
	desenhaTeaPot_2();
	glPopMatrix();
	
	glPushMatrix();
	desenhaCubeAzul();
	glPopMatrix();
	
	glPushMatrix();
	desenhaCubeRosa();
	glPopMatrix();
	
	glPushMatrix();
	desenhaLinhas();
	glPopMatrix();
	
	
    glutSwapBuffers();
}




int main(int argc, char** argv)
{	
	
		
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   
   
   glutDisplayFunc(display);
   glutKeyboardFunc(keyPressed);
   glutReshapeFunc(reshape);
   glutTimerFunc(0, update, 0);
   glutMainLoop();
   return 0;  
}
