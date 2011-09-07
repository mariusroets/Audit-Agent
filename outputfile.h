/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __OUTPUTFILE_H__
#define __OUTPUTFILE_H__

#include <string>

class OutputFile
{
    public:
        OutputFile(std::string filename);
        void write();

    private:
        std::string mFilename;
};

#endif	// __OUTPUTFILE_H__

