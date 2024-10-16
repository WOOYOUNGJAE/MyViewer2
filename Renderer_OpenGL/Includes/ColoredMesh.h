#pragma once
#include "MeshObject.h"


/**
 * @brief Mesh with Vertex(Position, Normal, Color)
 */
class CColoredMesh : public CMeshObject
{
public:
	CColoredMesh();
	~CColoredMesh() = default;
public:
	void Begin_CreateMesh(void* pData) override;
	void End_CreateMesh(void* pData) override;
	
private:
	POSITIONS m_vecPositions;
	NORMALS m_vecNormals;
	COLORS m_vecColors;

	
};