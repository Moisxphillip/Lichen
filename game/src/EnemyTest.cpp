// #include "EnemyTest.hpp"
// #include "Dummy.hpp"

// #include "Core/Engine.hpp"

// #define EnemyTest_IDLE SMState::Type01
// #define EnemyTest_WALK SMState::Type02
// #define EnemyTest_ATTACK SMState::Type03


// EnemyTest::EnemyTest(GameObject& Parent, std::string Label, float DetectionDistance, float AttackDistance): StateMachine(Parent, Label), _DetectionDistance(DetectionDistance), _AttackDistance(AttackDistance), _AttackCooldown(2){
//     EnemyTestCollider = nullptr;
//     this->LastPlayerQuadrant = Vector2(0,0);
// }

// void EnemyTest::SMStart(){
//     Sprite* galo = new Sprite(Parent, "./res/galor.png");
//     Parent.Depth = DepthMode::Foreground;
//     Parent.Box.Redimension(Vector2(galo->GetWidth(), galo->GetHeight()));
//     AddSprite(galo);

//     EnemyTestCollider = new AARectangle(Parent, ColliderKind::Rigid, Rectangle(0,0, galo->GetWidth(),galo->GetHeight()));
//     Parent.AddComponent(EnemyTestCollider);

//     StateInfo SI = {EnemyTest_IDLE, 0, 1, 0, false, true};
//     EnemyTestIdle *EI = new EnemyTestIdle(SI);
//     AddState(EnemyTest_IDLE, EI);
//     SetState(EnemyTest_IDLE);

//     SI = {EnemyTest_WALK, 0, 1, 0, false, true};
//     EnemyTestWalk * EW = new EnemyTestWalk(SI);
//     AddState(EnemyTest_WALK, EW);

//     SI = {EnemyTest_ATTACK, 0, 1, 0, false, true};
//     EnemyTestAttack * EA = new EnemyTestAttack(SI);
//     AddState(EnemyTest_ATTACK, EA);
// }

// float EnemyTest::GetDetectionDistance(){
//     return _DetectionDistance;
// }

// float EnemyTest::GetAttackDistance(){
//     return _AttackDistance;
// }

// int EnemyTest::GetAttackCooldown(){
//     return _AttackCooldown;
// }

// void EnemyTest::SetDetectionDistance(float Distance){
//     this->_DetectionDistance = Distance;
// }

// //------------------------------IDLE------------------------------

// EnemyTestIdle::EnemyTestIdle(const StateInfo& Specs): GenericState(Specs){}

// void EnemyTestIdle::PhysicsUpdate(StateMachine& Sm, float Dt){}

// void EnemyTestIdle::Update(StateMachine& Sm, float Dt){
//     EnemyTest* EnemyTestSM = reinterpret_cast<EnemyTest*>(&Sm);
//     if(Dummy::Player->Parent.Box.DistCenters(Sm.Parent.Box) <= EnemyTestSM->GetDetectionDistance()){
//         Sm.SetState(EnemyTest_WALK);
//     }
// }


// //------------------------------WALK------------------------------
// EnemyTestWalk::EnemyTestWalk(const StateInfo& Specs): GenericState(Specs){}

// void EnemyTestWalk::PhysicsUpdate(StateMachine& Sm, float Dt){
//     EnemyTest* EnemyTestSM = reinterpret_cast<EnemyTest*>(&Sm);
//     if(Dummy::Player->Parent.Box.DistCenters(Sm.Parent.Box) >= EnemyTestSM->GetDetectionDistance()){
//         Sm.SetState(EnemyTest_IDLE);
//     }


//     const std::vector<std::vector<int>> Grid = {
//         {0,0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0,0} , {0,0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0,0} , {0,0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0,0}
//     };

//     int GridWidth = 4;
//     int GridHeight = 4;
//     int GridWidthSize = Engine::Instance().GetWindowSize().x/GridWidth;
//     int GridHeightSize = Engine::Instance().GetWindowSize().y/GridHeight;

//     if(EnemyTestSM->LastPlayerQuadrant != Vector2(Dummy::Player->Parent.Box.Center().x/GridWidthSize, Dummy::Player->Parent.Box.Center().y/GridHeightSize)){
//             std::vector<Point> path = AStar::Search(Grid, {(int)Sm.Parent.Box.Center().x/GridWidthSize, 
//                                                 (int)Sm.Parent.Box.Center().y/GridHeightSize}, 
//                                                 {Dummy::Player->Parent.Box.Center().x/GridWidthSize, Dummy::Player->Parent.Box.Center().y/GridHeightSize}
//                                                 );
//             std::queue<Point> q(std::deque<Point>(path.begin(), path.end()));
//             EnemyTestSM->EnemyTestPath = q;
//             EnemyTestSM->LastPlayerQuadrant = Vector2(Dummy::Player->Parent.Box.Center().x/GridWidthSize, Dummy::Player->Parent.Box.Center().y/GridHeightSize);
//     };  

//     Point p = EnemyTestSM->EnemyTestPath.front();
//     std::cout<<"Now running against "<<p.x<<" "<<p.y<<std::endl;
//     if(EnemyTestSM->Parent.Box.Center().Distance(Vector2(p.x*GridWidthSize+(GridWidthSize/2),p.y*GridHeightSize+(GridHeightSize/2))) <  GridWidthSize/2){
//         EnemyTestSM->EnemyTestPath.pop();
//         if(EnemyTestSM->EnemyTestPath.empty()){
//             Sm.SetState(EnemyTest_ATTACK);
//             std::cout<<"Comeou a atacar "<<std::endl;
//             return;
//         }
//     }
    
//     p = EnemyTestSM->EnemyTestPath.front();
//     Vector2 direction = EnemyTestSM->Parent.Box.Center().DistVector2(Vector2(p.x*GridWidthSize+(GridWidthSize/2),p.y*GridHeightSize+(GridHeightSize/2)));
//     EnemyTestSM->EnemyTestCollider->ApplyForce(direction.Normalize()*300);
        
    
// }

// EnemyTestAttack::EnemyTestAttack(const StateInfo& Specs):GenericState(Specs){
//     _AttackCooldownTimer.Restart();
// }

// void EnemyTestAttack::PhysicsUpdate(StateMachine& Sm, float Dt){
//     EnemyTest* EnemyTestSM = reinterpret_cast<EnemyTest*>(&Sm);

    

//     _AttackCooldownTimer.Update(Dt);

//     if(EnemyTestSM->Parent.Box.Center().Distance(Dummy::Player->Parent.Box.Center()) >=  EnemyTestSM->GetAttackDistance()){
//         Sm.SetState(EnemyTest_ATTACK);
//         return;
//     }

//     std::cout<<_AttackCooldownTimer.Get()<<std::endl;

//     if(_AttackCooldownTimer.Get() >= EnemyTestSM->GetAttackCooldown()){
//         std::cout<<"Pimba"<<std::endl;
//         Dummy::Player->MyCollider->ApplyForce((Dummy::Player->Parent.Box.Center()-EnemyTestSM->Parent.Box.Center()).Normalized()*30000);
//         _AttackCooldownTimer.Restart();
//     }

// }

