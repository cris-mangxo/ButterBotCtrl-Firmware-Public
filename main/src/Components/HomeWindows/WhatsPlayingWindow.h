#ifndef BUTTERBOTCTRL_FIRMWARE_WHATSPLAYINGWINDOW_H
#define BUTTERBOTCTRL_FIRMWARE_WHATSPLAYINGWINDOW_H

#include "Components/HomeWindow.h"
#include "Themes.hpp"

class WhatsPlayingWindow : public HomeWindow {
public:
	/**
	 * Window showing the phone's currently playing track (title/artist/album),
	 * or a "nothing playing" state when no track is reported.
	 * @param parent parent LVGL object
	 * @param params currently playing track data
	 */
	WhatsPlayingWindow(lv_obj_t* parent, const WhatsPlayingData* params);

	void onData(const BBData* data) override;

private:
	static constexpr const char* TITLE = "Suena ahora";
	static constexpr const char* NothingSentence = "Solo suena el vacío";
	static constexpr const char* PlayingSentence = "Rola pegajosa detectada";

	void buildUI(const WhatsPlayingData& data);

	/* Adds an icon + value row (marquee-scrolling value for long fields) to the inner content */
	void addField(Asset icon, const std::string& value);
};

#endif //BUTTERBOTCTRL_FIRMWARE_WHATSPLAYINGWINDOW_H
