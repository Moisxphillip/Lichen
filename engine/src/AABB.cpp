#include "../lib/AABB.hpp"

#include <algorithm>
#include <cmath>

bool AABB::CheckAndResolve(TestRect& Rect1, TestRect& Rect2)
{
    float Lx = std::max(Rect1.x, Rect2.x);
    float Ty = std::max(Rect1.y, Rect2.y);
    float Rx = std::min(Rect1.x + Rect1.w, Rect2.x + Rect2.w);
    float By = std::min(Rect1.y + Rect1.h, Rect2.y + Rect2.h);
    TestRect Intersection = {0, 0, 0, 0};
    if (Rx > Lx && By > Ty) 
    {
        float W = Rx - Lx;
        float H = By - Ty;
        Intersection = {Lx, Ty, W, H};
    }
    //Stationary x Stationary collision detection won't be avaliable as they can't be resolved. Change it tho if they are needed somehow, and add the correct treatment
    if (Intersection.w == 0 || (Rect1.Stationary && Rect1.Stationary))
    {
        return false;
    }

    float PenetrationX = 0.0f, PenetrationY = 0.0f;
    //TODO fix penetration when one square is fully inside another

    // Determine the direction of penetration
    if (Intersection.w < Intersection.h)
    {
        PenetrationX = ((Rect1.x < Rect2.x) ? -Intersection.w : Intersection.w);
        PenetrationY = 0.0f; //Won't fix on this axis
    }
    else
    {
        PenetrationY = ((Rect1.y < Rect2.y) ? -Intersection.h : Intersection.h);
        PenetrationX = 0.0f; //Won't fix on this axis
    }
    if(Rect1.Stationary || Rect2.Stationary)
    {
        if(!Rect1.Stationary)
        {
            Rect1.x += PenetrationX;
            Rect1.y += PenetrationY;
        }
        else
        {
            Rect2.x -= PenetrationX;
            Rect2.y -= PenetrationY;
        }
    }
    else if(Rect1.Rigid && Rect2.Rigid)
    {
        float TotalMass = Rect1.Mass + Rect2.Mass;
        float Mass1Ratio = Rect1.Mass/TotalMass;
        float Mass2Ratio = Rect2.Mass/TotalMass;

        Rect1.x += PenetrationX * Mass2Ratio;
        Rect1.y += PenetrationY * Mass2Ratio;
        Rect2.x -= PenetrationX * Mass1Ratio;
        Rect2.y -= PenetrationY * Mass1Ratio;
    }
    //No displacement for non-solids
    return true;

}

bool AABB::CheckAndResolve(TestCircle& Circle1, TestCircle& Circle2) 
{
    float Distance = std::pow(Circle1.x - Circle2.x, 2) + std::pow(Circle1.y - Circle2.y, 2);
    
    if (!(Circle1.Stationary && Circle2.Stationary) && Distance < std::pow(Circle1.r+Circle2.r, 2))
    {
        float CollisionAngle = std::atan2(Circle2.y - Circle1.y, Circle2.x - Circle1.x);
        float Overlap = (Circle1.r + Circle2.r) -  std::sqrt(Distance);
        if(Circle1.Stationary || Circle2.Stationary)
        {
            if(!Circle1.Stationary)
            {
                Circle1.x -= Overlap * std::cos(CollisionAngle);
                Circle1.y -= Overlap * std::sin(CollisionAngle);
            }
            else
            {
                Circle2.x += Overlap * std::cos(CollisionAngle);
                Circle2.y += Overlap * std::sin(CollisionAngle);
            }

        }
        else if(Circle1.Rigid && Circle2.Rigid)
        {
            float TotalMass = Circle1.Mass + Circle2.Mass;
            float Mass1Ratio = Circle1.Mass/TotalMass;
            float Mass2Ratio = Circle2.Mass/TotalMass;

            Circle1.x -= Overlap * Mass2Ratio * std::cos(CollisionAngle);
            Circle1.y -= Overlap * Mass2Ratio * std::sin(CollisionAngle);
            Circle2.x += Overlap * Mass1Ratio * std::cos(CollisionAngle);
            Circle2.y += Overlap * Mass1Ratio * std::sin(CollisionAngle);
        }
        return true;
    }
    return false;
}

bool AABB::CheckAndResolve(TestRect& Rect1, TestCircle& Circle1)
{
    float ClosestX = std::max(Rect1.x, std::min(Circle1.x, Rect1.x + Rect1.w));
    float ClosestY = std::max(Rect1.y, std::min(Circle1.y, Rect1.y + Rect1.h));
    float SqDistance = std::pow(Circle1.x - ClosestX, 2) + std::pow(Circle1.y - ClosestY, 2);

    if (!(Circle1.Stationary && Rect1.Stationary) && SqDistance < std::pow(Circle1.r, 2))
    {
        float CollisionAngle = std::atan2(Circle1.y - ClosestY, Circle1.x - ClosestX);
        float Overlap = Circle1.r - std::sqrt(SqDistance);

        if (Circle1.Stationary || Rect1.Stationary)
        {
            if (!Circle1.Stationary)
            {
                Circle1.x += Overlap * std::cos(CollisionAngle);
                Circle1.y += Overlap * std::sin(CollisionAngle);
            }
            else
            {
                Rect1.x -= Overlap * std::cos(CollisionAngle);
                Rect1.y -= Overlap * std::sin(CollisionAngle);
            }
        }
        else if (Circle1.Rigid && Rect1.Rigid)
        {
            float TotalMass = Circle1.Mass + Rect1.Mass;
            float CircleMassRatio = Circle1.Mass/TotalMass;
            float RectMassRatio = Rect1.Mass/TotalMass;

            Circle1.x += Overlap * RectMassRatio* std::cos(CollisionAngle);
            Circle1.y += Overlap * RectMassRatio * std::sin(CollisionAngle);
            Rect1.x -= Overlap * CircleMassRatio * std::cos(CollisionAngle);
            Rect1.y -= Overlap * CircleMassRatio * std::sin(CollisionAngle);
        }
        return true;
    }
    return false;
}