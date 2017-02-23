#ifndef ASSET_FILEPATH_H
#define ASSET_FILEPATH_H

namespace valve
{
    //---------------------------------------------------------------------------
    // valve::Asset_Filepath
    //---------------------------------------------------------------------------
    // Data type for asset filepaths within Valve Source engine games. It's a
    // partial filepath that is limited to Ascii characters, and cannot contain
    // any whitespace chars.
    class Asset_Filepath
    {
    public:
        Asset_Filepath();
    };

}

#endif // ASSET_FILEPATH_H
