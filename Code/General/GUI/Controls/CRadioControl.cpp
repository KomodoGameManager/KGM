#include "CRadioControl.h"
#include "Math/CMathUtility.h"
#include "Event/CEventManager.h"
#include "Event/eEvent.h"
#include "GUI/Window/CWindow.h"
#include "GUI/CGUIManager.h"
#include "GUI/GraphicsLibrary/CGraphicsLibrary.h"
#include "GUI/Styles/CGUIStyles.h"

auto pOnMouseUp_Radio		= [](void *pControl, void *pTriggerArg) { ((CRadioControl*) pControl)->onMouseUp(*(CVector2i32*) pTriggerArg); };
auto pOnRender_Radio		= [](void *pControl) { ((CRadioControl*) pControl)->render(); };

CRadioControl::CRadioControl(void) :
	CGUIControl(GUI_CONTROL_RADIO),
	CGUIControlComponent_Text(),
	m_uiIconRightMargin(5),
	m_uiGroupId(0),
	m_bMarked(false)
{
}

// event binding
void		CRadioControl::bindEvents(void)
{
	storeEventBoundFunction(getWindow()->bindEvent(EVENT_onLeftMouseUp, pOnMouseUp_Radio, this));
	storeEventBoundFunction(getWindow()->bindEvent(EVENT_onRender, pOnRender_Radio, this));
}

// input
void		CRadioControl::onMouseUp(CVector2i32& vecCursorPosition)
{
	if (isPointInControl(vecCursorPosition))
	{
		if (getWindow()->triggerEvent(EVENT_onMarkRadio, this))
		{
			getWindow()->unmarkRadios(this);
			setMarked(true);
			getWindow()->setMarkedToRedraw(true);
		}
	}
}

// render
void		CRadioControl::render(void)
{
	CGraphicsLibrary *pGFX = CGUIManager::getInstance()->getGraphicsLibrary();

	float32 fRadius = getIconRadius();
	CVector2i32 vecCircleCenterPosition = getPosition();
	if (isMarked())
	{
		getStyles()->setStyleNameOverwrite("fill-colour", "fill-colour-marked");
	}
	else
	{
		getStyles()->setStyleNameOverwrite("fill-colour", "fill-colour-unmarked");
	}
	pGFX->drawCircle(vecCircleCenterPosition, fRadius, getStyles());
	getStyles()->restoreStyleNameOverwrites();
	pGFX->drawText(getTextPosition(), getTextSize(), getText(), getStyles());
}

// cursor
bool			CRadioControl::isPointInControl(CVector2i32& vecPoint)
{
	return CMathUtility::isPointInRectangle(vecPoint, getPosition(), getSizeWithText());
}

// position
CVector2i32		CRadioControl::getIconCenterPosition(void)
{
	return CMathUtility::getEllipseFromRectangle(getPosition(), getSize());
}

// size
CVector2ui32	CRadioControl::getSizeWithText(void)
{
	return getSize() + CVector2ui32(getTextWidth(), 0);
}

uint32			CRadioControl::getIconRadius(void)
{
	return CMathUtility::convertDiameterToRadius(getSize().m_x);
}

// text
CVector2i32		CRadioControl::getTextPosition(void)
{
	return CVector2i32(getPosition().m_x + getSize().m_x + getIconRightMargin(), getPosition().m_y);
}

CVector2ui32	CRadioControl::getTextSize(void)
{
	return CVector2ui32(500, getSize().m_y); // todo - change 500 to fetch the displayed width of just the text
}