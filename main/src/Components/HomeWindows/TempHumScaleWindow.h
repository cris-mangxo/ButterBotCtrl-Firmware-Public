#ifndef BUTTERBOTCTRL_FIRMWARE_TEMPHUMSCALEWINDOW_H
#define BUTTERBOTCTRL_FIRMWARE_TEMPHUMSCALEWINDOW_H

#include "Components/HomeWindow.h"

class TempHumScaleWindow : public HomeWindow {
public:
	/**
	 * Window that shows BB TempHumScaleWindow action
	 * @param parent parent LVGL object
	 * @param params data for TempHumScaleWindow action
	 */
	TempHumScaleWindow(lv_obj_t* parent, const TempHumScaleData* params);

private:
	static constexpr const char* TITLE = "Escala de clima";
	static constexpr const char* Sentence = "¡Elige tu escala!";

	void buildUI(TempHumScaleData data);
};


#endif //BUTTERBOTCTRL_FIRMWARE_TEMPHUMSCALEWINDOW_H