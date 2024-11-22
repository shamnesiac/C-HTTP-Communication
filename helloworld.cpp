#include <iostream>
#include <curl/curl.h>
#include <boost/json/src.hpp>
#include <boost/json.hpp>

using namespace boost::json;
using namespace std;


static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp)
{
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

static std::string cleanFormat(std::string s)
{
    std::string ans = "";
    for (auto i : s)
    {
        if (i != '//')
            ans += i;
    }
    return ans;
}

int main(int argc, char* argv[])
{
    std::cout << "Hello World!" << std::endl;

    CURL* curl;
    CURLcode res;

    std::string get_response;
    std::string post_response;


    curl = curl_easy_init();
    if (curl) {
        // Perform GET request
        curl_easy_setopt(curl, CURLOPT_URL, "https://httpbin.org/get?name=ali&age=56");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &get_response);
        res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            std::cout << "GET Response: " << get_response << std::endl;
            std::cout << "GET Response Code: " << response_code << std::endl;
        }
        else {
            std::cerr << "GET request failed: " << curl_easy_strerror(res) << std::endl;
        }

        get_response = cleanFormat(get_response);
        auto v = parse(get_response);
        auto obj = v.as_object();

        // Modify the JSON object
        auto args = obj["args"].as_object();
        args["name"] = "roger";  
        obj["args"] = args;  

        // Convert the modified JSON object back to a string
        get_response = serialize(obj);

        // Perform POST request
        curl_easy_setopt(curl, CURLOPT_URL, "https://httpbin.org/post");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, get_response.c_str());
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &post_response);

        res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            std::cout << "POST Response: " << post_response << std::endl;
            std::cout << "POST Response Code: " << response_code << std::endl;
        }
        else {
            std::cerr << "POST request failed: " << curl_easy_strerror(res) << std::endl;
        }


        auto v1 = parse(post_response);
        auto obj1 = v1.as_object();

        // Modify the JSON object
        object topost;
        auto args1 = obj1["json"].as_object();
        args1["name"] = "johnston";  
        obj1["args"] = args1;  
        object objnest;
        objnest["race"] = "asian";
        objnest["gender"] = "male";
        args1["subobject"] = objnest;
        topost["json"] = args1;
        // Convert the modified JSON object back to a string
        post_response = serialize(topost);
        //remove_if(get_response.begin(), get_response.end(), trimIf);

        std::string putData = post_response;
        std::string readBuffer;

        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, "https://httpbin.org/put?name=ryan&pass=45");
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, putData.c_str());
            curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            }
            else {
                std::cout << "PUT Response:\n" << readBuffer << std::endl;
            }

            curl_easy_cleanup(curl);
        }

        curl = curl_easy_init();
        std::string rem;
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, "https://httpbin.org/delete");
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &rem);
            //remove_if(rem.begin(), rem.end(), trimIf);
            res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            }
            else {
                std::cout << "DELETE Response:\n" << rem << std::endl;
            }

            curl_easy_cleanup(curl);
        }

        curl = curl_easy_init();
        std::string password;
        curl_easy_setopt(curl, CURLOPT_USERPWD, "a:5");
        curl_easy_setopt(curl, CURLOPT_URL, "https://httpbin.org/basic-auth/a/5");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &password);
        //remove_if(get_response.begin(), get_response.end(), trimIf);
        res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            std::cout << "GET Response: " << password << std::endl;
            std::cout << "GET Response Code: " << response_code << std::endl;
        }
        else {
            std::cerr << "GET request failed: " << curl_easy_strerror(res) << std::endl;
        }
    }

    return 0;
}
