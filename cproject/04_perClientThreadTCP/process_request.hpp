#include<cstdlib>
#include<iostream>
#include<cstring>
#include <common_hash.hpp>
#include <common_struct.hpp>
#include <network_utils.hpp>
#include<unordered_map>

extern  std::unordered_map<int32_t,ClientDetail>g_map_clients_detail;
extern  int32_t g_userid;

Signup_res process_signup(const Signup_req &req)
{
    Signup_res res;
    res.header.transcode = SIGNUP_RES;
    res.header.length = sizeof(Signup_res) - sizeof(Header);

    std::unordered_map<int32_t,ClientDetail>::iterator itr=g_map_clients_detail.begin();

    while(itr!=g_map_clients_detail.end()){
        if(strcmp(req.username,itr->second.username)==0){
            strncpy(res.msg,"User Already exist Please check username",sizeof(res.msg)-1);
            res.msg[sizeof(res.msg) - 1] = '\0';
            res.login_status=LOGIN_STATUS::FAIL;
            return res;
        }
        itr++;
    }

    std::cout << "Processing Signup for:\n";
    std::cout << " - Name: " << req.name << "\n";
    std::cout << " - Username: " << req.username << "\n";

    std::strncpy(res.name,req.name,sizeof(res.name)-1);
    res.name[sizeof(res.name)-1]='\0';

    std::strncpy(res.username,req.username,sizeof(res.username)-1);
    res.username[sizeof(res.username)-1]='\0';

    // hardcoding
    if(std::strcmp(req.name,"rohit")==0){
        res.login_status = LOGIN_STATUS::SUCCESS;
        std::strncpy(res.msg, "Signup Successful! You can login now.", sizeof(res.msg) - 1);
        ClientDetail temp_client={};
        temp_client.isLoggedIn=false;
        temp_client.userid=++g_userid;
        strcpy(temp_client.username,req.username);
        g_map_clients_detail[g_userid]=temp_client;

    }else{
        res.login_status = LOGIN_STATUS::USER_NOT_FOUND;
        std::strncpy(res.msg, "Signup Fail! User Does not exits", sizeof(res.msg) - 1);
    }
       
    
   

    res.msg[sizeof(res.msg) - 1] = '\0'; // Safe null-termination
    return res;
}


int processRequest(const char *buffer, char *response)
{

    Header *header = (Header *)buffer;

    switch (header->transcode)
    {
        case SIGNUP_REQ:
        {
            Signup_req* psignup=(Signup_req*)buffer;

            Signup_res signup_res=process_signup(*psignup);

            std::memcpy(response,&signup_res,sizeof(Signup_res));

            return sizeof(signup_res);

        }break;
        case LOGIN_REQ:{

        }break;
        default:
            break;
    }
}


