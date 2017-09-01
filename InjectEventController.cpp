#include "InjectEventController.h"
using namespace std;

#include <ctime>
#include <iostream>
#include <string>
#include <unistd.h>

InjectEventController::InjectEventController()
{
	last_vibrate = time(NULL);
}

std::string InjectEventController::ADB = "/Users/violynne/Library/Android/sdk/platform-tools/adb shell mysend ";
std::string InjectEventController::DEVICE  = "/dev/input/event4 ";
struct params{
    int type;
    int x;
    int y;
    int p;
};

void* InjectEventController::runSystem(void* p){
    params* params = reinterpret_cast<struct params* >(p);
    system((ADB + to_string(params->type) + " " + DEVICE + to_string(params->x) + " " + to_string(params->y)).c_str());
    cout<<"finish system"<<endl;
    return NULL;
}


void InjectEventController::touch_down(int x, int y, int pressure)
{
    pthread_t thread;
    params tmp;
    tmp.type = 0;
    tmp.x = x;
    tmp.y = y;
    tmp.p = pressure;
    pthread_create(&thread, NULL, InjectEventController::runSystem, &tmp);
    //system((ADB + "0 " + DEVICE + to_string(x) + " " + to_string(y)).c_str());
}

void InjectEventController::touch_move(int x, int y, int pressure){
    pthread_t thread;
    params tmp;
    tmp.type = 1;
    tmp.x = x;
    tmp.y = y;
    tmp.p = pressure;
    cout<< x << ' ' << y << endl << endl;
    pthread_create(&thread, NULL, InjectEventController::runSystem, &tmp);
    //system((ADB + "1 " + DEVICE + to_string(x) + " " + to_string(y)).c_str());
}

void InjectEventController::touch_up()
{
    cout<<"-------up-------"<< (float)clock() / CLOCKS_PER_SEC << endl;
	system((ADB + "2 " + DEVICE).c_str());
    cout<<"-------up-------"<< (float)clock() / CLOCKS_PER_SEC << endl << endl;
}

void InjectEventController::swipe(int start_x, int start_y, int end_x, int end_y)
{
	string cmd = "/Users/violynne/Library/Android/sdk/platform-tools/adb shell input swipe " + to_string(start_x) + " " + to_string(start_y) + " " + to_string(end_x) + " " + to_string(end_y);
	system(cmd.c_str());
}

void InjectEventController::vibrate()
{
	if (time(NULL) - last_vibrate > 2)
	{
		system("/Users/violynne/Library/Android/sdk/platform-tools/adb shell am startservice -n com.hwj.test/com.hwj.test.MyService");
		last_vibrate = time(NULL);
	}
}
