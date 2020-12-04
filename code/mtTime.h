#ifndef MT_TIME_H
#define MT_TIME_H

#include <Windows.h>
#include <stdint.h>

namespace mt {

    class Time
    {
    private:
        static float m_DeltaTime;
        static LARGE_INTEGER m_LastTime;
    public:
        static int64_t GetCurrentTime();
        static float GetDeltaTime();
    };

    float Time::m_DeltaTime;
    LARGE_INTEGER Time::m_LastTime;

    int64_t Time::GetCurrentTime()
    {
        LARGE_INTEGER Frequency;
        QueryPerformanceFrequency(&Frequency);
        LARGE_INTEGER CurrentTime;
        QueryPerformanceCounter(&CurrentTime);
        return int64_t{CurrentTime.QuadPart/Frequency.QuadPart};
    }

    float Time::GetDeltaTime()
    {
        LARGE_INTEGER Frequency;
        QueryPerformanceFrequency(&Frequency);
        LARGE_INTEGER CurrentTime;
        QueryPerformanceCounter(&CurrentTime);
        m_DeltaTime = (float)(CurrentTime.QuadPart - m_LastTime.QuadPart) / (float)Frequency.QuadPart;
        m_LastTime = CurrentTime;
        return m_DeltaTime;
    }

}
#endif
