#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H
#include "MouseEventListener.h"


class EventListener
{
public:
	EventListener(const EventListener&) = delete;
	EventListener(EventListener&&) = delete;
	EventListener& operator =(const EventListener&) = delete;
	EventListener& operator =(EventListener&&) = delete;

	EventListener() = delete;
	~EventListener();

	static void Update();
	
	static bool KEY_UP;
	static bool KEY_DOWN;
	static bool KEY_LEFT;
	static bool KEY_RIGHT;
	static bool KEY_B;
	static bool KEY_C;

	

};
#endif // !EVENTLISTENER_H
