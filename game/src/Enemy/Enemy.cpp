
#include "Enemy/Enemy.hpp"
#include "Dummy.hpp"
#include "Core/Engine.hpp"
#include "Dialogue.hpp"
#include <iostream>
#include <ctime>

#include "Core/Input.hpp"
#include "Core/Engine.hpp"

#include "Character/Player.hpp"
// #include "TestScene.hpp"
#include "Definitions.hpp"
#include "Tools/DistanceTrigger.hpp"

#include "Scene/MainGame.hpp"
#include "Mechanics/Progress.hpp"

int GridWidthSize = 64;
int GridHeightSize = 64;

int Enemy::EnemyCount = 0;
int Enemy::MaxEnemyCount = 20;


Enemy::Enemy(GameObject& Parent, std::string Label, Stats EnemyStats): 
    StateMachine(Parent, Label),
    _Hp(DEFAULT_HP),
    _AttackCooldown(DEFAULT_ATTACK_COOLDOWN),
    _DetectionRange(DEFAULT_DETECTION_RANGE),
    _AttackRange(DEFAULT_ATTACK_RANGE),
    _Damage(DEFAULT_DAMAGE),
    _KnockbackForce(DEFAULT_KNOCKBACK_FORCE),
    _MovimentationSpeed(DEFAULT_MOVIMENTATION_SPEED),
    _SearchTime(DEFAULT_SEARCH_TIME),
    _FollowRange(DEFAULT_FOLLOW_RANGE),
    _MemoryFollowRange(DEFAULT_MEMORY_RANGE),
    _FlickTime(0.0f),
    _Flick(false),
    _AttackTimePoint(0.f),
    MyStats(EnemyStats),
    MyCollider(nullptr)
    {
        _HitCooldown.SetLimit(DEFAULT_INVULNERABILITY);
        _HitCooldown.Update(DEFAULT_INVULNERABILITY);
        EnemyCount++;
    }


Enemy::~Enemy()
{
    EnemyCount--;
}

void Enemy::SMStart()
{
    Parent.AddComponent(new Attack(Parent, MyStats, {10, 1, ScalingStats::Strength}, Parent.Interacts));
    Parent.AddComponent(new DistanceTrigger(Parent, this, 2560, DistTriggerMode::Delete));
}

void Enemy::SMUpdate(float Dt)
{
    if(Progress::KillMinions)
    {
        Parent.RequestDelete();
        return;
    }
    
    if(!_HitCooldown.Finished())
    {
        _HitCooldown.Update(Dt);
        if(_HitCooldown.Get() > _FlickTime)
        {
            _FlickTime+=0.1f;
            if(!_Flick)
            {
                _Sections[0].get()->SetAddColor(Color("#ffffff"));
                _Flick = true;
            }
            else
            {
                _Sections[0].get()->SetAddColor(Color("#000000"));
                _Flick = false;
            }
        }
        
        if (_HitCooldown.Finished())
        {
            _Sections[0].get()->SetAddColor(Color("#000000"));
            _Flick = false;
            _FlickTime = 0.0f;
        }
    }   
}

void Enemy::SMOnCollision(GameObject& Other)
{
    if(_CurrState != ENEMY_HURT &&  _CurrState != ENEMY_DEATH && !Parent.IsDead() && Other.Contains(COMPONENT_ATTACK) && static_cast<bool>(Other.Represents & PLAYER_ATK_MASK))
    {
        Attack* Atk = (Attack*)Other.GetComponent(COMPONENT_ATTACK);
        int Dmg = Combat::CalculateDamage(Atk->Attacker, Atk->Data, MyStats, Parent.Box.Center());

        // TODO reaadd drop
        if(MyStats.HP <= 0)
        {
            if(Player::Self != nullptr)
            {
                Player::Self->AddExperience(Combat::DeathExp(MyStats.Level));
            }

            _HitCooldown.Restart();
            SetState(ENEMY_DEATH);
            return;
            // GameObject* Drop = new GameObject();
            // Drop->Depth = DepthMode::Dynamic;
            // Drop->AddComponent(new Equipment(*Drop));
            // Drop->Box.SetCenter(Parent.Box.Center());
            // Engine::Instance().CurrentScene().AddGameObj(Drop);
            // Parent.RequestDelete();
            // return;
        }

        SetState(ENEMY_HURT);
        MyCollider->ApplyForce(Other.Box.Center().DistVector2(Parent.Box.Center()).Normalized() * Atk->Data.Knockback * 50000);
        MyCollider->SetFriction(0.05f);
        _HitCooldown.Restart();
    }
}


void Enemy::MoveTo(Vector2 Destiny, float Dt)
{
    Destiny.x < Parent.Box.Center().x ? SetFlip(Flip::N) : SetFlip(Flip::H);
    Vector2 Distance = Parent.Box.Center().DistVector2(Destiny);

    // For now the enemy is teleporting, leave it commented
    // if(Distance.MagnitudeSquared() < MOVE_SPD*MOVE_SPD *Dt)
    // {
    //     Parent.Box.SetCenter(Destiny);
    // }

    MyCollider->ApplyForce(Distance.Normalized()*_MovimentationSpeed); 
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

float Enemy::GetFlickTime()
{
    return _FlickTime;
}

float Enemy::GetSearchTime()
{
    return _SearchTime;
}

float Enemy::GetFollowRange()
{
    return _FollowRange;
}

float Enemy::GetMemoryFollowRange()
{
    return _MemoryFollowRange;
}

float Enemy::GetAttackTimePoint()
{
    return _AttackTimePoint;
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

void Enemy::SetFlickTime(float FlickTime)
{
    this->_FlickTime  = FlickTime;
}

void SetSearchTime();
        void SetFollowRange();
        void SetMemoryFollowRange();

void Enemy::SetSearchTime(float SearchTime)
{
    _SearchTime = SearchTime;
}

void Enemy::SetFollowRange(float FollowRange)
{
    _FollowRange = FollowRange;
}

void Enemy::SetMemoryFollowRange(float MemoryFollowRange)
{
    _MemoryFollowRange = MemoryFollowRange;
}

void Enemy::SettAttackTimePoint(float AttackTimePoint)
{
    _AttackTimePoint = AttackTimePoint;
}

// ___________________________________________________________________EnemyBuilder___________________________________________________________________

Enemy::Builder::Builder(GameObject& Parent, std::string Label, Stats EnemyStats)
{
    _Enemy = new Enemy(Parent, Label,EnemyStats);
    _Enemy->Parent.Represents = ENEMY_MASK;
    _Enemy->Parent.Interacts = PLAYER_MASK | ENEMY_MASK | CollisionMask::Terrain;
}

Enemy::Builder::~Builder()
{
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

Enemy::Builder& Enemy::Builder::SetRepresentationMask(CollisionMask Represents)
{
    _Enemy->Parent.Represents = Represents;
    return *this;
}

Enemy::Builder& Enemy::Builder::SetInteractionMask(CollisionMask Interacts)
{
    _Enemy->Parent.Interacts = Interacts;
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

Enemy::Builder& Enemy::Builder::SetFlickTime(float FlickTime){
    _Enemy->SetFlickTime(FlickTime);
    return *this;
}

Enemy::Builder& Enemy::Builder::SetAttackTimePoint(float AttackTimePoint)
{
    _Enemy->SettAttackTimePoint(AttackTimePoint);
    return *this;
}

Enemy::Builder& Enemy::Builder::SetCollider(AACollider* Collider){
    _Enemy->MyCollider = Collider;
    _Enemy->MyCollider->SetFriction(DEFAULT_FRICTION);
    _Enemy->MyCollider->GetBall().SetCenter(_Enemy->Parent.Box.Center());

    _Enemy->Parent.AddComponent(Collider);
    return *this;
}

Enemy::Builder& Enemy::Builder::AddSprite(Sprite* Sheet){
     
    _Enemy->Parent.Depth = DepthMode::Dynamic;
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

EnemyIdle::EnemyIdle(const StateInfo& Specs):GenericState(Specs){}

void EnemyIdle::PhysicsUpdate(StateMachine& Sm, float Dt)
{

    float DistSq = Player::Self != nullptr ? Player::Self->Parent.Box.Center().DistanceSquared(Sm.Parent.Box.Center()) : reinterpret_cast<Enemy*>(&Sm)->GetDetectionRange()+1;

    if(DistSq < reinterpret_cast<Enemy*>(&Sm)->GetDetectionRange())
    {
        Sm.SetState(ENEMY_WALK);
        return;
    }
}


// ___________________________________________________________________EnemyWalk___________________________________________________________________


EnemyWalk::EnemyWalk(const StateInfo& Specs):GenericState(Specs), _HasSetLimit(false)
{
    _AttackCooldownTimer.Restart();
    _SearchPath.Restart();
}

void EnemyWalk::Start()
{
    _UpdateTime = false;
    if(Path.empty())
    {
        return;
    }
    Path = std::queue<Vector2>();
}

void EnemyWalk::PhysicsUpdate(StateMachine& Sm, float Dt){
    Enemy* EnemySM = reinterpret_cast<Enemy*>(&Sm);

    float DistSq = Player::Self != nullptr ? Player::Self->Parent.Box.Center().DistanceSquared(Sm.Parent.Box.Center()) : EnemySM->GetDetectionRange() +1;

    if(DistSq > EnemySM->GetMemoryFollowRange())
    {
        Path = std::queue<Vector2>();
        Sm.SetState(ENEMY_IDLE);
        return;
    }

    _UpdateTime = false;


    if(DistSq < EnemySM->GetAttackRange() && _AttackCooldownTimer.Get()>=EnemySM->GetAttackCooldown())
    {
        Path = std::queue<Vector2>();
        _AttackCooldownTimer.Restart();
        Sm.SetState(ENEMY_ATTACK);
        return;
    }

    if(DistSq < EnemySM->GetFollowRange())
    {
        Path = std::queue<Vector2>();
        EnemySM->MoveTo(Player::Self->Parent.Box.Center()+Vector2(0,64), Dt);
        return;
    }
    
    _UpdateTime = true;
    if(Player::Self != nullptr && _SearchPath.Finished() && MainMap::CollisionMap != nullptr && Path.size()< 4)
    {
        Path = std::queue<Vector2>();//empty old Path values
        _SearchPath.SetLimit(1.0f+ Engine::RandomFloat());
        _SearchPath.Restart();
        // int MinX = (int)Sm.Parent.Box.Center().x/64, MaxX = (int)Player::Self->Parent.Box.Center().x/64;
        // int MinY = (int)Sm.Parent.Box.Center().y/64, MaxY = (int)(Player::Self->Parent.Box.Center().y+32/*offset*/)/64;
        // if(MinX > MaxX)
        // {
        //     std::swap(MinX, MaxX);
        // }
        // if(MinY > MaxY)
        // {
        //     std::swap(MinY, MaxY);
        // }
        // MinX-=3;
        // MinY-=3;
        // MaxX+=3;
        // MaxY+=3;
        
        std::vector<Point> path = AStar::Search(
            /*AStar::TrimSubgrid(*/*MainMap::CollisionMap/*, MinY, MinX, MaxY-MinY, MaxX-MinX)*/,
            {(int)Sm.Parent.Box.Center().x/64, 
            (int)Sm.Parent.Box.Center().y/64}, 
            {(int)Player::Self->Parent.Box.Center().x/64,
            (int)(Player::Self->Parent.Box.Center().y+64)/64});

        for(int i = 1; i < (int)path.size(); i++)
        {
            Path.emplace(Vector2(path[i].x*64 + 32, path[i].y*64 + 32));
        }
    };  

    if(Path.empty())
    {
        return;
    }

    Vector2 NextPoint = Path.front();

    if(Sm.Parent.Box.Center().DistanceSquared(NextPoint) <  24*24)
    {
        Path.pop();
        if(Path.empty())
        {
            return;
        }
        NextPoint = Path.front();
    }
    EnemySM->MoveTo(NextPoint, Dt);
}

void EnemyWalk::Update(StateMachine& Sm, float Dt)
{
    _AttackCooldownTimer.Update(Dt);

    if(!_HasSetLimit)
    {
         _SearchPath.SetLimit(reinterpret_cast<Enemy*>(&Sm)->GetSearchTime() + Engine::RandomFloat());
         _HasSetLimit = true;
    }

    if(_UpdateTime)
    {
        _SearchPath.Update(Dt);
    }
}

// ___________________________________________________________________EnemyHurt___________________________________________________________________

EnemyHurt::EnemyHurt(const StateInfo& Specs)
: GenericState(Specs)
{
    _HurtTime.SetLimit(DEFAULT_INVULNERABILITY);
}


void EnemyHurt::Start()
{
    _HurtTime.Restart();
}

void EnemyHurt::Update(StateMachine& Sm, float Dt)
{
    _HurtTime.Update(Dt);
    if(_HurtTime.Finished())
    {
        Sm.SetState(ENEMY_IDLE);
        reinterpret_cast<Enemy*>(&Sm)->MyCollider->SetFriction(DEFAULT_FRICTION);
    }
   
}

// ___________________________________________________________________EnemyDeath___________________________________________________________________

EnemyDeath::EnemyDeath(const StateInfo& Specs)
: GenericState(Specs)
{
    _HurtTime.SetLimit(DEFAULT_INVULNERABILITY);
}


void EnemyDeath::Start()
{
    _HurtTime.Restart();
}

void EnemyDeath::Update(StateMachine& Sm, float Dt)
{
    _HurtTime.Update(Dt);
    if(_HurtTime.Finished())
    {
        Sm.Parent.RequestDelete();
    }
   
}


// ___________________________________________________________________EnemyAttack___________________________________________________________________

EnemyAttack::EnemyAttack(const StateInfo& Specs):GenericState(Specs), _HasAttacked(false){
    _AttackTimer.Restart();
}

void EnemyAttack::PhysicsUpdate(StateMachine& Sm, float Dt){

    _AttackTimer.Update(Dt);
    Enemy* EnemySM = reinterpret_cast<Enemy*>(&Sm);

    if(_AttackTimer.Get()>ATTACK_TIME){
        Sm.SetState(ENEMY_IDLE);
        _AttackTimer.Restart();
        _HasAttacked = false;
        return;
    }

    if(!_HasAttacked && Player::Self && _AttackTimer.Get() >= EnemySM->GetAttackTimePoint())
    {
        EnemySM->MyCollider->SetVelocity(Vector2::ZERO);
    
        GameObject* Atk = new GameObject;
        Atk->Represents = ENEMY_ATK_MASK;

        Vector2 Direction = EnemySM->Parent.Box.Center().DistVector2(Player::Self->Parent.Box.Center());

        Atk->Box.SetCenter(EnemySM->Parent.Box.Center() + Vector2(Direction.x/std::fabs(Direction.x) *40.0f, 0.0f));
        Atk->AddComponent(new Attack(*Atk, EnemySM->MyStats, {10, 1, ScalingStats::Strength}, EnemySM->Parent.Interacts, 0.3));
        AACircle* Ball = new AACircle(*Atk, ColliderKind::Trigger, Circle(0,0, 80));
        Ball->SetFriction(0.0f);
        Atk->AddComponent(Ball);

        Engine::Instance().CurrentScene().AddGameObj(Atk);

        _HasAttacked = true;
    }

    
}

