#pragma once
#include <manager.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif

#include <GLFW/glfw3.h>

enum ModalState
{
    NONE,
    EDIT,
    CREATE
};

struct ModalData
{
    std::string name;
    ImVec4 color;
};

class UIManager
{
    public:
        UIManager();
        UIManager(Manager* manager);
        ~UIManager();

        /**
         * @brief Initilize GLFW OpenGL and ImGui
         * 
         * @return true Success
         * @return false Failed to initialize
         */
        bool init();

        /**
         * @brief Wrapper around glfwWindowShouldClose
         * 
         * @return Value of the close flag
         */
        bool shouldWindowClose() const
        {
            return glfwWindowShouldClose(window);
        }

        /**
         * @brief Render the ImGui window
         * 
         */
        void render();

        /**
         * @brief Make OpenGL and ImGui cleanup calls to close window
         * 
         */
        void cleanup();

    private:
        Manager* manager;
        GLFWwindow* window;
        ImVec4 clear_color;
        bool showEditCreateModal;
        ModalData modalData;
        ModalState modalState;
        // Index of the project that is being used for modals
        int modalProjectIndex;

        void renderProject(int projectIndex);
        void renderMenuBar();
        void renderEditCreateModal(int projectIndex);
        void resetModalState()
        {
            this->modalState = ModalState::NONE;
            this->showEditCreateModal = false;
            this->modalProjectIndex = -1;
            this->modalData = {"New Project", ImVec4(1.0f, 0.0f, 0.0f, 1.0f)};
        }
};