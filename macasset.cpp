
#include <vector>
#include "commandparser.h"
#include "macasset.h"
#include "sysprofileparser.h"

MacAsset::MacAsset()
{
    read();
}
MacAsset::~MacAsset()
{
}
void MacAsset::read()
{
    mMachineName = SYS->value("Software:System Software Overview:Computer Name");
    mAssetNumber = "";
    mScanComp = "";
    mUser = SYS->value("Software:System Software Overview:User Name");
    mNWUser = SYS->value("Software:System Software Overview:User Name");
    mDescription = "";
    mUniqueId = "";

}
