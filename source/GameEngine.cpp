// GameEngine.cpp : Definesthe entry point for the application.
//
#pragma once
#include "GameEngine.h"   

#include <filesystem>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "inc/Rendering.h" 
#include "inc/Registry.h"
#include "inc/Components/RndComponent.hpp"

using std::filesystem::current_path;

using namespace std;

void testEntities()
{
	auto n = Registry::createActor();
	AComponent& ref = Registry::addComponent<RndComponent>(n, 0.f, 0.f);
	Registry::removeComponent<RndComponent>(n);
	Registry::removeEntity(n->id());
}

void testGraphics()
{
    auto window = (GLFWwindow *)Rendering::createWindow(); 
	auto shadersId = (GLuint*) Rendering::loadShaders(
		"assets/SimpleVertexShader.vert",
	"assets/SimpleFragmentShader.frag");
 
	GLfloat vertices[12] = {
		-1.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		-1.0f,  0.0f, 0.0f,
		0.0f,  0.0f, 0.0f,
	};
	GLuint indices[6] = {
		0,1,2,
		1,2,3
	};
	GLfloat vertices2[12] = {
		0.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  0.0f, 0.0f, 
		1.0f,  0.0f, 0.0f, 
	};
	GLuint indices2[6] = {
		0,1,2,
		1,2,3
	};
	GLfloat vertices3[12] = {
		-0.5f, 0.0f, 0.0f,
		0.5f, 0.0f, 0.0f,
		-0.5f,  1.0f, 0.0f,
		0.5f,  1.0f, 0.0f,
	};
	GLuint indices3[6] = {
		0,1,2,
		1,2,3
	};
	/// <summary>
	/// VAO 0 
	/// </summary>
	auto vao = VAO(Rendering::createVertexAttributeObjects(1));
	auto bufferData = (GLuint*) Rendering::createVertexBufferObject(vao.vao, vertices, sizeof(vertices));
	vao.vertexCount = sizeof(vertices) / (sizeof(GLfloat) * 3);
	auto ebo = (GLuint*) Rendering::createElementBufferObject(vao.vao, indices, sizeof(indices));
	vao.hasEbo = true;
	/// <summary>
	/// VAO 1
	/// </summary>
	auto vao2 = VAO(Rendering::createVertexAttributeObjects(1));
	auto bufferData2 = (GLuint*) Rendering::createVertexBufferObject(vao2.vao, vertices2, sizeof(vertices2));
	vao2.vertexCount = sizeof(vertices2) / (sizeof(GLfloat) * 3);
	auto ebo2 = (GLuint*)Rendering::createElementBufferObject(vao2.vao, indices2, sizeof(indices2));
	vao2.hasEbo = true;
	/// <summary>
	/// VAO 2
	/// </summary>
	auto vao3 = VAO(Rendering::createVertexAttributeObjects(1));
	auto bufferData3 = (GLuint*) Rendering::createVertexBufferObject(vao3.vao, vertices3, sizeof(vertices3));
	vao3.vertexCount = sizeof(vertices3) / (sizeof(GLfloat) * 3);
	auto ebo3 = (GLuint*)Rendering::createElementBufferObject(vao3.vao, indices3, sizeof(indices3));
	vao3.hasEbo = true; 


	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while(true)
	{
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(*((GLuint*)shadersId), "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		glUseProgram(*((GLuint*)shadersId));
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		glUseProgram(0);

		Rendering::draw(&vao, shadersId, sizeof(indices) / sizeof(GLfloat));
		Rendering::draw(&vao2, shadersId, sizeof(indices2) / sizeof(GLfloat));
		Rendering::draw(&vao3, shadersId, sizeof(indices3) / sizeof(GLfloat));
		//loads second time 
		Rendering::frame(window);
	}

}

int main()
{
	std::cout << current_path();
	cout << "Hello CMake." << endl;
	//testEntities();
	testGraphics();
	exit(0);
}
