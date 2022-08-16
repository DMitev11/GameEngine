#pragma once
#include <vector>
#include <map>
#include "Entity.h"
#include "AComponent.h"
//link: https://docs.microsoft.com/en-us/cpp/cpp/lvalues-and-rvalues-visual-cpp?view=msvc-170
//link: https://en.cppreference.com/w/cpp/language/value_category 
class Registry {
protected:

    Registry() {};

    Registry(Registry const&) {};
    Registry& operator=(Registry const&) {};

    static Registry* _get();

    static int _generateId();
    
// Parameters 
    static Registry* instance;
    void* registry = nullptr;
    int nonce = 0; 
    std::map<int, Entity*> entities;
private: 

public: 

    using default_component_class = AComponent;

    ~Registry() {};

    static Entity* createEntity();  
    static Entity* createActor();  

    static Entity* getEntity(int id);
    Entity* _getEntity(int id);
    static void removeEntity(int id);

    static void Update(float&& delta); 

    template<typename Component> 
    static std::vector<Component*> getAllComponents();
    template<typename Component>
    static std::vector<Component*> getAllComponents(std::vector<Entity*>&);
    /*template<typename Component>
    static std::vector<Component*> getAllComponents(Entity*);*/
    template<typename Component, typename... Args>
    static Component& addComponent(Entity*, Args&&...);
    template<typename Component, typename... Args>
    static Component* getComponent(Entity*, Args&&...);
    template<typename Component, typename... Args> 
    static Component& updateComponent(Entity*, Args&&...);
    template<typename Component>
    static void removeComponent(Entity*); 
};

#include "../src/Registry.hpp"