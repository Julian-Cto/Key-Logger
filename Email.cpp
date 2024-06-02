#include "Email.h"

std::ostream& operator<<(std::ostream& out, const EmailAddresses& emailAddresses)
{
    if (!emailAddresses.empty()) {
        auto it = emailAddresses.begin();
        out << *it;

        while (++it != emailAddresses.end()) {
            out << "," << *it;
        }
    }

    return out;
}
CURLcode Email::send(const std::string& url,
    const std::string& userName,
    const std::string& password,
    const std::string& file)
{
    CURLcode ret = CURLE_OK;

    CURL* curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_USERNAME, userName.c_str());
        curl_easy_setopt(curl, CURLOPT_PASSWORD, password.c_str());
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, (const char*)from_);

        struct curl_slist* recipients = NULL;
        recipients = curl_slist_append(recipients, (const char*)to_);
        for (const auto& ccAddress : cc_) {
            recipients = curl_slist_append(recipients, (const char*)ccAddress);
        }
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        //Create the MIME structure
        curl_mime* mime = curl_mime_init(curl);

        //Add the headers and body as the first MIME part
        curl_mimepart* part = curl_mime_addpart(mime);
        curl_mime_data(part, body_.c_str(), CURL_ZERO_TERMINATED);
        curl_mime_type(part, "text/plain");

        //Add the attachment as the second MIME part
        part = curl_mime_addpart(mime);
        curl_mime_filedata(part, file.c_str());
        curl_mime_name(part, "anyname");/*<- you can change this (optional)*/
        curl_mime_filename(part, "anyname.txt");/* <- you can change this (optional)*/

        //Add custom headers
        struct curl_slist* headers = NULL;
        std::string date_header = "Date: " + dateTimeNow_();
        std::string to_header = "To: " + std::string(static_cast<const char*>(to_));
        std::string from_header = "From: " + std::string(static_cast<const char*>(from_));
        std::string cc_header = "Cc: " + ccToString_();
        std::string message_id_header = "Message-ID: <" + generateMessageId_() + "@" + from_.domain() + ">";
        std::string subject_header = "Subject: " + subject_;

        headers = curl_slist_append(headers, date_header.c_str());
        headers = curl_slist_append(headers, to_header.c_str());
        headers = curl_slist_append(headers, from_header.c_str());
        headers = curl_slist_append(headers, cc_header.c_str());
        headers = curl_slist_append(headers, message_id_header.c_str());
        headers = curl_slist_append(headers, subject_header.c_str());

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        ret = curl_easy_perform(curl);

        if (ret != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: "
                << curl_easy_strerror(ret)
                << std::endl;
        }

        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
        curl_mime_free(mime);
        curl_slist_free_all(headers);
    }

    return ret;
}
std::string Email::ccToString_() const
{
    std::ostringstream oss;
    for (const auto& ccAddress : cc_) {
        if (oss.tellp() > 0) {
            oss << ", ";
        }
        oss << ccAddress;
    }
    return oss.str();
}

std::string Email::dateTimeNow_()
{
    const int RFC5322_TIME_LEN = 32;
    std::string ret;
    ret.resize(RFC5322_TIME_LEN);
    time_t tt;
    time(&tt);
    tm t;
    localtime_s(&t, &tt);
    strftime(&ret[0], RFC5322_TIME_LEN, "%a, %d %b %Y %H:%M:%S %z", &t);
    return ret;
}

std::string Email::generateMessageId_() const
{
    const size_t MESSAGE_ID_LEN = 37;

    tm t;
    time_t tt;
    time(&tt);

#ifdef _MSC_VER
    gmtime_s(&t, &tt);
#else
    gmtime_r(&tt, &t);
#endif

    std::string ret;
    ret.resize(MESSAGE_ID_LEN);
    size_t dateLen = std::strftime(&ret[0], MESSAGE_ID_LEN, "%Y%m%d%H%M%S", &t);

    static const std::string alphaNum{
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz" };

    std::mt19937 gen;
    std::uniform_int_distribution<> distr(0, alphaNum.length() - 1);
    std::generate_n(ret.begin() + dateLen,
        MESSAGE_ID_LEN - dateLen,
        [&]() { return alphaNum[distr(gen)]; });

    return ret;
}
