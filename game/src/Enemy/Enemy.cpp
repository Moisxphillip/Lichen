
#include "Enemy/Enemy.hpp"
#include "Dummy.hpp"
#include "Core/Engine.hpp"
#include "Dialogue.hpp"
#include <iostream>
#include <ctime>

#include "Core/Input.hpp"
#include "Core/Engine.hpp"

#include "Character/Player.hpp"
#include "TestScene.hpp"
#include "Definitions.hpp"
#include "Tools/DistanceTrigger.hpp"

#include "TestScene.hpp"


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
    _MovimentationSpeed(DEFAULT_MOVIMENTATION_SPEED),
    _FlickTime(0.0f),
    _Flick(false),
    MyCollider(nullptr)
    {
        // TODO invert depedence
        Parent.Represents = ENEMY_MASK | ENEMY_ATK_MASK;//Only use ATK_MASK in this part when you intend for the enemy to cause damage upon touch
        Parent.Interacts =  PLAYER_MASK | ENEMY_MASK | CollisionMask::Terrain;
        MyStats = DEFAULT_STATS; //TODO be sure thsi works
        // EnemyCount++; TODO move enemycoutn to facotry
        _HitCooldown.SetLimit(DEFAULT_INVULNERABILITY);
        _HitCooldown.Update(DEFAULT_INVULNERABILITY);

    }

Enemy::~Enemy(){}


void Enemy::SMStart()
{
    Parent.AddComponent(new Attack(Parent, MyStats, {10, 1, ScalingStats::Strength}, Parent.Interacts));
    Parent.AddComponent(new DistanceTrigger(Parent, this, 2560, DistTriggerMode::Delete));
}

void Enemy::SMUpdate(float Dt)
{
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
    if(_CurrState != ENEMY_HURT && !Parent.IsDead() && Other.Contains(COMPONENT_ATTACK) && static_cast<bool>(Other.Represents & PLAYER_ATK_MASK))
    {
        Attack* Atk = (Attack*)Other.GetComponent(COMPONENT_ATTACK);
        int Dmg = Combat::CalculateDamage(Atk->Attacker, Atk->Data, MyStats);

        // TODO reaadd drop
        // if(MyStats.HP <= 0)
        // {
        //     SetState(PLAYER_DEATH);
        //     GameObject* Drop = new GameObject();
        //     Drop->Depth = DepthMode::Dynamic;
        //     Drop->AddComponent(new Equipment(*Drop));
        //     Drop->Box.SetCenter(Parent.Box.Center());
        //     Engine::Instance().CurrentScene().AddGameObj(Drop);
        //     Parent.RequestDelete();
        //     return;
        // }
        SetState(ENEMY_HURT);
        MyCollider->ApplyForce(Other.Box.Center().DistVector2(Parent.Box.Center()).Normalized() * Atk->Data.Knockback * 50000);
        MyCollider->SetFriction(0.05f);
        _HitCooldown.Restart();
    }
}

#define MOVE_SPD 2000

void Enemy::MoveTo(Vector2 Destiny, float Dt)
{
    Destiny.x < Parent.Box.Center().x ? SetFlip(Flip::N) : SetFlip(Flip::H);
    Vector2 Distance = Parent.Box.Center().DistVector2(Destiny);

    if(Distance.MagnitudeSquared() < MOVE_SPD*MOVE_SPD *Dt)
    {
        Parent.Box.SetCenter(Destiny);
    }

    MyCollider->ApplyForce(Distance.Normalized()*MOVE_SPD); 
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


// ___________________________________________________________________EnemyBuilder___________________________________________________________________

Enemy::Builder::Builder(GameObject& Parent, std::string Label)
{
    _Enemy = new Enemy(Parent, Label);
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

#define DETECTION_RANGE 380*380
#define MEMORY_RANGE 550*550

EnemyIdle::EnemyIdle(const StateInfo& Specs):GenericState(Specs){}

void EnemyIdle::PhysicsUpdate(StateMachine& Sm, float Dt){
    float DistSq = Player::Self != nullptr ? Player::Self->Parent.Box.Center().DistanceSquared(Sm.Parent.Box.Center()) : DETECTION_RANGE+1;

    if(DistSq < DETECTION_RANGE)
    {
        Sm.SetState(ENEMY_WALK);
        return;
    }
}


// ___________________________________________________________________EnemyWalk___________________________________________________________________

#define SEARCH_TIME 0.8f
#define FOLLOW_RANGE 80*80

EnemyWalk::EnemyWalk(const StateInfo& Specs):GenericState(Specs)
{
    _SearchPath.SetLimit(SEARCH_TIME + Engine::RandomFloat());
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
    float DistSq = Player::Self != nullptr ? Player::Self->Parent.Box.Center().DistanceSquared(Sm.Parent.Box.Center()) : DETECTION_RANGE+1;

    if(DistSq > MEMORY_RANGE)
    {
        Path = std::queue<Vector2>();
        Sm.SetState(ENEMY_IDLE);
        return;
    }

    _UpdateTime = false;
    if(DistSq < FOLLOW_RANGE)
    {
        Path = std::queue<Vector2>();
        reinterpret_cast<Enemy*>(&Sm)->MoveTo(Player::Self->Parent.Box.Center()+Vector2(0,32), Dt);
        return;
    }
    
    _UpdateTime = true;
    if(Player::Self != nullptr && _SearchPath.Finished() && Test01::CollisionMap != nullptr && Path.size()< 4)
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
            /*AStar::TrimSubgrid(*/*Test01::CollisionMap/*, MinY, MinX, MaxY-MinY, MaxX-MinX)*/,
            {(int)Sm.Parent.Box.Center().x/64, 
            (int)Sm.Parent.Box.Center().y/64}, 
            {(int)Player::Self->Parent.Box.Center().x/64,
            (int)(Player::Self->Parent.Box.Center().y+32)/64});

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
    reinterpret_cast<Enemy*>(&Sm)->MoveTo(NextPoint, Dt);
}

void EnemyWalk::Update(StateMachine& Sm, float Dt)
{
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



// ___________________________________________________________________EnemyFighting___________________________________________________________________

EnemyFighting::EnemyFighting(const StateInfo& Specs):GenericState(Specs){}

void EnemyFighting::Update(StateMachine& Sm, float Dt){
    Enemy* EnemySM = reinterpret_cast<Enemy*>(&Sm);

    _AttackCooldownTimer.Update(Dt);

    if(Dummy::Self != nullptr && EnemySM->Parent.Box.Center().Distance(Dummy::Self->Parent.Box.Center()) >=  EnemySM->GetAttackRange()){
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

    // TODO create collider (see player for reference)

    if(Dummy::Self != nullptr)
    {
        Dummy::Self->MyCollider->ApplyForce((Dummy::Self->Parent.Box.Center()-EnemySM->Parent.Box.Center()).Normalized()*DEFAULT_KNOCKBACK_FORCE);
    }
}

