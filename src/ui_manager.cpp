#include <ui_manager.hpp>
#include <stdio.h>
#include <imgui_stdlib.h>
#include <iostream>

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

// Constructor and Destructor

UIManager::UIManager()
: manager(nullptr)
{
}

UIManager::UIManager(Manager* manager)
{
    this->manager = manager;
    this->window = nullptr;
    this->showEditCreateModal = false;
    this->modalProjectIndex = -1;
    this->modalData = {"New Project", ImVec4(1.0f, 0.0f, 0.0f, 1.0f)};
    this->modalState = ModalState::NONE;
    this->clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    // this->io = ImGui::GetIO();
}

UIManager::~UIManager()
{
    // Destructor implementation
}

// Init and cleanup

bool UIManager::init()
{
    glfwSetErrorCallback(glfw_error_callback);

    // Setup window
    if (!glfwInit())
        return false;

    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // Create window with graphics context
    this->window = glfwCreateWindow(1280, 720, "SimpleTimeTracker", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(this->window);
    glfwSwapInterval(1); // Enable vsync
    
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls

    // Set ImGui Style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(this->window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    return true;
}

void UIManager::cleanup()
{
    // ImGui cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(this->window);
    glfwTerminate();
}

/***************
    COMPONENTS
****************/

void UIManager::renderMenuBar()
{
    if (ImGui::BeginMenuBar()) 
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New Project", "Ctrl+N"))
            {
                // Open new project dialog
                this->modalState = ModalState::CREATE;
                this->showEditCreateModal = true;
                this->modalData = {"New Project", ImVec4(1.0f, 0.0f, 0.0f, 1.0f)};
            }

            if (ImGui::MenuItem("Save", "Ctrl+S"))
            {
                // Open save dialog
                this->manager->saveProjects();
            }
            if (ImGui::MenuItem("Load", "Ctrl+L"))
            {
                // Open load dialog
                this->manager->loadProjects();
            }

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Edit Categories"))
            {
                // Open categories page
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
}

void UIManager::renderProject(int projectIndex)
{
    Project* project = this->manager->getProject(projectIndex);
    const int t_hours = project->getHours() / 10;
    const int hours = project-> getHours() % 10;
    const int t_minutes = project->getMinutes() / 10;
    const int minutes = project->getMinutes() % 10;
    const int t_seconds = project->getSeconds() / 10;
    const int seconds = project->getSeconds() % 10;

    const std::string projId = "##" + std::to_string(projectIndex);

    ImGui::TextColored(project->getColor(), "%s", project->getName().c_str());
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "%i%i:%i%i:%i%i",
        t_hours, hours,
        t_minutes, minutes,
        t_seconds, seconds
    );
    ImGui::SameLine();
    if (ImGui::Button( ((project->getStatus() ? "Stop" : "Start") + projId).c_str() ) )
    {
        // Start/stop the project
        this->manager->toggleProject(projectIndex);
        this->manager->markChanges();
    }
    ImGui::SameLine();
    if (ImGui::Button(("Edit" + projId).c_str()))
    {
        // Open edit dialog
        this->modalProjectIndex = projectIndex;
        this->modalState = ModalState::EDIT;
        this->showEditCreateModal = true;
        this->modalData = {project->getName(), project->getColor()};
    }
}

void UIManager::renderEditCreateModal(int projectIndex = -1)
{
    Project* project = projectIndex != -1 ? this->manager->getProject(projectIndex) : new Project();
    const char* modalId = modalState == ModalState::EDIT ? "Edit Project" : "New Project";

    ImGui::OpenPopup(modalId);
    if (ImGui::BeginPopupModal(modalId, &showEditCreateModal, ImGuiWindowFlags_AlwaysAutoResize))
    {
        // Inputs
        ImGui::InputText("Name", &modalData.name);
        ImGui::ColorEdit4("Color", (float*)&modalData.color, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);

        ImGui::Separator();

        // Action buttons
        if (ImGui::Button("Save"))
        {
            project->setName(modalData.name);
            project->setColor(modalData.color);

            if (modalState == ModalState::CREATE)
            {
                this->manager->addProject(project);
                this->manager->markChanges();
            }

            this->resetModalState();
            ImGui::CloseCurrentPopup();

        }

        if (modalState == ModalState::EDIT)
        {
            ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 1.0f)); // Red background
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.8f, 0.0f, 0.0f, 1.0f)); // Darker red on hover
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.6f, 0.0f, 0.0f, 1.0f));
            if (ImGui::Button("Delete"))
            {
                this->manager->deleteProject(projectIndex);
                this->manager->markChanges();
                this->resetModalState();
                ImGui::CloseCurrentPopup();
            }
            ImGui::PopStyleColor(3); // Pop the three style colors we pushed
        }

        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
        {
            this->resetModalState();
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}

// Main render call
void UIManager::render()
{
    glfwPollEvents();
    bool isOpen = true;

    // If the window is minimized (iconified), sleep
    if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
    {
        ImGui_ImplGlfw_Sleep(10);
        return;
    }

    // Start the ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    int width, height;
    glfwGetWindowSize(this->window, &width, &height);
    ImGui::SetNextWindowSize(ImVec2(width, height));
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    
    // Set window flags
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_MenuBar;
    window_flags |= ImGuiWindowFlags_NoTitleBar;

    ImGui::Begin("Projects", &isOpen, window_flags);

    // Draw UI
    this->renderMenuBar();

    std::string text = "Projects";
    if (this->manager->hasUnsavedChanges())
    {
        text += "*";
    }

    ImGui::TextColored(ImVec4(0.247f, 0.831f, 0.922f, 1.0f), text.c_str());
    ImGui::Separator();
    ImGui::BeginChild("Scrolling");
    for (int i = 0; i < this->manager->getProjectCount(); i++)
    {
        this->renderProject(i);
    }

    ImGui::EndChild();

    ImGui::End();

    if (this->showEditCreateModal)
    {
        if (this->modalState == ModalState::CREATE)
        {
            this->renderEditCreateModal();
        }
        else if (this->modalState == ModalState::EDIT)
        {
            // Render the edit modal
            this->renderEditCreateModal(this->modalProjectIndex);
        }
    }



    ImGui::Render();

    // make openGL calls
    int display_w, display_h;
    glfwGetFramebufferSize(this->window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(this->window);

}