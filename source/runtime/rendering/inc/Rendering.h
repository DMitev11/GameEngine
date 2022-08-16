#pragma once
#include "GL/glew.h"
#include "inc/Model2D.h"

struct VAO {

    VAO(void* vao_, unsigned int&& vertexCount_, bool&& hasEbo_) {
        vao = vao_;
        vertexCount = vertexCount_;
        hasEbo = hasEbo_;
    }
    VAO(void* vao_) {
        vao = vao_;
        vertexCount = 0;
        hasEbo = false;
    }
    void* vao;
    unsigned int vertexCount;
    bool hasEbo;
}
;
class Rendering
{
public:
    static void* createWindow();
    static void* loadShaders(const char* vertex_file_path, const char* fragment_file_path);

    static void* createVertexAttributeObjects(unsigned int count);  
    template<typename... Args>
    static void* createVertexBufferObject(void* vao, void* buffer_data, Args&&...);  
    template<typename... Args>
    static void* createElementBufferObject(void* vao, void* buffer_data, Args&&...);
    //@TODO Create Element Buffer method 

    template<typename... Args>
    static void draw(VAO* vao, void* renderProgramId, Args&&...);
    static void frame(void*);
};
//@TODO: Evade this
template void* Rendering::createVertexBufferObject(void* vao, void* buffer_data, int&&);
template void* Rendering::createVertexBufferObject(void* vao, void* buffer_data, unsigned int&&);
template void* Rendering::createVertexBufferObject(void* vao, void* buffer_data, size_t&&);
//
template void* Rendering::createElementBufferObject(void* vao, void* buffer_data, int&&);
template void* Rendering::createElementBufferObject(void* vao, void* buffer_data, unsigned int&&);
template void* Rendering::createElementBufferObject(void* vao, void* buffer_data, size_t&&);
//
template void Rendering::draw(VAO*, void*, unsigned int&&);
template void Rendering::draw(VAO*, void*, size_t&&); 