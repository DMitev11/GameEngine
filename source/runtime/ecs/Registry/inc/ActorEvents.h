#pragma once 
#include "AComponent.h"
class Event_OnIntialize {
private:
    std::map<AComponent*, AComponent::OnInitialzeFunc> observers;
public:

    void Attach(AComponent* component, AComponent::OnInitialzeFunc func) {
        observers.emplace(component, func);
    }
    void Detach(AComponent* component) {
        observers.erase(observers.find(component));
    }
    void Emit() {
        for (const auto observer : observers) {
            (observer.first->*observer.second)();

        }
    }

};

class Event_OnUpdate {
private:
    std::map<AComponent*, AComponent::onUpdateFunc> observers;
public:

    void Attach(AComponent* component, AComponent::onUpdateFunc func) {
        observers.emplace(component, func);
    }
    void Detach(AComponent* component) {
        observers.erase(observers.find(component));
    }
    void Emit(float&& delta, float&& timeFromStart) {
        for (const auto observer : observers) {
            (observer.first->*observer.second)(std::move(delta), std::move(timeFromStart));
        }
    }

};

class Event_OnDestroy {
private:
    std::map<AComponent*, AComponent::OnDestroyFunc> observers;
public:

    void Attach(AComponent* component, AComponent::OnDestroyFunc func) {
        observers.emplace(component, func);
    }
    void Detach(AComponent* component) {
        observers.erase(observers.find(component));
    }
    void Emit() {
        for (const auto observer : observers) {
            (observer.first->*observer.second)();
        }
    }

};