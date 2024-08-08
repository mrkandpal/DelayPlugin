/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class DelayAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    DelayAudioProcessor();
    ~DelayAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    //The following two functions will be used by the DAW to save and restore the plugin parameter values
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayAudioProcessor)
    
    //Audio Processor Value Tree State Declarations
    
    //APVTS object, named apvts. This is initiliased using a constructor
    juce::AudioProcessorValueTreeState apvts{
        *this, nullptr, "Parameters", createParameterLayout()
    /* Arguments Description
     1. *this                   - pointer for self referencing
     2. nullptr                 - no undo manager provided
     3. "Parameters"            - name of the APVTS
     4. createParameterLayout() - list of parameters of the plugin (generated using a helper function)
     
     Refer to the following section in JUCE documentation for a comprehensive insight into the apvts
     constructor and ParameterLayout
     https://docs.juce.com/master/classAudioProcessorValueTreeState.html#acca3c6aca19e89d2781f0d1314d639e8
     */
    };
    
    //Helper function to create plugin parameter objects, which will be added to the APVTS
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
};
