/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <map>
#include <list>

#include "../JuceLibraryCode/JuceHeader.h"

#include "popup_slider.h"


//==============================================================================
/**
*/
class MidiLearnTestAudioProcessor  : public AudioProcessor, public SynthComponent::PopupSlider::Listener
{
public:
    //==============================================================================
    MidiLearnTestAudioProcessor();
    ~MidiLearnTestAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect () const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    AudioParameterFloat* getParameter(juce::String name);

    void sliderValueChanged(Slider* slider) override;
    void requestMidiLearn(SynthComponent::PopupSlider* slider) override;
    void requestClearLearn(SynthComponent::PopupSlider* slider) override;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiLearnTestAudioProcessor)

    AudioParameterFloat* slider1_;

    std::map<juce::String, AudioParameterFloat*> params_map_;
    std::map<int, AudioParameterFloat*> control_map_;
    AudioParameterFloat* learn_request_;
};
