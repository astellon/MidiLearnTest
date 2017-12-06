/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
MidiLearnTestAudioProcessor::MidiLearnTestAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    slider1_ = new AudioParameterFloat("slider1", "slider1", 0.0f, 1.0f, 0.0f);
    addParameter(slider1_);
    params_map_.insert(std::make_pair(slider1_->name.toStdString(), slider1_));
}

MidiLearnTestAudioProcessor::~MidiLearnTestAudioProcessor()
{
}

//==============================================================================
const String MidiLearnTestAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MidiLearnTestAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MidiLearnTestAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MidiLearnTestAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MidiLearnTestAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MidiLearnTestAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MidiLearnTestAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MidiLearnTestAudioProcessor::setCurrentProgram (int index)
{
}

const String MidiLearnTestAudioProcessor::getProgramName (int index)
{
    return {};
}

void MidiLearnTestAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MidiLearnTestAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void MidiLearnTestAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MidiLearnTestAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MidiLearnTestAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    MidiMessage midi_message;
    int sample_ofset;
    for (MidiBuffer::Iterator i(midiMessages); i.getNextEvent(midi_message, sample_ofset);) {
      if (midi_message.isController()) {
        int cc_num = midi_message.getControllerNumber();
        if (control_map_.count(cc_num)) {
          int value = midi_message.getControllerValue();
          if (value < 128)
            *control_map_[cc_num] = value / 127.0f;
        } else if (learn_request_) {
          control_map_[cc_num] = learn_request_;
          learn_request_ = nullptr;
        }
      }
    }

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool MidiLearnTestAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MidiLearnTestAudioProcessor::createEditor()
{
    return new MidiLearnTestAudioProcessorEditor (*this);
}

//==============================================================================
void MidiLearnTestAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MidiLearnTestAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

AudioParameterFloat* MidiLearnTestAudioProcessor::getParameter(juce::String name) {
  return params_map_[name.toStdString()];
}

void MidiLearnTestAudioProcessor::sliderValueChanged(Slider* slider) {
    *slider1_ = slider->getValue();
}

void MidiLearnTestAudioProcessor::requestMidiLearn(SynthComponent::PopupSlider* slider) {
    learn_request_ = params_map_[slider->getName().toStdString()];
}

void MidiLearnTestAudioProcessor::requestClearLearn(SynthComponent::PopupSlider* slider) {
  auto itr = control_map_.begin();
  while (itr != control_map_.end()) {
    auto pair = *itr;
    if (pair.second->name == slider->getName()) {
      itr = control_map_.erase(itr);
    }
    else {
      itr++;
    }
  }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MidiLearnTestAudioProcessor();
}
