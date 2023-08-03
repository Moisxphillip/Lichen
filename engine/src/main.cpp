// #include <iostream>

// #define SDL_MAIN_HANDLED //Fix later, find out why it isn't recognizing the written main

// #include "../lib/Game.hpp"
// #include "SDL2/SDL.h"


// int main(int argc, char** argv)
// {
//     Game::Instance();
//     std::cout << "hello\n";
//     SDL_Delay(5000);
//     SDL_Quit();
//     return 0;
// }
   
    // SoLoud::Soloud *SoundEngine = new SoLoud::Soloud;
    // SoundEngine->init();
    // // SoLoud::Wav WaveFile;
    // // WaveFile.load("casio.wav");
    // // SoundEngine->play(WaveFile);
    // SoundEngine->deinit();
    // delete SoundEngine;
   
// #include "irrKlang.h"

    // irrklang::ISoundEngine *engine = irrklang::createIrrKlangDevice();
    // if (!engine)
    //     return 0; // error starting up the engine

    // irrklang::ISound *music = engine->play2D("test.mp3", false, false, true, irrklang::ESM_AUTO_DETECT, true);

    // // SDL_Delay(5000);
    // irrklang::ISoundEffectControl* fx = 0;
    // if (music)
    //   fx = music->getSoundEffectControl();

    // if (!fx)
    // {
    //   // some sound devices do not support sound effects.
    //   printf("This device or sound does not support sound effects.\n");
    // }
    // else
    // {
    //     fx->enableWavesReverbSoundEffect();
    // }
    // // while(engine->isCurrentlyPlaying("test.mp3")){}
    // engine->drop(); // delete engine