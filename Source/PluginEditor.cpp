/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
MidiLearnTestAudioProcessorEditor::MidiLearnTestAudioProcessorEditor (MidiLearnTestAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

    slider_.setName("slider1");
    slider_.addListener(&processor);
    slider_.setRange(0.0, 1.0);
    //slider_.setValue(p.getParameter("slider1"));
    addAndMakeVisible(&slider_);
    // slider_.addControlListener(engine_);
    
    setSize (400, 300);

    startTimer(30);
}

MidiLearnTestAudioProcessorEditor::~MidiLearnTestAudioProcessorEditor()
{
}

//==============================================================================
void MidiLearnTestAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    // g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void MidiLearnTestAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    slider_.setBounds(100, 125, 200, 50);
}

void MidiLearnTestAudioProcessorEditor::timerCallback() {
  slider_.setValue(processor.getParameter(slider_.getName())->get());
}
