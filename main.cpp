#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

#include "CameraMotionHelper.h"
#include "ModelDescription.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/vec3.hpp"

using namespace glm;

#define ESCAPE '\033'
#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

CameraMotionHelper cameraMotionHelper;
GLfloat rotationAngle = 0.0f;
const GLfloat changingValueOfRotationAngle = 1.5f;
GLfloat scalingRate = 0.0f;
GLfloat changingValueOfScalingRate = 0.05f;

void setupLight()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
    GLfloat specularLight[] = { 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    GLfloat ambientLight0[] = { 0.3f, 0.3f, 0.3f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight0);
    GLfloat diffuseLight[] = { 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
}

void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glDisable(GL_COLOR_MATERIAL);
    setupLight();
}

void axis(GLfloat size)
{
    glEnable(GL_COLOR_MATERIAL);
    GLfloat emissionColor[] = { 0.0, 0.0, 0.0, 1.0f };
    glMaterialfv(GL_FRONT, GL_EMISSION, emissionColor);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(size, 0.0f, 0.0f);
    glVertex3f(-size, 0.0f, 0.0f);
    glEnd();
    glRasterPos3f(-size, 0.0f, 0.0f);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)'-');
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)'X');
    glRasterPos3f(size, 0.0f, 0.0f);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)'+');
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)'X');
    glBegin(GL_LINES);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, size, 0.0f);
    glVertex3f(0.0f, -size, 0.0f);
    glEnd();
    glRasterPos3f(0.0f, -size, 0.0f);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)'-');
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)'Y');
    glRasterPos3f(0.0f, size, 0.0f);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)'+');
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)'Y');
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, size);
    glVertex3f(0.0f, 0.0f, -size);
    glEnd();
    glRasterPos3f(0.0f, 0.0f, -size);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)'-');
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)'Z');
    glRasterPos3f(0.0f, 0.0f, size);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)'+');
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)'Z');
    glDisable(GL_COLOR_MATERIAL);
}

void renderLamp()
{
    GLfloat emissionColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat ambientColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat diffuseColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat specularColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambientColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
    glMaterialfv(GL_FRONT, GL_EMISSION, emissionColor);
    glMaterialf(GL_FRONT, GL_SHININESS, 20);
    glutSolidSphere(0.2f, 32, 32);
}

void renderModel()
{
    GLfloat emissionColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_EMISSION, emissionColor);
    GLfloat ambientColor[] = { 0.2125f, 0.1275f, 0.054f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambientColor);
    GLfloat diffuseColor[] = { 0.714f, 0.4284f, 0.18144f, 1.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
    GLfloat specularColor[] = { 0.393548f, 0.271906f, 0.166721f, 1.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
    glMaterialf(GL_FRONT, GL_SHININESS, 128 * 0.2f);
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, 0, normalArr);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertexArr);
    glDrawArrays(GL_TRIANGLES, 0, 54);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void renderName()
{
    glDisable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos3f(0.0f, 0.0f, 0.0f);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"Voltov");
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
}

void render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraMotionHelper.getDistance(),
              cameraMotionHelper.getDistance(),
              cameraMotionHelper.getDistance(),
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);
    glRotatef(cameraMotionHelper.getRotationXZ(), 1.0f, 0.0f, -1.0f);
    glRotatef(cameraMotionHelper.getRotationY(), 0.0f, 1.0f, 0.0f);
    glPushMatrix();
    GLfloat lightPos[] = { 6.0f, 6.0f, 6.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glTranslatef(lightPos[0], lightPos[1], lightPos[2]);
    renderLamp();
    glPopMatrix();
    axis(15.0f);
    glPushMatrix();
    glScalef(1.0f, scalingRate, 1.0f);
    glRotatef(-rotationAngle, 0.0f, 1.0f, 0.0f);
    axis(6.0f);
    renderModel();
    glTranslatef(-6.0f, 3.0f, -2.0f);
    renderName();
    glPopMatrix();
    glutSwapBuffers();
}

void changeViewPort(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat zNear = 1;
    GLfloat zFar = 200;
    gluPerspective(45.0, (float)w / (float)h, zNear, zFar);
}

void keyboardFunc(unsigned char key, int x, int y)
{
    if (key == ESCAPE)
    {
        exit(0);
    }
}

void doAnimations()
{
    rotationAngle += changingValueOfRotationAngle;
    scalingRate += changingValueOfScalingRate;
    if (scalingRate > 2.5f)
    {
        changingValueOfScalingRate = -0.05f;
    }
    if (scalingRate < 1.0f)
    {
        changingValueOfScalingRate = 0.05f;
    }
}


void updateAnimation(int value)
{
    doAnimations();
    glutPostRedisplay();
    glutTimerFunc(25, updateAnimation, 0);
}

void mouseFunc(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            cameraMotionHelper.startMove(x, y);
        }
        else
        {
            cameraMotionHelper.endMove();
        }
    }
}

void mouseMotionFunc(int x, int y)
{
    cameraMotionHelper.move(x, y);
}

void mouseWheelFunc(int button, int dir, int x, int y)
{
    if (dir < 0)
    {
        cameraMotionHelper.increaseDistance();
    }
    else
    {
        cameraMotionHelper.decreaseDistance();
    }
}

void calcModelNormals(const GLfloat* v, GLfloat* n, GLuint vertexCount)
{
    for (GLuint i = 0; i < vertexCount - 2; i += 3)
    {
        vec3 a = vec3(v[i * 3 + 0], v[i * 3 + 1], v[i * 3 + 2]);
        vec3 b = vec3(v[i * 3 + 3], v[i * 3 + 4], v[i * 3 + 5]);
        vec3 c = vec3(v[i * 3 + 6], v[i * 3 + 7], v[i * 3 + 8]);
        vec3 norm = glm::normalize(glm::cross(b - a, c - a));
        memmove(&n[i * 3 + 0], glm::value_ptr(norm), sizeof(GLfloat) * 3);
        memmove(&n[i * 3 + 3], glm::value_ptr(norm), sizeof(GLfloat) * 3);
        memmove(&n[i * 3 + 6], glm::value_ptr(norm), sizeof(GLfloat) * 3);
    }
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Практика 1");
    calcModelNormals(vertexArr, normalArr, 54);
    init();
    glutDisplayFunc(render);
    glutReshapeFunc(changeViewPort);
    glutKeyboardFunc(keyboardFunc);
    glutMouseFunc(mouseFunc);
    glutMouseWheelFunc(mouseWheelFunc);
    glutMotionFunc(mouseMotionFunc);
    glutTimerFunc(25, updateAnimation, 0);
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fprintf(stderr, "GLEW error");
        return 1;
    }
    glutMainLoop();
    return 0;
}
