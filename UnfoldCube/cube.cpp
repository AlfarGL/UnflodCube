#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <GL/freeglut.h>
#include <fstream>
#include "cube.h"
#include "m_text.h"

//fstream  configfile( "C:\\Users\\yangq\\Desktop\\config.txt", ios_base::in | ios_base::out);

const float M_COLOR_LIST[18] = { 1,0,0,
0,1,0,
0,0,1,
1,1,0,
0,1,1,
1,0,1 };
//std::string name = "test.txt";


void CCube::Init() 
{
	srand(time(0));
	for (int i = 0; i < 6; i++)
	{
		surface[i].dir_x = rand() % 4;
		surface[i].dir_y = rand() % 2;
		surface[i].color = i;
	}
	answer = rand() % 4;
	err_time = 0;

	for (size_t i = 0; i < 4; i++)
	{
		randnum0_1[i] = rand() % 2;
		randnum0_6[i] = rand() % 6;
	}

	for (size_t i = 0; i < 5; i++)
	{
		middle[i] = rand() % 6;
		angle[i] = rand() % 4;
	}
	int n = 0;
	do
	{
		for (size_t i = 0; i < 4; i++)
		{
			if (middle[i] == middle[4] &&
				angle[i] == angle[4]) {
				middle[4] = rand() % 6;
				angle[4] = rand() % 4;
				n = 0;
				break;
			}
			else
				++n;
		}
	} while (n < 3);
}

CCube::~CCube()
{
	if (configfile.is_open())
		configfile.close();
	if (recordfile.is_open())
		recordfile.close();
}

void CCube::Display() {
	float width = float(glutGet(GLUT_WINDOW_WIDTH));
	float height = float(glutGet(GLUT_WINDOW_HEIGHT));
	SIZE_Y = SIZE_X *  width /height;

	selectFont(48, GB2312_CHARSET, "微软雅黑");
	glColor3f(1.0f, 1.0f, 0.0f);//设置字体颜色
	glRasterPos2f(-0.9f, 0.95f);
	drawCNString("根据正方体表面展开图，选择以下四个选项中等价的展开图，填写数字1 - 4。");

	glRasterPos2f(-0.9f, 0.8f);
	drawCNString("展开图");
	glRasterPos2f(-0.9f, 0.2f);
	drawCNString("选项1");
	glRasterPos2f(0.0f, 0.2f);
	drawCNString("选项2");
	glRasterPos2f(-0.9f, -0.4f);
	drawCNString("选项3");
	glRasterPos2f(0.0f, -0.4f);
	drawCNString("选项4");

	glRasterPos2f(-0.9f, -0.95f);
	char* str = new char[message.size()+1];
	for (size_t i = 0; i < message.size(); i++)
	{
		str[i] = message[i];
	}
	str[message.size()] = '\0';
	drawCNString(str);

	Display_true(middle[4], angle[4],-0.9,0.9);
	
	float  position[8] = { -0.9,0.3,0,0.3,-0.9,-0.3,0,-0.3 };
	for (size_t i = 0; i < 4; i++)
	{
		if (i == answer)
			Display_true(middle[i], angle[i], position[i * 2], position[i * 2 + 1]);
		else
			Display_false(middle[i], angle[i], position[i * 2], position[i * 2 + 1],i);
	}

}

void  CCube::Simple_status(int& middle, int& angle, SSurface* end_sf, SSurface* surface) {

	int distance = (middle + 3) % 4;
	for (int i = 0; i < 4; i++)
	{
		end_sf[i] = surface[(i + distance) % 4];
	}
	end_sf[4] = surface[4];
	end_sf[5] = surface[5];
	end_sf[4].dir_x = (surface[4].dir_x + distance) % 4;
	end_sf[5].dir_x = (surface[5].dir_x + 4 - distance) % 4;//确定中心图像，

	end_sf[1].dir_x = (end_sf[1].dir_x + angle) % 4;//旋转中心图像
	SSurface temp[4];
	for (int i = 0; i < 4; i++)
	{
		temp[i] = end_sf[order[(-angle + 4 + i) % 4]];
		temp[i].dir_x = (temp[i].dir_x + angle) % 4;
	}
	for (size_t i = 0; i < 4; i++)
		end_sf[order[i]] = temp[i];//旋转上下左右图像旋转
	end_sf[3].dir_x = (end_sf[3].dir_x + 4 - angle) % 4;//旋转后侧图像

}

void  CCube::Fill(float x, float y, SSurface& ss) {
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_LOOP);//开始循环线图
	glVertex3f(x, y, 0.0f);
	glVertex3f(x + SIZE_X, y, 0.0f);
	glVertex3f(x + SIZE_X, y - SIZE_Y, 0.0f);
	glVertex3f(x, y - SIZE_Y, 0.0f);
	glEnd(); //结束循环线图
	glColor3f(M_COLOR_LIST[ss.color * 3], M_COLOR_LIST[ss.color * 3 + 1],
		M_COLOR_LIST[ss.color * 3 + 2]);
	glBegin(GL_LINES);//开始画线
	switch (ss.dir_x)
	{
	case 0:
		glVertex3f(x + SIZE_X / 2, y - SIZE_Y / 2, 0.0f);
		glVertex3f(x + SIZE_X / 2, y, 0.0f);
		break;
	case 1:
		glVertex3f(x + SIZE_X / 2, y - SIZE_Y / 2, 0.0f);
		glVertex3f(x + SIZE_X, y - SIZE_Y / 2, 0.0f);
		break;
	case 2:
		glVertex3f(x + SIZE_X / 2, y - SIZE_Y / 2, 0.0f);
		glVertex3f(x + SIZE_X / 2, y - SIZE_Y, 0.0f);
		break;
	case 3:
		glVertex3f(x + SIZE_X / 2, y - SIZE_Y / 2, 0.0f);
		glVertex3f(x, y - SIZE_Y / 2, 0.0f);
		break;
	default:
		break;
	}
	glEnd(); //结束画线

	int index;
	ss.dir_y ? index = (ss.dir_x + 1) % 4 : index = (ss.dir_x + 3) % 4;
	glBegin(GL_LINES);//开始画线
	switch (index)
	{
	case 0:
		glVertex3f(x + SIZE_X / 2, y - SIZE_Y / 2, 0.0f);
		glVertex3f(x + SIZE_X / 2, y - SIZE_Y / 4, 0.0f);
		break;
	case 1:
		glVertex3f(x + SIZE_X / 2, y - SIZE_Y / 2, 0.0f);
		glVertex3f(x + SIZE_X / 4 * 3, y - SIZE_Y / 2, 0.0f);
		break;
	case 2:
		glVertex3f(x + SIZE_X / 2, y - SIZE_Y / 2, 0.0f);
		glVertex3f(x + SIZE_X / 2, y - SIZE_Y / 4 * 3, 0.0f);
		break;
	case 3:
		glVertex3f(x + SIZE_X / 2, y - SIZE_Y / 2, 0.0f);
		glVertex3f(x + SIZE_X / 4, y - SIZE_Y / 2, 0.0f);
		break;
	default:
		break;
	}
	glEnd(); //结束画线
	
}

void CCube::Display_true(int& middle, int& angle, float x, float y) {
	SSurface end_sf[6];
	SSurface ss_temp[6];

	if (middle < 4)
		Simple_status(middle, angle, end_sf, surface);
	else {
		int m = 1, a;
		if (middle == 4)
			a = 1;
		else
			a = 3;
		Simple_status(m, a, end_sf,surface);
		m = 2;
		for (size_t i = 0; i < 6; i++)
		{
			ss_temp[i] = end_sf[i];
		}
		Simple_status(m, angle, end_sf,ss_temp);
	}

	Fill(x + SIZE_X, y, end_sf[4]);
	Fill(x, y - SIZE_Y, end_sf[0]);
	Fill(x + SIZE_X, y - SIZE_Y, end_sf[1]);
	Fill(x + SIZE_X * 2, y - SIZE_Y, end_sf[2]);
	Fill(x + SIZE_X * 3, y - SIZE_Y, end_sf[3]);
	Fill(x + SIZE_X, y - SIZE_Y * 2, end_sf[5]);
}

void CCube::Display_false(int& middle, int& angle, float x, float y,int i) {
	SSurface end_sf[6];
	SSurface ss_temp[6];

	if (middle < 4)
		Simple_status(middle, angle, end_sf, surface);
	else {
		int m = 1, a;
		if (middle == 4)
			a = 1;
		else
			a = 3;
		Simple_status(m, a, end_sf, surface);
		m = 2;
		for (size_t i = 0; i < 6; i++)
		{
			ss_temp[i] = end_sf[i];
		}
		Simple_status(m, angle, end_sf, ss_temp);
	}
	if (randnum0_1[i]) {
		end_sf[randnum0_6[i]].dir_x = (end_sf[randnum0_6[i]].dir_x + 1) % 4;
	}
	else
	{
		end_sf[randnum0_6[i]].dir_x = (end_sf[randnum0_6[i]].dir_x + 1) % 4;
		end_sf[(randnum0_6[i] + 1) % 6].dir_x = (end_sf[(randnum0_6[i] + 1) % 6].dir_x + 3) % 4;
	}
	Fill(x + SIZE_X, y, end_sf[4]);
	Fill(x, y - SIZE_Y, end_sf[0]);
	Fill(x + SIZE_X, y - SIZE_Y, end_sf[1]);
	Fill(x + SIZE_X * 2, y - SIZE_Y, end_sf[2]);
	Fill(x + SIZE_X * 3, y - SIZE_Y, end_sf[3]);
	Fill(x + SIZE_X, y - SIZE_Y * 2, end_sf[5]);
}

void CCube::Check(unsigned char& c) {
	if (c != answer + 49) {
		err_time++;
		message = "回答错误，错误次数：";
		message.push_back(err_time+48);
		std::string tmp = "你的回答是：";
		tmp.push_back(c);
		message += tmp;
	}
	else {
		message = "回答正确！";
		Init();
	}
}

void CCube::Set_size_font_up() {
	if (configfile.is_open())
		configfile << "sdf  " << std::endl;
	else
		message.append(" esdf");
}
void CCube::Set_size_font_down() {}
void CCube::Previous_problem() {}
void CCube::Next_problem() {}

