#include "ShakeWindow.h"

static constexpr const char* TAG = "ShakeWindow";

ShakeWindow::ShakeWindow(lv_obj_t* parent, const ShakeData* params) : HomeWindow(parent, TITLE){
	buildUI(*params);
}

void ShakeWindow::buildUI(const ShakeData data){
	// GIF control
	auto gifParent=innerContent;
    if(theme->getTheme()==Theme::Red){
        gifParent=lv_obj_create(innerContent);
        lv_obj_set_size(gifParent,78,62);
        lv_obj_set_style_pad_all(gifParent,0,0);
        lv_obj_set_style_border_width(gifParent,0,0);
        lv_obj_set_style_bg_opa(gifParent,LV_OPA_TRANSP,0);
        lv_obj_remove_flag(gifParent,LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_remove_flag(gifParent,LV_OBJ_FLAG_OVERFLOW_VISIBLE);
    }
    gif = new LVGIF(gifParent, theme->getAsset(Asset::Shake));
    if(theme->getTheme()==Theme::Red)lv_obj_set_pos(*gif,-26,-21);
	gif->setLooping(LVGIF::LoopType::On);
	gif->reset();

	// Sentence label
	sentenceLabel = lv_label_create(innerContent);
	lv_label_set_text(sentenceLabel, Sentence);
	lv_obj_add_style(sentenceLabel, labelDefaultStyle, 0);
	lv_obj_set_size(sentenceLabel, 76, LV_SIZE_CONTENT);

	updateLayout();
}

void ShakeWindow::onDismiss(){
	ESP_LOGI(TAG, "onDismiss");
	if(gif){
		gif->stop();
	}
}
