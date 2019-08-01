#include <windows.h>
#include <iostream>
#include <math.h>
#include <gl/GL.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <fstream>

#include <cstdlib>

int index = 0;
const GLfloat lightPosition0[] = { 0.0,0.0,10.0,0.0 };	// ��Դλ��
const GLfloat lightPosition1[] = { 0.0,0.0,0.0,0.0 };
const GLfloat lightPosition2[] = { 10.0,0.0,0.0,0.0 };
const GLfloat lightPosition3[] = { 0.0,10.0,0.0,0.0 };
const GLfloat whiteLight[] = { 0.8,0.8,0.8,1.0 };		// ����ǿ�� + ɢ��ǿ��
GLfloat matSpecular[] = { 0.3,0.3,0.3,1.0 };			// ���ʵľ��淴����ɫ
GLfloat matShininess[] = { 10.0 };						// ���淴��ָ��
GLfloat matEmission[] = { 0.3,0.3,0.3,1.0 };			// ���ʵķ������ɫ
GLfloat spinX = 0;
GLfloat spinY = 0;
GLfloat spinZ = 0;
GLint const sphereNumber = 20;
GLfloat sphereList[sphereNumber][3] = {};

int readFile() {
	std::ifstream in("heart.csv");
	int tempCount = 0;
	char buffer[100];

	if (!in.is_open()) {
		std::cout << "Error opening file" << std::endl; 
		exit(1);
	}
	in.getline(buffer, 100);
	//std::cout << buffer << std::endl;
	//in.getline(buffer, 100);
	//std::cout << buffer << std::endl;
	while (!in.eof() && tempCount < 20) {
		char ch;
		//std::cout << "Yes" << std::endl;
		in.get(ch);
		//std::cout << ch << std::endl;
		for (int i = 0; i < 2;) {
			if (ch == ',') {
				i++;
				in.get(ch);
			}
			in.get(ch);
			//std::cout << ch << std::endl;
		}
		//std::cout << "Yes" << std::endl;

		in.get(ch);
		while (ch != ',') {
			sphereList[tempCount][0] *= 10;
			sphereList[tempCount][0] += ch - '0';
			in.get(ch);
		}
		//std::cout << sphereList[tempCount][0] << std::endl;
		in.get(ch);
		while (ch != ',') {
			sphereList[tempCount][1] *= 10;
			sphereList[tempCount][1] += ch - '0';
			in.get(ch);
		}
		//std::cout << sphereList[tempCount][1] << std::endl;

		for (int i = 0; i < 2;) {
			if (ch == ',') {
				i++;
				in.get(ch);
			}
			in.get(ch);
		}
		
		in.get(ch);
		while (ch != ',') {
			sphereList[tempCount][2] *= 10;
			sphereList[tempCount][2] += ch - '0';
			in.get(ch);
		}
		//std::cout << sphereList[tempCount][2] << std::endl;

		while (ch != '\n')
			in.get(ch);
		
		tempCount++;
	}

	int max[3] = { sphereList[0][0], sphereList[0][1], sphereList[0][2] };
	int min[3] = { sphereList[0][0], sphereList[0][1], sphereList[0][2] };
	for (int i = 0; i < 20; i++) {
		if (max[0] < sphereList[i][0])
			max[0] = sphereList[i][0];
		if(max[1] < sphereList[i][1])
			max[1] = sphereList[i][1];
		if(max[2] < sphereList[i][2])
			max[2] = sphereList[i][2];

		if (min[0] > sphereList[i][0])
			min[0] = sphereList[i][0];
		if (min[1] > sphereList[i][1])
			min[1] = sphereList[i][1];
		if (min[2] > sphereList[i][2])
			min[2] = sphereList[i][2];
	}
	//std::cout << max[0] << " " << max[1] << " " << max[2] << std::endl;
	//std::cout << min[0] << " " << min[1] << " " << min[2] << std::endl;

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 3; j++) {
			sphereList[i][j] -= min[j];
			sphereList[i][j] /= max[j] - min[j];
			sphereList[i][j] *= 8;
			//std::cout << sphereList[i][j] << std::endl;
		}
	}

	//std::cout << "Yes" << std::endl;

	return 0;
}

void init(){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	// ����Ϊ��ɫ
	glClearDepth(1.0);						// �����Ϊ���
	glShadeModel(GL_SMOOTH);				// ��ɫ�仯��Ϊ����

	glEnable(GL_LIGHTING);					// ׼�������Դ
	glEnable(GL_LIGHT0);					// �����Դ 0
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	glMatrixMode(GL_MODELVIEW);				// ����ģ�Ͳ���
	glLoadIdentity();

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0);	// ���ù�Դλ��
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLight);		// ���ù�Դɢ��
	glLightfv(GL_LIGHT0, GL_SPECULAR, whiteLight);		// ���ù�Դ����

	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);	// ���ù�Դλ��
	glLightfv(GL_LIGHT1, GL_DIFFUSE, whiteLight);		// ���ù�Դɢ��
	glLightfv(GL_LIGHT1, GL_SPECULAR, whiteLight);		// ���ù�Դ����

	glLightfv(GL_LIGHT2, GL_POSITION, lightPosition2);	// ���ù�Դλ��
	glLightfv(GL_LIGHT2, GL_DIFFUSE, whiteLight);		// ���ù�Դɢ��
	glLightfv(GL_LIGHT2, GL_SPECULAR, whiteLight);		// ���ù�Դ����

	glLightfv(GL_LIGHT3, GL_POSITION, lightPosition3);	// ���ù�Դλ��
	glLightfv(GL_LIGHT3, GL_DIFFUSE, whiteLight);		// ���ù�Դɢ��
	glLightfv(GL_LIGHT3, GL_SPECULAR, whiteLight);		// ���ù�Դ����

	glLightModeli(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

void createCoordinate() {
	//����һ������ϵ��
	GLint factor = 2;
	GLushort pattern = 0x5555;
	glEnable(GL_LINE);					// ���õ㻭
	glLineStipple(factor, pattern);		// �㻭ģʽ

	glLineWidth(2.0f);

	glBegin(GL_LINES);

	for (float i = 0; i < 3000.0f; i += 1.0) {
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, i, 0.0f);
		glVertex3f(3000.0f, i, 0.0f);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.0f, 0.0f, i);
		glVertex3f(3000.0f, 0.0f, i);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(i, 0.0f, 0.0f);
		glVertex3f(i, 3000.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, i);
		glVertex3f(0.0f, 3000.0f, i);

		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(i, 0.0f, 0.0f);
		glVertex3f(i, 0.0f, 3000.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, i, 0.0f);
		glVertex3f(0.0f, i, 3000.0f);
	}

	glEnd();

	//�رյ㻭    
	glDisable(GL_LINE);
}

void creatFrame() {
	GLint factor = 2;
	GLushort pattern = 0x5555;
	GLfloat X = sphereList[index][0];
	GLfloat Y = sphereList[index][1];
	GLfloat Z = sphereList[index][2];

	glEnable(GL_LINE);					// ���õ㻭
	glLineStipple(factor, pattern);		// �㻭ģʽ

	glLineWidth(4.0f);

	glBegin(GL_LINES);

	glVertex3f(X, Y, 0.0f);
	glVertex3f(X, Y, Z);
	glVertex3f(0.0f, Y, Z);
	glVertex3f(X, Y, Z);
	glVertex3f(X, 0.0f, Z);
	glVertex3f(X, Y, Z);

	glEnd();

	//�رյ㻭    
	glDisable(GL_LINE);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);		// 3D model ����ʾ�ռ��С

	glMatrixMode(GL_MODELVIEW);
	//gluLookAt(5.0, 5.0, 5.0,  0.0, 0.0, 0.0,  0, 1, 0);
	glPushMatrix();

	glRotatef(spinX, 1.0f, 0.0f, 0.0f);
	glRotatef(spinY, 0.0f, 1.0f, 0.0f);						// �������ת�Ƕ�
	glRotatef(spinZ, 0.0f, 0.0f, 1.0f);

	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);	// ���ò�������
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);	// ���ò�������
	glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);	// ���ò�������: ������ɫ

	createCoordinate();

	//glColor3f(1.0,1.0,1.0);
	for (int i = 0; i < sphereNumber; i++) {
		if (i == index) {
			glColor3f(1.0, 0.0, 1.0);
			creatFrame();
		} else {
			glColor3f(1.0, 1.0, 1.0);
		}
		glTranslatef(sphereList[i][0], sphereList[i][1], sphereList[i][2]);
		glutSolidSphere(0.2, 50, 50);
		glTranslatef(-sphereList[i][0], -sphereList[i][1], -sphereList[i][2]);
	}
	
	glPopMatrix();
	glFlush();
}

void reshape(GLsizei w, GLsizei h) {
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// std::cout << w << " and " << h << std::endl;

	if (w <= h)	{
		glOrtho(-10.0, 10.0, -10.0, 10.0 * h / w, -10.0, 10.0);
		// std::cout << "Yes" << std::endl;
	} else {
		glOrtho(-10.0, 10.0 * w / h, -10.0, 10.0, -10.0, 10.0);
		// std::cout << "No" << std::endl;
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboardFunc(unsigned char key, int x, int y) {
	switch (key) {
		case 'a':
			spinY += 1;
			break;

		case 'd':
			spinY -= 1;
			break;

		case 'w':
			spinX += 1;
			break;

		case 's':
			spinX -= 1;
			break;

		case 'e':
			spinZ += 1;
			break;

		case 'q':
			spinZ -= 1;
			break;
	}

	if (spinX < 360)
		spinX += 360;
	else if (spinX >= 360)
		spinX -= 360;
	
	if (spinY < 360)
		spinY += 360;
	else if (spinY >= 360)
		spinY -= 360;

	if (spinZ < 360)
		spinZ += 360;
	else if (spinZ >= 360)
		spinZ -= 360;

	glutPostRedisplay();
}

void mouseFunc(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		switch (button)
		{
			case GLUT_LEFT_BUTTON:
				if (index < sphereNumber - 1) {
					index++;
				}
				//matEmission[0] += 1.0;
				//if (matEmission[0] > 1.0)
					//matEmission[0] -= 1.1;
				break;

			//case GLUT_MIDDLE_BUTTON:
				//matEmission[1] += 1.0;
				//if (matEmission[1] > 1.0)
					//matEmission[1] -= 1.1;
				//break;

			case GLUT_RIGHT_BUTTON:
				if (index > 0) {
					index--;
				}
				//matEmission[2] += 1.0;
				//if (matEmission[2] > 1.0)
					//matEmission[2] -= 1.1;
				break;
		}


		glutPostRedisplay();
	}
}

int main(int argc, char *argv[]){
	//int index;
	readFile();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowSize(700, 700);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("Kobe's rotate sphere");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboardFunc);
	glutMouseFunc(mouseFunc);

	init();
	glutMainLoop();

	return EXIT_SUCCESS;
}