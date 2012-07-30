
#include <iostream>
#include <cstdlib>
#include <fstream>
#include "delimitedfile.h"
#include "general.h"

DelimitedFile::DelimitedFile(const std::string& f) : filename(f)
{
}
void DelimitedFile::setDelimiters(std::set<char> delim)
{
    delimiters = delim;
}
void DelimitedFile::setCommentChars(std::set<char> c)
{
    commentChars = c;
}
void DelimitedFile::read()
{
    std::ifstream in(filename.c_str());

    // Could not open file
    if (!in) throw General::BadFile(filename);

    // Read file
    std::string line;
    while( getline(in, line) ) {
        line = General::trim_string(line);
        if (line.empty()) continue;
        if (commentChars.find(line[0]) != commentChars.end()) continue;
        tokenize(line);
        lines.push_back(fields);
        //process_field(fields);
        
    }
}
void DelimitedFile::tokenize(const std::string& line)
{
    fields.clear();

    std::string::const_iterator it;
    bool in_token = false;
    std::string field;
    for (it = line.begin(); it != line.end(); it++) {
        char c = (*it);
        if (delimiters.find(c) != delimiters.end()) {
        // If char is a delimiter
            if (in_token) {
                // Add the field to the list, clear the field variable
                fields.push_back(field);
                field = "";
                in_token = false;
            }
        } else {
        // If char is not a delimiter
            field += c;
            in_token = true;
        }
    }
    if (!field.empty()) fields.push_back(field);
}
std::string DelimitedFile::operator[](int i)
{
    return fields[i];
}
int DelimitedFile::asInt(int index)
{
    return atoi(fields[index].c_str());
}
int DelimitedFile::asDouble(int index)
{
    return atof(fields[index].c_str());
}
bool DelimitedFile::asBool(int index)
{
    return (bool)atoi(fields[index].c_str());
}
void DelimitedFile::first()
{
    if (lines.size() <= 0)
        throw General::IndexOutOfRange("The file contains no lines");
    index = 0;
    fields = lines[index];
}
bool DelimitedFile::next()
{
    index++;
    if (index >= (int)lines.size()) {
        fields.clear();
        return false;
    }
    fields = lines[index];
    return true;
}
bool DelimitedFile::previous()
{
    index--;
    if (index < 0) {
        fields.clear();
        return false;
    }
    fields = lines[index];
    return true;
}
int DelimitedFile::count() const
{
    return lines.size();
}
void DelimitedFile::showCommentChars()
{
    showSet(commentChars);
}
void DelimitedFile::showDelimiters()
{
    showSet(delimiters);
}
void DelimitedFile::showSet(std::set<char> s)
{
    std::set<char>::iterator it;
    std::cout << "Set Values: ";
    for (it=s.begin(); it!=s.end(); it++)
        std::cout << " " << *it;
    std::cout << std::endl;
}
