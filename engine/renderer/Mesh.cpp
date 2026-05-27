#include "Mesh.h"

#include "glad/glad.h"


Mesh::Mesh(const std::vector<Vertex>& vertices)
    : VAO(0),
    VBO(0),
    EBO(0),
    vertexCount(static_cast<int>(vertices.size())),
    indexCount(0),
    useIndices(false) {

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(Vertex),
        vertices.data(),
        GL_STATIC_DRAW
        );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (void*)offsetof(Vertex, position)
        );

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (void*)offsetof(Vertex, color)
        );

    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices)
    : VAO(0),
    VBO(0),
    EBO(0),
    vertexCount(static_cast<int>(vertices.size())),
    indexCount(static_cast<int>(indices.size())),
    useIndices(true) {

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(Vertex),
        vertices.data(),
        GL_STATIC_DRAW
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        indices.size() * sizeof(unsigned int),
        indices.data(),
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (void*)offsetof(Vertex, position)
    );

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1,
         3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (void*)offsetof(Vertex, color)
    );

    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

Mesh::~Mesh() {
    if (VAO != 0) {
        glDeleteVertexArrays(1, &VAO);
    }

    if (VBO != 0) {
        glDeleteBuffers(1, &VBO);
    }

    if (EBO != 0) {
        glDeleteBuffers(1, &EBO);
    }
}

void Mesh::draw() const {
    glBindVertexArray(VAO);

    if (useIndices) {
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
    }
    else {
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    }

    glBindVertexArray(0);
}
