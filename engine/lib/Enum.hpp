#ifndef LYCHEN_ENUM
#define LYCHEN_ENUM

//Game components must be defined by the game as they're named.
enum ComponentType 
{
    _None =         0,
    _Type01 =  1 << 0,
    _Type02 =  1 << 1,
    _Type03 =  1 << 2,
    _Type04 =  1 << 3,
    _Type05 =  1 << 4,
    _Type06 =  1 << 5,
    _Type07 =  1 << 6,
    _Type08 =  1 << 7,
    _Type09 =  1 << 8,
    _Type10 =  1 << 9,
    _Type11 = 1 << 10,
    _Type12 = 1 << 11,
    _Type13 = 1 << 12,
    _Type14 = 1 << 13,
    _Type15 = 1 << 14,
    _Type16 = 1 << 15,
    _Type17 = 1 << 16,
    _Type18 = 1 << 17,
    _Type19 = 1 << 18,
    _Type20 = 1 << 19,
    _Type21 = 1 << 20,
    _Type22 = 1 << 21,
    _Type23 = 1 << 22,
    _Type24 = 1 << 23,
    _Type25 = 1 << 24,
    _Type26 = 1 << 25,
    _Type27 = 1 << 26,
    _Type28 = 1 << 27,
    _Type29 = 1 << 28,
    _Type30 = 1 << 29,
    _Type31 = 1 << 30,
    _Type32 = 1 << 31,
    //Extensible til' 64 if needed... I'm lazy to do that now.
    //TODO extend to 64 bits flags and add engine components with predefined values
};


#endif//LYCHEN_ENUM