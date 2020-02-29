#ifndef TIMER_H
#define TIMER_H

class Timer {

public:
	Timer(const Timer&) = delete;
	Timer(Timer&&) = delete;
	Timer& operator =(const Timer&) = delete;
	Timer& operator =(Timer&&) = delete;

	Timer();
	~Timer();

	void Start();

private:
	int currentCount;
	sf::Time totalTime;
	sf::Clock timer;

};

#endif // !TIMER_H