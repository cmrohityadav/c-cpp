#pragma once
#include<stdint.h>
// Transcode
#define SIGNUP_REQ 1001
#define SIGNUP_RES 1002
#define LOGIN_REQ  1003
#define LOGIN_RES  1004

// fixex size len
#define USERNAME 20
#define NAME 20
#define PASSWORD 40
#define MESSAGE 50


//enums
enum class LOGIN_STATUS:uint16_t{
    SUCCESS,
    FAIL,
    USER_NOT_FOUND
};


