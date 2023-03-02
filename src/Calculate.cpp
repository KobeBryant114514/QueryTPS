#include <ScheduleAPI.h>
#include <ctime>
#include <HookAPI.h>
#include "Global.h"

typedef std::chrono::high_resolution_clock timer_clock;
#define TIMER_START auto start = timer_clock::now();
#define TIMER_END auto elapsed = timer_clock::now() - start; long long timeReslut = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

unsigned short ticks = 0;
bool cmspt = false;
float CurrentTPS;
float AverageTPS = 20;
float mspt;
std::list<unsigned short> avrtps;

THook(void, "?tick@ServerLevel@@UEAAXXZ", Level* _this) {
	ticks++;
	TIMER_START
	original(_this);
	TIMER_END
	if (cmspt == true) {
		mspt = (double)timeReslut / 1000;
		cmspt = false;
	}
	return;
}

void CaculateTPS() {
	std::thread th1([] {
		while (true) {
			std::this_thread::sleep_for(std::chrono::seconds(1));
			cmspt = true;
            if (mspt <= 50) {
                CurrentTPS = 20;
            }
            else {
                CurrentTPS = (float)(1000.0 / mspt);
            }
		}
	});
	th1.detach();
}

void Avtps() {
	std::thread th2([] {
		while (true) {
			std::this_thread::sleep_for(std::chrono::seconds(5));
			avrtps.push_back(ticks);
			ticks = 0;
			if (avrtps.size() >= 12) {
				avrtps.clear();
				continue;
			}
			unsigned short ticks_minute = 0;
			for (auto i : avrtps) {
				ticks_minute = ticks_minute + i;
			}
			AverageTPS = (float)ticks_minute / (5*(float)avrtps.size());
		}
	});
	th2.detach();
}