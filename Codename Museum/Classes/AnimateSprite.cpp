#include "AnimateSprite.h"
//interprogram dependency

//initializing static const double
const double Clock::m_CLOCKS_PER_SECOND = 1000.00f;

AnimatedSprite::AnimatedSprite(const std::vector<Sprite *> &a_SpriteCollection)
{
	for (unsigned int i = 0; i < a_SpriteCollection.size(); i++)
	{
		m_SpriteCollection.push_back(a_SpriteCollection[i]);
	}
}

AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::AddSprite(Sprite *a_Sprite)
{
	m_SpriteCollection.push_back(a_Sprite);
}

void AnimatedSprite::Animate()
{
	m_Clock.CalculateDeltaTime();
	m_CurrentTime += m_Clock.GetDeltaTime();
	if (m_CurrentTime > m_TimeBetweenSprites)
	{
		++m_CurrentSprite;
		m_CurrentTime = 0.00f;

		if (m_CurrentSprite >= m_SpriteCollection.size())
		{
			m_CurrentSprite = 0;
		}
	}
}

