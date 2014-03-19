/*
*
*	Star Wars: Astromechs
*	By: Darren Kent
*
*/
#ifndef _TIME_MANAGER_
#define _TIME_MANAGER_

// Time Manager
class TimeManager{
	public:
		TimeManager();										// Time Manager Constructor

		void StartTime();									// Sets the start time of the manager
		void TimeFrame();									// Calculates each value for that frame

		double GetDeltaTime();								// Returns time since last frame in milliseconds
		double GetDeltaTimeSeconds();						// Returns time since last frame in seconds
		double GetFramesPerSecond();						// Returns the frames per second

		float GetActiveTime();								// Returns the amount of time since the Time Mgr was started	
	protected:
	private:
		double	mStartTime;									// Time in which the time manager started
		int		mFrames, mFrameRefreshCap;					// Frame count and the amount of frames we do before refresing calculations
		double	mCurrentTime, mLastTime, mDeltaTime;		// The current time, last frame's Time, and the time since last frame
		double	mFramesPerSecond, mLastKeyFrame;			// The average frames per second, and the last frame we checked fps
};

#endif // _TIME_MANAGER_
