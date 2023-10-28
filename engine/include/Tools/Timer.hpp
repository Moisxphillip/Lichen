#ifndef LICHEN_TIMER
#define LICHEN_TIMER

class Timer
{
    private:
        float _Time;
        float _Limit;

    public:
        Timer(float TimeLimit = 0);
        float Get();
        void Update(float Dt);
        void Restart();
        bool Finished();
        void SetLimit(float TimeLimit);
};

#endif//LICHEN_TIMER