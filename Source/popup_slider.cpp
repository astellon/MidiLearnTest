#include "Popup_slider.h"

namespace SynthComponent {

static void sliderPopupCallback(int result, PopupSlider* slider) {
  if (slider != nullptr && result != PopupSlider::CANCEL)
    slider->handlePopupResult(result);
}

PopupSlider::PopupSlider() {
  menu_ = new juce::PopupMenu ();
  menu_ ->clear();
  menu_ ->addItem(MIDI_LEARN, "Learn MIDI CC");
  menu_ ->addItem(CLEAR_MIDI_LEARN, "Clear MIDI CC Learn");
}

PopupSlider::~PopupSlider() {
  delete menu_;
  menu_ = nullptr; 
}

void PopupSlider::addListener(PopupSlider::Listener* listener) {
  listeners_.push_back(listener);
  juce::Slider::addListener(listener);
}

void PopupSlider::mouseDown(const MouseEvent& e) {
  if (e.mods.isPopupMenu()) {
    menu_->showMenuAsync(PopupMenu::Options(),
                       ModalCallbackFunction::forComponent(sliderPopupCallback, this));
  } else {
    Slider::mouseDown(e);
  }
}

void PopupSlider::handlePopupResult(int result) {
  switch (result) {
    case MIDI_LEARN:
      for (auto listener : listeners_) {
        listener->requestMidiLearn(this);
      }
      break;
    case CLEAR_MIDI_LEARN:
      for (auto listener : listeners_) {
        listener->requestClearLearn(this);
      }
      break;
  }
}
}  // namespace SynthComponent