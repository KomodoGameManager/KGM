#ifndef CWindowManager_H
#define CWindowManager_H

#include "CManager.h"

class CWindow;

class CWindowManager : public CManager
{
public:
	void					init(void);
	void					uninit(void);

	CWindow*				openWindow(void);

	void					processWindows(void);
};

#endif