#pragma once

/*=============================================================================*/
// Copyright 2020-2021 Elite Engine
// Authors: Yosha Vandaele
/*=============================================================================*/
// Original File: EGraphNodeTypes.h
/*=============================================================================*/

// ALL GRAPH RELATED FILES ARE MADE BY YOSHA VANDAELE
// I DID *NOT* MAKE THESE MYSELF TO SPARE TIME

#ifndef INTEGRIAN_GRAPHNODE_H
#define INTEGRIAN_GRAPHNODE_H

#include "IntegrianPCH.h"
#include "GraphEnums.h"

namespace Integrian
{
	class GraphNode
	{
	public:
		GraphNode() : m_Index(invalid_node_index) {}
		explicit GraphNode(int idx) : m_Index(idx) {}

		virtual ~GraphNode() = default;

		int GetIndex() const { return m_Index; }
		void SetIndex(int newIdx) { m_Index = newIdx; }

		bool operator==(const GraphNode& rhs) { return m_Index == rhs.m_Index; }

	protected:
		int m_Index;
	};

	class GraphNode2D : public GraphNode
	{
	public:
		GraphNode2D(int index, const Point2f& pos = {})
			: GraphNode(index), m_Position(pos), m_Color()
		{
		}
		virtual ~GraphNode2D() = default;

		Point2f GetPosition() const { return m_Position; }
		void SetPosition(const Point2f& newPos) { m_Position = newPos; }

		RGBColour GetColor() const { return m_Color; }
		void SetColor(const RGBColour& color) { m_Color = color; }

	protected:
		Point2f m_Position;
		RGBColour m_Color;
	};
}

#endif // !INTEGRIAN_GRAPHNODE_H