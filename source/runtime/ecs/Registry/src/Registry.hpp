#include <entt.hpp>
#include "../inc/win32/EnttEntity.h"
#include "inc/Components/IdComponent.h"
#include "inc/Components/TickComponent.hpp"

//@TODO: Pointers to removed components still exist, as well as the allocated memory for them
Registry* Registry::_get() {
    if (!instance || instance->registry == nullptr) {
        instance = new Registry(); 
        instance->registry = new entt::registry();
    }
    return instance;
}
int Registry::_generateId() {
    Registry* instance = _get();
    int returnNonce = instance->nonce;
    instance->nonce++;
    return returnNonce;
}

//Static Declarations 
Registry* Registry::instance{nullptr}; 

//Actual declarations

void Registry::Update(float&& delta) {
    Registry* _instance = _get();
    auto entity = instance->_getEntity(0);

    std::vector<Entity*> entities;
    std::vector<TickComponent*> components = getAllComponents<TickComponent>(entities);
    for (TickComponent* component : components) {
        // TODO: Add runtime-generated `timeSinceStart` argument
        component->onUpdate(std::move(delta), 0);

    }
    return;
}
  
Entity* Registry::createEntity() {
    Registry* _instance = _get();
    entt::registry* _registry = (entt::registry*)_instance->registry;
    entt::entity entt_entity = _registry->create();
    int id = _generateId();
    EnttEntity* entity = EnttEntity::create(id, entt_entity);
    _registry->emplace<Id>(entity->entity(), std::move(id));
    _instance->entities[id] = entity;
    return (EnttEntity*)(_instance->entities[id]);
}
 
  
Entity* Registry::createActor() {
    Registry* _instance = _get();
    entt::registry* _registry = (entt::registry*)_instance->registry;
    entt::entity entt_entity = _registry->create();
    int id = _generateId();
    EnttEntity* entity = EnttEntity::create(id, entt_entity);
    _registry->emplace<Id>(entity->entity(), std::move(id));
    auto& component = _registry->emplace<TickComponent>(entity->entity(), 0.f, 0.f);
    component.onConstruct(0.f, 0.f);
    _instance->entities[id] = entity;
    return (EnttEntity*)(_instance->entities[id]);
}
 
Entity* Registry::getEntity(int id) { 
    Registry* _instance = _get();
    return _instance->_getEntity(id);
}

Entity* Registry::_getEntity(int id) {
    Entity* entity = this->entities[id];
    return (EnttEntity*)(entity);
}

void Registry::removeEntity(int id) {
    Registry* _instance = _get();
    entt::registry* _registry = (entt::registry*)_instance->registry;
    assert(_instance->entities[id]);
    Entity* entity = _instance->entities[id];
    const entt::entity entt_entity = ((EnttEntity*)(entity))->entity();
    AComponent* const tick = _registry->try_get<TickComponent>(entt_entity);
    if (tick)tick->onDestroy(); 
    _registry->destroy(entt_entity);
    delete _instance->entities[id];
    _instance->entities.erase(id);
}

template<typename Component>
std::vector<Component*> Registry::getAllComponents() {
    Registry* _instance = _get();
    entt::registry* _registry = (entt::registry*)_instance->registry;
    auto view = _registry->view<Component>();
    std::vector<Component*> components; 
    for (auto&& [entity, component] : view.each()) {
        components.push_back(&component);
    }; 
    return components;
}

template<typename Component>
std::vector<Component*> Registry::getAllComponents(std::vector<Entity*>& entities_) { 
    Registry* _instance = _get();
    entt::registry* _registry = (entt::registry*)_instance->registry;
    auto view = _registry->view<Component, Id>();
    std::vector<Component*> components;  
    for (auto&& [entity, component, id] : view.each()) {
        components.push_back(&component);
        EnttEntity* entity = (EnttEntity*)_instance->_getEntity(id.id);
        entities_.push_back(entity);
    }; 
    return components;
}

////@TODO: Get all children components, rather than all of class
//template<typename Component> 
//std::vector<Component*> Registry::getAllComponents(Entity* entity_) {
//    Registry* _instance = _get();
//    entt::registry* _registry = (entt::registry*)_instance->registry; 
//    entt::entity entity = ((EnttEntity*)entity_)->entity();
//    auto const storage = _registry->storage();
//    std::vector<Component*> components;
//    for (auto pool : storage) { 
//        if(pool.second.contains(entity))
//        {
//            auto const name = typeid(pool.second.type().name()).name();
//            auto const index = pool.second.type().index();
//            components.push_back((Component*)(pool.second.get(entity)));
//        }
//    } 
//    return components;
//}
 
template<typename Component, typename... Args>
Component& Registry::addComponent(Entity* entity, Args&&... args) {
    //std::string const msg = "Registry:: Component needs to derive from" + (typeid(default_component_class).name());
    assert(typeid(default_component_class).hash_code() == typeid(Component).hash_code()
        || typeid(default_component_class).before(typeid(Component)));
    Registry* _instance = _get();
    entt::registry* _registry = (entt::registry*)_instance->registry;
    if (entity->id() <= -1) throw "Invalid entity"; 
    Component& component = _registry->emplace<Component>(((EnttEntity*)entity)->entity(), std::forward<Args>(args)...);
    component.onConstruct(std::forward<Args>(args)...);
    TickComponent& tick = _registry->get<TickComponent>(((EnttEntity*)entity)->entity()); 
    AComponent::onUpdateFunc updateFunc = &AComponent::onUpdate;
    AComponent::OnDestroyFunc destroyFunc = &AComponent::onDestroy;
    tick.Emitter_OnUpdate.Attach(&component, updateFunc);
    tick.Emitter_OnDestroy.Attach(&component, destroyFunc);
    return component;
}  
 
template<typename Component, typename... Args>
Component* Registry::getComponent(Entity* entity, Args&&... args) {
    Registry* _instance = _get();
    entt::registry* _registry = (entt::registry*)_instance->registry;
    if (entity->id() <= -1) throw "Invalid entity";
    entt::entity entt_entity = ((EnttEntity*)entity)->entity(); 
    return _registry->try_get<Component>(entt_entity);
}    

template<typename Component, typename... Args>
Component& Registry::updateComponent(Entity* entity, Args&&... args) {
    Registry* _instance = _get();
    entt::registry* _registry = (entt::registry*)_instance->registry;
    if (entity->id() == -1) throw "Invalid entity";
    entt::entity entt_entity = ((EnttEntity*)entity)->entity();
    return _registry->patch<Component>(entt_entity, std::forward<Args>(args)...);
}

template<typename Component>
void Registry::removeComponent(Entity* entity) {
    Registry* _instance = _get();
    entt::registry* _registry = (entt::registry*)_instance->registry;
    if (entity->id() <= -1) throw "Invalid entity";
    entt::entity entt_entity = ((EnttEntity*)entity)->entity();
    Component* const component = _registry->try_get<Component>(entt_entity);
    auto const type = entt::type_hash<Component>::value();
    assert(component);
    component->onDestroy(); 
    _registry->remove<Component>(entt_entity);
    clean_pools<Component>(_registry);
    return;
} 

template<typename Component>
void clean_pools(entt::registry* registry)
{
    for (auto const pool : registry->storage()) {
        if(entt::type_hash<Component>::value() == pool.second.type().hash()
            && pool.second.size() <=0)
        {
            delete &pool.second;
        }
    } 
}