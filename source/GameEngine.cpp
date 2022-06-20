// GameEngine.cpp : Defines the entry point for the application.
//
#pragma once
#include "GameEngine.h"  
#include "runtime/ecs/Registry/inc/Registry.h"
#include "entt.hpp"
#include "runtime/ecs/Registry/inc/win32/EnttEntity.h"
#include "runtime/ecs/Registry/inc/AComponent.h" 
#include "runtime/ecs/Registry/inc/Components/RndComponent.hpp" 
using namespace std;

int main()
{ 
	cout << "Hello CMake." << endl; 
	auto registry = entt::registry();
	auto entity = registry.create();
	auto n = (EnttEntity*)Registry::createActor();    
	auto en = (EnttEntity*)Registry::createActor();    
	Registry::addComponent<RndComponent>(n, 0.f, 0.f); 
	Registry::addComponent<RndComponent>(en, 0.f, 0.f); 
	Registry::removeComponent<RndComponent>(n);
	Registry::removeComponent<RndComponent>(en);
	Registry::removeEntity(n->id());
	exit(0);
}
