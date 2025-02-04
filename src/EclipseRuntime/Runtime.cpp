#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <implot.h>
#include <implot_internal.h>

#include <EclipseGL/GL.hpp>
#include <EclipseRuntime/Window.hpp>
#include <EclipseUtils/Logger.hpp>
#include <EclipseUtils/Maths.hpp>

#include <vector>

double delta = 0;
bool vsync = false;

std::vector<double> frametimes;
const size_t max_points = 100; 

void static init_imgui(et::window _pwindow) {
	// ImGui Initialize
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImPlot::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.Fonts->AddFontFromFileTTF("../assets/Poppins-Regular.ttf", 15);
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(_pwindow, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void static destroy_imgui() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImPlot::DestroyContext();
	ImGui::DestroyContext();
}

void static listen_to_input() {

}

et::u32 static display_with_interval(et::u32 value, et::u32 interval) {
	static et::u32 interval_timer = 0;
	static et::u32 display_with_interval_previous_value = 0;
	interval_timer++;
	if (interval_timer > interval) {
		interval_timer = 0;
		display_with_interval_previous_value = value;
	}
	return display_with_interval_previous_value;
}

int main(int argc, char* argv[]) {
	// Create window
	e::window window(e::window::WindowCreateInfo{"Eclipse", 800, 600, true, false, vsync, 4});

	// Create OpenGL Context
	e::gl gl((GLADloadproc)e::window::getProcAddress);

	// Set viewport
	gl.set_viewport_size(0, 0, window.window_width, window.window_height);

	// Enable MSAA
	gl.enable(GL_MULTISAMPLE);

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Initalize ImGUI
	init_imgui(window.pwindow);

	// mainloop
	while (!window.shouldClose()) {
		// delta
		delta = window.getIntervalToPreviousCall();
		// Store frametime (e.g., in milliseconds)
		double ms = delta * 1000.0;
		frametimes.push_back(ms);
		if (frametimes.size() > max_points)
			frametimes.erase(frametimes.begin());
		
		// Input
		listen_to_input();

		// Clear framebuffer before draw
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Frame start call
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// GL Layer

		// UI Layer 
		ImGui::Begin("Debugger");
		
		ImGui::Text("FPS: %d", display_with_interval(e::maths::ceil(1 / delta), 100));

		if (ImPlot::BeginPlot("Frametime Graph", ImVec2(-1, 150))) {
			// Optional: setup axes labels and automatic fitting
			ImPlot::SetupAxes("Frame", "ms", ImPlotAxisFlags_AutoFit, ImPlotAxisFlags_LockMin);

			// Build x-axis values as indices (0 to N-1)
			std::vector<double> xs(frametimes.size());
			for (size_t i = 0; i < frametimes.size(); ++i)
				xs[i] = static_cast<double>(i);

			ImPlot::PushStyleColor(ImPlotCol_Line, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
			ImPlot::PlotLine("Frame Time", xs.data(), frametimes.data(), static_cast<int>(frametimes.size()));
			ImPlot::PopStyleColor();  // Restore previous style
			ImPlot::EndPlot();
		}

		ImGui::Checkbox("Vsync", &vsync);

		ImGui::End();
		ImGui::Render();

		// Draw
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (vsync)
			window.setVsync(true);
		else
			window.setVsync(false);

		window.update();
	}

	destroy_imgui();
}