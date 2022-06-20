#pragma once
#include <string>

class AComponent {
protected:
    bool initialized = false;
public: 
    static constexpr auto in_place_delete = true;

    typedef void(AComponent::* OnInitialzeFunc)();
    typedef void(AComponent::* onUpdateFunc)(float&&, float&&); 
    typedef void(AComponent::* OnDestroyFunc)();

    AComponent() {}; 
    virtual void onConstruct(float&& delta, float&& timeSinceStart_) = 0;
    virtual void onInitialize() = 0;
    virtual void onUpdate(float&& delta, float&& timeSinceStart_) = 0;
    virtual void onDestroy() = 0;

};
