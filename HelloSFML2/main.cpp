#include "imgui.h"
#include "imgui-sfml.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML\Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "", sf::Style::Fullscreen);
	window.setVerticalSyncEnabled(true);
	ImGui::SFML::Init(window);

	sf::Vector2i mousePos;

	int activeColor{ 0 };

	float color[3] = { 0.f, 0.f, 0.f };
	float my_color[3] { 0.f, 0.f, 0.f };
	sf::Color bgColor;
	sf::Color bgColor2;

	bool my_tool_active{ true };
	bool contextMenu{ false };
	bool refresh{ true };

	sf::Font font;
	if (!font.loadFromFile("../arial.ttf"))
	{
		// error...
	}
	sf::Text text;
	// select the font
	text.setFont(font); // font is a sf::Font
	// set the string to display
	text.setString("CNN Creator");
	// set the character size
	text.setCharacterSize(32); // in pixels, not points!
	// set the color
	text.setFillColor(sf::Color(100,100,100));

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
			if (event.type == sf::Event::MouseButtonPressed)
			{
				// right click opens / closes context menu on current mouse position
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					contextMenu = !contextMenu;
					refresh = true;
					mousePos = sf::Mouse::getPosition();
				}
			}
			if (event.type == sf::Event::KeyPressed)
			{
				// close program if escape is pressed
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
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

		if (my_tool_active) {
			// Create a window called "My First Tool", with a menu bar.
			ImGui::Begin("My First Tool", &my_tool_active, ImGuiWindowFlags_MenuBar);
			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
					if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
					if (ImGui::MenuItem("Close", "Ctrl+W")) { my_tool_active = false; }
					ImGui::EndMenu();
				}
				ImGui::EndMenuBar();
			}

			// Edit a color (stored as ~3 floats)
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
		}

		if (contextMenu) {
			if (refresh) {
				ImGui::SetNextWindowPos(mousePos);
				refresh = false;
			}
			ImGui::SetNextWindowSize(sf::Vector2f(200.f, 150.f));
			ImGui::Begin("ClickWindow", &contextMenu, ImGuiWindowFlags_NoResize);
			ImGui::Text("Hello, world %d", 123);
			if (ImGui::Button("Save"))
			{
				// do stuff
			}
			if (ImGui::Button("Close Window"))
			{
				contextMenu = false;
				refresh = true;
			}
			ImGui::End();
		}

		if (activeColor == 0)
			window.clear(bgColor); // fill background with color
		else
			window.clear(bgColor2);

		window.draw(text);
		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
}