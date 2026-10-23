#pragma once
#include <cinttypes>
#include <common_hash.hpp>

#pragma pack(push, 1) // #pragma pack(1)

struct Header
{
    uint32_t transcode;
    uint32_t length;
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

#pragma pack(pop)