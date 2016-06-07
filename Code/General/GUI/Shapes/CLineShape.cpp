#include "CLineShape.h"
#include "Event/eEvent.h"
#include "GUI/CGUIManager.h"
#include "GUI/GraphicsLibrary/CGraphicsLibrary.h"

auto pOnRender_Line		= [](void *pShape, void *pTriggerArg) { ((CLineShape*) pShape)->render(); };

CLineShape::CLineShape(void) :
	CGUIShape(GUI_SHAPE_LINE)
{
}

// event binding
void					CLineShape::bindEvents(void)
{
	storeEventBoundFunction(getWindow()->bindEvent(EVENT_onRender, pOnRender_Line, this));
}

// render
void					CLineShape::render(void)
{
	CGraphicsLibrary *pGFX = CGUIManager::getInstance()->getGraphicsLibrary();

	pGFX->drawLine(getPolygonPointPositions()[0], getPolygonPointPositions()[1], getStyles());
}