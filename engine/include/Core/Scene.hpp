#ifndef LICHEN_STATE
#define LICHEN_STATE

//C++ includes
#include <vector>
#include <memory>

//Engine includes
#include "Core/GameObject.hpp"
#include "Core/Music.hpp"
#include "Core/Camera.hpp"

class Scene
{
    protected:
        bool _QuitRequested;
        bool _PopRequested;
        bool _Started;
        bool _LayerChanged;

        std::vector<std::shared_ptr<GameObject>> SceneGameObjects;
        
        virtual void Start();
        virtual void Pause();
        virtual void Resume();
        virtual void LoadAssets();
        virtual void PhysicsUpdate(float Dt);
        virtual void Update(float Dt);
        virtual void LateUpdate(float Dt);
        virtual void Render();

        Music * _SceneMusic;
       
    public:
        Camera Cam;
        
        void SceneStart();
        void ScenePause();
        void SceneResume();
        void ScenePhysicsUpdate(float Dt);
        void SceneUpdate(float Dt);
        void SceneLateUpdate(float Dt);
        void SceneRender();

        bool HasStarted();
        bool PopRequested();
        bool QuitRequested();
        void RequestQuit();

        Scene();
        virtual ~Scene();

        std::weak_ptr<GameObject> AddGameObj(GameObject*);
        std::weak_ptr<GameObject> GetGameObjPtr(GameObject*);
};

#endif//LICHEN_STATE