#include <GL/glut.h>
#include <math.h>

void mobil() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Langit biru
    glColor3f(0.5f, 0.8f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, 0.2f);
        glVertex2f(1.0f, 0.2f);
        glVertex2f(1.0f, 1.0f);
        glVertex2f(-1.0f, 1.0f);
    glEnd();
    
    // Matahari
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
        float cx = 0.8f, cy = 0.8f, r = 0.1f;
        glVertex2f(cx, cy);
        for (int i = 0; i <= 360; i += 10) {
            float angle = i * 3.14159f / 180;
            glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
        }
    glEnd();
    
    // Jalanan aspal
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -0.2f);
        glVertex2f(1.0f, -0.2f);
        glVertex2f(1.0f, 0.2f);
        glVertex2f(-1.0f, 0.2f);
    glEnd();
    
    // Mobil hitam (badan utama)
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.6f, 0.0f);
        glVertex2f(0.6f, 0.0f);
        glVertex2f(0.6f, 0.3f);
        glVertex2f(-0.6f, 0.3f);
    glEnd();
    
    // Atap mobil (trapesium)
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.4f, 0.3f);
        glVertex2f(0.4f, 0.3f);
        glVertex2f(0.3f, 0.5f);
        glVertex2f(-0.3f, 0.5f);
    glEnd();
    
    // Jendela kiri
    glColor3f(0.7f, 0.9f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.3f, 0.3f);
        glVertex2f(-0.05f, 0.3f);
        glVertex2f(-0.05f, 0.45f);
        glVertex2f(-0.25f, 0.45f);
    glEnd();
    
    // Jendela kanan
    glBegin(GL_QUADS);
        glVertex2f(0.05f, 0.3f);
        glVertex2f(0.3f, 0.3f);
        glVertex2f(0.25f, 0.45f);
        glVertex2f(0.05f, 0.45f);
    glEnd();
    
    // Lampu depan
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(0.6f, 0.1f);
        glVertex2f(0.65f, 0.1f);
        glVertex2f(0.65f, 0.2f);
        glVertex2f(0.6f, 0.2f);
    glEnd();
    
    // Lampu belakang
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.6f, 0.1f);
        glVertex2f(-0.65f, 0.1f);
        glVertex2f(-0.65f, 0.2f);
        glVertex2f(-0.6f, 0.2f);
    glEnd();
    
    // Gagang pintu
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_QUADS);
        glVertex2f(-0.3f, 0.15f);
        glVertex2f(-0.22f, 0.15f);
        glVertex2f(-0.22f, 0.17f);
        glVertex2f(-0.3f, 0.17f);
    glEnd();
    
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_QUADS);
        glVertex2f(0.02f, 0.15f);
        glVertex2f(0.1f, 0.15f);
        glVertex2f(0.1f, 0.17f);
        glVertex2f(0.02f, 0.17f);
    glEnd();
    
    // Bemper
    glColor3f(0.211f, 0.211f, 0.211f);
    glBegin(GL_QUADS);
        glVertex2f(-0.6f, 0.0f);
        glVertex2f(-0.45f, 0.0f);
        glVertex2f(-0.45f, 0.07f);
        glVertex2f(-0.6f, 0.07f);
    glEnd();
    
    glColor3f(0.211f, 0.211f, 0.211f);
    glBegin(GL_QUADS);
        glVertex2f(0.45f, 0.0f);
        glVertex2f(0.6f, 0.0f);
        glVertex2f(0.6f, 0.07f);
        glVertex2f(0.45f, 0.07f);
    glEnd();
    
    // Roda mobil dengan velg (hanya 2 roda)
    for (float x = -0.4f; x <= 0.4f; x += 0.8f) {
        // Roda
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(x, -0.05f);
            for (int i = 0; i <= 360; i += 10) {
                float angle = i * 3.14159f / 180;
                glVertex2f(x + 0.1f * cos(angle), -0.05f + 0.1f * sin(angle));
            }
        glEnd();
        
        // Velg
        glColor3f(0.5f, 0.5f, 0.5f);
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(x, -0.05f);
            for (int i = 0; i <= 360; i += 10) {
                float angle = i * 3.14159f / 180;
                glVertex2f(x + 0.05f * cos(angle), -0.05f + 0.05f * sin(angle));
            }
        glEnd();
    }
    glFlush();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(640,480);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutCreateWindow("Objek Mobil");
	glutDisplayFunc(mobil);
	glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
	glutMainLoop();
	return 0;
}

