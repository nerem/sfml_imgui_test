#include "imgui.h"
#include "imgui-sfml.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "");
	window.setVerticalSyncEnabled(true);
	ImGui::SFML::Init(window);


	int activeColor{ 0 };

	float color[3] = { 0.f, 0.f, 0.f };
	float my_color[3] { 0.f, 0.f, 0.f };
	sf::Color bgColor;
	sf::Color bgColor2;

	// let's use char array as buffer, see next part
	// for instructions on using std::string with ImGui
	char windowTitle[255] = "ImGui + SFML = <3";

	window.setTitle(windowTitle);
	window.resetGLStates(); // call it if you only draw ImGui. Otherwise not needed.
	sf::Clock deltaClock;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		ImGui::SFML::Update(window, deltaClock.restart());

		ImGui::Begin("Sample window"); // begin window

									   // Background color edit
		if (ImGui::ColorEdit3("Background color", color)) {
			// this code gets called if color value changes, so
			// the background color is upgraded automatically!
			bgColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
			bgColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
			bgColor.b = static_cast<sf::Uint8>(color[2] * 255.f);
		}

		// Window title text edit
		ImGui::InputText("Window title", windowTitle, 255);

		if (ImGui::Button("Update window title")) {
			// this code gets if user clicks on the button
			// yes, you could have written if(ImGui::InputText(...))
			// but I do this to show how buttons work :)
			window.setTitle(windowTitle);
		}

		if (ImGui::Button("Make Master")) {
			activeColor = 0;
		}
		ImGui::End(); // end window

		// Create a window called "My First Tool", with a menu bar.
		ImGui::Begin("My First Tool", false, ImGuiWindowFlags_MenuBar);
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
				if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
				if (ImGui::MenuItem("Close", "Ctrl+W")) {  }
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}


		// Edit a color (stored as ~4 floats)
		if (ImGui::ColorEdit3("Color", my_color)) {
			bgColor2.r = static_cast<sf::Uint8>(my_color[0] * 255.f);
			bgColor2.g = static_cast<sf::Uint8>(my_color[1] * 255.f);
			bgColor2.b = static_cast<sf::Uint8>(my_color[2] * 255.f);
		}

		if (ImGui::Button("Make Master")) {
			activeColor = 1;
		}

		// Plot some values
		const float my_values[] = { 0.2f, 0.1f, 1.0f, 0.5f, 0.9f, 2.2f };
		ImGui::PlotLines("Frame Times", my_values, IM_ARRAYSIZE(my_values));

		// Display contents in a scrolling region
		ImGui::TextColored(ImVec4(1, 1, 0, 1), "Important Stuff");
		ImGui::BeginChild("Scrolling");
		for (int n = 0; n < 50; n++)
			ImGui::Text("%04d: Some text", n);
		ImGui::EndChild();
		ImGui::End();

		if (activeColor == 0)
			window.clear(bgColor); // fill background with color
		else
			window.clear(bgColor2);

		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
}