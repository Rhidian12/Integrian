#include "pch.h"
#include "Utility Functions.h"
void Engine::DrawRectangle(const Rectf& rect)
{
	glBegin(GL_LINE_LOOP);
	{
		glVertex2f(rect.leftBottom.x, rect.leftBottom.y);
		glVertex2f(rect.leftBottom.x + rect.width, rect.leftBottom.y);
		glVertex2f(rect.leftBottom.x + rect.width, rect.leftBottom.y + rect.height);
		glVertex2f(rect.leftBottom.x, rect.leftBottom.y + rect.height);
	}
	glEnd();
}
void Engine::DrawRectangle(const Rectf& rect, const RGBColour& colour)
{
	glColor3f(colour.r, colour.g, colour.b);
	glBegin(GL_LINE_LOOP);
	{
		glVertex2f(rect.leftBottom.x, rect.leftBottom.y);
		glVertex2f(rect.leftBottom.x + rect.width, rect.leftBottom.y);
		glVertex2f(rect.leftBottom.x + rect.width, rect.leftBottom.y + rect.height);
		glVertex2f(rect.leftBottom.x, rect.leftBottom.y + rect.height);
	}
	glEnd();
}
void Engine::DrawFilledRectangle(const Rectf& rect)
{
	glBegin(GL_POLYGON);
	{
		glVertex2f(rect.leftBottom.x, rect.leftBottom.y);
		glVertex2f(rect.leftBottom.x + rect.width, rect.leftBottom.y);
		glVertex2f(rect.leftBottom.x + rect.width, rect.leftBottom.y + rect.height);
		glVertex2f(rect.leftBottom.x, rect.leftBottom.y + rect.height);
	}
	glEnd();
}
void Engine::DrawFilledRectangle(const Rectf& rect, const RGBColour& colour)
{
	glColor3f(colour.r, colour.g, colour.b);
	glBegin(GL_POLYGON);
	{
		glVertex2f(rect.leftBottom.x, rect.leftBottom.y);
		glVertex2f(rect.leftBottom.x + rect.width, rect.leftBottom.y);
		glVertex2f(rect.leftBottom.x + rect.width, rect.leftBottom.y + rect.height);
		glVertex2f(rect.leftBottom.x, rect.leftBottom.y + rect.height);
	}
	glEnd();
}
void Engine::DrawCircle(const Circlef& circle)
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
void Engine::DrawFilledCircle(const Circlef& circle, const RGBColour& colour)
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
void Engine::DrawTriangle(const Point2f& top, const Point2f& left, const Point2f& right)
{
	glBegin(GL_LINE_LOOP);
	{
		glVertex2f(top.x, top.y);
		glVertex2f(left.x, left.y);
		glVertex2f(right.x, right.y);
	}
	glEnd();
}
void Engine::DrawFilledTriangle(const Point2f& top, const Point2f& left, const Point2f& right)
{
	glBegin(GL_TRIANGLES);
	{
		glVertex2f(top.x, top.y);
		glVertex2f(left.x, left.y);
		glVertex2f(right.x, right.y);
	}
	glEnd();
}
void Engine::DrawLine(const Point2f& start, const Point2f& end, const RGBColour& colour, const float lineWidth)
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