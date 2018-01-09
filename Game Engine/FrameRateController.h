#pragma once
class FrameRateController
{
public:
	FrameRateController(unsigned int MaxFrameRate);
	~FrameRateController();

	void FrameStart(void);
	void FrameEnd(void);

	unsigned int GetFrameTime(void);

private:
	unsigned int mMaxFrameRate;
	unsigned int mTicksPerFrame;

	unsigned int mTickStart;
	unsigned int mTickEnd;

	unsigned int mFrameTime;
};

