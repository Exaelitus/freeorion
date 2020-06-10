#ifndef _Directories_h_
#define _Directories_h_

#include <string>
#include <boost/filesystem/path.hpp>
#include <GG/Enum.h>
#include "Export.h"


//! Types of root directories
GG_ENUM(PathType,
    PATH_BINARY,
    PATH_RESOURCE,
    PATH_PYTHON,
    PATH_DATA_ROOT,
    PATH_DATA_USER,
    PATH_CONFIG,
    PATH_SAVE,
    PATH_TEMP,
    PATH_INVALID
)


//! Returns a string representation of PathType
FO_COMMON_API auto PathTypeToString(PathType path_type) -> std::string const&;

//! Returns a vector of strings for all PathTypes
FO_COMMON_API auto PathTypeStrings() -> std::vector<std::string> const&;

//! Migrates outstating user configuration and data to a XDG Base Diretory spec
//! compliant directory.
//!
//! It stores the current working directory as well as creating local
//! directories if they do not yet exist.
//
//! @note This function must be called before any Get*Dir function is called.
FO_COMMON_API void CompleteXDGMigration();

//! Initializes the directories used by FreeOrion.
//!
//! @note This function completes the migration of directories to the XDG
//! specified location by updating the save.path option to the new location
//! after the option is loaded from XML files.  It only updates the option
//! if it is set to the old default option.
FO_COMMON_API void InitDirs(std::string const& argv0);

//! Returns the directory where FreeOrion store user configurations.
//!
//! This covers:
//! * user configuration
//!
//! Defaults to:
//! * Windows: Path to `%appdata%`\FreeOrion`.
//! * MacOS: Path to `${HOME}/Library/FreeOrion`.
//! * UNIX-like: Follows XDG Base Dir spec; Path to `${XDG_CONFIG_HOME}/freeorion`.
//!
//! @note
//! * If the directory does not exist, it will be created.
//! * This directory can be considered writable!
FO_COMMON_API auto GetUserConfigDir() -> boost::filesystem::path const;

//! Returns the directory where FreeOrion stores user specific data.
//!
//! This covers:
//! * savegames
//! * log files
//!
//! Defaults to:
//! * Windows: Path to `%appdata%`\FreeOrion`.
//! * MacOS: Path to `${HOME}/Library/FreeOrion`.
//! * UNIX-like: Follows XDG Base Dir spec; Path to `${XDG_DATA_HOME}/freeorion`.
//!
//! @note
//! * If the directory does not exist, it will be created.
//! * This directory can be considered writable!
FO_COMMON_API auto GetUserDataDir() -> boost::filesystem::path const;

//! Converts UTF-8 string into a path, doing any required wide-character
//! conversions as determined by the operating system / filesystem.
FO_COMMON_API auto FilenameToPath(std::string const& path_str) -> boost::filesystem::path;

//! Returns the directory that contains all game resources.
//!
//! This covers:
//! * game entity defintions
//! * graphics
//! * Translations
FO_COMMON_API auto GetResourceDir() -> boost::filesystem::path const;

//! Returns the root data directory of FreeOrion.
//!
//! Defaults to:
//! * Windows: Path to the installation directory.
//! * Mac OS: Path to `<FreeOrion App bundle>/Contents/Resources`.
//! * UNIX-like: Path to `<installation prefix>/share/freeorion`.
//!
//! @note This directory and everything in it should be assumed read-only!
FO_COMMON_API auto GetRootDataDir() -> boost::filesystem::path const;

//! Returns the directory where the binaries are located.
//!
//! Defaults to:
//! * Windows: Path to the installation directory.
//! * Mac OS: Path to `<FreeOrion App bundle>/Contents/Executables`.
//! * UNIX-like: Path to `<installation prefix>/bin`.
//
//! @note This directory and everything in it should be assumed read-only!
FO_COMMON_API auto GetBinDir() -> boost::filesystem::path const;

#if defined(FREEORION_MACOSX) || defined(FREEORION_WIN32)
//! Returns the Python home directory on platform where Python is embedded.
FO_COMMON_API auto GetPythonHome() -> boost::filesystem::path const;
#endif

//! Returns the full path to the configfile.
FO_COMMON_API auto GetConfigPath() -> boost::filesystem::path const;

//! Returns the full path to the configfile.
FO_COMMON_API auto GetPersistentConfigPath() -> boost::filesystem::path const;

//! Returns the directory where save files are located.
//!
//! This is typically the directory "save" within the user directory.
FO_COMMON_API auto GetSaveDir() -> boost::filesystem::path const;

//! Returns the directory where server save files are located.
//!
//! This is typically the directory "save" within the user directory.
FO_COMMON_API auto GetServerSaveDir() -> boost::filesystem::path const;

//! Returns an utf-8 encoded string from the given filesystem path.
FO_COMMON_API auto PathToString(boost::filesystem::path const& path) -> std::string;

//! Returns current timestamp in a form that can be used in file names
FO_COMMON_API auto FilenameTimestamp() -> std::string;

//! Returns the path to @p to, as it appears from @p from.
FO_COMMON_API auto RelativePath(boost::filesystem::path const& from, boost::filesystem::path const& to) -> boost::filesystem::path;

//! Returns true if the given @p path referrs to a FO content script and false
//! otherwise.
FO_COMMON_API auto IsFOCScript(boost::filesystem::path const& path) -> bool;

//! Returns a vector of pathes within @p path including a recursive search
//! though sub-dirs.
//!
//! When passing a @p predicate, the pathes need to match this predicate.  If
//! no predicate is given pathes need to refer to files.
FO_COMMON_API auto ListDir(boost::filesystem::path const& path, std::function<bool (boost::filesystem::path const&)> predicate=nullptr) -> std::vector<boost::filesystem::path>;

//! Returns true iff the @p test_dir is in @p dir and @p dir
//! is existing directory.
FO_COMMON_API auto IsInDir(boost::filesystem::path const& dir, boost::filesystem::path const& test_dir) -> bool;

//! Returns path currently defined for @p path_type
FO_COMMON_API auto GetPath(PathType path_type) -> boost::filesystem::path;

//! Returns path for path type cast from @p path_string
FO_COMMON_API auto GetPath(std::string const& path_string) -> boost::filesystem::path;

//! Returns true iff path exists and is a regular file
FO_COMMON_API auto IsExistingFile(boost::filesystem::path const& path) -> bool;
#endif
