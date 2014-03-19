/*
*
*	Star Wars: Astromechs
*	By: Darren Kent
*
*/
#include <time.h>

#include "Debug.h"
#include "TimeManager.h"

TimeManager::TimeManager() {
	DebugMessage( "Initializing Time Manager...", 3 );
	mFrames				= 0;
	mFrameRefreshCap	= 200;
	mCurrentTime		= 0.0;
	mStartTime			= 0.0;
	mDeltaTime			= 0.0;
	mLastTime			= 0.0;
	mLastKeyFrame		= 0.0;
	mFramesPerSecond	= 0.0;
	srand( (unsigned int)time( NULL ) );
}

void TimeManager::StartTime() {
	mStartTime = clock();
}

void TimeManager::TimeFrame() {
	mFrames ++;
	mCurrentTime	= clock() - mStartTime;
	mDeltaTime		= mCurrentTime - mLastTime;
	mLastTime		= mCurrentTime;

	if ( mFrames % mFrameRefreshCap == 0 ) {
		mFramesPerSecond	= mFrameRefreshCap / ( ( mCurrentTime - mLastKeyFrame ) / 1000.0 );
		mLastKeyFrame		= mCurrentTime;
	}
}

double TimeManager::GetDeltaTime() {
	return mDeltaTime;
}

double TimeManager::GetDeltaTimeSeconds() {
	return mDeltaTime / 1000.0;
}

double TimeManager::GetFramesPerSecond() {
	return mFramesPerSecond;
}

float TimeManager::GetActiveTime() {
	return (float)( clock() - mStartTime );
}