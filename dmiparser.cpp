
#include "dmiparser.h"
#include "util.h"
#include "commandparser.h"
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>

DMIParser::DMIParser(Types type)
{
    mType = type;
    mCurrentFrame = -1;
}
DMIParser::~DMIParser()
{
}

void DMIParser::exec()
{
    bool readDescription = false;
    bool readFeatureList = true;
    std::string currentFeature = "";
    int currentIndex = -1;
    CommandParser parser;
    std::vector<std::string> lines = parser.parse( str( boost::format("sudo dmidecode/dmidecode --type %s") % mType ) );
    std::vector<std::vector<std::string> > fields = parser.split(":");
    // Process the lines one by one
    for (unsigned int i = 0; i < lines.size() ; ++i) {
        if (readDescription) {
            mFrames[currentIndex].Description = lines[i];
            readDescription = false;
            continue;
        }
        if (lines[i].substr(0,6) == "Handle") {
            // Start new Frame
            Frame f;
            f.Handle = lines[i];
            mFrames.push_back(f);
            currentIndex++;
            readDescription = true;
            readFeatureList = false;
            continue;
        }
        if (currentIndex < 0)
            continue;
        if (lines[i].find(":") != std::string::npos) {
            readFeatureList = false;
        } else if (readFeatureList) {
            mFrames[currentIndex].FeatureData[currentFeature].push_back(lines[i]);
        }
        if (fields[i].size() == 2) {
            // Simple field
            readFeatureList = false;
            mFrames[currentIndex].Data[fields[i][0]] = fields[i][1];
        } else {
            // Possible Feature list type field
            boost::trim(fields[i][0]);
            currentFeature = fields[i][0];
            readFeatureList = true;
        }

    }
}
void DMIParser::setCurrentFrame(int frame)
{
    mCurrentFrame = frame;
}
int DMIParser::currentFrame()
{
    return mCurrentFrame;
}
std::string DMIParser::operator[](std::string index)
{
    if ((mCurrentFrame < 0) && (mCurrentFrame >= (int)mFrames.size()))
        return "";

    if (mFrames[mCurrentFrame].Data.find(index) != mFrames[mCurrentFrame].Data.end()) {
        return mFrames[mCurrentFrame].Data[index];
    }
    if (mFrames[mCurrentFrame].FeatureData.find(index) != mFrames[mCurrentFrame].FeatureData.end()) {
        std::string s;
        std::vector<std::string>::iterator i = mFrames[mCurrentFrame].FeatureData[index].begin();
        while (i != mFrames[mCurrentFrame].FeatureData[index].end()) {
            s = (*i) + "\n"; 
            ++i;
        }
        return s;
    }

    return "";

}
int DMIParser::frameCount()
{
    return mFrames.size();
}
