#pragma once

#include <vector>
#include "components/simple_scene.h"
#include "lab_m1/tema2/lab_camera.h"

namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
    public:
        Tema2();
        ~Tema2();

        void Init() override;
        Mesh* CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices, const glm::vec3& color);

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color1, const glm::vec3& color2);
        void CreateForest(int numberOfTrees, float terrainWidth, float terrainLength, float minScale, float maxScale);
        float RandomFloat(float min, float max);
        void CreateTree(glm::vec3 position, float scale);
        bool CheckGroundCollision(glm::vec3 position);
        bool CheckTrunkCollision(const glm::vec3& newPosition);
        bool CheckConeCollision(const glm::vec3& newPosition);
		bool CheckRockCollision(const glm::vec3& newPosition);
        float GetDroneRadius() const { return 1.0f; }

        void CreatePackage();
        void CreateDestination();
        void UpdatePackage(float deltaTimeSeconds);
        void CheckPackageCollection();
        void CheckPackageDelivery();

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

    protected:
        implemented::Tema2Camera* camera;
        glm::mat4 projectionMatrix;
        bool renderCameraTarget;

        float time;

        float angleOx = 0.0f;
        float angleOy = 0.0f;
        float angleOz = 0.0f;
        float rotationSpeed = 1.0f;

        glm::vec3 dronePosition = glm::vec3(0.0f, 0.0f, 0.0f);
        float movementSpeed = 3.0f;
        glm::mat4 droneModelMatrix = glm::mat4(1);

        float fov = 60;
        bool isFovWide = false;

        struct TreeData {
            glm::vec3 position;
            float scale;
            float trunkRadius;
            float crownBaseRadius;
            float crownTopRadius;
            float trunkHeight;
            float crownHeight;
        };

        std::vector<TreeData> treePositions;

        struct RockData {
            glm::vec3 position;
            float length;
            float width;
            float height;
            glm::vec3 scale;
        };

        std::vector<RockData> rocks;

        Mesh* packageMesh;
        glm::vec3 packagePosition;
        bool isPackagePickedUp = false;

        glm::vec3 destinationPosition;
        Mesh* destinationMesh;

        int score = 0;

        bool spacePressed = false;
    };
}   // namespace m1
