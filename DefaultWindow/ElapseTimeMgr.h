#pragma once
class ElapseTimeMgr
{
private:
    LARGE_INTEGER m_frequency;
    LARGE_INTEGER m_lastTime;
public:
    static ElapseTimeMgr& GetInstance()
    {
        static ElapseTimeMgr instance;
        return instance;
    }

    float GetElapsedTime()
    {
        LARGE_INTEGER currentTime;
        QueryPerformanceCounter(&currentTime);

        float elapsedTime = (float)(currentTime.QuadPart - m_lastTime.QuadPart) / (float)m_frequency.QuadPart;

        m_lastTime = currentTime;

        return elapsedTime;
    }
    

private:
    ElapseTimeMgr()
    {
        QueryPerformanceFrequency(&m_frequency);
        QueryPerformanceCounter(&m_lastTime);
    }
};
