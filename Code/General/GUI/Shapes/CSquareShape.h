#ifndef CSquareShape_H
#define CSquareShape_H

#include "CVector2i32.h"
#include "CVector2ui32.h"
#include "GUI/Shape/eGUIShape.h"
#include "GUI/Shapes/Geometries/CGUIShapeGeometry_1xPoint_1x1DSize.h"

class CSquareShape : public CGUIShapeGeometry_1xPoint_1x1DSize
{
public:
	CSquareShape(void);

	void							bindEvents(void);
	void							render(void);
	bool							isPointInItem(CVector2i32& vecPoint);
	CVector2i32						getBoundingRectanglePosition(void);
	CVector2ui32					getBoundingRectangleSize(void);
};

#endif