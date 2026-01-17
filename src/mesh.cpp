#include "mesh.h"
Mesh::Mesh(){
    for (int i = 0; i < MAX_BUFFER; i++){
        buffer_object[i] = 0;
    }

    glGenVertexArrays(1, &array_object);

    num_vertices = 0;
    vertices = NULL;
    colors = NULL;
    type = GL_TRIANGLES;
}

Mesh::~Mesh(){
    glDeleteVertexArrays(1, &array_object);
    glDeleteBuffers(MAX_BUFFER, buffer_object);
    delete[] vertices;
    delete[] colors;
}

Mesh* Mesh::generate_triangle(){
    Mesh* m = new Mesh();
    m->num_vertices = 3;

    m->vertices = new Vector3[m->num_vertices];
    m->vertices[0] = Vector3(   0.0f,   0.5f,   0.0f);
    m->vertices[1] = Vector3(   0.5f,  -0.5f,   0.0f);
    m->vertices[2] = Vector3(  -0.5f,  -0.5f,   0.0f);

    m->colors = new Vector4[m->num_vertices];
    m->colors[0] = Vector4(1.f,0.f,0.f,1.f);
    m->colors[1] = Vector4(0.f,1.f,0.f,1.f);
    m->colors[2] = Vector4(0.f,0.f,1.f,1.f);

    m->buffer_data();
    return m;
}

void Mesh::buffer_data(){
    glBindVertexArray(array_object);
    glGenBuffers(1, &buffer_object[VERTEX_BUFFER]);
    glBindBuffer(GL_ARRAY_BUFFER, buffer_object[VERTEX_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, num_vertices*sizeof(Vector3), 
                                    vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(VERTEX_BUFFER);
    if (colors){
        glGenBuffers(1, &buffer_object[COLOR_BUFFER]);
        glBindBuffer(GL_ARRAY_BUFFER, buffer_object[COLOR_BUFFER]);
        glBufferData(GL_ARRAY_BUFFER, num_vertices*sizeof(Vector4), 
                                    colors, GL_STATIC_DRAW);
        glVertexAttribPointer(COLOR_BUFFER, 4, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(COLOR_BUFFER);
    }
    glBindVertexArray(0);
}

void Mesh::draw(){
    glBindVertexArray(array_object);
    glDrawArrays(type, 0, num_vertices);
    glBindVertexArray(0);
}