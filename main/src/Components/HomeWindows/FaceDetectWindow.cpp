#include "FaceDetectWindow.h"

static constexpr const char* TAG = "FaceDetectWindow";

static const std::map<FaceDetectData::State, Asset> FaceDetectAssetImgMap = {
	{ FaceDetectData::State::AlreadySaved, Asset::FaceNesprema },
	{ FaceDetectData::State::NoFaceFound, Asset::FaceNevidi },
	{ FaceDetectData::State::NotRecognized, Asset::FaceNeprepoznavanje },
	{ FaceDetectData::State::Recognized, Asset::FacePrepoznavanje },
};

static const std::map<FaceDetectData::State, const char*> FaceDetectSentences = {
	{ FaceDetectData::State::AlreadySaved, "Error: conflicto emocional" },
	{ FaceDetectData::State::NewOwner, "Cariño en proceso" },
	{ FaceDetectData::State::NoFaceFound, "Puro vacío" },
	{ FaceDetectData::State::NotRecognized, "Tú no eres mi papá" },
	{ FaceDetectData::State::Recognized, "¡Eres tú, amo de la mantequilla!" },
	{ FaceDetectData::State::Scanning, "Analizando tu cara" },
};

FaceDetectWindow::FaceDetectWindow(lv_obj_t* parent, const FaceDetectData* params) : HomeWindow(parent, TITLE){
	buildUI(*params);
}

void FaceDetectWindow::onData(const BBData* data){
	const auto newData = *(const FaceDetectData*)data;

	// Clear and rebuild UI
	lv_obj_clean(innerContent);
	buildUI(newData);
}

void FaceDetectWindow::buildUI(const FaceDetectData data){
    const bool scanning=data.state==FaceDetectData::State::Scanning;
    lv_obj_set_style_pad_hor(innerContent,scanning?0:1,0);
    lv_obj_set_style_border_side(innerContent,static_cast<lv_border_side_t>(scanning?(LV_BORDER_SIDE_TOP|LV_BORDER_SIDE_LEFT|LV_BORDER_SIDE_BOTTOM):LV_BORDER_SIDE_FULL),0);
	// Sentence label
	lv_obj_t* sentenceLabel = lv_label_create(innerContent);
	lv_label_set_text(sentenceLabel, FaceDetectSentences.at(data.state));
	lv_label_set_long_mode(sentenceLabel, LV_LABEL_LONG_WRAP);
	lv_obj_add_style(sentenceLabel, labelDefaultStyle, 0);
	lv_obj_set_size(sentenceLabel, 116, LV_SIZE_CONTENT);

	switch(data.state){
		case FaceDetectData::State::Recognized:
		case FaceDetectData::State::NotRecognized:
		case FaceDetectData::State::NoFaceFound:
		case FaceDetectData::State::AlreadySaved: {
			lv_obj_t* img = lv_image_create(innerContent);
			lv_image_set_src(img, theme->getAsset(FaceDetectAssetImgMap.at(data.state)));
			lv_obj_set_style_pad_bottom(img, 20, 0);
			break;
		}
		case FaceDetectData::State::Scanning: {
			// GIF
			gif = new LVGIF(innerContent, theme->getAsset(Asset::FaceScan));
			gif->setLooping(LVGIF::LoopType::On);
			gif->reset();
			lv_obj_set_style_bg_opa(innerContent, LV_OPA_COVER, 0);
			lv_obj_set_style_bg_color(innerContent, theme->getTertiaryColor(), 0);

			// Distance hint label
			lv_obj_t* hintLabel = lv_label_create(innerContent);
			lv_label_set_text(hintLabel, "Pon tu cara a 0.5M de la cámara");
			lv_label_set_long_mode(hintLabel, LV_LABEL_LONG_WRAP);
			lv_obj_add_style(hintLabel, labelDefaultStyle, 0);
			lv_obj_set_size(hintLabel, 116, LV_SIZE_CONTENT);
			break;
		}
		case FaceDetectData::State::NewOwner: {
			// GIF
			gif = new LVGIF(innerContent, theme->getAsset(Asset::FaceNovivlasnik));
			gif->setLooping(LVGIF::LoopType::On);
			gif->reset();
			break;
		}
		default:
			ESP_LOGE(TAG, "Face detection state not recognised");
			break;
	}

	updateLayout();
}

void FaceDetectWindow::onDismiss(){
	ESP_LOGI(TAG, "onDismiss");
	if(gif){
		gif->stop();
	}
}
