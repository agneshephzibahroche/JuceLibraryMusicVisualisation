/*
  ==============================================================================

	This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "PlaylistComponent.h"

//==============================================================================
/*
	This component lives inside our window, and this is where you should put all
	your controls and content.
*/
class MainComponent : public AudioAppComponent
{
public:
	//==============================================================================
	MainComponent();
	~MainComponent();

	//==============================================================================
	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
	void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
	void releaseResources() override;

	//==============================================================================
	void paint(Graphics& g) override;
	void resized() override;

private:
	//==============================================================================
	// Your private member variables go here...

	AudioFormatManager formatManager;
	AudioThumbnailCache thumbCache{ 10 }; // cache up to 100 files

	int channelL = 0;
	int channelR = 1;

	PlaylistComponent playlistComponent{ formatManager };
	DJAudioPlayer playerLeft{ formatManager };
	DeckGUI deckGUILeft{ &playerLeft, &playlistComponent, formatManager, thumbCache, channelL };

	DJAudioPlayer playerRight{ formatManager };
	DeckGUI deckGUIRight{ &playerRight, &playlistComponent, formatManager, thumbCache, channelR };

	//==============================================================================
	Label waveformLabel;
	Label posLabel;
	Label widgetLabel;
	Label playlistLabel;

	//==============================================================================
	MixerAudioSource mixerSource;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
