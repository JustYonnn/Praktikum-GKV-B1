#include <GL/glut.h>

static int shoulder = 0, elbow = 0;
static int pinky = 0, ring_finger = 0, middle_finger = 0, index_finger = 0, thumb = 0;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void drawFinger(float x, float y, float z, int rotation, int segments, float tiltX, float tiltY) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(tiltX, 1.0, 0.0, 0.0); 
    glRotatef(tiltY, 0.0, 1.0, 0.0); 
    
    for (int i = 0; i < segments; i++) {
        glRotatef((GLfloat)rotation, 0.0, 0.0, 1.0); 
        glPushMatrix();
        glScalef(0.2, 0.05, 0.05);
        glutWireCube(1.0);
        glPopMatrix();
        glTranslatef(0.15, 0.0, 0.0);
    }
    glPopMatrix();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    // Transformasi bahu
    glTranslatef(-1.0, 0.0, 0.0);
    glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    
    glPushMatrix();
    glScalef(2.0, 0.4, 0.7);
    glutWireCube(1.0); // Lengan atas
    glPopMatrix();

    // Transformasi siku
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    
    glPushMatrix();
    glScalef(1.5, 0.4, 0.7);
    glutWireCube(1.0); // Lengan bawah
    glPopMatrix();

    // Telapak tangan
    glTranslatef(1.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.8, 0.4, 0.8);
    glutWireCube(1.0);
    glPopMatrix();

    // Menggambar jari-jari 
    drawFinger(0.3, 0.15, -0.25, pinky, 3, 0, 0);       // Jari kelingking
    drawFinger(0.3, 0.15, -0.1, ring_finger, 3, 0, 0);   // Jari manis
    drawFinger(0.3, 0.15,  0.05, middle_finger, 3, 0, 0); // Jari tengah
    drawFinger(0.3, 0.15,  0.2, index_finger, 3, 0, 0);  // Jari telunjuk
    drawFinger(0.2, -0.1,  0.45, thumb, 3, -30, -20);     // Jempol 

    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 's': shoulder = (shoulder + 5) % 360; break;
        case 'S': shoulder = (shoulder - 5) % 360; break;
        case 'e': elbow = (elbow + 5) % 360; break;
        case 'E': elbow = (elbow - 5) % 360; break;
        case '1': pinky = (pinky + 5) % 90; break;
        case '!': pinky = (pinky - 5) % 90; break;
        case '2': ring_finger = (ring_finger + 5) % 90; break;
        case '@': ring_finger = (ring_finger - 5) % 90; break;
        case '3': middle_finger = (middle_finger + 5) % 90; break;
        case '#': middle_finger = (middle_finger - 5) % 90; break;
        case '4': index_finger = (index_finger + 5) % 90; break;
        case '$': index_finger = (index_finger - 5) % 90; break;
        case '5': thumb = (thumb + 5) % 90; break;
        case '%': thumb = (thumb - 5) % 90; break;
        case 27: exit(0); break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Simulasi Lengan");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

