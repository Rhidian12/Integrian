#include "IntegrianPCH.h" // precompiled header
#include "OrthographicCamera.h" // header
#include <assert.h> // assert()
Integrian::OrthographicCamera::OrthographicCamera(const uint32_t windowWidth, const uint32_t windowHeight, const Rectf& levelBoundaries)
	: m_WindowWidth{ windowWidth }
	, m_WindowHeight{ windowHeight }
	, m_LevelBoundaries{ levelBoundaries }
{
}
Integrian::Point2f Integrian::OrthographicCamera::Transform(const Integrian::Rectf& target)
{
	// == Track Target And Make Sure Camera Does Not Leave LevelBoundaries ==
	Integrian::Point2f camPosition{ Track(target) };
	Clamp(camPosition);

	// == Translate The World ==
	glTranslatef(-camPosition.x, -camPosition.y, 0);

	// == Draw Camera View For Debugging Purposes ==
	glColor3f(0.f, 0.f, 1.f);
	Integrian::DrawRectangle(Integrian::Rectf{ camPosition, float(m_WindowWidth), float(m_WindowHeight) });
	
	return camPosition;
}
Integrian::Point2f Integrian::OrthographicCamera::Track(const Integrian::Rectf& target)
{
	// == Get The Center Coordinates Of The Target ==
	float x = target.leftBottom.x + (target.width / 2);
	float y = target.leftBottom.y + (target.height / 2);

	// == Return The Center Of The Target - Center Of The Screen ==
	return Point2f{ x - m_WindowWidth / 2,y - m_WindowHeight / 2 };
}
void Integrian::OrthographicCamera::Clamp(Integrian::Point2f& bottomLeftPos) const
{
	// == Check If The LevelBoundaries Are Initialised ==
	assert(m_LevelBoundaries != Integrian::Rectf{});

	// == Check Level Boundaries ==
	if (bottomLeftPos.x <= m_LevelBoundaries.leftBottom.x)
		bottomLeftPos.x = m_LevelBoundaries.leftBottom.x;

	if (bottomLeftPos.x + m_WindowWidth >= m_LevelBoundaries.leftBottom.x + m_LevelBoundaries.width)
		bottomLeftPos.x = m_LevelBoundaries.leftBottom.x + m_LevelBoundaries.width - m_WindowWidth;

	if (bottomLeftPos.y <= m_LevelBoundaries.leftBottom.y)
		bottomLeftPos.y = m_LevelBoundaries.leftBottom.y;

	if (bottomLeftPos.y + m_WindowHeight >= m_LevelBoundaries.leftBottom.y + m_LevelBoundaries.height)
		bottomLeftPos.y = m_LevelBoundaries.leftBottom.y + m_LevelBoundaries.height - m_WindowHeight;
}
void Integrian::OrthographicCamera::SetLevelBoundaries(const Integrian::Rectf& levelBoundaries)
{
	m_LevelBoundaries = levelBoundaries;
}