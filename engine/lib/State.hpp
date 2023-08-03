#ifndef LICHEN_STATE
#define LICHEN_STATE

//C++ includes
#include <vector>
#include <memory>

//Engine includes
#include "GameObject.hpp"
#include "Music.hpp"
#include "Camera.hpp"

class State
{
    protected:
        bool _QuitRequested;
        bool _PopRequested;
        bool _Started;

        std::vector<std::shared_ptr<GameObject>> GameObjVec;
        std::vector<std::shared_ptr<GameObject>> LateRenderVec;
        
        void _StartArray();
        void _UpdateArray(float);
        void _RenderArray();

        Music * _StateMusic;
       
    public:
        Camera Cam;

        bool HasStarted();
        bool PopRequested();
        bool QuitRequested();
        void RequestQuit();

        State();
        virtual ~State();

        virtual void Start();
        virtual void Pause();
        virtual void Resume();

        std::weak_ptr<GameObject> AddGameObj(GameObject*);
        std::weak_ptr<GameObject> AddLateRenderObj(GameObject*);
        std::weak_ptr<GameObject> GetGameObjPtr(GameObject*);
        std::weak_ptr<GameObject> GetLateRenderObjPtr(GameObject*);
        
        virtual void LoadAssets();
        virtual void Update(float);
        virtual void Render();

};

#endif//LICHEN_STATE