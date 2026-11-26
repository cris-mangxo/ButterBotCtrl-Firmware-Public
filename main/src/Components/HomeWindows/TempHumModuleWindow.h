#ifndef BUTTERBOTCTRL_FIRMWARE_TEMPHUMMODULEWINDOW_H
#define BUTTERBOTCTRL_FIRMWARE_TEMPHUMMODULEWINDOW_H

#include "Components/HomeWindow.h"

class TempHumModuleWindow : public HomeWindow {
public:
	/**
	 * Window that shows BB TempHumModule action
	 * @param parent parent LVGL object
	 * @param params data for TempHumModule action
	 */
	TempHumModuleWindow(lv_obj_t* parent, const TempHumModuleData* params);

private:
	static constexpr const char* TITLE = "Módulo de clima";
	static constexpr const char* Sentence = "Reporte del ambiente";
	static constexpr const char* MissingModuleSentence = "¡Falta módulo de clima!";

	void buildUI(TempHumModuleData data);
};


#endif //BUTTERBOTCTRL_FIRMWARE_TEMPHUMMODULEWINDOW_H
