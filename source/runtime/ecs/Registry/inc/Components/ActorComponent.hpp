#pragma once 
#include "../AComponent.h"
#include "../ActorEvents.h"

class ActorComponent : public AComponent {  
public: 
    ActorComponent() {};
    virtual void onConstruct(float&& delta, float&& timeSinceStart_) {

    };
    virtual void onInitialize() override {
        Emitter_OnInitialize.Emit();
        initialized = true;
    }
    virtual void onUpdate(float&& delta, float&& timeSinceStart_) override {
        if (!initialized) {
            onInitialize();
        }
        Emitter_OnUpdate.Emit(std::move(delta), std::move(timeSinceStart_));
    };
    virtual void onDestroy() override {
        Emitter_OnDestroy.Emit();
    };


    Event_OnIntialize Emitter_OnInitialize;
    Event_OnUpdate Emitter_OnUpdate;
    Event_OnDestroy Emitter_OnDestroy;
}; 