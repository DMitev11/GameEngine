#pragma once
#include "../Entity.h"
#include <entt.hpp>

class EnttEntity : public Entity {
private:   
    //parameters
    entt::entity _entity{}; 
public: 
    EnttEntity(EnttEntity const&); 
    EnttEntity(int&, entt::entity&);
       
    entt::entity entity() {
        //Copy, instead of possibly reference it
        return entt::entity(_entity);
    }

    static EnttEntity* create(int&, entt::entity&); 
}; 