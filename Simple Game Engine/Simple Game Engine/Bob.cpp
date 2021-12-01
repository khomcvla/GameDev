#include "pch.h"
#include "bob.h"

Bob::Bob()
{
	m_Speed = 400;

	m_Texture.loadFromFile("bob.png");
	m_Sprite.setTexture(m_Texture);

	m_Position.x = 500;
	m_Position.y = 800;

}

Sprite Bob::getSprite()
{
	return m_Sprite;
}

void Bob::moveLeft()
{
	m_LeftPressed = true;
}

void Bob::moveRight()
{
	m_RightPressed = true;
}

void Bob::stopLeft()
{
	m_LeftPressed = false;
}

void Bob::stopRight()
{
	m_RightPressed = false;
}

void Bob::update(float elapsedTime)
{
	if (m_RightPressed)
	{
		m_Position.x += m_Speed * elapsedTime;
	}

	if (m_LeftPressed)
	{
		m_Position.x -= m_Speed * elapsedTime;
	}

	m_Sprite.setPosition(m_Position);

}