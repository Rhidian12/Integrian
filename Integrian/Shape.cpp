#include "IntegrianPCH.h"
#include "Shape.h"

Integrian::Shape::Shape(const TypeOfShape shape)
	: m_Shapes{}
	, m_TypeOfShape{ shape }
{

}

void Integrian::Shape::SetShape(const TypeOfShape shape) noexcept
{
	m_TypeOfShape = shape;
}

Integrian::Shape::VariantShape&& Integrian::Shape::operator[](const uint8_t index) const noexcept
{
	return std::move(m_Shapes[static_cast<TypeOfShape>(index)]);
}
