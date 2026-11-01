#pragma once
#include<stdint.h>
// Transcode
#define SIGNUP_REQ 1001
#define SIGNUP_RES 1002
#define LOGIN_REQ  1003
#define LOGIN_RES  1004
#define ADDTOKEN_REQ 1005
#define ADDTOKEN_RES 1006
#define CHECK_HOLDING_REQ 1007
#define CHECK_HOLDING_RES 1008
#define HOLDING_HEADER 1009
#define HOLDING_DATA 1010
#define HOLDING_TRAILER 1011
#define MODIFY_HOLDING_REQ 1012
#define MODIFY_HOLDING_RES 1013


// fixex size len
#define USERNAME 20
#define NAME 20
#define PASSWORD 40
#define MESSAGE 50
#define MAXMSGSIZE 5000
#define SCRIPSIZE 15

#define USERPASSFILENAME "userpass.txt"

//enums
enum class LOGIN_STATUS:uint16_t{
    SUCCESS,
    FAIL,
    USER_NOT_FOUND
};


