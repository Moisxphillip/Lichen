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
        bool _LayerChanged;

        std::vector<std::shared_ptr<GameObject>> StateGameObjects;
        
        virtual void Start();
        virtual void Pause();
        virtual void Resume();
        virtual void LoadAssets();
        virtual void PhysicsUpdate(float);
        virtual void Update(float);
        virtual void LateUpdate(float);
        virtual void Render();

        Music * _StateMusic;
       
    public:
        Camera Cam;
        
        void StateStart();
        void StatePause();
        void StateResume();
        void StatePhysicsUpdate(float);
        void StateUpdate(float);
        void StateLateUpdate(float);
        void StateRender();

        bool HasStarted();
        bool PopRequested();
        bool QuitRequested();
        void RequestQuit();

        State();
        virtual ~State();

        std::weak_ptr<GameObject> AddGameObj(GameObject*);
        std::weak_ptr<GameObject> GetGameObjPtr(GameObject*);
};

#endif//LICHEN_STATE