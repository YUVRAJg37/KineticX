#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>

constexpr int Width = 800;
constexpr int Height = 800;

int main()
{
	sf::RenderWindow window(sf::VideoMode(Width, Height), "Test");
	ImGui::SFML::Init(window);

	bool circleExists = true;
	float circleRadius = 200.0f;
	int circleSegment = 100.0f;
	float circleColor[3] = { (float)204 / 255, (float)77 / 255, (float)5 / 255 };

	window.setFramerateLimit(60);

	sf::CircleShape circle(200.0f, 100);
	circle.setPosition(200, 200);

	sf::Clock deltaClock;
	while (window.isOpen())
	{
		sf::Event event;

		while(window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed)
				window.close();
		}

		ImGui::SFML::Update(window, deltaClock.restart());

		ImGui::Begin("Window Title");
		ImGui::Checkbox("Circle", &circleExists);
		ImGui::SliderFloat("Circle Radius", &circleRadius, 10.0f, 300.0f);
		ImGui::SliderInt("Circle Segments", &circleSegment, 3.0f,200.0f);
		ImGui::ColorEdit3("Circle Color", circleColor);
		ImGui::End();

		circle.setRadius(circleRadius);
		circle.setPointCount(circleSegment);
		circle.setFillColor(sf::Color(
			(int)(circleColor[0] * 255),
			(int)(circleColor[1] * 255),
			(int)(circleColor[2] * 255)
		));
		circle.setPosition(Width / 2 - circle.getRadius(), Height / 2 -circle.getRadius());

		window.clear(sf::Color(18,33,43));
		if(circleExists)
			window.draw(circle);
		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
	return 0;
}