#include "stdafx.h"
#include <tuple>
#include <string>

using UserInfo =                 // type alias; see Item 9
std::tuple< std::string,        // name
            std::string,        // email
            std::size_t>;      // reputation

// C++11
template<typename E>
constexpr typename std::underlying_type<E>::type toUType_C11(E enumerator) noexcept
{
    return static_cast<typename std::underlying_type<E>::type>(enumerator);
}

// C++14
template<typename E>                               
constexpr std::underlying_type_t<E> toUType_C14(E enumerator) noexcept
{
    return static_cast<std::underlying_type_t<E>>(enumerator);
}

// C++14 auto
template<typename E>
constexpr auto toUType_C14Auto(E enumerator) noexcept
{
    return static_cast<std::underlying_type_t<E>>(enumerator);
}

BEGIN_TEST(TestEnumClass)
    //C++98
    {
        enum UserInfoFields { uiName, uiEmail, uiReputation };

        UserInfo uInfo;                         // as before
        std::string& val = std::get<uiEmail>(uInfo);    // ah, get value of
                                                // email field
    }
    
    //C++11
    {
        enum class UserInfoFields { uiName, uiEmail, uiReputation };

        UserInfo uInfo;                        // as before
        std::string& val = std::get<static_cast<std::size_t>(UserInfoFields::uiEmail)>(uInfo);
    }

    //C++11
    {
        enum class UserInfoFields { uiName, uiEmail, uiReputation };

        UserInfo uInfo;                        // as before
        std::string& val = std::get<toUType_C11(UserInfoFields::uiEmail)>(uInfo);
    }

    //C++14
    {
        enum class UserInfoFields { uiName, uiEmail, uiReputation };

        UserInfo uInfo;                        // as before
        std::string& val = std::get<toUType_C14(UserInfoFields::uiEmail)>(uInfo);
    }

    //C++14
    {
        enum class UserInfoFields { uiName, uiEmail, uiReputation };

        UserInfo uInfo;                        // as before
        std::string& val = std::get<toUType_C14Auto(UserInfoFields::uiEmail)>(uInfo);
    }
END_TEST()