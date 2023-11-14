#pragma once
class AnimSprite
{
public:

	//스프라이트 프레임 인덱스(값)
	int mCurIndexFrame = 0;
	float mAnitime = 0.0f;

	float mTimeInterval = 0.1f;

	int mTotalFrameCount = 0;




public:

	void CreatePSW(int TotalFrameCount, float floatmTimeInterval)
	{
		mTotalFrameCount = TotalFrameCount;
		mTimeInterval = floatmTimeInterval;
	}
	void UpdatePSW(float fElapseTime)
	{
		if (mAnitime >= mTimeInterval)		//애니메이션 동작 속도
		{
			//todo
			//순서대로 스프라이트 프레임 인덱스를 증가시킴
			if (mCurIndexFrame < mTotalFrameCount - 1)
			{
				mCurIndexFrame++;
			}
			else
			{
				mCurIndexFrame = 0;
			}

			mAnitime = 0.0f;
		}
		else
		{
			mAnitime = mAnitime + fElapseTime;
		}

	}

	//함수선언,정의를 합쳐서 작성
	int GetCurIndexFrame() const			//GetCurIndexFrame  () 여기에 mCurIndexFrame 이 값을 돌려 주겠다
	{
		return mCurIndexFrame;
	}

};

