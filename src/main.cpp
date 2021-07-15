#include "md5.h"

#include <httplib.h>
#include <tinyxml2.h>

#include <iostream>
#include <string>
#include <locale>
#include <codecvt>

std::string toMd5(const std::string& in);

constexpr char username[] = "";
constexpr int port = 80;
constexpr char hostname[] = "fritz.box";
constexpr char password[] = "";
constexpr char device[] = "<device>";

int main(int argc, char** argv)
{
    httplib::Client cli(hostname , port);

    // The AVM communication is very slow, so we have to increase the timeout.
    cli.set_read_timeout(10, 0); // 10 seconds

    std::string login_path{"/login_sid.lua?username="};
    login_path += username;

    if (auto res = cli.Get(login_path.c_str()))
    {
        std::cout << res->status << std::endl;
        std::cout << res->get_header_value("Content-Type") << std::endl;
        std::cout << res->body << std::endl;

        tinyxml2::XMLDocument doc;
        tinyxml2::XMLError err = doc.Parse(res->body.c_str(), res->body.size());
        if (err != tinyxml2::XML_SUCCESS) {
            std::cerr << "Could not parse body: " << doc.ErrorIDToName(err) << std::endl;
        }

        // Get challenge
        std::string challenge = doc.FirstChildElement("SessionInfo")->FirstChildElement("Challenge")->GetText();
        std::cout << "Challenge: " << challenge << std::endl;

        // wget -q -O - --post-data="response=4640f673-1b8a76233fe8a89ffe908a9ea8c63410&username=" http://192.168.178.1/login_sid.lua # Wer wget lieber hat...
        std::string hashstring = challenge + "-" + password;
        std::u16string utf16 = std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>{}.from_bytes(hashstring.data());

        std::string md5 = MD5::Calc(utf16);
        std::cout << "MD5(" << challenge << "-" << password << ") = " << md5 << std::endl;
        std::string post_body = "response=" + challenge + "-" + md5 + "&username=" + username;
        std::cout << post_body << std::endl;
        if (res = cli.Post("/login_sid.lua", post_body, "application/x-www-form-urlencoded")) {
            std::cout << res->status << std::endl;
            std::cout << res->get_header_value("Content-Type") << std::endl;
            std::cout << res->body << std::endl;

            tinyxml2::XMLError err = doc.Parse(res->body.c_str(), res->body.size());
            if (err != tinyxml2::XML_SUCCESS) {
                std::cerr << "Could not parse body: " << doc.ErrorIDToName(err) << std::endl;
            }
            std::string sid = doc.FirstChildElement("SessionInfo")->FirstChildElement("SID")->GetText();
            std::cout << "SID: " << sid << std::endl;

            // Sperren iPad
            //post_body = "sid=" + sid + "&page=edit_device2&dev_name=" + device + "&lang=de&kisi_profile=filtprof9999&dev_ip3=22&dev_ip=192.168.178.22&bock_dev=&xhr=1&dev=landevice6229&no_sidrenew=&static_dhcp=on&allow_pcp_and_upnp=off";
            //post_body = "{\"xhr\": \"1\",\"dev_name\": \"" + device + "\",\"dev_ip3\": \"22\",\"dev_ip\": \"192.168.178.22\",\"static_dhcp\": \"on\",\"allow_pcp_and_upnp\": \"off\",\"kisi_profile\": \"filtprof9999\",\"back_to_page\": \"homeNet\",\"dev\": \"landevice6229\",\"apply\": \"\",\"sid\": \"" + sid + "\",\"lang\": \"de\",\"page\": \"edit_device2\"}";
            post_body = "xhr=1&dev_name=" + device + "&dev_ip3=22&dev_ip=192.168.178.22&static_dhcp=on&allow_pcp_and_upnp=off&kisi_profile=filtprof9999&back_to_page=homeNet&dev=landevice6229&apply=&sid=" + sid + "&lang=de&page=edit_device2";
            std::cout << post_body << std::endl;
            if (res = cli.Post("/data.lua", post_body, "application/x-www-form-urlencoded")) {
            //if (res = cli.Post("/data.lua", post_body, "application/json")) {
                std::cout << res->status << std::endl;
                std::cout << res->get_header_value("Content-Type") << std::endl;
                std::cout << res->body << std::endl;

            } else {
                std::cerr << "Error code: " << res.error() << std::endl;
            }
        } else {
            std::cerr << "Error code: " << res.error() << std::endl;
        }
    } else {
        std::cerr << "Error code: " << res.error() << std::endl;
    }

    return EXIT_SUCCESS;
}
