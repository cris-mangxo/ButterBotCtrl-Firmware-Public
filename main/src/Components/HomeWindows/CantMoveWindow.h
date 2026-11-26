#ifndef BUTTERBOTCTRL_FIRMWARE_CANTMOVEWINDOW_H
#define BUTTERBOTCTRL_FIRMWARE_CANTMOVEWINDOW_H

#include "Components/HomeWindow.h"

class CantMoveWindow : public HomeWindow {
public:
	CantMoveWindow(lv_obj_t* parent, const CantMoveData* params);

private:
	static constexpr const char* TITLE = "No puedo moverme";
	static constexpr const char* SentenceCharging = "No me muevo: cargando";
	static constexpr const char* SentenceUnstable = "No me muevo: inestable";

	void buildUI(CantMoveData data);
};

#endif //BUTTERBOTCTRL_FIRMWARE_CANTMOVEWINDOW_H
