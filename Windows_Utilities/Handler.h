#pragma once
#include "Windows.h"
#include "wintoastlib.h"

using namespace WinToastLib;

class WinToastHandlerExample : public IWinToastHandler {
public:
	WinToastHandlerExample();
	// Public interfaces
	void toastActivated(int actionIndex) const override;
	void toastActivated() const override;
	void toastDismissed(WinToastDismissalReason state) const override;
	void toastFailed() const override;
};
