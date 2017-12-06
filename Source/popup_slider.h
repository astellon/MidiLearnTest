#pragma once

#include <string>
#include <vector>

#include "../JuceLibraryCode/JuceHeader.h"

namespace SynthComponent {
/*==============================================================================
PopupSlider class
- this class is extended slider with popup menu.
==============================================================================*/
class PopupSlider : public juce::Slider {

 public:
  class Listener : public juce::Slider::Listener {
   public:
    virtual ~Listener(){};
    virtual void requestMidiLearn(PopupSlider* slider) = 0;
    virtual void requestClearLearn(PopupSlider* slider) = 0;
  };

  enum MenuIds {
    CANCEL,
    MIDI_LEARN,
    CLEAR_MIDI_LEARN,
  };

  PopupSlider();
  ~PopupSlider();

  void addListener(PopupSlider::Listener* lister);

  void mouseDown(const MouseEvent& e) override;

  void handlePopupResult(int result);

 private:
  std::vector<PopupSlider::Listener*> listeners_;
  juce::PopupMenu* menu_;
};
}