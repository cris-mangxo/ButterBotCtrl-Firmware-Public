#ifndef BUTTERBOTCTRL_FIRMWARE_MEDIACONTROLWINDOW_H
#define BUTTERBOTCTRL_FIRMWARE_MEDIACONTROLWINDOW_H

#include "Components/HomeWindow.h"
#include "Themes.hpp"

/**
 * Shared base for the phone media-control windows (previous/next track, play/stop).
 * They only differ by title, icon and caption text.
 */
class MediaControlWindow : public HomeWindow {
protected:
	MediaControlWindow(lv_obj_t* parent, const char* title, Asset icon, const char* sentence);

private:
	void buildUI(Asset icon, const char* sentence);
};

class PrevSongWindow : public MediaControlWindow {
public:
	PrevSongWindow(lv_obj_t* parent, const MediaControlData* params)
		: MediaControlWindow(parent, "Música", Asset::MusicBack, "Esto me suena"){}
};

class NextSongWindow : public MediaControlWindow {
public:
	NextSongWindow(lv_obj_t* parent, const MediaControlData* params)
		: MediaControlWindow(parent, "Música", Asset::MusicForward, "Otra canción, misma tristeza"){}
};

class PlayMusicWindow : public MediaControlWindow {
public:
	PlayMusicWindow(lv_obj_t* parent, const MediaControlData* params)
		: MediaControlWindow(parent, "Música", Asset::MusicPlay, "Sigue el ruido"){}
};

class StopMusicWindow : public MediaControlWindow {
public:
	StopMusicWindow(lv_obj_t* parent, const MediaControlData* params)
		: MediaControlWindow(parent, "Música", Asset::MusicPause, "Silencio, por fin"){}
};

#endif //BUTTERBOTCTRL_FIRMWARE_MEDIACONTROLWINDOW_H
