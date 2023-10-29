
#include "Enemy.hpp"
#include "Dummy.hpp"
#include "Core/Engine.hpp"
#include <iostream>

#include "TestScene.hpp"

// TODO delete this once TileSet grid is settled
const std::vector<std::vector<int>> Grid = {
        {0,0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0,0} , {0,0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0,0} , {0,0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0,0}
    };
// int GridWidth = 4;
// int GridHeight = 4;
int GridWidthSize = 64;
int GridHeightSize = 64;


Enemy::Enemy(GameObject& Parent, std::string Label): 
    StateMachine(Parent, Label),
    _Hp(DEFAULT_HP),
    _AttackCooldown(DEFAULT_ATTACK_COOLDOWN),
    _DetectionRange(DEFAULT_DETECTION_RANGE),
    _AttackRange(DEFAULT_ATTACK_RANGE),
    _Damage(DEFAULT_DAMAGE),
    _KnockbackForce(DEFAULT_KNOCKBACK_FORCE),
    _MovimentationSpeed(DEFAULT_MOVIMENTATION_SPEED){}


void Enemy::SMStart(){
}

bool Enemy::MoveTo(Vector2 Destiny, float Dt){
    Destiny.x > Parent.Box.x ? SetFlip(Flip::H) : SetFlip(Flip::N);
    Vector2 Distance = Parent.Box.Center().DistVector2(Destiny);
    if(Distance.Magnitude()<_MovimentationSpeed*Dt){
        Parent.Box.SetCenter(Destiny);
        return false;
    }

    else{
        Collider->SetVelocity(Distance.Normalize()*_MovimentationSpeed*Dt); 
        return true; 
    }
}

float Enemy::GetAttackCooldown(){
    return _AttackCooldown;
}

float Enemy::GetDetectionRange(){
    return _DetectionRange;
}

float Enemy::GetAttackRange(){
    return _AttackRange;
}

float Enemy::GetDamage(){
    return _Damage;
}

float Enemy::GetMovimentationSpeed(){
    return _MovimentationSpeed;
}

float Enemy::GetKnockbackForce(){
    return _KnockbackForce;
}


void Enemy::SetAttackCooldown(float AttackCooldown){
    this->_AttackCooldown  = AttackCooldown;
}

void Enemy::SetDetectionRange(float DetectionRange){
    this->_DetectionRange = DetectionRange;
}

void Enemy::SetAttackRange(float AttackRange){
    this->_AttackRange  = AttackRange;
}

void Enemy::SetDamage(float Damage){
    this->_Damage  = Damage;
}

void Enemy::SetMovimentationSpeed(float MovimentationSpeed){
    this->_MovimentationSpeed  = MovimentationSpeed;
}

void Enemy::SetKnockbackForce(float KnockbackForce){
    this->_KnockbackForce  = KnockbackForce;
}


// ___________________________________________________________________EnemyBuilder___________________________________________________________________

Enemy::Builder::Builder(GameObject& Parent, std::string Label){
    _Enemy = new Enemy(Parent, Label);
}

Enemy::Builder::~Builder(){
    Reset();
}

Enemy::Builder& Enemy::Builder::SetAttackCooldown(float AttackCooldown){
    _Enemy->SetAttackCooldown(AttackCooldown);
    return *this;
}

Enemy::Builder& Enemy::Builder::SetDetectionRange(float DetectionRange){
    _Enemy->SetDetectionRange(DetectionRange);
    return *this;
}

Enemy::Builder& Enemy::Builder::SetAttackRange(float AttackRange){
    _Enemy->SetAttackRange(AttackRange);
    return *this;
}

Enemy::Builder& Enemy::Builder::SetDamage(float Damage){
    _Enemy->SetDamage(Damage);
    return *this;
}

Enemy::Builder& Enemy::Builder::SetMovimentationSpeed(float MovimentationSpeed){
    _Enemy->SetMovimentationSpeed(MovimentationSpeed);
    return *this;
}

Enemy::Builder& Enemy::Builder::SetKnockbackForce(float KnockbackForce){
    _Enemy->SetKnockbackForce(KnockbackForce);
    return *this;
}

Enemy::Builder& Enemy::Builder::SetCollider(AARectangle* Collider){

    _Enemy->Collider = Collider;
    _Enemy->Parent.AddComponent(Collider);
    return *this;
}

Enemy::Builder& Enemy::Builder::AddSprite(Sprite* Sheet){
     
    _Enemy->Parent.Depth = DepthMode::Foreground;
    _Enemy->Parent.Box.Redimension(Vector2(Sheet->GetWidth(), Sheet->GetHeight()));
    _Enemy->AddSprite(Sheet);
    return *this;
}

Enemy::Builder& Enemy::Builder::AddState(SMState Id, GenericState* Add){
    _Enemy->AddState(Id, Add);
    return *this;
}

Enemy::Builder& Enemy::Builder::SetInitialState(SMState Id){
    _Enemy->SetState(Id);
    return *this;
}

void Enemy::Builder::Reset(){
    _Enemy  = nullptr;
}

Enemy* Enemy::Builder:: Build(){
   
    if (_Enemy->GetCurrentState() == SMState::None) 
    {
        Error("Enemy::Builder::Build: State is none");
        return nullptr;
    }
    Enemy* Enemy = _Enemy;
    Reset();
    return Enemy;
}



// ___________________________________________________________________EnemyIdle___________________________________________________________________

EnemyIdle::EnemyIdle(const StateInfo& Specs):GenericState(Specs){
    _Randomizer = XrandU64(42);
    _WanderingTimer.Restart();
    _WanderingInterval = _Randomizer.gen()%MAX_WANDERING_INTERVAL+1;
}

void EnemyIdle::PhysicsUpdate(StateMachine& Sm, float Dt){
    Enemy* EnemySM = reinterpret_cast<Enemy*>(&Sm);
    _WanderingTimer.Update(Dt);

    if(Dummy::Player->Parent.Box.DistCenters(Sm.Parent.Box) <= EnemySM->GetDetectionRange()){
        _WanderingTimer.Restart();
        Sm.SetState(ENEMY_PURSUIT);
    }

    // if(_WanderingTimer.Get()>= _WanderingInterval){
    //     _WanderingTimer.Restart();
    //     _WanderingInterval = _Randomizer.gen()%MAX_WANDERING_INTERVAL+1;
    //     Sm.SetState(ENEMY_WALK);
    // }
}

// ___________________________________________________________________EnemyWalk___________________________________________________________________

EnemyWalk::EnemyWalk(const StateInfo& Specs):GenericState(Specs){
}

void EnemyWalk::PhysicsUpdate(StateMachine& Sm, float Dt){
}

// ___________________________________________________________________EnemyPursuit___________________________________________________________________

EnemyPursuit::EnemyPursuit(const StateInfo& Specs):GenericState(Specs){}

void EnemyPursuit::PhysicsUpdate(StateMachine& Sm, float Dt){
    Enemy* EnemySM = reinterpret_cast<Enemy*>(&Sm);

    float distanceToPlayer = Dummy::Player->Parent.Box.DistCenters(Sm.Parent.Box);

    if(distanceToPlayer >= EnemySM->GetDetectionRange()){
        std::queue<Vector2> empty;
        EnemyPath.swap(empty);
        Sm.SetState(ENEMY_IDLE);
        return;
    }

    if(distanceToPlayer < EnemySM->GetAttackRange()){
        std::queue<Vector2> empty;
        EnemyPath.swap(empty);
        Sm.SetState(ENEMY_ATTACK);
        return;
    }
    
    if(Engine::Instance().GetPing() && Test01::CollisionMap != nullptr)
    {
        std::vector<Point> path = AStar::Search(*Test01::CollisionMap, {(int)Sm.Parent.Box.Center().x/GridWidthSize, 
                                            (int)Sm.Parent.Box.Center().y/GridHeightSize}, 
                                            {(int)Dummy::Player->Parent.Box.Center().x/GridWidthSize, (int)Dummy::Player->Parent.Box.Center().y/GridHeightSize} 
                                            );
        for(auto p : path)
        {
            // std::cout  << p.x  << ' ' << p.y << '\n';//TODO REMOVE
            EnemyPath.emplace(Vector2(p.x*GridWidthSize+(GridWidthSize/2),p.y*GridHeightSize+(GridHeightSize/2)));
        }
        // std::cout <<path.size()<< '\n';//TODO REMOVE

        if(path.size() > 0) //shouldn't follow if there's no valid path
        {
            EnemyPath.emplace(Dummy::Player->Parent.Box.Center());
        }    
    };  

    if(EnemyPath.empty())
        return;

    Vector2 NextPoint = EnemyPath.front();

    if(EnemySM->Parent.Box.Center().Distance(NextPoint) <  GridWidthSize/2){
        EnemyPath.pop();
        if(EnemyPath.empty())
            return;
        NextPoint = EnemyPath.front();
    }

    EnemySM->MoveTo(NextPoint, Dt);
}

// ___________________________________________________________________EnemyFighting___________________________________________________________________

EnemyFighting::EnemyFighting(const StateInfo& Specs):GenericState(Specs){}

void EnemyFighting::Update(StateMachine& Sm, float Dt){
    Enemy* EnemySM = reinterpret_cast<Enemy*>(&Sm);

    _AttackCooldownTimer.Update(Dt);

    if(EnemySM->Parent.Box.Center().Distance(Dummy::Player->Parent.Box.Center()) >=  EnemySM->GetAttackRange()){
        Sm.SetState(ENEMY_IDLE);
        return;
    }

    if(_AttackCooldownTimer.Get() >= EnemySM->GetAttackCooldown()){
        Sm.SetState(ENEMY_ATTACK);
        _AttackCooldownTimer.Restart();
    }
}


// ___________________________________________________________________EnemyAttack___________________________________________________________________

EnemyAttack::EnemyAttack(const StateInfo& Specs):GenericState(Specs){
    _AttackTimer.Restart();
}

void EnemyAttack::PhysicsUpdate(StateMachine& Sm, float Dt){

    _AttackTimer.Update(Dt);
    Enemy* EnemySM = reinterpret_cast<Enemy*>(&Sm);
    if(_AttackTimer.Get()>ATTACK_TIME){
        Sm.SetState(ENEMY_FIGHTING);
        _AttackTimer.Restart();
    }

    Dummy::Player->MyCollider->ApplyForce((Dummy::Player->Parent.Box.Center()-EnemySM->Parent.Box.Center()).Normalized()*DEFAULT_KNOCKBACK_FORCE);
}

