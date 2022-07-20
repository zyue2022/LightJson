#include <fstream>
#include <iostream>

#include "Json.h"
#include "cassert"
#include "string.h"
#include "unistd.h"

using namespace std;
using namespace lightJson;

int main() {
    char* tmp = nullptr;
    tmp       = getcwd(nullptr, 0);
    assert(tmp);
    std::string src_dir_(tmp);
    std::cout << src_dir_ << std::endl;

    std::string   config_path = src_dir_ + "/serverConf.json";
    std::ifstream ifstrm(config_path);
    if (!ifstrm.is_open()) {
        cout << "file wrong" << endl;
        return 0;
    }

    std::string json_str;
    while (ifstrm) {
        std::string line;
        std::getline(ifstrm, line);
        json_str += line + "\n";
    }

    std::string err_msg;
    Json        json = Json::parseAPI(json_str, err_msg);
    if (!err_msg.empty()) {
        cout << err_msg << endl;
        //return 0;
    }

    int  port_       = json["webConf"]["port"].toNumber();
    int  trigMode_   = json["webConf"]["trigMode"].toNumber();
    int  timeoutMS_  = json["webConf"]["timeoutMS"].toNumber();
    bool openLinger_ = json["webConf"]["openLinger"].toBool();
    int  threadNum_  = json["webConf"]["threadNum"].toNumber();

    cout << port_ << " " << trigMode_ << " " << timeoutMS_ << " " << openLinger_ << " "
         << threadNum_ << endl;

    int         sqlPort_    = json["sqlConf"]["sqlPort"].toNumber();
    std::string sqlUser_    = json["sqlConf"]["sqlUser"].toString();
    std::string sqlPwd_     = json["sqlConf"]["sqlPwd"].toString();
    std::string dbName_     = json["sqlConf"]["dbName"].toString();
    int         sqlConnNum_ = json["sqlConf"]["sqlConnNum"].toNumber();

    cout << sqlPort_ << " " << sqlUser_ << " " << sqlPwd_ << " " << dbName_ << " " << sqlConnNum_
         << endl;

    bool openLog_    = json["logConf"]["openLog"].toBool();
    int  logLevel_   = json["logConf"]["logLevel"].toNumber();
    int  logQueSize_ = json["logConf"]["logQueSize"].toNumber();

    cout << openLog_ << " " << logLevel_ << " " << logQueSize_ << endl;

    cout << json.serialize() << endl << endl;

    cout << json << endl;

    return 0;
}