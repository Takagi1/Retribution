#include "pch.h"
#include "Animation.h"

Animation::Animation() : totalTime(0)
{

}


Animation::~Animation()
{

}

void Animation::RestartAnimation()
{
	totalTime = 0;
}
