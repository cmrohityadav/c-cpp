#include <cstdlib>
#include <iostream>
#include <cstring>
#include <common_hash.hpp>
#include <common_struct.hpp>
#include <network_utils.hpp>
#include <unordered_map>
#include <mutex>
#include<fstream>

extern std::unordered_map<int32_t, ClientDetail> g_map_clients_detail;
extern std::unordered_map<std::string,std::string>g_map_user_password;
extern std::mutex mtx_user_detail;
using  UserMap=std::unordered_map<std::string,std::string>;
extern UserMap g_map_user_password;
extern int32_t g_userid;
extern bool append_in_user_file(std::string username,std::string password);


template<size_t N>
static void copy_field(char (&dst)[N], const char *src, size_t src_size)
{
    size_t len = strnlen(src, src_size);
    if (len >= N) len = N - 1;
    std::memcpy(dst, src, len);
    dst[len] = '\0';
}

static bool append_user_to_file(const std::string &username, const std::string &password)
{

    std::ofstream file(USERPASSFILENAME, std::ios::app);
    if(!file.is_open()){
        printf("%s","could not open file for appending\n");
        return false;
    }

    file<<username<<','<<password<<'\n';
    file.flush();

    return static_cast<bool>(file);
}



Signup_res process_signup(const Signup_req& req)
{
    std::cout << "Entered process_signup\n";

    Signup_res res{};

    std::cout << "Signup_res initialized\n";
    res.header.transcode = SIGNUP_RES;
    res.header.length = sizeof(Signup_res) - sizeof(Header);

    char name[NAME];
    char username[USERNAME];
    char password[PASSWORD];

    copy_field(name, req.name, sizeof(req.name));
    copy_field(username, req.username, sizeof(req.username));
    copy_field(password, req.password, sizeof(req.password));
    

    copy_field(res.name, name, sizeof(name));
    copy_field(res.username, username, sizeof(username));

    std::cout << "Processing Signup for:\n";
    std::cout << " - Name: " << name << "\n";
    std::cout << " - Username: " << username << "\n";

    if(username[0]=='\0' || password[0]=='\0' || strpbrk(username,",\r\n") || strpbrk(password,",\r\n")){
        res.login_status = LOGIN_STATUS::FAIL;
        copy_field(res.msg, "Invalid username or password", sizeof(res.msg));
        return res;
    }



    std::lock_guard<std::mutex> lck(mtx_user_detail);
    if(g_map_user_password.find(username)!=g_map_user_password.end()){
        copy_field(res.msg,"User Already exist Please check username",sizeof(res.msg));
        res.login_status=LOGIN_STATUS::FAIL;
        return res;
    }

    if(!append_user_to_file(username,password)){
        res.login_status = LOGIN_STATUS::FAIL;
        copy_field(res.msg, "Signup Fail! Server could not save user", sizeof(res.msg));
        return res;
    }


    g_map_user_password[username]=password;

    res.login_status = LOGIN_STATUS::SUCCESS;
    copy_field(res.msg, "Signup Successful! You can login now.", sizeof(res.msg));

    return res;

}

Login_res process_login(const Login_req &req)
{
    Login_res res{};
    res.header.transcode = LOGIN_RES;
    res.header.length = sizeof(Login_res) - sizeof(Header);

    char username[USERNAME];
    char password[PASSWORD];
    copy_field(username, req.username, sizeof(req.username));
    copy_field(password, req.password, sizeof(req.password));

    std::cout << "Processing Login for: " << username << "\n";

    std::lock_guard<std::mutex> lck(mtx_user_detail);

    UserMap::iterator itr=g_map_user_password.find(username);
    if(itr==g_map_user_password.end()){
        res.login_status = LOGIN_STATUS::USER_NOT_FOUND;
        copy_field(res.msg, "User does not exist, please signup", sizeof(res.msg));
    }else if(itr->second!=password){
        res.login_status = LOGIN_STATUS::FAIL;
        copy_field(res.msg, "Wrong password", sizeof(res.msg));
    }else{
        res.login_status = LOGIN_STATUS::SUCCESS;
        copy_field(res.msg, "Login Successful!", sizeof(res.msg));
    }

    return res;
}



int processRequest(const char *buffer, char *response)
{

    Header *header = (Header *)buffer;

    switch (header->transcode)
    {
    case SIGNUP_REQ:
    {
        Signup_req* psignup = (Signup_req *)buffer;

        Signup_res signup_res = process_signup(*psignup);

        std::memcpy(response, &signup_res, sizeof(Signup_res));

        return sizeof(signup_res);
    }
    break;
    case LOGIN_REQ:
    {
    }
    break;
    default:
        break;
    }

    return 0;
}
