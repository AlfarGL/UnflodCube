#pragma once

class CCube
{
public:
	bool flag = false;//if it true;exit;
	
	CCube();
	~CCube();
	void Display();
	void Check(unsigned char& c);
	void Set_size_font(int i);
	void Select_problem(bool  is_next_problem);

private:
	struct SSurface
	{
		int dir_x;
		int dir_y;
		int color;
	}surface[6];
	int answer;
	int randnum0_1[6];
	int randnum0_6[6];
	int middle[6], angle[6];

	const int order[4] = { 0,4,2,5 };
	const float SIZE_X=0.1f;//每一面所占屏幕宽度
    float SIZE_Y;
	
	std::string message;
	std::string message_status;
	
	const char* file_path_config = "config.txt";
	const char* file_path_record = "record.txt";

	int size_font;//size of font
	size_t num_err;//number of consecutive wrong answers
	size_t num_cca;//number of consecutive correct answers
	size_t num_problems;//The number of problems that have been done
	size_t num_doing;//The order of problems that is doing now 
	size_t num_mwa;//num_max_wrong_answer;
	long long score;//wrong -10, right   +1+num_cca*2

	void Init();
	void Display_true(int& middle, int& angle, float x, float y);
	void Display_false(int& middle, int& angle, float x, float y,int i);
	void Simple_status(int& middle, int& angle, SSurface* end_sf, SSurface* ss_temp);
	void Fill(float x, float y, SSurface& ss);
};