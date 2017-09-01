#ifndef INJECTEVENTCONTROLLER_H
#define INJECTEVENTCONTROLLER_H
#include <ctime>
#include <string>

class InjectEventController
{
public:
	InjectEventController();
    static std::string ADB;
    static std::string DEVICE;
	void touch_down(int x, int y, int pressure = 50);
	void touch_move(int x, int y, int pressure = 50);
	void touch_up();
	void swipe(int start_x, int start_y, int end_x, int end_y);
	void vibrate();
    static void* runSystem(void*);
private:
	int last_vibrate;
    FILE *pf;

	
};

#endif // 
