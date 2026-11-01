#pragma once
#include <cinttypes>
#include <common_hash.hpp>

#pragma pack(push, 1) // #pragma pack(1)

struct Header
{
    uint32_t transcode;
    uint32_t length;
};

struct ClientDetail{
    int32_t userid;
    char username[USERNAME];
    bool isLoggedIn;
    int32_t clientfd;
};

struct Signup_req
{
    Header header;
    char name[NAME];
    char username[USERNAME];
    char password[PASSWORD];
};

struct Signup_res
{
    Header header;
    char name[NAME];
    char username[USERNAME];
    LOGIN_STATUS login_status;
    char msg[MESSAGE];
};

struct Login_req
{
    Header header;
    char username[USERNAME];
    char password[PASSWORD];
};

struct Login_res
{
    Header header;
    char msg[MESSAGE];
    LOGIN_STATUS login_status;
};

struct AddTokenRequest{
    Header header;
    char username[USERNAME];
    char scrip[SCRIPSIZE];
    char remark[MESSAGE];
    uint32_t token;
};

struct AddTokenResponse{
    Header header;
    uint8_t isAddedflag; //1: added sucessfully , 2: fail to add 
    char msg[MESSAGE];
    uint32_t token;
};

struct TokenDetail{
    char scrip[SCRIPSIZE];
    char remark[MESSAGE];
    uint32_t token;
};

#pragma pack(pop)
