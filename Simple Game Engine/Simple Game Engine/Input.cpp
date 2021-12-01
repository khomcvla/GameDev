#include "pch.h"
#include "Engine.h"

void Engine::input()
{
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		m_Window.close();
	}

	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		m_Bob.moveLeft();
	}
	else
	{
		m_Bob.stopLeft();
	}

	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		m_Bob.moveRight();
	}
	else
	{
		m_Bob.stopRight();
	}

}