// #include "Mechanics/Equipment.hpp"

// #include "Core/Input.hpp"
// #include "Components/Sprite.hpp"
// #include "Components/AACircle.hpp"

// #include "Definitions.hpp"

// Equipment::Equipment(GameObject& Parent)
// : Component(Parent)
// {
//     // _Type = COMPONENT_EQUIP;
//     // Parent.AddComponent(new AACircle(Parent, ColliderKind::Trigger, Circle(0,0,32)));
//     // Parent.Represents = INTERACT_MASK;
//     // Parent.Interacts = PLAYER_MASK;
//     // Sprite* Item = new Sprite(Parent,"./res/img/Item/Boot.png");
//     // Parent.Box.Redimension(Vector2(Item->GetWidth(), Item->GetHeight()));
//     // Parent.AddComponent(Item);
// }

// void Equipment::OnCollision(GameObject& Other)
// {
//     if(!Parent.IsDead() && Other.Contains(COMPONENT_PLAYER) && Input::Instance().KeyJustPressed(Key::F))
//     {
//         Parent.RequestDelete();
//     }
// }