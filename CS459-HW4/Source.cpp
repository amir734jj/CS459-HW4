#include <GL/glut.h>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

#define MAX_NUMBER_OF_OBJECTS 200
#define PI 3.14159265
#define MENU_1 1
#define MENU_2 2
#define SUB_MENU_1 3
#define SUB_MENU_2 4
#define SUB_MENU_3 5
#define SUB_MENU_4 6

#define SUB_MENU_5 7
#define SUB_MENU_6 8
#define SUB_MENU_7 9
#define SUB_MENU_8 10

#define SUB_MENU_9 11
#define SUB_MENU_10 12

#define SUB_MENU_11 12
#define SUB_MENU_12 13

static int step = 0;

static float alpha = 0.0;
static float beta = PI / 6.0;

static GLdouble cpos[3];
static GLfloat lpos[] = { 0.0, 1.0, 0.0, 0.0 };
static GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
static GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
static GLfloat gray[] = { 0.5, 0.5, 0.5, 1.0 };
static GLfloat red[] = { 1.0, 0.0, 0.0, 1.0 };
static GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 };
static GLfloat blue[] = { 0.0, 0.0, 1.0, 1.0 };
static GLfloat yellow[] = { 1.0, 1.0, 0.0, 1.0 };
static GLfloat magenta[] = { 1.0, 0.0, 1.0, 1.0 };
static GLfloat cyan[] = { 0.0, 1.0, 1.0, 1.0 };
static GLfloat darkcyan[] = { 0.0, 0.4, 0.4, 1.0 };
static GLfloat purple[] = { 1.0, 0.5, 1.0, 1.0 };
static GLfloat gold[] = { 255.0 / 255.0, 215.0 / 255.0, 1.0 };
static GLfloat silver[] = { 204.0 / 255.0, 204.0 / 255.0, 1.0 };



static bool trianglesExist = false;
static float stepBefore = step;
static float zoom = 15.0;
static bool lightSource = true;


static bool draggingRightNOW = false;
static int draggingRightNOW_ID = -1;
static bool runRandomizeFunction = true;

static int NUMBER_OF_OBJECTS = 0;

static int reproductionRate = 7;
static GLdouble objx, objy, objz;

time_t startTime, EndTime, randmoizeStartTime, randmoizeEndTime;

static bool restart = false;

// 0 -> randomize Every 100ms
// 1 -> randomize Every 150ms
// 2 -> randomize Every 200ms
// 3 -> randomize Every 1s

static int randomizeBehavior = 3;
static bool holdBugsWhenLeftButtonOfMouseIsDown = false;

// true -> try to prevent over lap as much as possible
// false -> no over lap at all - Not recommended
static bool overLapBehavior = true;

static int bugSpeed = 100;

static bool usePreDefinedSpeed = true;

class Object
{
public:
	float X;
	float Y;
	float Z;
	float PreX;
	float PreY;
	float PreZ;
	int id;
	int angle;
	bool visible;
	GLfloat color[4];
};

static Object ObjectArray[MAX_NUMBER_OF_OBJECTS];



bool isThereObjectAtThatPosition(int x, int y, int z, int id){
	for (int i = 0; i < NUMBER_OF_OBJECTS; i++)
		if (i != id &&sqrt(pow((x - ObjectArray[i].X), 2) + pow((y - ObjectArray[i].Y), 2) + pow((z - ObjectArray[i].Z), 2)) <= 1.0)
			return true;
	return false;
}

double elapsedTime(time_t end, time_t start){
	return difftime(end, start);
}


void createObjects(){
	for (int i = 0; i < MAX_NUMBER_OF_OBJECTS; i++){
		Object obj;
		obj.X = obj.PreX = rand() % 13 - 6;
		obj.Y = obj.PreY = 0.75;
		obj.Z = obj.PreZ = rand() % 13 - 6;
		obj.id = i;
		obj.angle = 0;
		obj.visible = false;
		if (i % 10 == 0){
			obj.color[0] = gray[0];
			obj.color[1] = gray[1];
			obj.color[2] = gray[2];
			obj.color[3] = gray[3];
		}
		else if (i % 10 == 1){
			obj.color[0] = red[0];
			obj.color[1] = red[1];
			obj.color[2] = red[2];
			obj.color[3] = red[3];
		}
		else if (i % 10 == 2){
			obj.color[0] = yellow[0];
			obj.color[1] = yellow[1];
			obj.color[2] = yellow[2];
			obj.color[3] = yellow[3];
		}
		else if (i % 10 == 3){
			obj.color[0] = green[0];
			obj.color[1] = green[1];
			obj.color[2] = green[2];
			obj.color[3] = green[3];
		}
		else if (i % 10 == 4){
			obj.color[0] = silver[0];
			obj.color[1] = silver[1];
			obj.color[2] = silver[2];
			obj.color[3] = silver[3];
		}
		else if (i % 10 == 5){
			obj.color[0] = purple[0];
			obj.color[1] = purple[1];
			obj.color[2] = purple[2];
			obj.color[3] = purple[3];
		}
		else if (i % 10 == 6){
			obj.color[0] = magenta[0];
			obj.color[1] = magenta[1];
			obj.color[2] = magenta[2];
			obj.color[3] = magenta[3];
		}
		else if (i % 10 == 7){
			obj.color[0] = gold[0];
			obj.color[1] = gold[1];
			obj.color[2] = gold[2];
			obj.color[3] = gold[3];
		}
		else if (i % 10 == 8){
			obj.color[0] = darkcyan[0];
			obj.color[1] = darkcyan[1];
			obj.color[2] = darkcyan[2];
			obj.color[3] = darkcyan[3];
		}
		else if (i % 10 == 8){
			obj.color[0] = blue[0];
			obj.color[1] = blue[1];
			obj.color[2] = blue[2];
			obj.color[3] = blue[3];
		}
		ObjectArray[i] = obj;
	}
}


void randomizeObjects(){
	int attempts;
	for (int i = 0; i < NUMBER_OF_OBJECTS; i++){
		attempts = 0;
		if (ObjectArray[i].visible == true){

			ObjectArray[i].PreX = ObjectArray[i].X;
			ObjectArray[i].PreZ = ObjectArray[i].Z;

			// Try Not to Pass Through Others but we also make sure we don't run into infinite loop unless user wants No over lap at all
			for (;;){
				ObjectArray[i].X += rand() % 3 - 1;
				ObjectArray[i].Z += rand() % 3 - 1;

				if (ObjectArray[i].X > 6)
					ObjectArray[i].X--;
				if (ObjectArray[i].X < -6)
					ObjectArray[i].X++;
				if (ObjectArray[i].Z > 6)
					ObjectArray[i].Z--;
				if (ObjectArray[i].Z < -6)
					ObjectArray[i].Z++;

				if (isThereObjectAtThatPosition(ObjectArray[i].X, ObjectArray[i].Y, ObjectArray[i].Z, i) == true){
					ObjectArray[i].X = ObjectArray[i].PreX;
					ObjectArray[i].Z = ObjectArray[i].PreZ;
				}
				else
					break;

				// No infinite loop
				if (overLapBehavior == true){
					// We don't run into infinite loop
					if (attempts > 5){
						ObjectArray[i].X += rand() % 3 - 1;
						ObjectArray[i].Z += rand() % 3 - 1;

						if (ObjectArray[i].X > 6)
							ObjectArray[i].X--;
						if (ObjectArray[i].X < -6)
							ObjectArray[i].X++;
						if (ObjectArray[i].Z > 6)
							ObjectArray[i].Z--;
						if (ObjectArray[i].Z < -6)
							ObjectArray[i].Z++;
						break;
					}

				}
				attempts++;
			}

		}
	}
}

void drawObjects(){
	for (int i = 0; i < NUMBER_OF_OBJECTS; i++){
		if (ObjectArray[i].visible == true){
			float angleX = 0.0;
			glPushMatrix();



			if (ObjectArray[i].X - ObjectArray[i].PreX == 1 && ObjectArray[i].Z == ObjectArray[i].PreZ)
				angleX = 90.0;
			if (ObjectArray[i].X - ObjectArray[i].PreX == -1 && ObjectArray[i].Z == ObjectArray[i].PreZ)
				angleX = -90.0;
			if (ObjectArray[i].X == ObjectArray[i].PreX  && ObjectArray[i].Z - ObjectArray[i].PreZ == 1)
				angleX = 0.0;
			if (ObjectArray[i].X == ObjectArray[i].PreX  && ObjectArray[i].Z - ObjectArray[i].PreZ == -1)
				angleX = 180.0;
			if (ObjectArray[i].X - ObjectArray[i].PreX == 1 && ObjectArray[i].Z - ObjectArray[i].PreZ == 1)
				angleX = 45.0;
			if (ObjectArray[i].X - ObjectArray[i].PreX == -1 && ObjectArray[i].Z - ObjectArray[i].PreZ == 1)
				angleX = -45.0;
			if (ObjectArray[i].X - ObjectArray[i].PreX == 1 && ObjectArray[i].Z - ObjectArray[i].PreZ == -1)
				angleX = 135.0;
			if (ObjectArray[i].X - ObjectArray[i].PreX == -1 && ObjectArray[i].Z - ObjectArray[i].PreZ == -1)
				angleX = 235.0;

			ObjectArray[i].angle = angleX;

			glTranslatef(ObjectArray[i].X, ObjectArray[i].Y, ObjectArray[i].Z);
			glRotatef(angleX, 0, 1, 0);

			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ObjectArray[i].color);
			glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, ObjectArray[i].color);
			glutSolidSphere(0.5, 20, 20);

			// Legs
			glLineWidth(3.5);
			glBegin(GL_LINES);
			glVertex3f(0.0 + 0.15, 0.0, 0.0);
			glVertex3f(0.0 + 0.15, 0.0 - 0.75, 0.0);
			glEnd();

			glLineWidth(3.5);
			glBegin(GL_LINES);
			glVertex3f(0.0 - 0.15, 0.0, 0.0);
			glVertex3f(0.0 - 0.15, 0.0 - 0.75, 0.0);
			glEnd();

			//Hands
			glLineWidth(3.5);
			glBegin(GL_LINES);
			glVertex3f(0.0 + 0.5, 0.0, 0.0);
			glVertex3f(0.0 + 0.5 + 0.15, 0.0, 0.0 + 0.5 + 0.15);
			glEnd();

			glLineWidth(3.5);
			glBegin(GL_LINES);
			glVertex3f(0.0 - 0.5, 0.0, 0.0);
			glVertex3f(0.0 - 0.5 - 0.15, 0.0, 0.0 + 0.5 + 0.15);
			glEnd();

			// Face
			glLineWidth(1.5);
			glBegin(GL_LINES);
			glVertex3f(0.0 - 0.05, 0.0 + 0.65, 0.0 + 0.15);
			glVertex3f(0.0 + 0.05, 0.0 + 0.65, 0.0 + 0.15);
			glEnd();

			glLineWidth(1.5);
			glBegin(GL_LINES);
			glVertex3f(0.0, 0.0 + 0.65 + 0.10, 0.0 + 0.15);
			glVertex3f(0.0, 0.0 + 0.65 - 0.10, 0.0 + 0.15);
			glEnd();

			glPushMatrix();
			glTranslatef(0.0, 0.5 + 0.15, 0.0);
			glutSolidSphere(0.15, 20, 20);
			glPopMatrix();

			glRotatef(-angleX, 0, 1, 0);
			glPopMatrix();
		}
	}
}

void addObject(int newNumberOfObject){
	for (int i = NUMBER_OF_OBJECTS; i < NUMBER_OF_OBJECTS + newNumberOfObject; i++)
		ObjectArray[i].visible = true;
	NUMBER_OF_OBJECTS += newNumberOfObject;
}
void writemessage()
{
	printf("HW-4 - Computer Graphics - Professor Suzuki\n");
	printf("Seyedamirhossein Hesamian\n\n");
	printf(" ^ => Move camera up\n");
	printf(" > => Move camera right\n");
	printf(" < => Move camera left\n");
	printf(" down arrow => Move camera down\n");
	printf("\n");
	printf("\n");
	printf(" 0 => Toggling light source\n");
	printf("\n");
	printf(" - => Increases the time it takes to reproduce\n");
	printf(" + => Deccreases the time it takes to reproduce\n");
	printf("\n");
	printf(" q => Zoom-in\n");
	printf(" a => Zoom-out\n");
	printf("\n");
	printf(" w => Wire Frame Mode\n");
	printf("\n");
	printf(" s => Stop the moving of bugs until left click of mouse\n");
	printf("\n");
	printf(" > => Increases the bug speed\n");
	printf(" < => Decreases the bug speed\n");
	printf("\n");
	printf("When are picking a Bug remeber to SEE the real time location of bug and try to put a bug outside of table\ntable dimention is 14 X 14");
	printf("\n");
	printf(" You can not move the light source when the light source is off !!!");
}

void init(void)
{
	writemessage();
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_LIGHTING);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_LIGHT0);
}



void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75.0, (GLfloat)w / (GLfloat)h, 1.0, 35.0);
	glMatrixMode(GL_MODELVIEW);
}



void display(void)
{
	static int i;
	static double angle1, angle2, angle3, angle4, Y1, Z1, Y2, Z2, X3, Y3, X4, Y4;
	static double angle5, angle6, angle7, angle8, X5, Y5, X6, Y6, X7, Y7, X8, Y8;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	cpos[0] = zoom * cos(beta) * sin(alpha);
	cpos[1] = zoom * sin(beta);
	cpos[2] = zoom * cos(beta) * cos(alpha);
	gluLookAt(cpos[0], cpos[1], cpos[2], 0.0, 1.0, 0.0, 0.0, 1.0, 0.0);


	glMaterialfv(GL_FRONT, GL_EMISSION, black);

	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 64);

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
	glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, blue);
	glNormal3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(7.0, -0.001, -7.0);
	glVertex3f(-7.0, -0.001, -7.0);
	glVertex3f(-7.0, -0.001, 7.0);
	glVertex3f(7.0, -0.001, 7.0);
	glEnd();



	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);
	glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, green);
	glMaterialfv(GL_BACK, GL_SPECULAR, green);


	drawObjects();


	glFlush();
	glutSwapBuffers();

}



void keyboard(unsigned char key, int x, int y)
{
	static int polygonmode[2];

	switch (key) {
	case 27:
		exit(0);
		break;
	case 'w':
		glGetIntegerv(GL_POLYGON_MODE, polygonmode);
		if (polygonmode[0] == GL_FILL)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case '<':
		usePreDefinedSpeed = false;
		randomizeBehavior = -1;
		printf("Bug Speed Call Back Function will be called Every: %d ms\n", bugSpeed);
		bugSpeed++;
		break;
	case '>':
		printf("Bug Speed Call Back Function will be called Every: %d ms\n", bugSpeed);
		usePreDefinedSpeed = false;
		randomizeBehavior = -1;
		if (bugSpeed - 1 >= 0)
			bugSpeed--;
		break;
	case 'x':
		if (lightSource == true)
			lpos[0] = lpos[0] + 0.2;
		break;
	case 'X':
		if (lightSource == true)
			lpos[0] = lpos[0] - 0.2;
		break;
	case 'y':
		if (lightSource == true)
			lpos[1] = lpos[1] + 0.2;
		break;
	case 'Y':
		if (lightSource == true)
			lpos[1] = lpos[1] - 0.2;
		break;
	case 'z':
		if (lightSource == true)
			lpos[2] = lpos[2] + 0.2;
		break;
	case 'Z':
		if (lightSource == true)
			lpos[2] = lpos[2] - 0.2;
		break;
	case 'q':
		if (zoom != 1.5)zoom = zoom - 0.5;
		break;
	case 'a':
		if (zoom != 25)zoom = zoom + 0.5;
		break;
	case '0':
		if (lightSource == true){
			glDisable(GL_LIGHT0);
			lightSource = false;
		}
		else{
			glEnable(GL_LIGHT0);

			lightSource = true;
		}
		break;
	case '-':
		reproductionRate++;
		printf("reProductionRate: %d // Every %d Second There Will be New Bug\n", reproductionRate, reproductionRate);
		break;
	case '+':
		if (reproductionRate > 1)
			reproductionRate--;
		printf("reProductionRate: %d // Every %d Second There Will be New Bug\n", reproductionRate, reproductionRate);
		break;
	case 's':
		if (runRandomizeFunction == true)
			runRandomizeFunction = false;
		else
			runRandomizeFunction = true;
		break;
	default:
		break;
	}
}

void processMouseClick(){
	for (int i = 0; i < NUMBER_OF_OBJECTS; i++){
		if (ObjectArray[i].visible && sqrt(pow((objx - ObjectArray[i].X), 2) + pow((objy - ObjectArray[i].Y), 2) + pow((objz - ObjectArray[i].Z), 2)) <= 0.65){
			draggingRightNOW_ID = i;
			return;
		}
	}
}

void processDrag(){
	if ((objx>7 || objx < -7) || (objz>7 || objz < -7)){
		ObjectArray[draggingRightNOW_ID].visible = false;
	}
	else{
		ObjectArray[draggingRightNOW_ID].Y = 0.75;
	}
}

void doMouseProcess(int x, int y){
	GLint viewport[4];
	GLdouble modelview[16], projection[16];
	GLfloat wx = x, wy, wz;

	glGetIntegerv(GL_VIEWPORT, viewport);
	y = viewport[3] - y;
	wy = y;
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &wz);
	gluUnProject(wx, wy, wz, modelview, projection, viewport, &objx, &objy, &objz);
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_RIGHT_BUTTON || button == GLUT_MIDDLE_BUTTON)
		return;

	doMouseProcess(x, y);

	processMouseClick();

	if (state == GLUT_DOWN && draggingRightNOW_ID != -1){
		draggingRightNOW = true;
	}


	if (holdBugsWhenLeftButtonOfMouseIsDown == true && state == GLUT_DOWN)
		runRandomizeFunction = false;
	else
		runRandomizeFunction = true;



	if (state == GLUT_UP && draggingRightNOW == true){
		processDrag();
		draggingRightNOW = false;
		draggingRightNOW_ID = -1;
	}


	printf("isDraggingNow: %s \t", draggingRightNOW ? "true" : "false");
	printf("draggingRightNOW_ID: %d\n", draggingRightNOW_ID);
}

void specialkey(GLint key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_RIGHT:
		alpha = alpha + PI / 180;
		if (alpha > 2 * PI) alpha = alpha - 2 * PI;
		break;
	case GLUT_KEY_LEFT:
		alpha = alpha - PI / 180;
		if (alpha < 0) alpha = alpha + 2 * PI;
		break;
	case GLUT_KEY_UP:
		if (beta < 0.45*PI) beta = beta + PI / 180;
		break;
	case GLUT_KEY_DOWN:
		if (beta > -0.05*PI) beta = beta - PI / 180;
		break;
	default:
		break;
	}
}

void mouseMove(int x, int y)
{
	if (draggingRightNOW == true && draggingRightNOW_ID != -1){
		doMouseProcess(x, y);
	}
}

void anim(){
	time(&EndTime);
	time(&randmoizeEndTime);

	if (runRandomizeFunction == true && (int)elapsedTime(EndTime, startTime) >= reproductionRate){
		printf("|-----------------------------------------------------------|\n");
		printf("Elasped time for re-production is %f seconds.\n", difftime(EndTime, startTime));
		printf("Elasped time for randomize is %f seconds.\n", difftime(randmoizeEndTime, randmoizeStartTime));
		printf("Total Number Of Bugs Currently Running: %d\n", NUMBER_OF_OBJECTS);
		printf("|-----------------------------------------------------------|\n");
	}

	if (runRandomizeFunction == true && (int)elapsedTime(EndTime, startTime) >= reproductionRate)
	{
		time(&startTime);
		if (NUMBER_OF_OBJECTS < MAX_NUMBER_OF_OBJECTS)
			addObject(1);
	}



	if (runRandomizeFunction == true && randomizeBehavior != 3){
		time(&randmoizeStartTime);
		randomizeObjects();
	}


	if (draggingRightNOW == true && draggingRightNOW_ID != -1){
		ObjectArray[draggingRightNOW_ID].PreX = ObjectArray[draggingRightNOW_ID].X;
		ObjectArray[draggingRightNOW_ID].PreY = ObjectArray[draggingRightNOW_ID].Y;
		ObjectArray[draggingRightNOW_ID].PreZ = ObjectArray[draggingRightNOW_ID].Z;

		ObjectArray[draggingRightNOW_ID].X = objx;
		ObjectArray[draggingRightNOW_ID].Y = objy;
		ObjectArray[draggingRightNOW_ID].Z = objz;

		printf("# X: %f\tY: %f\tZ: %f\n", ObjectArray[draggingRightNOW_ID].X, ObjectArray[draggingRightNOW_ID].Y, ObjectArray[draggingRightNOW_ID].Z);
		printf("$ X: %f\tY: %f\tZ: %f\n", objx, objy, objz);
	}

	Sleep(30);



	if (usePreDefinedSpeed == true && randomizeBehavior == 0)
		Sleep(100);
	else if (usePreDefinedSpeed == true && randomizeBehavior == 1)
		Sleep(150);
	else if (usePreDefinedSpeed == true && randomizeBehavior == 2)
		Sleep(200);
	else if (usePreDefinedSpeed == true && randomizeBehavior == 3)
	{
		if (runRandomizeFunction == true && (int)elapsedTime(randmoizeEndTime, randmoizeStartTime) >= 1){
			time(&randmoizeStartTime);
			randomizeObjects();
		}
	}
	else if (usePreDefinedSpeed == false)
		Sleep(bugSpeed);


	glutPostRedisplay();
}
void handleRestart(int num){
	time(&startTime);
	time(&randmoizeStartTime);
	createObjects();
	addObject(num);
}
void processMenuEvents(int option) {
	if (option == MENU_1)
		exit(0);
	if (option == SUB_MENU_1)
		handleRestart(1);
	if (option == SUB_MENU_2)
		handleRestart(4);
	if (option == SUB_MENU_3)
		handleRestart(8);
	if (option == SUB_MENU_4)
		handleRestart(12);

	if (option == SUB_MENU_5 || option == SUB_MENU_6 || option == SUB_MENU_7 || option == SUB_MENU_8)
		usePreDefinedSpeed = true;
	if (option == SUB_MENU_5)
		randomizeBehavior = 0;
	if (option == SUB_MENU_6)
		randomizeBehavior = 1;
	if (option == SUB_MENU_7)
		randomizeBehavior = 2;
	if (option == SUB_MENU_8)
		randomizeBehavior = 3;

	if (option == SUB_MENU_9)
		holdBugsWhenLeftButtonOfMouseIsDown = true;
	if (option == SUB_MENU_10)
		holdBugsWhenLeftButtonOfMouseIsDown = false;

	if (option == SUB_MENU_11)
		overLapBehavior = true;
	if (option == SUB_MENU_12)
		overLapBehavior = false;
}

void set_up_menu(void)
{
	int menu, submenu, submenu2, submenu3, submenu4;

	// create the menu and
	// tell glut that "processMenuEvents" will
	// handle the events

	submenu = glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("1", SUB_MENU_1);
	glutAddMenuEntry("4", SUB_MENU_2);
	glutAddMenuEntry("8", SUB_MENU_3);
	glutAddMenuEntry("12", SUB_MENU_4);


	submenu2 = glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("100ms", SUB_MENU_5);
	glutAddMenuEntry("150ms", SUB_MENU_6);
	glutAddMenuEntry("200ms", SUB_MENU_7);
	glutAddMenuEntry("1s", SUB_MENU_8);

	submenu3 = glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("Yes, Hold the Bugs when left button of mouse is down", SUB_MENU_9);
	glutAddMenuEntry("No, Don't Hold the Bugs when left button of mouse is down", SUB_MENU_10);

	submenu4 = glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("Try To Prevent Overlap Of Bugs As Much As Possible", SUB_MENU_11);
	glutAddMenuEntry("Strictly No Overlap of Bugs, Which May Cause Unexpected Behavior Such As Infinite Loop", SUB_MENU_12);

	menu = glutCreateMenu(processMenuEvents);

	//add entries to our menu
	glutAddSubMenu("Restarting Simulation with # of Bugs", submenu);
	glutAddSubMenu("Run Randmize Movement Function Every", submenu2);
	glutAddSubMenu("Hold the Bugs (Stop Bugs from Moving) When Left Button of Mouse if Down (Dragging Mode)", submenu3);
	glutAddSubMenu("Overlap of Bugs: Strictly No Overlap (Not Recommended) or try to prevent it as much as possible (Recommended)", submenu4);

	glutAddMenuEntry("Exit Program", MENU_1);


	// attach the menu to the right button
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}



int main(int argc, char** argv)
{
	time(&startTime);
	time(&randmoizeStartTime);
	createObjects();
	addObject(4);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(anim);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMove);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialkey);
	set_up_menu(); // build pop up menu
	glutMainLoop();
	return 0;
}