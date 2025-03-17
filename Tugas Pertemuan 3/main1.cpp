#include <GL/glut.h>
#include <math.h>

void Lingkaran() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Menggambar lingkaran
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
        float cx = 0.0f, cy = 0.0f, r = 0.5f;
        glVertex2f(cx, cy);
        for (int i = 0; i <= 360; i += 10) {
            float angle = i * 3.14159f / 180;
            glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
        }
    glEnd();
    
    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w >= h) {
        float aspect = (float)w / (float)h;
        gluOrtho2D(-aspect, aspect, -1.0, 1.0);
    } else {
        float aspect = (float)h / (float)w;
        gluOrtho2D(-1.0, 1.0, -aspect, aspect);
    }
    glMatrixMode(GL_MODELVIEW);
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, 1.0, 1.0);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(640,480);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutCreateWindow("Lingkaran");
	glutDisplayFunc(Lingkaran);
	glutReshapeFunc(reshape);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glutMainLoop();
	return 0;
}

