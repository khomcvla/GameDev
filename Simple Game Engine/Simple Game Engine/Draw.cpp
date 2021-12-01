#include "pch.h"
#include "Engine.h"

void Engine::draw()
{
	m_Window.clear(Color::White);

	m_Window.draw(m_BackgroundSprite);
	m_Window.draw(m_Bob.getSprite());

	m_Window.display();
}