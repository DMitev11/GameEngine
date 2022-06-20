#pragma once
#include "ActorComponent.hpp"

class Id/*: public ActorComponent*/{
public:
    int id;

    Id(int&& id_)
    {
        id = id_;
    };
};
