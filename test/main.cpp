#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <Mesh.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <Empty.hpp>
#include <Colored.hpp>

using namespace Gremlin::Mesh;
using namespace Gremlin::Graphics;

double r = 1;
Mesh dSun, dEarth, dMoon, dMars;
Object sun, earth, moon, mars;
Empty origin, earthE, moonE, marsE;

Colored mMars, mEarth, mMoon, mSun;

Transform3Df trans;

/* white ambient light at half intensity (rgba) */
GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };

/* super bright, full intensity diffuse light. */
GLfloat LightDiffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat redDiffuseMaterial[] = { 0.0, 0.0, 0.0 };

/* position of light (x, y, z, (position of light)) */
GLfloat LightPosition[] = { 0.0f, 0.0f, 0.0f, 1.0f };

void drawItems() {
	usleep(25000);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	origin.renderChildren(true);

	sun.transMatrix().rotateX(0.005, true);
	earthE.transMatrix().rotateX(0.01);
	earthE.transMatrix().rotateX(0.05, true);
	earthE.pushMatrix();

	marsE.transMatrix().rotateX(0.005);
	marsE.pushMatrix();

	origin.pushMatrix();

	glutSwapBuffers();
}

void loadFromFile(Mesh &m, string fileName) {
	// nacteni bodu
	fstream f(fileName.c_str(), ios::in);
	char buffer[512];

	VertexGroup &vGroup = m.VGroup(0);

	while (!f.eof()) {
		// nacteni radku
		f.getline(buffer, 512);

		if (buffer[0] == 0x0)
			break;

		GLfloat x, y, z;
		GLfloat n1, n2, n3;
		sscanf(buffer, "%f %f %f %f %f %f", &x, &y, &z, &n1, &n2, &n3);

		// zapis bodu
		vGroup.addPoint(x, y, z, n1, n2, n3);
	}

	// nacitani trojuhelniku
	while (!f.eof()) {
		f.getline(buffer, 512);

		size_t p1, p2, p3;

		sscanf(buffer, "%lu %lu %lu", &p1, &p2, &p3);

		vGroup.addTriangle(p1, p2, p3);
	}
}

/* A general OpenGL initialization function.  Sets all of the initial parameters. */
GLvoid InitGL(GLsizei Width, GLsizei Height) // We call this right after our OpenGL window is created.
		{
	// LoadGLTextures();                           // load the textures.
	// glEnable(GL_TEXTURE_2D);                    // Enable texture mapping.

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);// This Will Clear The Background Color To Black
	glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
	glDepthFunc(GL_LESS);			// The Type Of Depth Test To Do
	glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
	glShadeModel(GL_FLAT);			// Enables Smooth Color Shading

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();				// Reset The Projection Matrix

	gluPerspective(120.0f, (GLfloat) Width / (GLfloat) Height, 0.1f, 100.0f);// Calculate The Aspect Ratio Of The Window

	glMatrixMode(GL_MODELVIEW);

	// set up light number 1.
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);  // add lighting. (ambient)
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);  // add lighting. (diffuse).
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition); // set light position.
	glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular);
	glEnable(GL_LIGHT1);                             // turn light 1 on.

	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
}

int main(int argc, char** argv) {
	// pocatek
	//earth = Mesh();
	trans.translate(0, 0, -10, true);
	origin.transMatrix().translate(0, 0, -10, true);
	origin.transMatrix().rotateY(1, true);
	origin.transMatrix().rotateZ(1, true);

	// nacteni dat a nastaveni dat objektum
	dSun.addVGroup();
	loadFromFile(dSun, "../Tests/koule.txt");

	dEarth = dMoon = dMars = dSun;

	sun.graphicData(&dSun);
	earth.graphicData(&dEarth);
	moon.graphicData(&dMoon);
	mars.graphicData(&dMars);

	// nastaveni materialu
	mSun.difuse().color(0.9, 1, 0.05, 1);
	mSun.specular().color(0.1, 0.1, 0.1, 1);
	mSun.ambient().color(0.0, 0.0, 0.0);
	mSun.emision().color(0.0, 0.0, 0.0);
	mSun.shininess(127);

	mEarth.difuse().color(0, 1, 0.9, 1);
	mEarth.specular().color(0.1, 0.1, 0.1, 1);
	mEarth.ambient().color(0.0, 0.0, 0.0);
	mEarth.emision().color(0.0, 0.0, 0.0);
	mEarth.shininess(127);

	mMoon.difuse().color(0.7, 0.7, 0.7, 1);
	mMoon.specular().color(0.1, 0.1, 0.1, 1);
	mMoon.ambient().color(0.0, 0.0, 0.0);
	mMoon.emision().color(0.0, 0.0, 0.0);
	mMoon.shininess(127);

	mMars.difuse().color(1, 0, 0, 1);
	mMars.specular().color(0.1, 0.1, 0.1, 1);
	mMars.ambient().color(0.0, 0.0, 0.0);
	mMars.emision().color(0.0, 0.0, 0.0);
	mMars.shininess(127);

	// nastaveni materialu objektum
	dSun.VGroup(0).addMaterial(&mSun);
	dEarth.VGroup(0).addMaterial(&mEarth);
	dMars.VGroup(0).addMaterial(&mMars);
	dMoon.VGroup(0).addMaterial(&mMoon);

	glEnable(GL_COLOR_MATERIAL);

	sun.transMatrix().scale(1);
	origin.addChild(&sun);

	// zeme
	earthE.transMatrix().translate(0, 4.0, 0, true);
	origin.addChild(&earthE);
	earth.transMatrix().scale(0.3);
	earthE.addChild(&earth);

	// mesic
	moonE.transMatrix().translate(0, 0.4, 0, true);
	earthE.addChild(&moonE);
	moon.transMatrix().scale(0.1);
	moonE.addChild(&moon);

	// mars
	marsE.transMatrix().translate(0, 6, 0, true);
	origin.addChild(&marsE);
	mars.transMatrix().scale(0.2);
	marsE.addChild(&mars);

	origin.pushMatrix();

	/* Initialize GLUT state - glut will take any command line arguments that pertain to it or
	 X Windows - look at its documentation at http://reality.sgi.com/mjk/spec3/spec3.html */
	glutInit(&argc, argv);

	/* Select type of Display mode:
	 Double buffer
	 RGBA color
	 Alpha components supported
	 Depth buffer */
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);

	/* get a 640 x 480 window */
	glutInitWindowSize(800, 600);

	/* the window starts at the upper left corner of the screen */
	glutInitWindowPosition(0, 0);

	/* Open a window */
	glutCreateWindow("Gremlin test");

	/* Register the function to do all our OpenGL drawing. */
	glutDisplayFunc(&drawItems);

	/* Even if there are no events, redraw our gl scene. */
	glutIdleFunc(&drawItems);

	/* Initialize our window. */
	InitGL(800, 600);

	/* Start Event Processing Engine */
	glutMainLoop();

	return 1;
}
