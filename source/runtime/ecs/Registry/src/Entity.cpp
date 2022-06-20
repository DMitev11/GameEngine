#include "../inc/Entity.h"
Entity::Entity() { 
}
Entity::Entity(const Entity& entity) { 
    this->_id = entity._id;
}
Entity::Entity(int& id_) { _id = id_; }
Entity Entity::create(int& id) {
    return Entity(id);
}