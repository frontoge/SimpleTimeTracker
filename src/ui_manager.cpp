#include <ui_manager.hpp>
#include <stdio.h>



static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}


UIManager::UIManager()
: manager(nullptr)
{
}

UIManager::UIManager(Manager* manager)
{
    this->manager = manager;
    this->window = nullptr;
    // this->io = ImGui::GetIO();
}

UIManager::~UIManager()
{
    // Destructor implementation
}

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
    if (ImGui::BeginMenuBar()) 
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Save", "Ctrl+S"))
            {
                // Open save dialog
                this->manager->saveProjects();
            }
            if (ImGui::MenuItem("Load", "Ctrl+L"))
            {
                // Open load dialog
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

    ImGui::TextColored(ImVec4(0.247f, 0.831f, 0.922f, 1.0f), "Projects");
    ImGui::Separator();
    ImGui::BeginChild("Scrolling");
    for (int i = 0; i < this->manager->getProjectCount(); i++)
    {
        const Project* proj = this->manager->getProject(i);
        const int t_hours = proj->getHours() / 10;
        const int hours = proj-> getHours() % 10;
        const int t_minutes = proj->getMinutes() / 10;
        const int minutes = proj->getMinutes() % 10;
        const int t_seconds = proj->getSeconds() / 10;
        const int seconds = proj->getSeconds() % 10;

        ImGui::TextColored(ImVec4(0.247f, 0.831f, 0.922f, 1.0f), "%s", proj->getName().c_str());
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "%i%i:%i%i:%i%i",
            t_hours, hours,
            t_minutes, minutes,
            t_seconds, seconds
        );
        ImGui::SameLine();
        if (ImGui::Button(proj->getStatus() ? "Stop" : "Start"))
        {
            this->manager->toggleProject(i);
        }
        ImGui::SameLine();
        if (ImGui::Button("Edit"))
        {
            // Open edit dialog
        }
    }
    ImGui::EndChild();

    ImGui::End();

    bool show_demo_window = true;
    ImGui::ShowDemoWindow(&show_demo_window);

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

void UIManager::cleanup()
{
    // ImGui cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(this->window);
    glfwTerminate();
}