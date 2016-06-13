#ifndef CGUIShapeGeometry_1xPoint_1x1DSize_H
#define CGUIShapeGeometry_1xPoint_1x1DSize_H

#include "Types.h"
#include "CVector2i32.h"
#include "GUI/Shape/eGUIShape.h"
#include "GUI/Shape/CGUIShape.h"

class CGUIShapeGeometry_1xPoint_1x1DSize : public CGUIShape
{
public:
	CGUIShapeGeometry_1xPoint_1x1DSize(eGUIShape eShapeType);

	CVector2i32						getCenterPosition(void);

	void							moveItem(CVector2i32& vecPositionChange) { m_vecPosition += vecPositionChange; }
	void							resizeItemViaOffsets(CVector2i32& vecItemSizeChange) { m_fSize += (((vecItemSizeChange.m_x + vecItemSizeChange.m_y) < 0) ? -1 : 1) * sqrt(vecItemSizeChange.m_x + vecItemSizeChange.m_y); } // todo - methodify

	void							setPosition(CVector2i32& vecPosition) { m_vecPosition = vecPosition; }
	CVector2i32&					getPosition(void) { return m_vecPosition; }

	void							setSize(float32 fSize) { m_fSize = fSize; }
	float32							getSize(void) { return m_fSize; }
	
private:
	CVector2i32						m_vecPosition;
	float32							m_fSize;
};

#endif