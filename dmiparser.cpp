
#include "dmiparser.h"
#include "util.h"
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
    // Run dmidecode and get output
    std::string s = Util::exec( str( boost::format("sudo dmidecode/dmidecode --type %s") % mType ) );
    // Split output in vector of lines
    std::vector<std::string> lines;
    boost::split(lines, s, boost::is_any_of("\n\r"), boost::token_compress_on);
    // Process the lines one by one
    for (unsigned int i = 0; i < lines.size() ; ++i) {
        boost::trim(lines[i]);
        // Skip empty lines
        if (lines[i].empty())
            continue;
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
        // Lines consist of name: value pairs. Split on ':' to seperate them.
        std::vector<std::string> fields;
        boost::split(fields, lines[i], boost::is_any_of(":"));
        if (fields.size() == 2) {
            // Simple field
            readFeatureList = false;
            boost::trim(fields[0]);
            boost::trim(fields[1]);
            mFrames[currentIndex].Data[fields[0]] = fields[1];
        } else {
            // Possible Feature list type field
            boost::trim(fields[0]);
            currentFeature = fields[0];
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
