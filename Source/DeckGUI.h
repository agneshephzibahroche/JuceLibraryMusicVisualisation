/*
  ==============================================================================

	DeckGUI.h
	Author: Agnes

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include "PlaylistComponent.h"

//==============================================================================
/*
 */

class DeckGUI : public Component,
	public Button::Listener,
	public Slider::Listener,
	public TableListBoxModel,
	public Timer
{
public:
	DeckGUI(DJAudioPlayer* player,
		PlaylistComponent* playlistComponent,
		AudioFormatManager& formatManagerToUse,
		AudioThumbnailCache& cacheToUse,
		int channelToUse);
	~DeckGUI();

	void paint(Graphics&) override;
	void resized() override;
	/** implement Button::Listener */
	void buttonClicked(Button*) override;

	/** implement Slider::Listener */
	void sliderValueChanged(Slider* slider) override;

	/*bool isInterestedInFileDrag (const StringArray &files) override;
	void filesDropped (const StringArray &files, int x, int y) override;*/
	int getNumRows() override;

	void paintRowBackground(Graphics&,
		int rowNumber,
		int width,
		int height,
		bool rowIsSelected) override;

	void paintCell(Graphics&,
		int rowNumber,
		int columnId,
		int width,
		int height,
		bool rowIsSelected) override;

	void timerCallback() override;

private:
	TextButton playButton{ "PLAY" };
	TextButton stopButton{ "STOP" };
	TextButton loadButton{ "LOAD" };

	Slider volSlider;
	Slider speedSlider;
	Slider posSlider;

	Label volLabel;
	Label speedLabel;

	LookAndFeel_V4 lookandfeel;

	DJAudioPlayer* player;

	PlaylistComponent* playlistComponent;

	WaveformDisplay waveformDisplay;

	TableListBox upNext;

	int channel;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
};
