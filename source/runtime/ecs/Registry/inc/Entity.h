#pragma once
class Entity {
protected:
    int _id = -1;
public:
    Entity();
    Entity(int& id);
    Entity(const Entity&);
    ~Entity() {}; 
    static Entity create(int& id);

    int id(){ return _id; };
};
