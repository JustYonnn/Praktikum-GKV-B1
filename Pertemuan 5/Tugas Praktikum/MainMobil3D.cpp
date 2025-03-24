#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

// Parameter kamera
float cameraX = 0.0f;
float cameraY = 5.0f;
float cameraZ = 15.0f;
float lookX = 0.0f;
float lookY = 0.0f;
float lookZ = 0.0f;
float cameraSpeed = 0.5f;
float angleX = 0.0f;
float angleY = 0.0f;

// Parameter pencahayaan
GLfloat light_position[] = {5.0f, 10.0f, 5.0f, 1.0f};
GLfloat light_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

// Material properties
GLfloat mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
GLfloat mat_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat high_shininess[] = {100.0f};

// Grid parameters
int gridSize = 20;
float gridScale = 1.0f;

// Inisialisasi OpenGL
void init() {
    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    
    // Setup pencahayaan
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    
    // Setup material
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    
    // Enable normalization for proper lighting
    glEnable(GL_NORMALIZE);
}

// Menggambar grid
void drawGrid() {
    float gridScale = 2.0f;
    int gridSize = 200;
    
    for (int i = -gridSize/2; i < gridSize/2; i++) {
        for (int j = -gridSize/2; j < gridSize/2; j++) {
            glPushMatrix();
            glTranslatef(i * gridScale, 0.0f, j * gridScale);
            glBegin(GL_QUADS);
            if ((i + j) % 2 == 0) {
                glColor3f(0.4f, 0.8f, 0.4f); 
            } else {
                glColor3f(0.0f, 0.5f, 0.0f); 
            }
            glNormal3f(0.0f, 1.0f, 0.0f);  
            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(gridScale, 0.0f, 0.0f);
            glVertex3f(gridScale, 0.0f, gridScale);
            glVertex3f(0.0f, 0.0f, gridScale);
            glEnd();
            glPopMatrix();
        }
    }
}

// Variabel rotasi
static GLfloat spin = 0.0;
static GLfloat wheelSpin = 0.0;

// Fungsi untuk membuat roda
void drawWheel(GLfloat x, GLfloat y, GLfloat z) {
    GLfloat tireColor[] = {0.1, 0.1, 0.1, 1.0};
    GLfloat rimColor[] = {0.8, 0.8, 0.8, 1.0};
    GLfloat hubColor[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat spokeColor[] = {0.9, 0.9, 0.9, 1.0}; 
    
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(90, 0.0, 1.0, 0.0); 
    glRotatef(wheelSpin, 0.0, 0.0, 1.0); 
    
    // Ban luar
    glColor3f(tireColor[0], tireColor[1], tireColor[2]);
    glutSolidTorus(0.1, 0.2, 16, 20);
    
    // Velg luar
    glColor3f(rimColor[0], rimColor[1], rimColor[2]);
    glutSolidTorus(0.03, 0.17, 16, 20);
    
    // Pusat velg (hub cap)
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    glColor3f(hubColor[0], hubColor[1], hubColor[2]);
    glutSolidSphere(0.07, 12, 12);
    
    // Desain tengah hub cap
    glColor3f(0.7, 0.7, 0.7);
    glTranslatef(0.0, 0.0, 0.07);
    glutSolidTorus(0.01, 0.04, 12, 12);
    glPopMatrix();
    
    // Jari-jari velg (spokes)
    glColor3f(spokeColor[0], spokeColor[1], spokeColor[2]);
    for (int i = 0; i < 5; i++) {
        glPushMatrix();
        glRotatef(i * 72, 0.0, 0.0, 1.0); 
        
        // Jari-jari utama
        glPushMatrix();
        glTranslatef(0.0, 0.0, 0.0);
        glScalef(0.02, 0.15, 0.02);
        glutSolidCube(1.0);
        glPopMatrix();
        
        // Jari-jari pendukung 1
        glPushMatrix();
        glTranslatef(0.05, 0.05, 0.0);
        glRotatef(45, 0.0, 0.0, 1.0);
        glScalef(0.02, 0.1, 0.02);
        glutSolidCube(1.0);
        glPopMatrix();
        
        // Jari-jari pendukung 2
        glPushMatrix();
        glTranslatef(-0.05, 0.05, 0.0);
        glRotatef(-45, 0.0, 0.0, 1.0);
        glScalef(0.02, 0.1, 0.02);
        glutSolidCube(1.0);
        glPopMatrix();
        
        glPopMatrix();
    }
    
    glPopMatrix();
}

// Fungsi untuk menampilkan mobil
void drawCar() {
    // Warna untuk badan mobil
    GLfloat bodyColor[] = {0.5, 0.5, 0.5, 1.0}; 
    GLfloat windowColor[] = {0.7, 0.8, 1.0, 0.8}; 
    GLfloat lightColor[] = {1.0, 1.0, 0.0, 1.0};

    // Badan mobil utama
    glPushMatrix();
    glColor3f(bodyColor[0], bodyColor[1], bodyColor[2]);
    glTranslatef(0.0, 0.0, 0.0);
    glScalef(1.0, 0.5, 2.0);
    glutSolidCube(1.0);
    glPopMatrix();

    // Bagian atas mobil (kabin)
    glPushMatrix();
    glColor3f(bodyColor[0], bodyColor[1], bodyColor[2]);
    glTranslatef(0.0, 0.35, -0.1);
    glScalef(0.8, 0.3, 1.2);
    glutSolidCube(1.0);
    glPopMatrix();

    // Kaca depan
    glPushMatrix();
    glColor4f(windowColor[0], windowColor[1], windowColor[2], windowColor[3]);
    glTranslatef(0.0, 0.35, 0.5);
    glRotatef(60, 1.0, 0.0, 0.0);
    glScalef(0.8, 0.1, 0.25);
    glutSolidCube(1.0);
    glPopMatrix();

    // Kaca belakang
    glPushMatrix();
    glColor4f(windowColor[0], windowColor[1], windowColor[2], windowColor[3]);
    glTranslatef(0.0, 0.35, -0.7);
    glRotatef(-60, 1.0, 0.0, 0.0);
    glScalef(0.8, 0.1, 0.25);
    glutSolidCube(1.0);
    glPopMatrix();

    // Kaca samping kiri
    glPushMatrix();
    glColor4f(windowColor[0], windowColor[1], windowColor[2], windowColor[3]);
    glTranslatef(-0.4, 0.35, -0.1);
    glScalef(0.05, 0.2, 1.0);
    glutSolidCube(1.0);
    glPopMatrix();

    // Kaca samping kanan
    glPushMatrix();
    glColor4f(windowColor[0], windowColor[1], windowColor[2], windowColor[3]);
    glTranslatef(0.4, 0.35, -0.1);
    glScalef(0.05, 0.2, 1.0);
    glutSolidCube(1.0);
    glPopMatrix();

    // Roda dengan velg
    drawWheel(-0.5, -0.25, 0.7);  // Roda depan kiri
    drawWheel(0.5, -0.25, 0.7);   // Roda depan kanan
    drawWheel(-0.5, -0.25, -0.7); // Roda belakang kiri
    drawWheel(0.5, -0.25, -0.7);  // Roda belakang kanan
    
    // Lampu depan
    glPushMatrix();
    glColor3f(lightColor[0], lightColor[1], lightColor[2]);
    // Lampu depan kiri
    glPushMatrix();
    glTranslatef(-0.3, 0.0, 1.0);
    glScalef(0.1, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Lampu depan kanan
    glPushMatrix();
    glTranslatef(0.3, 0.0, 1.0);
    glScalef(0.1, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();
    glPopMatrix();
    
    // Lampu belakang
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    // Lampu belakang kiri
    glPushMatrix();
    glTranslatef(-0.3, 0.0, -1.0);
    glScalef(0.1, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Lampu belakang kanan
    glPushMatrix();
    glTranslatef(0.3, 0.0, -1.0);
    glScalef(0.1, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();
    glPopMatrix();
    
    // Grill depan
    glPushMatrix();
    glColor3f(0.1, 0.1, 0.1);
    glTranslatef(0.0, 0.0, 1.0);
    glScalef(0.4, 0.1, 0.02);
    glutSolidCube(1.0);
    glPopMatrix();
}

// Fungsi display - dipanggil setiap frame
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Setup kamera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Posisikan kamera
    gluLookAt(cameraX, cameraY, cameraZ,
              lookX, lookY, lookZ,
              0.0f, 1.0f, 0.0f);
    
    // Update posisi light sesuai posisi kamera
    light_position[0] = cameraX;
    light_position[1] = cameraY + 5.0f;
    light_position[2] = cameraZ;
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    // Gambar grid
    drawGrid();
    
    // Gambar mobil
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f);
    drawCar();
    glPopMatrix();
    
    glutSwapBuffers();
}

// Fungsi reshape untuk mengatur proyeksi
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Fungsi keyboard untuk input
void keyboard(unsigned char key, int x, int y) {
    float angleRadX = angleX * M_PI / 180.0f;
    float angleRadY = angleY * M_PI / 180.0f;
    
    switch (key) {
        case 'w': // Maju
            cameraX += cameraSpeed * sin(angleRadY);
            cameraZ -= cameraSpeed * cos(angleRadY);
            break;
        case 's': // Mundur
            cameraX -= cameraSpeed * sin(angleRadY);
            cameraZ += cameraSpeed * cos(angleRadY);
            break;
        case 'a': // Kiri (strafe)
            cameraX -= cameraSpeed * cos(angleRadY);
            cameraZ -= cameraSpeed * sin(angleRadY);
            break;
        case 'd': // Kanan (strafe)
            cameraX += cameraSpeed * cos(angleRadY);
            cameraZ += cameraSpeed * sin(angleRadY);
            break;
        case 'q': // Putar kiri
            angleY -= 5.0f;
            break;
        case 'e': // Putar kanan
            angleY += 5.0f;
            break;
        case 'z': // Lihat ke atas
            angleX += 5.0f;
            if (angleX > 89.0f) angleX = 89.0f;
            break;
        case 'c': // Lihat ke bawah
            angleX -= 5.0f;
            if (angleX < -89.0f) angleX = -89.0f;
            break;
        case 'x': // ESC
            exit(0);
            break;
    }
    
    // Update look target berdasarkan sudut kamera
    lookX = cameraX + sin(angleRadY) * cos(angleRadX);
    lookY = cameraY + sin(angleRadX);
    lookZ = cameraZ - cos(angleRadY) * cos(angleRadX);
    
    glutPostRedisplay();
}

// Fungsi special key untuk panah
void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            angleX += 5.0f;
            if (angleX > 89.0f) angleX = 89.0f;
            break;
        case GLUT_KEY_DOWN:
            angleX -= 5.0f;
            if (angleX < -89.0f) angleX = -89.0f;
            break;
        case GLUT_KEY_LEFT:
            angleY -= 5.0f;
            break;
        case GLUT_KEY_RIGHT:
            angleY += 5.0f;
            break;
    }
    
    // Update look target berdasarkan sudut kamera
    float angleRadX = angleX * M_PI / 180.0f;
    float angleRadY = angleY * M_PI / 180.0f;
    
    lookX = cameraX + sin(angleRadY) * cos(angleRadX);
    lookY = cameraY + sin(angleRadX);
    lookZ = cameraZ - cos(angleRadY) * cos(angleRadX);
    
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Mobil 3D dengan OpenGL");
    
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    
    glutMainLoop();
    
    return 0;
}
