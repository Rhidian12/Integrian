#include "IntegrianPCH.h" // precompiled header
#include "Utility Functions.h" // header

#pragma region DrawFunctions
void Integrian::DrawRectangle(const Rectf& rect)
{
	glBegin(GL_LINE_LOOP);
	{
		glVertex2f(rect[VertexLocation::LeftBottom].x, rect[VertexLocation::LeftBottom].y);
		glVertex2f(rect[VertexLocation::RightBottom].x, rect[VertexLocation::RightBottom].y);
		glVertex2f(rect[VertexLocation::RightTop].x, rect[VertexLocation::RightTop].y);
		glVertex2f(rect[VertexLocation::LeftTop].x, rect[VertexLocation::LeftTop].y);
	}
	glEnd();
}

void Integrian::DrawRectangle(const Rectf& rect, const RGBColour& colour)
{
	glColor3f(colour.r, colour.g, colour.b);
	glBegin(GL_LINE_LOOP);
	{
		glVertex2f(rect[VertexLocation::LeftBottom].x, rect[VertexLocation::LeftBottom].y);
		glVertex2f(rect[VertexLocation::RightBottom].x, rect[VertexLocation::RightBottom].y);
		glVertex2f(rect[VertexLocation::RightTop].x, rect[VertexLocation::RightTop].y);
		glVertex2f(rect[VertexLocation::LeftTop].x, rect[VertexLocation::LeftTop].y);
	}
	glEnd();
}

void Integrian::DrawFilledRectangle(const Rectf& rect)
{
	glBegin(GL_POLYGON);
	{
		glVertex2f(rect[VertexLocation::LeftBottom].x, rect[VertexLocation::LeftBottom].y);
		glVertex2f(rect[VertexLocation::RightBottom].x, rect[VertexLocation::RightBottom].y);
		glVertex2f(rect[VertexLocation::RightTop].x, rect[VertexLocation::RightTop].y);
		glVertex2f(rect[VertexLocation::LeftTop].x, rect[VertexLocation::LeftTop].y);
	}
	glEnd();
}
void Integrian::DrawFilledRectangle(const Rectf& rect, const RGBColour& colour)
{
	glColor3f(colour.r, colour.g, colour.b);
	glBegin(GL_POLYGON);
	{
		glVertex2f(rect[VertexLocation::LeftBottom].x, rect[VertexLocation::LeftBottom].y);
		glVertex2f(rect[VertexLocation::RightBottom].x, rect[VertexLocation::RightBottom].y);
		glVertex2f(rect[VertexLocation::RightTop].x, rect[VertexLocation::RightTop].y);
		glVertex2f(rect[VertexLocation::LeftTop].x, rect[VertexLocation::LeftTop].y);
	}
	glEnd();
}

void Integrian::DrawCircle(const Circlef& circle)
{
	glBegin(GL_POINTS);
	{
		for (int i{}; i < 360; ++i)
		{
			glVertex2f(circle.center.x + circle.radius * cosf(float(i)), circle.center.y + circle.radius * sinf(float(i)));
		}
	}
	glEnd();
}

void Integrian::DrawFilledCircle(const Circlef& circle, const RGBColour& colour)
{
	glColor3f(colour.r, colour.g, colour.b);
	glBegin(GL_POLYGON);
	{
		for (int i{}; i < 360; ++i)
		{
			glVertex2f(circle.center.x + circle.radius * cosf(float(i)), circle.center.y + circle.radius * sinf(float(i)));
		}
	}
	glEnd();
}

void Integrian::DrawTriangle(const Point2f& top, const Point2f& left, const Point2f& right)
{
	glBegin(GL_LINE_LOOP);
	{
		glVertex2f(top.x, top.y);
		glVertex2f(left.x, left.y);
		glVertex2f(right.x, right.y);
	}
	glEnd();
}

void Integrian::DrawFilledTriangle(const Point2f& top, const Point2f& left, const Point2f& right)
{
	glBegin(GL_TRIANGLES);
	{
		glVertex2f(top.x, top.y);
		glVertex2f(left.x, left.y);
		glVertex2f(right.x, right.y);
	}
	glEnd();
}

void Integrian::DrawLine(const Point2f& start, const Point2f& end, const RGBColour& colour, const float lineWidth)
{
	glColor3f(colour.r, colour.g, colour.b);
	glLineWidth(lineWidth);
	glBegin(GL_LINES);
	{
		glVertex2f(start.x, start.y);
		glVertex2f(end.x, end.y);
	}
	glEnd();
}
constexpr bool Integrian::AlwaysFalse()
{
	return false;
}
#pragma endregion