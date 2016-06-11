#include "CGUILayer.h"
#include "GUI/Controls/CButtonControl.h"
#include "GUI/Controls/CCheckControl.h"
#include "GUI/Controls/CDropControl.h"
#include "GUI/Controls/CEditControl.h"
#include "GUI/Controls/CListControl.h"
#include "GUI/Controls/CMenuControl.h"
#include "GUI/Controls/CProgressControl.h"
#include "GUI/Controls/CRadioControl.h"
#include "GUI/Controls/CScrollControl.h"
#include "GUI/Controls/CTabControl.h"
#include "GUI/Controls/CTextControl.h"
#include "GUI/Shapes/CCircleShape.h"
#include "GUI/Shapes/CEllipseShape.h"
#include "GUI/Shapes/CLineShape.h"
#include "GUI/Shapes/CPolygonShape.h"
#include "GUI/Shapes/CRectangleShape.h"
#include "GUI/Shapes/CSquareShape.h"
#include "GUI/Shapes/CTriangleShape.h"
#include "Math/CMathUtility.h"

using namespace std;

CGUILayer::CGUILayer(void) :
	m_pWindow(nullptr),
	m_bEnabled(true)
{
}

// event binding
void									CGUILayer::bindAllEvents(void)
{
	for (CGUIShape *pGUIShape : getShapes().getEntries())
	{
		pGUIShape->bindEvents();
	}
	for (CGUIControl *pWindowControl : getControls().getEntries())
	{
		pWindowControl->bindEvents();
	}
}

void									CGUILayer::unbindAllEvents(void)
{
	for (CGUIControl *pWindowControl : getControls().getEntries())
	{
		pWindowControl->unbindEvents();
	}
	for (CGUIShape *pGUIShape : getShapes().getEntries())
	{
		pGUIShape->unbindEvents();
	}
}

// add control - derived
CButtonControl*		CGUILayer::addButton(CVector2i32& vecPosition, CVector2ui32& vecSize, string strButtonText, CGUIStyles *pStyles)
{
	CButtonControl *pControl = new CButtonControl;
	pControl->setText(strButtonText);
	_addControl(pControl, vecPosition, vecSize, pStyles);
	return pControl;
}

CCheckControl*		CGUILayer::addCheck(CVector2i32& vecPosition, CVector2ui32& vecSize, string strCheckText, CGUIStyles *pStyles)
{
	CCheckControl *pControl = new CCheckControl;
	pControl->setText(strCheckText);
	_addControl(pControl, vecPosition, vecSize, pStyles);
	return pControl;
}

CDropControl*		CGUILayer::addDrop(CVector2i32& vecPosition, CVector2ui32& vecSize, CGUIStyles *pStyles)
{
	CDropControl *pControl = new CDropControl;
	_addControl(pControl, vecPosition, vecSize, pStyles);
	return pControl;
}

CEditControl*		CGUILayer::addEdit(CVector2i32& vecPosition, CVector2ui32& vecSize, string strEditText, CGUIStyles *pStyles)
{
	CEditControl *pControl = new CEditControl;
	pControl->setText(strEditText);
	_addControl(pControl, vecPosition, vecSize, pStyles);
	return pControl;
}

CListControl*		CGUILayer::addList(CVector2i32& vecPosition, CVector2ui32& vecSize, CGUIStyles *pStyles)
{
	CListControl *pControl = new CListControl;
	_addControl(pControl, vecPosition, vecSize, pStyles);
	return pControl;
}

CMenuControl*		CGUILayer::addMenu(CVector2i32& vecPosition, CVector2ui32& vecSize, CGUIStyles *pStyles)
{
	CMenuControl *pControl = new CMenuControl;
	_addControl(pControl, vecPosition, vecSize, pStyles);
	return pControl;
}

CProgressControl*	CGUILayer::addProgress(CVector2i32& vecPosition, CVector2ui32& vecSize, CGUIStyles *pStyles)
{
	CProgressControl *pControl = new CProgressControl;
	_addControl(pControl, vecPosition, vecSize, pStyles);
	return pControl;
}

CRadioControl*		CGUILayer::addRadio(CVector2i32& vecPosition, CVector2ui32& vecSize, string strRadioText, CGUIStyles *pStyles)
{
	CRadioControl *pControl = new CRadioControl;
	pControl->setText(strRadioText);
	_addControl(pControl, vecPosition, vecSize, pStyles);
	return pControl;
}

CScrollControl*		CGUILayer::addScroll(CVector2i32& vecPosition, CVector2ui32& vecSize, CGUIStyles *pStyles)
{
	CScrollControl *pControl = new CScrollControl;
	_addControl(pControl, vecPosition, vecSize, pStyles);
	return pControl;
}

CTabControl*		CGUILayer::addTabBar(CVector2i32& vecPosition, CVector2ui32& vecSize, CGUIStyles *pStyles)
{
	CTabControl *pControl = new CTabControl;
	_addControl(pControl, vecPosition, vecSize, pStyles);
	return pControl;
}

CTextControl*		CGUILayer::addText(CVector2i32& vecPosition, CVector2ui32& vecSize, string strText, CGUIStyles *pStyles)
{
	CTextControl *pControl = new CTextControl;
	pControl->setText(strText);
	_addControl(pControl, vecPosition, vecSize, pStyles);
	return pControl;
}

// add control - base
void						CGUILayer::_addControl(CGUIControl *pControl, CVector2i32& vecPosition, CVector2ui32& vecSize, CGUIStyles *pStyles)
{
	pControl->setLayer(this);
	pControl->setPosition(vecPosition);
	pControl->setSize(vecSize);
	if (pStyles)
	{
		pControl->setStyles(pStyles);
	}
	getControls().addEntry(pControl);
}

// create shape
CGUIShape*					CGUILayer::createShapeFromId(eGUIShape eShapeId)
{
	switch (eShapeId)
	{
	case GUI_SHAPE_CIRCLE:		return new CCircleShape;
	case GUI_SHAPE_ELLIPSE:		return new CEllipseShape;
	case GUI_SHAPE_LINE:		return new CLineShape;
	case GUI_SHAPE_POLYGON:		return new CPolygonShape;
	case GUI_SHAPE_RECTANGLE:	return new CRectangleShape;
	case GUI_SHAPE_SQUARE:		return new CSquareShape;
	case GUI_SHAPE_TRIANGLE:	return new CTriangleShape;
	}
	return nullptr;
}

// add shape - derived
CGUIShape*					CGUILayer::addShape(eGUIShape eShapeId, CGUIStyles *pStyles)
{
	CGUIShape *pShape = createShapeFromId(eShapeId);
	_addShape(pShape, pStyles);
	return pShape;
}

CLineShape*					CGUILayer::addLine(CVector2i32& vecPoint1, CVector2i32& vecPoint2, CGUIStyles *pStyles)
{
	CLineShape *pLine = new CLineShape;
	vector<CVector2i32> vecPoints;
	vecPoints.resize(2);
	pLine->setPoint1(vecPoint1);
	pLine->setPoint2(vecPoint2);
	_addShape(pLine, pStyles);
	return pLine;
}

CRectangleShape*			CGUILayer::addRectangle(CVector2i32& vecPosition, CVector2ui32& vecSize, CGUIStyles *pStyles)
{
	CRectangleShape *pRectangle = new CRectangleShape;
	pRectangle->setPosition(vecPosition);
	pRectangle->setSize(vecSize);
	_addShape(pRectangle, pStyles);
	return pRectangle;
}

CEllipseShape*				CGUILayer::addEllipse(CVector2i32& vecPosition, CVector2ui32& vecSize, CGUIStyles *pStyles)
{
	CEllipseShape *pEllipse = new CEllipseShape;
	pEllipse->setPosition(vecPosition);
	pEllipse->setSize(vecSize);
	_addShape(pEllipse, pStyles);
	return pEllipse;
}

CPolygonShape*				CGUILayer::addPolygon(vector<CVector2i32>& vecPoints, CGUIStyles *pStyles)
{
	CPolygonShape *pPolygon = new CPolygonShape;
	pPolygon->setPoints(vecPoints);
	_addShape(pPolygon, pStyles);
	return pPolygon;
}

// add shape - derived - wrappers
CSquareShape*				CGUILayer::addSquare(CVector2i32& vecPosition, uint32 uiSideLength, CGUIStyles *pStyles)
{
	CSquareShape *pSquare = new CSquareShape;
	pSquare->setPosition(vecPosition);
	pSquare->setSize(uiSideLength);
	_addShape(pSquare, pStyles);
	return pSquare;
}

CCircleShape*				CGUILayer::addCircle(CVector2i32& vecPosition, uint32 uiRadius, CGUIStyles *pStyles)
{
	CCircleShape *pCircle = new CCircleShape;
	uint32 uiDiameter = uiRadius * 2;
	pCircle->setPosition(vecPosition);
	pCircle->setSize(uiRadius);
	_addShape(pCircle, pStyles);
	return pCircle;
}

CTriangleShape*				CGUILayer::addTriangle(CVector2i32& vecPoint1, CVector2i32& vecPoint2, CVector2i32& vecPoint3, CGUIStyles *pStyles)
{
	CTriangleShape *pTriangle = new CTriangleShape;
	pTriangle->setPoint1(vecPoint1);
	pTriangle->setPoint2(vecPoint2);
	pTriangle->setPoint3(vecPoint3);
	_addShape(pTriangle, pStyles);
	return pTriangle;
}

CTriangleShape*				CGUILayer::addEquilateralTriangle(CVector2i32& vecBottomLeftPoint, CVector2i32& vecBottomRightPoint, CGUIStyles *pStyles)
{
	const float32
		fSidesLength = CMathUtility::getDistanceBetweenPoints(vecBottomLeftPoint, vecBottomRightPoint),
		fBaseAngle = CMathUtility::getAngleBetweenPoints(vecBottomLeftPoint, vecBottomRightPoint),
		fAngle = CMathUtility::convertDegreesToRadians(60.0f);
	CVector2i32
		vecTipPoint = CMathUtility::getPositionInFrontOfPosition(vecBottomLeftPoint, fBaseAngle - fAngle, fSidesLength);
	return addTriangle(vecBottomLeftPoint, vecBottomRightPoint, vecTipPoint, pStyles);
}

CTriangleShape*				CGUILayer::addEquilateralTriangle(CVector2i32& vecBottomLeftPoint, float32 fSidesLength, float32 fBaseAngle, CGUIStyles *pStyles)
{
	const float32
		fAngle = CMathUtility::convertDegreesToRadians(60.0f);
	fBaseAngle = CMathUtility::convertDegreesToRadians(fBaseAngle);
	CVector2i32
		vecBottomRightPoint = CMathUtility::getPositionInFrontOfPosition(vecBottomLeftPoint, fBaseAngle, fSidesLength),
		vecTopPoint = CMathUtility::getPositionInFrontOfPosition(vecBottomLeftPoint, fBaseAngle - fAngle, fSidesLength);
	return addTriangle(vecBottomLeftPoint, vecBottomRightPoint, vecTopPoint, pStyles);
}

CTriangleShape*				CGUILayer::addIsoscelesTriangle(CVector2i32& vecBaseCenterPoint, CVector2i32& vecTipPoint, uint32 uiBaseHalfWidth, CGUIStyles *pStyles)
{
	const float32
		fBaseToTipDistance = CMathUtility::getDistanceBetweenPoints(vecBaseCenterPoint, vecTipPoint),
		fBaseToTipAngle = CMathUtility::getAngleBetweenPoints(vecBaseCenterPoint, vecTipPoint),
		f90DegreeAngle = CMathUtility::convertDegreesToRadians(90.0f);
	CVector2i32
		vecBasePoint1 = CMathUtility::getPositionInFrontOfPosition(vecBaseCenterPoint, fBaseToTipAngle - f90DegreeAngle, uiBaseHalfWidth),
		vecBasePoint2 = CMathUtility::getPositionInFrontOfPosition(vecBaseCenterPoint, fBaseToTipAngle + f90DegreeAngle, uiBaseHalfWidth);
	return addTriangle(vecBasePoint1, vecBasePoint2, vecTipPoint, pStyles);
}

CTriangleShape*				CGUILayer::addIsoscelesTriangle(CVector2i32& vecBottomLeftPoint, float32 fBaseLength, float32 fTipAngle, float32 fBaseAngle, CGUIStyles *pStyles)
{
	float32
		fLinesAngle = (180.0f - fTipAngle) / 2.0f,
		fHeight = (fBaseLength / 2.0f) * tan(fLinesAngle),
		fSidesLength = sqrt(((fBaseLength * fBaseLength) / 4.0f) + (fHeight * fHeight));
	fTipAngle = CMathUtility::convertDegreesToRadians(fTipAngle);
	fBaseAngle = CMathUtility::convertDegreesToRadians(fBaseAngle);
	fLinesAngle = CMathUtility::convertDegreesToRadians(fLinesAngle);
	CVector2i32
		vecBottomRightPoint = CMathUtility::getPositionInFrontOfPosition(vecBottomLeftPoint, fBaseAngle, fBaseLength),
		vecTipPoint = CMathUtility::getPositionInFrontOfPosition(vecBottomLeftPoint, fBaseAngle - fLinesAngle, fSidesLength);
	return addTriangle(vecBottomLeftPoint, vecBottomRightPoint, vecTipPoint, pStyles);
}

// add shape - base
void						CGUILayer::_addShape(CGUIShape *pShape, CGUIStyles *pStyles)
{
	pShape->setLayer(this);
	if (pStyles)
	{
		pShape->setStyles(pStyles);
	}
	getShapes().addEntry(pShape);
}

// enabled state
void						CGUILayer::setEnabled(bool bEnabled)
{
	bool bPreviousEnabledState = m_bEnabled;
	m_bEnabled = bEnabled;
	if (bEnabled)
	{
		if (!bPreviousEnabledState)
		{
			bindAllEvents();
		}
	}
	else
	{
		if (bPreviousEnabledState)
		{
			unbindAllEvents();
		}
	}
}