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
        
        virtual void Start();
        virtual void Pause();
        virtual void Resume();
        virtual void LoadAssets();
        virtual void PhysicsUpdate(float);
        virtual void Update(float);
        virtual void Render();

        Music * _StateMusic;
       
    public:
        Camera Cam;
        
        void StateStart();
        void StatePause();
        void StateResume();
        void StateUpdate(float);
        void StatePhysicsUpdate(float);
        void StateRender();

        bool HasStarted();
        bool PopRequested();
        bool QuitRequested();
        void RequestQuit();

        State();
        virtual ~State();


        std::weak_ptr<GameObject> AddGameObj(GameObject*);
        std::weak_ptr<GameObject> AddLateRenderObj(GameObject*);
        std::weak_ptr<GameObject> GetGameObjPtr(GameObject*);
        std::weak_ptr<GameObject> GetLateRenderObjPtr(GameObject*);
        

};

#endif//LICHEN_STATE