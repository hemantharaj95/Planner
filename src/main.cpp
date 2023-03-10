#include <iostream>
#include <../include/environment/environment.h>
#include <../include/planner/planner.h>

#include "imgui.h"
#include "imgui_impl_glut.h"
#include "imgui_impl_opengl2.h"
#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/freeglut.h>
#endif

#ifdef _MSC_VER
#pragma warning (disable: 4505) // unreferenced local function has been removed
#endif

// Our state
static bool show_demo_window = true;
static bool show_another_window = false;
static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

class App
{
    public:
        App()
        {
            // Create GLUT window
            int argc = 0;
            char* argv[1] = {(char*)"hi"};
            glutInit(&argc, argv);
        #ifdef __FREEGLUT_EXT_H__
            glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
        #endif
            glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE);
            glutInitWindowSize(1280, 720);
            glutCreateWindow("Planning Algorithm");

            // Setup GLUT display function
            // We will also call ImGui_ImplGLUT_InstallFuncs() to get all the other functions installed for us,
            // otherwise it is possible to install our own functions and call the imgui_impl_glut.h functions ourselves.
            glutDisplayFunc(glut_display_func);

            // Setup Dear ImGui context
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO(); (void)io;
            //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

            // Setup Dear ImGui style
            ImGui::StyleColorsDark();
            //ImGui::StyleColorsLight();

            // Setup Platform/Renderer backends
            // FIXME: Consider reworking this example to install our own GLUT funcs + forward calls ImGui_ImplGLUT_XXX ones, instead of using ImGui_ImplGLUT_InstallFuncs().
            ImGui_ImplGLUT_Init();
            ImGui_ImplGLUT_InstallFuncs();
            ImGui_ImplOpenGL2_Init();

            // show_demo_window = true;
            // show_another_window = true;
            // clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        }
    
        ~App()
        {
            // Cleanup
            ImGui_ImplOpenGL2_Shutdown();
            ImGui_ImplGLUT_Shutdown();
            ImGui::DestroyContext();
        }

        static void my_display_code()
        {
            // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
            if (show_demo_window)
                ImGui::ShowDemoWindow(&show_demo_window);

            // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
            {
                static float f = 0.0f;
                static int counter = 0;

                ImGui::Begin("Inputs");                          // Create a window called "Hello, world!" and append into it.

                ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
                ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
                ImGui::Checkbox("Another Window", &show_another_window);

                ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
                ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

                if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                    counter++;
                ImGui::SameLine();
                ImGui::Text("counter = %d", counter);

                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                ImGui::End();
            }

            // 3. Show another simple window.
            if (show_another_window)
            {
                ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
                ImGui::Text("Hello from another window!");
                if (ImGui::Button("Close Me"))
                    show_another_window = false;
                ImGui::End();
            }
        }

        void update()
        {
            glutMainLoop();
        }

        static void glut_display_func()
        {
            // Start the Dear ImGui frame
            ImGui_ImplOpenGL2_NewFrame();
            ImGui_ImplGLUT_NewFrame();

            my_display_code();

            // Rendering
            ImGui::Render();
            ImGuiIO& io = ImGui::GetIO();
            glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);
            glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT);
            //glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound, but prefer using the GL3+ code.
            ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

            glutSwapBuffers();
            glutPostRedisplay();
        }
};

int main()
{
    std::shared_ptr<Grid_Map<int>> env = std::make_shared<Grid_Map<int>>(); 

    std::vector<int> neigh = env->neighbor(10);

    for(int val : neigh){
        std::cout << "->" << val << std::endl; 
    }

    Dijkstra<int> dijk = Dijkstra<int>(env);
    dijk.set_timeout(60000);
    dijk.set_start(3);
    dijk.set_goal(17);
    dijk.plan();

    for(auto state: dijk.get_soln()){
        std::cout << "Plan " << state <<"->";
    }
    std::cout << std::endl;
}