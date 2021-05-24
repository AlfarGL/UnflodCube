#pragma once

class CCube
{
public:
	CCube(const std::string& strPathCon, const std::string& strPathRec,
		std::ios_base::openmode mode = std::ios::out | std::ios::in) :
		recordfile(strPathRec.c_str()),
		configfile(strPathCon.c_str())
	{
		Init();
		message = "Fighting！";
	}
	~CCube();
	void Display();
	void Check(unsigned char& c);

	void Set_size_font_up();
	void Set_size_font_down();
	void Previous_problem();
	void Next_problem();

private:
	struct SSurface
	{
		int dir_x;
		int dir_y;
		int color;
	}surface[6];
	const float SIZE_X=0.1f;//每一面所占屏幕宽度
    float SIZE_Y;
	const int order[4] = { 0,4,2,5 };
	int answer;
	std::string message;
	int err_time;

	int randnum0_1[4];
	int randnum0_6[4];
	int middle[5], angle[5];

	//std::string  record_path;
	//std::string  congfig_path;
	std::fstream configfile;
    std::fstream recordfile;//("C:\\Users\\yangq\\Desktop\\record.txt", std::ios::in | std::ios::out);
	int size_font;//size of font
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