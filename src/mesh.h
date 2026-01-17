#pragma once // precompiler directive to only include header once

#include "../glad/glad.h"
#include <GLFW/glfw3.h>
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

enum MeshBuffer {
    VERTEX_BUFFER, COLOR_BUFFER, MAX_BUFFER
};

class Mesh{
    public:
        Mesh();
        ~Mesh();

        void draw();
        static Mesh* generate_triangle();
        
    protected:
        void buffer_data();

        GLuint array_object;
        GLuint buffer_object[MAX_BUFFER];
        GLuint num_vertices;
        GLuint type;

        Vector3* vertices;
        Vector4* colors;
};