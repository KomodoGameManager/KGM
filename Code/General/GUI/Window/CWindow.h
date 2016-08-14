#ifndef CWindow_H
#define CWindow_H

#include <Windows.h>
#include <gdiplus.h>
#include "Types.h"
#include "CSize2D.h"
#include "Pool/CVectorPool.h"
#include "Event/CEventType.h"
#include "Event/CEventBoundFunction.h"
#include "Event/CEventBinder.h"
#include "GUI/Layer/CGUILayer.h"
#include "GUI/Item/CGUIItem.h"
#include "GUI/Control/CGUIControl.h"
#include "GUI/Styles/CGUIStyleableEntity.h"
#include "GUI/Interaction/CRectangleItemPlacement.h"

class CRadioControl;
class CDropTarget;
class CGUIStyles;
class CWindow;
class CInputEventCallbacks;

class CWindow : public CEventType, public CEventBinder, public CGUIStyleableEntity, public CVectorPool<CGUILayer*>
{
public:
	CWindow(void);
	~CWindow(void);
	
	void									unload(void);

	void									bindEvents(void);
	void									unbindEvents(void);
	void									bindAllEvents(void);
	void									unbindAllEvents(void);
	
	void									unserialize(void);
	void									serialize(void);

	CEventBoundFunction*					bindEvent(uint32 uiEventId, void(*pFunction)(void*), void *pTriggerArgument = nullptr, int32 iZOrder = 0);
	CEventBoundFunction*					bindEvent(uint32 uiEventId, void(*pFunction)(void*, void*), void *pTriggerArgument = nullptr, int32 iZOrder = 0);
	CEventBoundFunction*					bindEvent(uint32 uiEventId, CInputEventCallbacks *pObject, void *pTriggerArgument = nullptr, int32 iZOrder = 0);
	bool									triggerEvent(uint32 uiEventId, void *pTriggerArgument = nullptr);

	void									onMouseDown(CPoint2D& vecCursorPosition);
	void									onMouseUp(CPoint2D& vecCursorPosition);
	void									onMouseMove(CPoint2D& vecCursorPosition);
	void									onDoubleLeftClick(CPoint2D& vecCursorPosition);

	virtual void							render(void);
	void									checkToRender(void);
	void									onRenderFromWMPaint(void);

	CGUILayer*								addLayer(bool bEnabled = true);
	CGUILayer*								addLayer(CWindow *pWindow, bool bEnabled = true);

	bool									doesActiveItemExist(void) { return m_pActiveItem != nullptr; }
	void									setActiveItem(CGUIItem *pItem);
	void									clearActiveItem(void);

	void									unmarkRadios(CRadioControl *pRadio);

	void									setOpenLastFilename(std::string strFileName);
	void									clearOpenLastFilename(void);

	void									setWindowHandle(HWND hwndWindow) { m_hwndWindow = hwndWindow; }
	HWND									getWindowHandle(void) { return m_hwndWindow; }

	void									setMarkedToRedraw(bool bMarkedToRedraw) { m_bMarkedToRedraw = bMarkedToRedraw; }
	bool									isMarkedToRedraw(void) { return m_bMarkedToRedraw; }
	
	void									setFocusedControl(CGUIControl *pWindowControl) { m_pFocusedControl = pWindowControl; }
	CGUIControl*							getFocusedControl(void) { return m_pFocusedControl; }

	void									setPosition(CPoint2D& vecPosition);
	CPoint2D&								getPosition(void) { return m_vecPosition; }

	void									setSize(CSize2D& vecSize);
	CSize2D&								getSize(void) { return m_vecSize; }

	void									setMovingWindow(bool bMovingMainWindow) { m_bMovingWindow = bMovingMainWindow; }
	bool									isMovingWindow(void) { return m_bMovingWindow; }

	void									setResizingWindow(bool bResizingWindow) { m_bResizingWindow = bResizingWindow; }
	bool									isResizingWindow(void) { return m_bResizingWindow; }

	void									setWindowResizeEdges(uint32 uiMainWindowResizeEdges) { m_uiWindowResizeEdges = uiMainWindowResizeEdges; }
	uint32									getWindowResizeEdges(void) { return m_uiWindowResizeEdges; }

	void									setParentWindow(CWindow *pParentWindow) { m_pParentWindow = pParentWindow; }
	CWindow*								getParentWindow(void) { return m_pParentWindow; }

	void									setTitleBarHeight(uint32 uiTitleBarHeight) { m_uiTitleBarHeight = uiTitleBarHeight; }
	uint32									getTitleBarHeight(void) { return m_uiTitleBarHeight; }

	void									setMaximized(bool bMaximized);
	bool									isMaximized(void) { return m_bMaximized; }

	void									setPreviousPosition(CPoint2D& vecPreviousPosition) { m_vecPreviousPosition = vecPreviousPosition; }
	CPoint2D&								getPreviousPosition(void) { return m_vecPreviousPosition; }

	void									setPreviousSize(CSize2D& vecPreviousSize) { m_vecPreviousSize = vecPreviousSize; }
	CSize2D&								getPreviousSize(void) { return m_vecPreviousSize; }

	void									setEventTriggerEventTypeId(eEventType eEventTriggerEventTypeId) { m_eEventTriggerEventTypeId = eEventTriggerEventTypeId; }
	eEventType								getEventTriggerEventTypeId(void) { return m_eEventTriggerEventTypeId; }

private:
	HWND									m_hwndWindow;
	CWindow*								m_pParentWindow;
	CGUIControl*							m_pFocusedControl;
	CPoint2D								m_vecPosition;
	CSize2D									m_vecSize;
	uint32									m_uiWindowResizeEdges;
	CDropTarget*							m_pDropTarget;
	uint32									m_uiTitleBarHeight;
	uint8									m_bMovingWindow					: 1;
	uint8									m_bResizingWindow				: 1;
	uint8									m_bMarkedToRedraw				: 1;
	uint8									m_bMaximized					: 1;
	CPoint2D								m_vecPreviousPosition;
	CSize2D									m_vecPreviousSize;
	CGUIItem*								m_pActiveItem;
	eEventType								m_eEventTriggerEventTypeId;
	// todo CRectangleItemPlacement<CWindow>			m_placeableWindow;	// gui windows
	CRectangleItemPlacement<CGUIItem>			m_placeableItem;	// gui items - e.g. shapes and controls

	/*
	todo
	HMENU						m_hMenu_File;
	HMENU						m_hSubMenu_File_OpenRecent;
	HMENU						m_hMenu_Entry_Sort;
	HMENU						m_hSubMenu_File_Sessions;

	std::unordered_map<uint32, CRWVersion*>			m_umapMenuItemMapping_SelectRWVersion; // todo - move this shit to like CMenuManager
	std::unordered_map<uint32, CRWVersion*>			m_umapMenuItemMapping_ConvertDFFtoRWVersion;
	std::unordered_map<uint32, CRWVersion*>			m_umapMenuItemMapping_FilterRWVersion;
	std::unordered_map<uint32, eCOLVersion>			m_umapMenuItemMapping_FilterCOLVersion;
	std::unordered_map<uint32, CRWVersion*>			m_umapMenuItemMapping_ConvertTXDtoRWVersion;
	std::unordered_map<uint32, CRasterDataFormat*>	m_umapMenuItemMapping_ConvertTXDtoTextureFormat;
	std::unordered_map<uint32, CCOLVersion*>		m_umapMenuItemMapping_ConvertCOLtoCOLVersion;
	std::unordered_map<uint32, CRWVersion*>			m_umapMenuItemMapping_ConvertDFFtoRWVersion_DragDrop;
	std::unordered_map<uint32, CRWVersion*>			m_umapMenuItemMapping_ConvertTXDtoRWVersion_DragDrop;
	std::unordered_map<uint32, CRasterDataFormat*>	m_umapMenuItemMapping_ConvertTXDtoTextureFormat_DragDrop;
	std::unordered_map<uint32, CCOLVersion*>		m_umapMenuItemMapping_ConvertCOLtoCOLVersion_DragDrop;

	std::unordered_map<uint32, eCOLVersion>		m_umapFilterMapping_COLVersion;
	std::unordered_map<uint32, eRWVersion>		m_umapFilterMapping_RWVersion;
	int											m_iFilterMapping_UnknownVersion;
	*/
};

#endif