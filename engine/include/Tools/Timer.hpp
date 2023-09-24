#ifndef LICHEN_TIMER
#define LICHEN_TIMER

class Timer
{
    private:
        float _Time;

    public:
        Timer();
        float Get();
        void Update(float Dt);
        void Restart();
};

#endif//LICHEN_TIMER