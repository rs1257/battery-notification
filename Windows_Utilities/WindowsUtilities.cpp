#include "Windows.h"
#include <Iostream>
#include "wintoastlib.h"
#include "Handler.h"

using namespace WinToastLib;

std::wstring FOLDER_PATH = L"C:/Users/Ryan/Documents/GitHub/Cplusplus/Windows_Utilities/Windows_Utilities/";
bool set = false;
void sendToast(const std::wstring AppName, const std::wstring Icon, const std::wstring Message);

int main()
{
	FreeConsole();
	SYSTEM_POWER_STATUS lpSystemPowerStatus = SYSTEM_POWER_STATUS();
	std::wstring AppName = L"Battery Moniter";
	while (1) {
		int result = GetSystemPowerStatus(&lpSystemPowerStatus);
		set = false;
		if (result != 0) {
			int onPower = lpSystemPowerStatus.ACLineStatus;
			int percentage = lpSystemPowerStatus.BatteryLifePercent;
			if (onPower == 1 && percentage == 100) {
				sendToast(AppName, L"battery_status5.png", L"Battery Full");
			}
			else if (onPower == 0 && percentage == 80) {
				sendToast(AppName, L"battery_status4.png", L"80% Battery Left");
			}
			else if (onPower == 0 && percentage == 60) {
				sendToast(AppName, L"battery_status3.png", L"60% Battery Left");
			}
			else if (onPower == 0 && percentage == 40) {
				sendToast(AppName, L"battery_status2.png", L"40% Battery Left");
			}
			else if (onPower == 0 && percentage == 20) {
				sendToast(AppName, L"battery_status1.png", L"20% Battery Left");
			}
			else if (onPower == 0 && percentage == 10) {
				sendToast(AppName, L"battery_status0.png", L"Battery Low");
			}
		}
		if (set) {
			Sleep(300000);
		}
		else {
			Sleep(60000);
		}
	}
    return 0;
}

void sendToast(std::wstring AppName, std::wstring Icon, std::wstring Message) {
	if (!WinToast::isCompatible()) {
		std::wcout << L"Error, your system in not supported!" << std::endl;
	}
	else {
		WinToast::instance()->setAppName(AppName);
		WinToast::instance()->setAppUserModelId(
		WinToast::configureAUMI(L"", L"", AppName, L""));

		if (!WinToast::instance()->initialize()) {
			std::wcout << L"Error, could not initialize the lib!" << std::endl;
		}

		WinToastHandlerExample* handler = new WinToastHandlerExample;
		WinToastTemplate toast = WinToastTemplate(WinToastTemplate::ImageAndText03);
		toast.setImagePath(FOLDER_PATH + Icon);
		toast.setTextField(Message, WinToastTemplate::FirstLine);

		if (!WinToast::instance()->showToast(toast, handler)) {
			std::wcout << L"Error: Could not launch your toast notification!" << std::endl;
		}

		set = true;
	}

}

