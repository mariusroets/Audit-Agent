
#include <vector>
#include "commandparser.h"
#include "macasset.h"
#include "sysprofileparser.h"
#include "util.h"

MacAsset::MacAsset()
{
}
MacAsset::~MacAsset()
{
}
void MacAsset::read()
{
    SysProfileParser *sys = SysProfileParser::Instance();
    mMachineName = sys->value("Software:System Software Overview:Computer Name");
    mAssetNumber = "";
    mScanComp = "4.1.0.13";
    mUser = sys->value("Software:System Software Overview:User Name");
    mNWUser = sys->value("Software:System Software Overview:User Name");
    mUniqueId = Util::SETTINGS->unique_id;
    mDescription = "";
    // Remove fullname from user name
    size_t p = mUser.find("(");
    mUser = mUser.substr(0,p-1);

}
