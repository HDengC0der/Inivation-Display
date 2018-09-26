// Created by denghan 2018/9/25
// right reserved
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <GL/glut.h>
using namespace std;

struct point{
	int xAddr;
	int yAddr;
	bool polarity;
};
vector<vector<point>> readTxt(){
	FILE *fp;
	char c;
	vector<vector<string>> data;
	vector<string> frame;
	string single_data="";
	fp=fopen("/var/www/html/data.txt","r");
	while((c=fgetc(fp))!=EOF){
		if(c=='/'){
			frame.push_back(single_data);
			single_data.erase(0);
		}else if(c=='\n'){
			data.push_back(frame);
			frame.clear();
		}else{
			single_data+=c;
		}
	}
	vector<vector<point>> result;
	for(int i=0; i<data.size(); i++){
		vector<point> temp;
		for(int j=0; j<data[i].size(); j+=3){
			int xAddress=atoi(data[i][j].c_str());
			int yAddress=atoi(data[i][j+1].c_str());
			int polarity=atoi(data[i][j+2].c_str());
			point tempPoint;
			tempPoint.xAddr=xAddress;
			tempPoint.yAddr=yAddress;
			tempPoint.polarity=polarity;
			temp.push_back(tempPoint);
		}
		result.push_back(temp);
	}
	return result;
}

const int windowWidth=400;
const int windowHeight=400;
vector<vector<point>> Data=readTxt();
static int Count=0;

void inivationDisplay(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPointSize(2.0);
	glBegin(GL_POINTS);
	for(int i=0; i<Data[Count].size(); i++){
		if(Data[Count][i].polarity==1){
			glColor3f(1.0f,0.0f,0.0f);
			glVertex2f(Data[Count][i].xAddr,Data[Count][i].yAddr);
		}else{
			glColor3f(0.0f,1.0f,0.0f);
			glVertex2f(Data[Count][i].xAddr,Data[Count][i].yAddr);
		}
	}
	glEnd();
	glFlush();
	glutSwapBuffers();
}

void timerFunc(int value){
	++Count;
	glutPostRedisplay();
	glutTimerFunc(33,timerFunc,1);
}

int main(int argc,char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(windowWidth,windowHeight);
	glutCreateWindow("Inivation display");
	gluOrtho2D(0.0,windowWidth,0.0,windowHeight);
	glutDisplayFunc(inivationDisplay);
	glutTimerFunc(33,timerFunc,1);
	glutMainLoop();
	return 0;
}
