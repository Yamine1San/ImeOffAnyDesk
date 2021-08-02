#include <regex>
namespace std
{
#ifdef _UNICODE
    typedef std::wstring tstring;
    typedef std::wregex tregex;
    typedef std::wsmatch tsmatch;
#else
    typedef std::string tstring;
    typedef std::regex tregex;
    typedef std::smatch tsmatch;
#endif
}