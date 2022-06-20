#pragma once
#include "./ActorComponent.hpp" 
class RndComponent : public ActorComponent { 
private: 
    float deltaTime = 0.f;
    float timeSinceStart = 0.f;
public:
    static constexpr auto in_place_delete = true;

    RndComponent() {};
    
    RndComponent(float delta_, float timeSinceStart_) {
        deltaTime = delta_;
        timeSinceStart = timeSinceStart_;
    }
    
    void onConstruct(float&& delta, float&& timeSinceStart_) override {
        deltaTime = delta;
        timeSinceStart = timeSinceStart_;
    };
    
     void onInitialize() override { 
        ActorComponent::onInitialize();
    };
    
    void onUpdate(float&& delta, float&& timeSinceStart_) override {
        deltaTime = delta;
        timeSinceStart = timeSinceStart_;
        ActorComponent::onUpdate(std::move(delta), std::move(timeSinceStart_));
    };
    
    void onDestroy() override {};
     
};

