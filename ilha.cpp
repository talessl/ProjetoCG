#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>


float posCameraX, posCameraY, posCameraZ;
static GLuint camp;

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
     
        
    
        
   
   //inicializa posição da câmera
    posCameraX = 0.3;
    posCameraY = 0.1;
    posCameraZ = 0;

}

 
// Função responsável pela especificação dos parâmetros de iluminação
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
	glNormal3f(0.0, 0.0, 1.0);	// Normal da face
	glVertex3f(0.8, 0.1, 0.8);
	glVertex3f(-0.8, 0.1, 0.8);
	glVertex3f(-0.8, 0, 0.8);
	glVertex3f(0.8, 0, 0.8);
glEnd();


glBegin(GL_QUADS);			// Face frontal
	glNormal3f(0.0, 0.0, -1.0); 	// Normal da face
	glVertex3f(0.8, 0.1, -0.8);
	glVertex3f(0.8, 0, -0.8);
	glVertex3f(-0.8, 0, -0.8);
	glVertex3f(-0.8, 0.1, -0.8);
glEnd();
glBegin(GL_QUADS);			// Face lateral esquerda
	glNormal3f(-1.0, 0.0, 0.0); 	// Normal da face
	glVertex3f(-0.8, 0.1, 0.8);
	glVertex3f(-0.8, 0.1, -0.8);
	glVertex3f(-0.8, 0, -0.8);
	glVertex3f(-0.8, 0, 0.8);
glEnd();
glBegin(GL_QUADS);			// Face lateral direita
	glNormal3f(1.0, 0.0, 0.0);	// Normal da face
	glVertex3f(0.8, 0.1, 0.8);
	glVertex3f(0.8, 0, 0.8);
	glVertex3f(0.8, 0, -0.8);
	glVertex3f(0.8, 0.1, -0.8);
glEnd();
glBegin(GL_QUADS);			// Face superior
	glNormal3f(0.0, 1.0, 0.0);  	// Normal da face
	glVertex3f(-0.8, 0.1, -0.8);
	glVertex3f(-0.8, 0.1, 0.8);
	glVertex3f(0.8, 0.1, 0.8);
	glVertex3f(0.8, 0.1, -0.8);
glEnd();
glBegin(GL_QUADS);			// Face inferior
	glNormal3f(0.0, -1.0, 0.0); 	// Normal da face
	glVertex3f(-0.8, 0, -0.8);
	glVertex3f(0.8, 0, -0.8);
	glVertex3f(0.8, 0, 0.8);
	glVertex3f(-0.8, 0, 0.8);
glEnd();

	
	}
	
	
	
   
   
	

// Função que exibe a cena
void display() {
	
	
	
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    DefineIluminacao();
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);   	
	glBindTexture(GL_TEXTURE_2D, camp);
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
   DefineIluminacao();
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
