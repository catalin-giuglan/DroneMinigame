#include "lab_m1/tema2/lab5.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

void Tema2::Init()
{
    renderCameraTarget = false;

    camera = new implemented::Tema2Camera();
	camera->Set(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1.5, 0));

    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

    {
        Mesh* mesh = new Mesh("plane");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Shader* shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    {
        float length = 0.2f;
        float width = 0.15f;
        float depth = 1.7f;

        std::vector<VertexFormat> vertices = {

            VertexFormat(glm::vec3(-length / 2, -width / 2, depth / 2), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f)),
            VertexFormat(glm::vec3(length / 2, -width / 2, depth / 2), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f)),
            VertexFormat(glm::vec3(length / 2, width / 2, depth / 2), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)),
            VertexFormat(glm::vec3(-length / 2, width / 2, depth / 2), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f)),

            VertexFormat(glm::vec3(-length / 2, -width / 2, -depth / 2), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 0.0f)),
            VertexFormat(glm::vec3(length / 2, -width / 2, -depth / 2), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f)),
            VertexFormat(glm::vec3(length / 2, width / 2, -depth / 2), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)),
            VertexFormat(glm::vec3(-length / 2, width / 2, -depth / 2), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 0.0f)),

            VertexFormat(glm::vec3(-length / 2, -width / 2, -depth / 2), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.5f, 0.0f)),
            VertexFormat(glm::vec3(-length / 2, -width / 2, depth / 2), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.0f, 0.0f)),
            VertexFormat(glm::vec3(-length / 2, width / 2, depth / 2), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f)),
            VertexFormat(glm::vec3(-length / 2, width / 2, -depth / 2), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 1.0f, 0.0f)),

            VertexFormat(glm::vec3(length / 2, -width / 2, -depth / 2), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 0.5f)),
            VertexFormat(glm::vec3(length / 2, -width / 2, depth / 2), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f)),
            VertexFormat(glm::vec3(length / 2, width / 2, depth / 2), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f)),
            VertexFormat(glm::vec3(length / 2, width / 2, -depth / 2), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 1.0f, 0.5f)),

            VertexFormat(glm::vec3(-length / 2, -width / 2, -depth / 2), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f)),
            VertexFormat(glm::vec3(length / 2, -width / 2, -depth / 2), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)),
            VertexFormat(glm::vec3(length / 2, -width / 2, depth / 2), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f)),
            VertexFormat(glm::vec3(-length / 2, -width / 2, depth / 2), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.5f, 0.0f)),

            VertexFormat(glm::vec3(-length / 2, width / 2, -depth / 2), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 1.0f)),
            VertexFormat(glm::vec3(length / 2, width / 2, -depth / 2), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 0.5f)),
            VertexFormat(glm::vec3(length / 2, width / 2, depth / 2), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 1.0f)),
            VertexFormat(glm::vec3(-length / 2, width / 2, depth / 2), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 1.0f)),
        };

        std::vector<unsigned int> indices = {
            0, 1, 2,  0, 2, 3,
            4, 5, 6,  4, 6, 7,
            8, 9, 10,  8, 10, 11,
            12, 13, 14,  12, 14, 15,
            16, 17, 18,  16, 18, 19,
            20, 21, 22,  20, 22, 23,
        };

        Mesh* rectangleMesh = CreateMesh("rectangle", vertices, indices, glm::vec3(0.5f, 0.5f, 0.5f));
        meshes[rectangleMesh->GetMeshID()] = rectangleMesh;
    }

    {
        float length = 0.2f;
        float width = 0.15f;
        float depth = 1.7f;

        std::vector<VertexFormat> vertices = {

            VertexFormat(glm::vec3(-length / 2, -width / 2, depth / 2), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)),
            VertexFormat(glm::vec3(length / 2, -width / 2, depth / 2), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
            VertexFormat(glm::vec3(length / 2, width / 2, depth / 2), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
            VertexFormat(glm::vec3(-length / 2, width / 2, depth / 2), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)),

            VertexFormat(glm::vec3(-length / 2, -width / 2, -depth / 2), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f)),
            VertexFormat(glm::vec3(length / 2, -width / 2, -depth / 2), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
            VertexFormat(glm::vec3(length / 2, width / 2, -depth / 2), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
            VertexFormat(glm::vec3(-length / 2, width / 2, -depth / 2), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f)),

            VertexFormat(glm::vec3(-length / 2, -width / 2, -depth / 2), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.5f, 0.0f)),
            VertexFormat(glm::vec3(-length / 2, -width / 2, depth / 2), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.0f, 0.0f)),
            VertexFormat(glm::vec3(-length / 2, width / 2, depth / 2), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
            VertexFormat(glm::vec3(-length / 2, width / 2, -depth / 2), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 1.0f, 0.0f)),

            VertexFormat(glm::vec3(length / 2, -width / 2, -depth / 2), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.5f)),
            VertexFormat(glm::vec3(length / 2, -width / 2, depth / 2), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)),
            VertexFormat(glm::vec3(length / 2, width / 2, depth / 2), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
            VertexFormat(glm::vec3(length / 2, width / 2, -depth / 2), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 1.0f, 0.5f)),

            VertexFormat(glm::vec3(-length / 2, -width / 2, -depth / 2), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)),
            VertexFormat(glm::vec3(length / 2, -width / 2, -depth / 2), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
            VertexFormat(glm::vec3(length / 2, -width / 2, depth / 2), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
            VertexFormat(glm::vec3(-length / 2, -width / 2, depth / 2), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.5f, 0.0f)),

            VertexFormat(glm::vec3(-length / 2, width / 2, -depth / 2), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 1.0f)),
            VertexFormat(glm::vec3(length / 2, width / 2, -depth / 2), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.5f)),
            VertexFormat(glm::vec3(length / 2, width / 2, depth / 2), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 1.0f)),
            VertexFormat(glm::vec3(-length / 2, width / 2, depth / 2), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f)),
        };

        std::vector<unsigned int> indices = {
            0, 1, 2,  0, 2, 3,
            4, 5, 6,  4, 6, 7,
            8, 9, 10,  8, 10, 11,
            12, 13, 14,  12, 14, 15,
            16, 17, 18,  16, 18, 19,
            20, 21, 22,  20, 22, 23,
        };

        Mesh* rectangleMesh = CreateMesh("propeller", vertices, indices, glm::vec3(0.5f, 0.5f, 0.5f));
        meshes[rectangleMesh->GetMeshID()] = rectangleMesh;
    }

    {
        std::vector<VertexFormat> vertices = {

            VertexFormat(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f)),
            VertexFormat(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f)),
            VertexFormat(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)),
            VertexFormat(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f)),

            VertexFormat(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 0.0f)),
            VertexFormat(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f)),
            VertexFormat(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)),
            VertexFormat(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 0.0f)),

            VertexFormat(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.5f, 0.0f)),
            VertexFormat(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.0f, 0.0f)),
            VertexFormat(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f)),
            VertexFormat(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 1.0f, 0.0f)),

            VertexFormat(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 0.5f)),
            VertexFormat(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f)),
            VertexFormat(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f)),
            VertexFormat(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 1.0f, 0.5f)),

            VertexFormat(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f)),
            VertexFormat(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)),
            VertexFormat(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f)),
            VertexFormat(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.5f, 0.0f)),

            VertexFormat(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 1.0f)),
            VertexFormat(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 0.5f)),
            VertexFormat(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 1.0f)),
            VertexFormat(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 1.0f)),

        };

        std::vector<unsigned int> indices = {
            0, 1, 2,  0, 2, 3,
            4, 5, 6,  4, 6, 7,
            8, 9, 10,  8, 10, 11,
            12, 13, 14,  12, 14, 15,
            16, 17, 18,  16, 18, 19,
            20, 21, 22,  20, 22, 23,
        };

        Mesh* cubeMesh = CreateMesh("cube", vertices, indices, glm::vec3(0.5f, 0.5f, 0.5f));
        meshes[cubeMesh->GetMeshID()] = cubeMesh;
    }

    {
        std::vector<VertexFormat> vertices;

        vertices.push_back(VertexFormat(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.1f, 0.5f, 0.1f), glm::vec3(1, 0, 0)));

        vertices.push_back(VertexFormat(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.1f, 0.5f, 0.1f), glm::vec3(0, 1, 0)));

        int numSegments = 36;
        float radius = 0.5f;

        for (int i = 0; i <= numSegments; ++i) {
            float angle = glm::radians(360.0f * i / numSegments);
            float x = radius * cos(angle);
            float z = radius * sin(angle);
            vertices.push_back(VertexFormat(glm::vec3(x, 0.0f, z), glm::vec3(0.1f, 0.5f, 0.1f), glm::vec3(0, 0, 1)));
        }

        std::vector<unsigned int> indices;

        for (int i = 2; i <= numSegments + 1; ++i) {
            indices.push_back(0);
            indices.push_back(i);
            indices.push_back(i + 1);
        }

        for (int i = 2; i <= numSegments + 1; ++i) {
            indices.push_back(1);
            indices.push_back(i);
            indices.push_back(i + 1);
        }

        Mesh* coneMesh = CreateMesh("cone", vertices, indices, glm::vec3(0.1f, 0.5f, 0.1f));
        meshes[coneMesh->GetMeshID()] = coneMesh;
    }

    {
        std::vector<VertexFormat> vertices;

        int numSegments = 36;
        float radius = 0.5f;
        float height = 2.0f;

        vertices.push_back(VertexFormat(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.545f, 0.271f, 0.075f), glm::vec3(0, 1, 0)));

        vertices.push_back(VertexFormat(glm::vec3(0.0f, height, 0.0f), glm::vec3(0.545f, 0.271f, 0.075f), glm::vec3(1, 0, 0)));

        for (int i = 0; i <= numSegments; ++i) {
            float angle = glm::radians(360.0f * i / numSegments);
            float x = radius * cos(angle);
            float z = radius * sin(angle);

            vertices.push_back(VertexFormat(glm::vec3(x, 0.0f, z), glm::vec3(0.545f, 0.271f, 0.075f), glm::vec3(0, 0, 1)));

            vertices.push_back(VertexFormat(glm::vec3(x, height, z), glm::vec3(0.545f, 0.271f, 0.075f), glm::vec3(1, 0, 1)));
        }

        std::vector<unsigned int> indices;

        for (int i = 2; i <= numSegments * 2; i += 2) {
            indices.push_back(0);
            indices.push_back(i);
            indices.push_back(i + 2);
        }

        for (int i = 3; i <= numSegments * 2 + 1; i += 2) {
            indices.push_back(1);
            indices.push_back(i + 2);
            indices.push_back(i);
        }

        for (int i = 2; i <= numSegments * 2; i += 2) {

            indices.push_back(i);
            indices.push_back(i + 3);
            indices.push_back(i + 1);

            indices.push_back(i);
            indices.push_back(i + 2);
            indices.push_back(i + 3);
        }

        Mesh* cylinderMesh = CreateMesh("cylinder", vertices, indices, glm::vec3(0.545f, 0.271f, 0.075f));
        meshes[cylinderMesh->GetMeshID()] = cylinderMesh;
    }
    CreatePackage();
    CreateDestination();

    for (int i = 0; i < 10; i++) {
        RockData rock;
        rock.position = glm::vec3(RandomFloat(-12, 12), 0.0f, RandomFloat(-12, 12));
        rock.scale = glm::vec3(RandomFloat(0.8f, 2.0f), RandomFloat(1.3f, 2.0f), RandomFloat(0.8f, 2.0f));
        rocks.push_back(rock);
    }
}

Mesh* Tema2::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices, const glm::vec3& color)
{
    unsigned int VAO = 0;
    // Create the VAO and bind it
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create the VBO and bind it
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Send vertices data into the VBO buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    // Create the IBO and bind it
    unsigned int IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    // Send indices data into the IBO buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

    // Set vertex position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    // Set vertex normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

    // Set texture coordinate attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

    // Set vertex color attribute
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
    // ========================================================================

    // Unbind the VAO
    glBindVertexArray(0);

    // Check for OpenGL errors
    CheckOpenGLError();

    // Mesh information is saved into a Mesh object
    meshes[name] = new Mesh(name);
    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
    meshes[name]->vertices = vertices;
    meshes[name]->indices = indices;
    return meshes[name];
}

void Tema2::FrameStart()
{
    glClearColor(0.5f, 0.8f, 1.0f, 1); // Un albastru deschis RGBA
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);

    CreateForest(10, 20, 20, 1.5f, 3.5f);
    for (const auto& rock : rocks) {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, rock.position);
        modelMatrix = glm::scale(modelMatrix, rock.scale);
		RenderSimpleMesh(meshes["cube"], shaders["VertexColor"], modelMatrix, rock.scale, glm::vec3(0.5f, 0.5f, 0.5f));
    }
}

void Tema2::Update(float deltaTimeSeconds) {
    
    time = Engine::GetElapsedTime();

    static float rotationAngle = 0.0f;
    rotationAngle += 10 * deltaTimeSeconds;

    UpdatePackage(deltaTimeSeconds);
    if (!isPackagePickedUp) {

        float distanceToPackage = glm::distance(dronePosition, packagePosition);
        if (distanceToPackage <= 1.5f && window->KeyHold(GLFW_KEY_SPACE)) {
            CheckPackageCollection();
        }
    }
    else {

        float distanceToDestination = glm::distance(dronePosition, destinationPosition);
        if (distanceToDestination <= 1.5f && window->KeyHold(GLFW_KEY_SPACE)) {
            CheckPackageDelivery();
        }
    }

    glm::mat4 modelMatrix = glm::mat4(1);

    if (!isPackagePickedUp) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, packagePosition);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0f));
        RenderSimpleMesh(meshes["package"], shaders["LabShader"], modelMatrix, glm::vec3(0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
    }
    else {
        glm::mat4 destinationMatrix = glm::mat4(1);
        destinationMatrix = glm::translate(destinationMatrix, destinationPosition + glm::vec3(0, 0.5, 0));
        destinationMatrix = glm::scale(destinationMatrix, glm::vec3(2.5f));
        RenderSimpleMesh(destinationMesh, shaders["VertexColor"], destinationMatrix,
            glm::vec3(0.1f, 0.1f, 1.0f), glm::vec3(0.1f, 0.1f, 1.0f));
    }

        droneModelMatrix = glm::translate(droneModelMatrix, dronePosition);
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.01f, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.75f));
        RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix,
            glm::vec3(0.1f, 0.5f, 0.1f), glm::vec3(1.0f, 0.5f, 0.0f));

    {
        glm::mat4 modelMatrix1 = droneModelMatrix;
        modelMatrix1 = glm::translate(modelMatrix1, glm::vec3(0.0f, 1.5f, 0.0f));
        modelMatrix1 = glm::scale(modelMatrix1, glm::vec3(0.75f));
        modelMatrix1 = glm::rotate(modelMatrix1, RADIANS(45), glm::vec3(0, 1, 0));
        RenderSimpleMesh(meshes["rectangle"], shaders["VertexColor"], modelMatrix1, glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f));

        glm::mat4 modelMatrix2 = droneModelMatrix;
        modelMatrix2 = glm::translate(modelMatrix2, glm::vec3(0.0f, 1.5f, 0.0f));
        modelMatrix2 = glm::scale(modelMatrix2, glm::vec3(0.75f));
        modelMatrix2 = glm::rotate(modelMatrix2, RADIANS(-45), glm::vec3(0, 1, 0));
        RenderSimpleMesh(meshes["rectangle"], shaders["VertexColor"], modelMatrix2, glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f));

        glm::mat4 cubeMatrix1 = modelMatrix1;
        cubeMatrix1 = glm::translate(cubeMatrix1, glm::vec3(0.0f, 0.15f, 0.75f));
        cubeMatrix1 = glm::scale(cubeMatrix1, glm::vec3(0.2f));
        RenderSimpleMesh(meshes["cube"], shaders["VertexColor"], cubeMatrix1, glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f));

        glm::mat4 propellerMatrix1 = cubeMatrix1;
        propellerMatrix1 = glm::translate(propellerMatrix1, glm::vec3(0.0f, 0.5f, 0.0f));
        propellerMatrix1 = glm::rotate(propellerMatrix1, rotationAngle, glm::vec3(0, 1, 0));
        propellerMatrix1 = glm::scale(propellerMatrix1, glm::vec3(1.5f));
        RenderSimpleMesh(meshes["propeller"], shaders["VertexColor"], propellerMatrix1, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

        glm::mat4 cubeMatrix2 = modelMatrix1;
        cubeMatrix2 = glm::translate(cubeMatrix2, glm::vec3(0.0f, 0.15f, -0.75f));
        cubeMatrix2 = glm::scale(cubeMatrix2, glm::vec3(0.2f));
        RenderSimpleMesh(meshes["cube"], shaders["VertexColor"], cubeMatrix2, glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f));

        glm::mat4 propellerMatrix2 = cubeMatrix2;
        propellerMatrix2 = glm::translate(propellerMatrix2, glm::vec3(0.0f, 0.5f, 0.0f));
        propellerMatrix2 = glm::rotate(propellerMatrix2, rotationAngle, glm::vec3(0, 1, 0));
        propellerMatrix2 = glm::scale(propellerMatrix2, glm::vec3(1.5f));
        RenderSimpleMesh(meshes["propeller"], shaders["VertexColor"], propellerMatrix2, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

        glm::mat4 cubeMatrix3 = modelMatrix2;
        cubeMatrix3 = glm::translate(cubeMatrix3, glm::vec3(0.0f, 0.15f, 0.75f));
        cubeMatrix3 = glm::scale(cubeMatrix3, glm::vec3(0.2f));
        RenderSimpleMesh(meshes["cube"], shaders["VertexColor"], cubeMatrix3, glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f));

        glm::mat4 propellerMatrix3 = cubeMatrix3;
        propellerMatrix3 = glm::translate(propellerMatrix3, glm::vec3(0.0f, 0.5f, 0.0f));
        propellerMatrix3 = glm::rotate(propellerMatrix3, rotationAngle, glm::vec3(0, 1, 0));
        propellerMatrix3 = glm::scale(propellerMatrix3, glm::vec3(1.5f));
        RenderSimpleMesh(meshes["propeller"], shaders["VertexColor"], propellerMatrix3, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

        glm::mat4 cubeMatrix4 = modelMatrix2;
        cubeMatrix4 = glm::translate(cubeMatrix4, glm::vec3(0.0f, 0.15f, -0.75f));
        cubeMatrix4 = glm::scale(cubeMatrix4, glm::vec3(0.2f));
        RenderSimpleMesh(meshes["cube"], shaders["VertexColor"], cubeMatrix4, glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f));

        glm::mat4 propellerMatrix4 = cubeMatrix4;
        propellerMatrix4 = glm::translate(propellerMatrix4, glm::vec3(0.0f, 0.5f, 0.0f));
        propellerMatrix4 = glm::rotate(propellerMatrix4, rotationAngle, glm::vec3(0, 1, 0));
        propellerMatrix4 = glm::scale(propellerMatrix4, glm::vec3(1.5f));
        RenderSimpleMesh(meshes["propeller"], shaders["VertexColor"], propellerMatrix4, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    }
}

void Tema2::CreateTree(glm::vec3 position, float scale)
{
    // Creeaza trunchiul copacului
    glm::mat4 trunkMatrix = glm::mat4(1);
    trunkMatrix = glm::translate(trunkMatrix, position);
    trunkMatrix = glm::scale(trunkMatrix, glm::vec3(0.2f * scale, 0.5f * scale, 0.2f * scale));
    RenderSimpleMesh(meshes["cylinder"], shaders["VertexColor"], trunkMatrix, glm::vec3(0.545f, 0.271f, 0.075f), glm::vec3(0.545f, 0.271f, 0.075f));

    // Creeaza coroana copacului
    glm::mat4 crownMatrix = glm::mat4(1);
    crownMatrix = glm::translate(crownMatrix, position + glm::vec3(0.0f, 0.8f * scale, 0.0f));
    crownMatrix = glm::scale(crownMatrix, glm::vec3(1.0f * scale, 1.0f * scale, 1.0f * scale));
    RenderSimpleMesh(meshes["cone"], shaders["VertexColor"], crownMatrix, glm::vec3(0.1f, 0.5f, 0.1f), glm::vec3(0.1f, 0.5f, 0.1f));

    crownMatrix = glm::mat4(1);
    crownMatrix = glm::translate(crownMatrix, position + glm::vec3(0.0f, 1.35f * scale, 0.0f));
    crownMatrix = glm::scale(crownMatrix, glm::vec3(0.8f * scale, 0.8f * scale, 0.8f * scale));
    RenderSimpleMesh(meshes["cone"], shaders["VertexColor"], crownMatrix, glm::vec3(0.1f, 0.5f, 0.1f), glm::vec3(0.1f, 0.5f, 0.1f));
}

float Tema2::RandomFloat(float min, float max) {
    return min + (rand() / (RAND_MAX / (max - min)));
}


void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    glm::vec3 currentPosition = glm::vec3(droneModelMatrix[3]);
    glm::vec3 move = glm::normalize(glm::vec3(sin(angleOy), 0, cos(angleOy)));

    // Exemplu: W/S pentru mers înainte/înapoi
    if (window->KeyHold(GLFW_KEY_W)) {
        glm::vec3 newPosition = currentPosition + move * movementSpeed * deltaTime;
        if (!CheckTrunkCollision(newPosition) && !CheckConeCollision(newPosition) && !CheckRockCollision(newPosition)) {
            droneModelMatrix = glm::translate(droneModelMatrix, move * movementSpeed * deltaTime);
        }
    }
    if (window->KeyHold(GLFW_KEY_S)) {
        glm::vec3 newPosition = currentPosition - move * movementSpeed * deltaTime;
        if (!CheckTrunkCollision(newPosition) && !CheckConeCollision(newPosition) && !CheckRockCollision(newPosition)) {
            droneModelMatrix = glm::translate(droneModelMatrix, -move * movementSpeed * deltaTime);
        }
    }

    // Mișcare sus/jos (altitudine)
    if (window->KeyHold(GLFW_KEY_Q)) {
        droneModelMatrix = glm::translate(droneModelMatrix, glm::vec3(0, -movementSpeed * deltaTime, 0));
        if (!CheckGroundCollision(glm::vec3(droneModelMatrix[3])) && !CheckConeCollision(glm::vec3(droneModelMatrix[3])) && !CheckRockCollision(glm::vec3(droneModelMatrix[3]))) {
            droneModelMatrix = glm::translate(droneModelMatrix, glm::vec3(0, movementSpeed * deltaTime, 0));
        }
    }

    if (window->KeyHold(GLFW_KEY_E)) {
        droneModelMatrix = glm::translate(droneModelMatrix, glm::vec3(0, movementSpeed * deltaTime, 0));
        if (!CheckGroundCollision(glm::vec3(droneModelMatrix[3])) && !CheckConeCollision(glm::vec3(droneModelMatrix[3])) && !CheckRockCollision(glm::vec3(droneModelMatrix[3]))) {
            droneModelMatrix = glm::translate(droneModelMatrix, glm::vec3(0, -movementSpeed * deltaTime, 0));
        }
    }

    // YAW (Rotire stânga/dreapta)
    if (window->KeyHold(GLFW_KEY_A)) {
        droneModelMatrix = glm::rotate(droneModelMatrix, movementSpeed * deltaTime * 0.5f, glm::vec3(0, 1, 0));
    }
    if (window->KeyHold(GLFW_KEY_D)) {
        droneModelMatrix = glm::rotate(droneModelMatrix, -movementSpeed * deltaTime * 0.5f, glm::vec3(0, 1, 0));
    }


    // PITCH
    if (window->KeyHold(GLFW_KEY_UP)) {
        if (angleOx > glm::radians(-15.0f)) {
            droneModelMatrix = glm::rotate(droneModelMatrix, movementSpeed * deltaTime * 0.5f, glm::vec3(1, 0, 0));
            angleOx -= movementSpeed * deltaTime * 0.5f;
        }
    }

    if (window->KeyHold(GLFW_KEY_DOWN)) {
        if (angleOx < glm::radians(15.0f)) {
            droneModelMatrix = glm::rotate(droneModelMatrix, -movementSpeed * deltaTime * 0.5f, glm::vec3(1, 0, 0));
            angleOx += movementSpeed * deltaTime * 0.5f;
        }
    }

    // ROLL
    if (window->KeyHold(GLFW_KEY_LEFT)) {
        if (angleOz < glm::radians(15.0f)) {
            droneModelMatrix = glm::rotate(droneModelMatrix, -movementSpeed * deltaTime * 0.5f, glm::vec3(0, 0, 1));
            angleOz += movementSpeed * deltaTime * 0.5f;
        }
    }

    if (window->KeyHold(GLFW_KEY_RIGHT)) {
        if (angleOz > glm::radians(-15.0f)) {
            droneModelMatrix = glm::rotate(droneModelMatrix, movementSpeed * deltaTime * 0.5f, glm::vec3(0, 0, 1));
            angleOz -= movementSpeed * deltaTime * 0.5f;
        }
    }

    glm::vec3 dronePosition = glm::vec3(droneModelMatrix[3]);

    glm::vec3 forward = glm::normalize(glm::vec3(-droneModelMatrix[2]));
    glm::vec3 up = glm::normalize(glm::vec3(droneModelMatrix[1]));
    glm::vec3 right = glm::normalize(glm::vec3(droneModelMatrix[0]));

    glm::vec3 cameraOffset = glm::vec3(0.0f, 2.0f, -2.0f);
    glm::vec3 cameraPosition = dronePosition - forward * cameraOffset.z + up * cameraOffset.y;

    glm::quat cameraRotation = glm::quatLookAt(-forward, up);

    GetSceneCamera()->SetPosition(cameraPosition);
    GetSceneCamera()->SetRotation(cameraRotation);

    GetSceneCamera()->Update();
}

void Tema2::OnKeyPress(int key, int mods) {

    if (key == GLFW_KEY_P) {
        if (isFovWide) {
            projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
            isFovWide = false;
        }
        else {
            projectionMatrix = glm::perspective(RADIANS(90), window->props.aspectRatio, 0.01f, 200.0f);
            isFovWide = true;
        }
    }
    if (key == GLFW_KEY_SPACE) {
        if (isPackagePickedUp == true) {
            isPackagePickedUp = false;
		}
		if (isPackagePickedUp == false) {
			isPackagePickedUp = true;
		}
    }
}

bool Tema2::CheckGroundCollision(glm::vec3 position) {
	return position.y > -0.8f;
}

void Tema2::CreateForest(int numberOfTrees, float terrainWidth, float terrainLength, float minScale, float maxScale) {
    srand(static_cast<unsigned int>(0));
    treePositions.clear();

    for (int i = 0; i < numberOfTrees; ++i) {
        bool validPosition = false;
        TreeData tree;

        while (!validPosition) {
            tree.position.x = RandomFloat(-terrainWidth / 2, terrainWidth / 2);
            tree.position.z = RandomFloat(-terrainLength / 2, terrainLength / 2);
            tree.scale = RandomFloat(minScale, maxScale);
            tree.position.y = tree.scale - 1.01f * tree.scale;

            tree.trunkRadius = 0.2f * tree.scale;
            tree.crownBaseRadius = 1.0f * tree.scale;
            tree.crownTopRadius = 0.5f * tree.scale;
            tree.trunkHeight = 0.5f * tree.scale;
            tree.crownHeight = 2.0f * tree.scale;

            validPosition = true;
            for (const auto& existingTree : treePositions) {
                float minDistance = (tree.crownBaseRadius + existingTree.crownBaseRadius) * 1.2f;
                if (glm::distance(tree.position, existingTree.position) < minDistance) {
                    validPosition = false;
                    break;
                }
            }
        }

        treePositions.push_back(tree);
        CreateTree(tree.position, tree.scale);
    }
}

bool Tema2::CheckTrunkCollision(const glm::vec3& newPosition) {
    float droneRadius = GetDroneRadius();
    float droneHeight = 0.1f;

    for (const auto& tree : treePositions) {
        float dx = newPosition.x - tree.position.x;
        float dz = newPosition.z - tree.position.z;
        float horizontalDist = sqrt(dx * dx + dz * dz);

        if (horizontalDist <= (droneRadius + tree.trunkRadius - 1) &&
            newPosition.y <= (tree.position.y + tree.trunkHeight + droneHeight / 2)) {
            return true;
        }
    }

    return false;
}

bool Tema2::CheckConeCollision(const glm::vec3& newPosition) {
    float droneRadius = GetDroneRadius();
    float droneHeight = 0.1f;

    for (const auto& tree : treePositions) {
        float dx = newPosition.x - tree.position.x;
        float dz = newPosition.z - tree.position.z;
        float horizontalDist = sqrt(dx * dx + dz * dz);

        if (newPosition.y >= tree.position.y + tree.trunkHeight &&
            newPosition.y <= tree.position.y + tree.trunkHeight + tree.crownHeight) {

            float heightInCrown = (newPosition.y - (tree.position.y + tree.trunkHeight)) / tree.crownHeight;
            float crownRadiusAtHeight = tree.crownBaseRadius * (1.0f - heightInCrown) + tree.crownTopRadius * heightInCrown;

            if (horizontalDist <= crownRadiusAtHeight - 0.9) {
                return true;
            }
        }

        if (newPosition.y >= tree.position.y &&
            newPosition.y <= tree.position.y + tree.trunkHeight) {

            float heightInTrunk = (newPosition.y - tree.position.y) / tree.trunkHeight;
            float trunkRadiusAtHeight = tree.trunkRadius * (1.0f - heightInTrunk) + tree.crownBaseRadius * heightInTrunk;

            if (horizontalDist <= trunkRadiusAtHeight - 0.5) {
                return true;
            }
        }
    }

    return false;
}

bool Tema2::CheckRockCollision(const glm::vec3& newPosition) {
    float droneRadius = GetDroneRadius();
    for (const auto& rock : rocks) {

        glm::vec3 rockHalfSizes = rock.scale * 0.5f;

        glm::vec3 rockMin = rock.position - rockHalfSizes;
        glm::vec3 rockMax = rock.position + rockHalfSizes;

        if (newPosition.x + droneRadius <= rockMin.x || newPosition.x - droneRadius >= rockMax.x ||
            newPosition.y + droneRadius <= rockMin.y || newPosition.y - droneRadius >= rockMax.y - 2.2 ||
            newPosition.z + droneRadius <= rockMin.z || newPosition.z - droneRadius >= rockMax.z) {
            continue;
        }
        return true;
    }
    return false;
}


void Tema2::CreatePackage() {
    bool validPosition = false;
    while (!validPosition) {
        packagePosition = glm::vec3(RandomFloat(0.0f, 7.0f), 0.1f, RandomFloat(0.0f, 7.0f));
        validPosition = true;
        for (const auto& tree : treePositions) {
            float dx = packagePosition.x - tree.position.x;
            float dz = packagePosition.z - tree.position.z;
            float dist = sqrt(dx * dx + dz * dz);
            if (dist < (tree.crownBaseRadius + 1.0f)) {
                validPosition = false;
                break;
            }
        }
        if (validPosition) {
            for (const auto& rock : rocks) {
                glm::vec3 rockHalfSizes = rock.scale * 0.5f;
                glm::vec3 rockMin = rock.position - rockHalfSizes;
                glm::vec3 rockMax = rock.position + rockHalfSizes;
                if (packagePosition.x >= rockMin.x && packagePosition.x <= rockMax.x &&
                    packagePosition.z >= rockMin.z && packagePosition.z <= rockMax.z) {
                    validPosition = false;
                    break;
                }
            }
        }
    }
    std::vector<VertexFormat> vertices = {
        VertexFormat(glm::vec3(-0.25f, -0.25f, 0.25f), glm::vec3(1.0f, 0.0f, 0.0f)),
        VertexFormat(glm::vec3(0.25f, -0.25f, 0.25f), glm::vec3(1.0f, 0.0f, 0.0f)),
        VertexFormat(glm::vec3(0.25f, 0.25f, 0.25f), glm::vec3(1.0f, 0.0f, 0.0f)),
        VertexFormat(glm::vec3(-0.25f, 0.25f, 0.25f), glm::vec3(1.0f, 0.0f, 0.0f)),
        VertexFormat(glm::vec3(-0.25f, -0.25f, -0.25f), glm::vec3(1.0f, 0.0f, 0.0f)),
        VertexFormat(glm::vec3(0.25f, -0.25f, -0.25f), glm::vec3(1.0f, 0.0f, 0.0f)),
        VertexFormat(glm::vec3(0.25f, 0.25f, -0.25f), glm::vec3(1.0f, 0.0f, 0.0f)),
        VertexFormat(glm::vec3(-0.25f, 0.25f, -0.25f), glm::vec3(1.0f, 0.0f, 0.0f))
    };

    std::vector<unsigned int> indices = {
        0, 1, 2,  0, 2, 3,
        4, 5, 6,  4, 6, 7,
        0, 1, 5,  0, 5, 4,
        1, 2, 6,  1, 6, 5,
        2, 3, 7,  2, 7, 6,
        3, 0, 4,  3, 4, 7
    };

    packageMesh = CreateMesh("package", vertices, indices, glm::vec3(1.0f, 0.0f, 0.0f));
}

void Tema2::CreateDestination() {
    bool validPosition = false;
    while (!validPosition) {
        destinationPosition = glm::vec3(RandomFloat(-7.0f, 7.0f), 0.1f, RandomFloat(-7.0f, 7.0f));
        validPosition = true;
        for (const auto& tree : treePositions) {
            float dx = destinationPosition.x - tree.position.x;
            float dz = destinationPosition.z - tree.position.z;
            float dist = sqrt(dx * dx + dz * dz);
            if (dist < (tree.crownBaseRadius + 1.0f)) {
                validPosition = false;
                break;
            }
        }
        if (validPosition) {
            for (const auto& rock : rocks) {
                glm::vec3 rockHalfSizes = rock.scale * 0.5f;
                glm::vec3 rockMin = rock.position - rockHalfSizes;
                glm::vec3 rockMax = rock.position + rockHalfSizes;
                if (destinationPosition.x >= rockMin.x && destinationPosition.x <= rockMax.x &&
                    destinationPosition.z >= rockMin.z && destinationPosition.z <= rockMax.z) {
                    validPosition = false;
                    break;
                }
            }
        }
    }
    std::vector<VertexFormat> vertices;
    int numSegments = 36;
    float radius = 1.0f;

    vertices.push_back(VertexFormat(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f)));
    for (int i = 0; i <= numSegments; ++i) {
        float angle = glm::radians(360.0f * i / numSegments);
        float x = radius * cos(angle);
        float z = radius * sin(angle);
        vertices.push_back(VertexFormat(glm::vec3(x, 0.0f, z), glm::vec3(1.0f, 1.0f, 0.0f)));
    }

    std::vector<unsigned int> indices;
    for (int i = 1; i <= numSegments; ++i) {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);
    }

    destinationMesh = CreateMesh("destination", vertices, indices, glm::vec3(1.0f, 1.0f, 0.0f));
}


void Tema2::UpdatePackage(float deltaTimeSeconds) {
    if (isPackagePickedUp) {
        packagePosition = dronePosition;
    }
}

void Tema2::CheckPackageCollection() {
    float distance = glm::distance(dronePosition, packagePosition);
    if (distance <= 5.0f && !isPackagePickedUp) {
        isPackagePickedUp = true;
    }
}

void Tema2::CheckPackageDelivery() {
    float distance = glm::distance(dronePosition, destinationPosition);
    if (distance <= 5.0f && isPackagePickedUp == true) {
        isPackagePickedUp = false;
        score++;
        CreatePackage();
    }
}

void Tema2::FrameEnd()
{
    DrawCoordinateSystem();
}

void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color1, const glm::vec3& color2)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    glUseProgram(shader->program);

    GLint modelLoc = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    GLint viewLoc = glGetUniformLocation(shader->program, "View");
    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    GLint projLoc = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    GLint timeLoc = glGetUniformLocation(shader->program, "Time");
    glUniform1f(timeLoc, Engine::GetElapsedTime());

	GLint colorLoc = glGetUniformLocation(shader->program, "culoare1");
	glUniform3fv(colorLoc, 1, glm::value_ptr(color1));

	GLint colorLoc2 = glGetUniformLocation(shader->program, "culoare2");
	glUniform3fv(colorLoc2, 1, glm::value_ptr(color2));

    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}
