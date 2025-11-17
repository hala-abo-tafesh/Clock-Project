#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <learnopengl/shader_m.h>
#include <vector>
#include <cmath>

class Sphere {
public:
    Sphere(float radius, unsigned int sectorCount, unsigned int stackCount, glm::vec3 c) {
        color = c;
        model = glm::mat4(1.0f);

        //  vertices
        for (unsigned int i = 0; i <= stackCount; ++i) {
            float stackAngle = glm::pi<float>() / 2 - i * glm::pi<float>() / stackCount;
            float xy = radius * cosf(stackAngle);
            float z = radius * sinf(stackAngle);

            for (unsigned int j = 0; j <= sectorCount; ++j) {
                float sectorAngle = j * 2 * glm::pi<float>() / sectorCount;
                float x = xy * cosf(sectorAngle);
                float y = xy * sinf(sectorAngle);
                vertices.push_back(glm::vec3(x, y, z));
            }
        }

        // indices
        for (unsigned int i = 0; i < stackCount; ++i) {
            unsigned int k1 = i * (sectorCount + 1);
            unsigned int k2 = k1 + sectorCount + 1;

            for (unsigned int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
                if (i != 0) {
                    indices.push_back(k1);
                    indices.push_back(k2);
                    indices.push_back(k1 + 1);
                }
                if (i != (stackCount - 1)) {
                    indices.push_back(k1 + 1);
                    indices.push_back(k2);
                    indices.push_back(k2 + 1);
                }
            }
        }

        //  VAO/VBO/EBO
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
    }

    void transformation(glm::mat4 t) {
        model = t;
    }

    void draw(Shader& shader) {
        shader.setVec3("objectColor", color);
        shader.setMat4("model", model);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    }

    void deleteBuffers() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

private:
    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;
    glm::vec3 color;
    glm::mat4 model;
    GLuint VAO, VBO, EBO;
};
