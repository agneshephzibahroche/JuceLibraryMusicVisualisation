/*
  ==============================================================================

	WaveformDisplay.cpp

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(AudioFormatManager& formatManagerToUse,
	AudioThumbnailCache& cacheToUse) : audioThumb(1000, formatManagerToUse, cacheToUse),
	fileLoaded(false),
	position(0)

{
	// In your constructor, you should add any child components, and
	// initialise any special settings that your component needs.

	audioThumb.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint(Graphics& g)
{
	/* This demo code just fills the component's background and
	   draws some placeholder text to get you started.

	   You should replace everything in this method with your own
	   drawing code..
	*/

	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId)); // clear the background
	g.fillAll(Colour(35, 17, 35));
	g.setColour(Colours::grey);
	g.drawRect(getLocalBounds(), 1); // draw an outline around the component

	if (fileLoaded)
	{
		g.setColour(juce::Colour(167, 199, 231));
		audioThumb.drawChannel(g,
			getLocalBounds(),
			0,
			audioThumb.getTotalLength(),
			0,
			1.0f);

		g.setColour(Colours::floralwhite);
		g.fillRect(position * getWidth(), 0, 2, getHeight());

		g.setColour(juce::Colours::black);
		g.setFont(16.0f);
		g.drawText(nowPlaying, getLocalBounds(),
			juce::Justification::centred, true);
	}
	else
	{
		g.setColour(juce::Colour(189, 198, 103));
		g.setFont(20.0f);
		g.drawText("Load File to Channel to Begin...", getLocalBounds(),
			juce::Justification::centred, true);
	}
}

void WaveformDisplay::resized()
{
	// This method is where you should set the bounds of any child
	// components that your component contains..
}

void WaveformDisplay::loadURL(URL audioURL)
{
	audioThumb.clear();
	fileLoaded = audioThumb.setSource(new URLInputSource(audioURL));
	if (fileLoaded)
	{
		std::cout << "wfd: loaded! " << std::endl;
		std::string justFile = audioURL.toString(false).toStdString();
		std::size_t startFilePos = justFile.find_last_of("/");
		std::size_t startExtPos = justFile.find_last_of(".");
		std::string extn = justFile.substr(startExtPos + 1, justFile.length() - startExtPos);
		std::string file = justFile.substr(startFilePos + 1, justFile.length() - startFilePos - extn.size() - 2);

		nowPlaying = file;
		repaint();
	}
	else
	{
		std::cout << "wfd: not loaded! " << std::endl;
	}
}

void WaveformDisplay::changeListenerCallback(ChangeBroadcaster* source)
{
	std::cout << "wfd: change received! " << std::endl;

	repaint();
}

void WaveformDisplay::setPositionRelative(double pos)
{
	if (pos != position)
	{
		position = pos;
		repaint();
	}
}
