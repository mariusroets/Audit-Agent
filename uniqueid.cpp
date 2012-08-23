
#include <sstream>
#include <fstream>
#include <cstdlib>
#include "uniqueid.h"
#include "util.h"

#define FILENAME ".unique_id"

UniqueId::UniqueId()
{
    read();
}
UniqueId::~UniqueId()
{
}
std::string UniqueId::id()
{
    return unique;
}
void UniqueId::generate()
{
    std::string name = Util::getMachineName();

    std::stringstream o;
    int name_value = 0;
    for (int i = 0; i < (int)name.size(); ++i) {
        name_value += name[i];
    }
    o << name_value << (int)time(0) << rand() % 10000;
    unique = o.str();
}
void UniqueId::write()
{
    std::ofstream f;
    std::string filename = Util::SETTINGS->install_path + "/" + FILENAME;
    f.open(filename.c_str());
    f << unique;
    f.close();
}
void UniqueId::read()
{
    std::ifstream f;
    std::string filename = Util::SETTINGS->install_path + "/" + FILENAME;
    f.open(filename.c_str());
    if (f) {
        f >> unique;
        f.close();
    } else {
        generate();
        write();
    }
}

