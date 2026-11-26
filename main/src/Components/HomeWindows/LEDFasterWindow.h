#ifndef BUTTERBOTCTRL_FIRMWARE_LEDFASTERWINDOW_H
#define BUTTERBOTCTRL_FIRMWARE_LEDFASTERWINDOW_H

#include <LV_Interface/LVGIF.h>
#include "Components/HomeWindow.h"

class LEDFasterWindow : public HomeWindow {
public:
	/**
	 * Window that shows BB LEDFaster action
	 * @param parent parent LVGL object
	 * @param params data for LEDFaster action
	 */
	LEDFasterWindow(lv_obj_t* parent, const LEDFasterData* params);

	void onDismiss() override;

private:
	static constexpr const char* TITLE = "LED más rápido";
	static constexpr const char* Sentence = "Rápido y luminoso";

	LVGIF* gif = nullptr;

	void buildUI(LEDFasterData data);
};


#endif //BUTTERBOTCTRL_FIRMWARE_LEDFASTERWINDOW_H
