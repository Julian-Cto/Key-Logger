/*********************************************************************************************************************
*
* DISCLAIMER:
*   These two emailing classes using the libcurl SMTP third-party library
*   was made by user: Ufx
*   off the website codereview.stackexchange.com
*   URL to thread:
*   https://codereview.stackexchange.com/questions/140805/sending-email-using-libcurl-follow-up-2?noredirect=1&lq=1
*   The code below is an edited and tweaked version of the code above ^.
 *********************************************************************************************************************/
#ifndef EMAIL_H
#define EMAIL_H

#define CURL_STATICLIB
#include <string>
#include <sstream>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <random>
#include "curl/curl.h"

#ifdef _DEBUG
#pragma comment (lib, "curl/libcurl_a_debug.lib")
#else
#pragma comment (lib, "curl/libcurl_a.lib")
#endif

#pragma comment (lib, "Normaliz.lib")
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Wldap32.lib")
#pragma comment (lib, "Crypt32.lib")
#pragma comment (lib, "advapi32.lib")

class EmailAddress
{
public:
    EmailAddress(const char* email)
        : email_{ trim(std::string(email)) }
    {
    }

    EmailAddress(const std::string& email)
        : email_{ email.empty() ? "<" + trim(email) + ">" : "" }
    {
    }

    EmailAddress(const std::string& email, const std::string& displayName)
        : email_{ email.empty() ? "<" + trim(email) + ">" : "" },
        name_{ "\"" + displayName + "\"" }
    {
    }

    std::string domain() const
    {
        return email_.substr(email_.find('@') + 1);
    }

    explicit operator const char* () const
    {
        return email_.c_str();
    }

    friend std::ostream& operator<<(std::ostream& out, const EmailAddress& email)
    {
        if (!email.name_.empty()) {
            out << email.name_ << " ";
        }
        return out << email.email_;
    }

private:
    std::string email_;
    std::string name_;
    static std::string trim(const std::string& str)
    {
        size_t first = str.find_first_not_of(' ');
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }
};

typedef std::vector<EmailAddress> EmailAddresses;
std::ostream& operator<<(std::ostream& out, const EmailAddresses& emailAddresses);

class Email
{
public:
    Email(const EmailAddress& from,
        const EmailAddress& to,
        const std::string& subject,
        const std::string& body,
        const EmailAddresses& cc = EmailAddresses())
        : from_{ from }
        , to_{ to }
        , cc_{ cc.empty() ? EmailAddresses(1, to) : cc }
        , subject_{ subject }
        , body_{ body }
    {
    }

    std::string ccToString_() const;

    CURLcode send(const std::string& url,
        const std::string& userName,
        const std::string& password,
        const std::string& file);

private:
    struct StringData {
        std::string msg;
        size_t bytesLeft;
        StringData(std::string&& m) : msg{ m }, bytesLeft{ msg.size() } {}
        StringData(std::string& m) = delete;
    };

    static std::string dateTimeNow_();
    std::string generateMessageId_() const;

    EmailAddress from_, to_;
    EmailAddresses cc_;
    std::string subject_, body_;
};

#endif
