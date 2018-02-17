#ifndef ANIMATESPRITE_H_
#define ANIMATESPRITE_H_

#include <vector>
#include <ctime>

class Clock
{
public:
	Clock()
	{
		m_LastTime = (double)(std::clock() / m_CLOCKS_PER_SECOND);
	};
	~Clock() {};
	void CalculateDeltaTime()
	{
		m_DeltaTime = (double)(std::clock() / m_CLOCKS_PER_SECOND) - m_LastTime;
		m_LastTime = (double)(std::clock() / m_CLOCKS_PER_SECOND);
	}
	//in milliseconds
	double GetDeltaTime() const { return m_DeltaTime; }
private:
	double m_LastTime = 0;
	double m_DeltaTime = 0;
	static const double m_CLOCKS_PER_SECOND;
};

//forward declaration
class Sprite;

class AnimatedSprite
{
public:
	AnimatedSprite(const std::vector<Sprite *> &a_SpriteCollection);
	AnimatedSprite() {};
	~AnimatedSprite();

	void AddSprite(Sprite *a_Sprite);
	void Animate();
private:
	std::vector<Sprite *> m_SpriteCollection;
	unsigned int m_CurrentSprite = 0;
	double m_CurrentTime = 0.0f;
	double m_TimeBetweenSprites = 1.00f;
	Clock m_Clock;
};

#endif // !ANIMATESPRITE_H_

