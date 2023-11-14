#pragma once
class AnimSprite
{
public:

	//��������Ʈ ������ �ε���(��)
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
		if (mAnitime >= mTimeInterval)		//�ִϸ��̼� ���� �ӵ�
		{
			//todo
			//������� ��������Ʈ ������ �ε����� ������Ŵ
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

	//�Լ�����,���Ǹ� ���ļ� �ۼ�
	int GetCurIndexFrame() const			//GetCurIndexFrame  () ���⿡ mCurIndexFrame �� ���� ���� �ְڴ�
	{
		return mCurIndexFrame;
	}

};

