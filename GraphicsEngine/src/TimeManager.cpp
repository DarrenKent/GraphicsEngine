/*
*
*	Graphics Engine
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
	mStartTime = (float)clock();
}

void TimeManager::TimeFrame() {
	mFrames ++;
	mCurrentTime	= (float)clock() - mStartTime;
	mDeltaTime		= mCurrentTime - mLastTime;
	mLastTime		= mCurrentTime;

	if ( mFrames % mFrameRefreshCap == 0 ) {
		mFramesPerSecond	= mFrameRefreshCap / ( ( mCurrentTime - mLastKeyFrame ) / 1000.0f );
		mLastKeyFrame		= mCurrentTime;
	}
}

float TimeManager::GetDeltaTime() {
	return mDeltaTime;
}

float TimeManager::GetDeltaTimeSeconds() {
	return mDeltaTime / 1000.0f;
}

float TimeManager::GetFramesPerSecond() {
	return mFramesPerSecond;
}

float TimeManager::GetActiveTime() {
	return (float)( clock() - mStartTime );
}