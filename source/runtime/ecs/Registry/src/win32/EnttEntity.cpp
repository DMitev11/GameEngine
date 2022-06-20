#include "../../inc/win32/EnttEntity.h" 
EnttEntity::EnttEntity(int& id, entt::entity& entity)
{
    this->_id = id;
    this->_entity = entity;
    return;
} 

EnttEntity::EnttEntity(EnttEntity const& entity) {
    _entity = entity._entity;
    _id = entity._id;
};
EnttEntity* EnttEntity::create(int& id, entt::entity& entity) {
    return new EnttEntity(id, entity);
}
 