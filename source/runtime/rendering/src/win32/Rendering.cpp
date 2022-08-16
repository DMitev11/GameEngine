#include "inc/Rendering.h"

#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
void* Rendering::createWindow()
{ 
	if(!glfwInit())
	{
		throw "Failed to initialize GLFW";
	}
	glfwWindowHint(GLFW_SAMPLES, 32); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(1024, 768, "GameEngine", NULL, NULL);
	glViewport(0, 0, 1024, 768);
    glfwMakeContextCurrent(window); 
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glewExperimental = true; 
	if(glewInit() != GLEW_OK)
	{
		throw "Failed to initialze GLEW"; 
	}
    return window;
}

//@TODO: Use buffer*, bufferSize and bufferLength to reinterpret passed data
//https://en.cppreference.com/w/cpp/string/byte/memcpy
//@TODO: Try using templates for the same as above (state types of parameters in the pack)

void* Rendering::createVertexAttributeObjects(unsigned int count) {
	GLuint* vao = new GLuint[count]{};
	glGenVertexArrays(count, vao);
	return vao;
}

template<typename... Args>
void* Rendering::createVertexBufferObject(void* vao, void* bufferData, Args&&... args)
{
	std::tuple<Args...> argsTuple{ std::forward<Args>(args)... };
	glBindVertexArray(*((GLuint*)vao));
	//@TODO: Size 4 instead of size 32, as the origin sizeof(var).Use length 
	// This will identify our vertex buffer
	GLuint* vbo = new GLuint();
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, vbo);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, *vbo);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, std::get<0>(argsTuple), bufferData, GL_STATIC_DRAW); 
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		3 * sizeof(GLfloat),                  // stride
		(void*)0            // array buffer offset
	);
	// Draw the triangle !
	glEnableVertexAttribArray(0);
	return vbo;
}
template<typename... Args>
void* Rendering::createElementBufferObject(void* vao, void* bufferData, Args&&... args)
{
	std::tuple<Args...> argsTuple{ std::forward<Args>(args)... };
	glBindVertexArray(*((GLuint*)vao));

	GLuint* EBO = new GLuint();
	glGenBuffers(1, EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
	// Give our vertices to OpenGL.
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, std::get<0>(argsTuple), bufferData, GL_STATIC_DRAW);
	// Draw the triangle !
	glEnableVertexAttribArray(0);
	return EBO;
}

void* Rendering::loadShaders(const char* vertex_file_path, const char* fragment_file_path) {

	// Create the shaders
	GLuint vShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE; 
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const* VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(vShaderId, 1, &VertexSourcePointer, NULL);
	glCompileShader(vShaderId);

	// Check Vertex Shader
	glGetShaderiv(vShaderId, GL_COMPILE_STATUS, &Result); 
	glGetShaderiv(vShaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(vShaderId, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const* FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(fShaderId, 1, &FragmentSourcePointer, NULL);
	glCompileShader(fShaderId);

	// Check Fragment Shader
	glGetShaderiv(fShaderId, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(fShaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(fShaderId, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program\n");
	GLuint* ProgramID = new GLuint(glCreateProgram()); 
	glAttachShader(*ProgramID, vShaderId);
	glAttachShader(*ProgramID, fShaderId);
	glLinkProgram(*ProgramID);

	// Check the program
	glGetProgramiv(*ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(*ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(*ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDetachShader(*ProgramID, vShaderId);
	glDetachShader(*ProgramID, fShaderId);

	glDeleteShader(vShaderId);
	glDeleteShader(fShaderId);

	return ProgramID;
}

template<typename... Args>
void Rendering::draw(VAO* vao, void* const renderingProgramId, Args&&... args)
{ 
	glUseProgram(*((GLuint*)renderingProgramId));
	glBindVertexArray(*((GLuint*)vao->vao));

	std::tuple<Args...> argsTuple{ std::forward<Args>(args)... };
	
	vao->hasEbo ?
		glDrawElements(GL_TRIANGLES, std::get<0>(argsTuple), GL_UNSIGNED_INT, 0) :
		glDrawArrays(GL_TRIANGLES, 0, std::get<0>(argsTuple)); // Starting from vertex 0; 3 vertices total -> 1 triangle 
	return;
}   

void Rendering::frame(void* window)
{ 
	glfwSwapBuffers((GLFWwindow*)window);
	glClear(GL_COLOR_BUFFER_BIT); 
	glClear(GL_DRAW_BUFFER); 
}
