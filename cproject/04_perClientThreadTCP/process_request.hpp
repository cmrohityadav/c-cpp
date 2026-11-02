#include <cstdlib>
#include <iostream>
#include <cstring>
#include <common_hash.hpp>
#include <common_struct.hpp>
#include <network_utils.hpp>
#include <unordered_map>
#include <mutex>
#include <fstream>
#include <types.hpp>

extern std::unordered_map<std::string, ClientDetail> g_map_clients_detail;
extern std::unordered_map<std::string, std::string> g_map_user_password;
extern std::mutex mtx_user_detail;
using UserMap = std::unordered_map<std::string, std::string>;
extern UserMap g_map_user_password;
extern int32_t g_userid;
extern bool append_in_user_file(std::string username, std::string password);

extern TokenByUserNameMap_t g_map_token_by_client;
extern std::mutex mtx_token;
// extern TokenDetailMap_t g_map_token_detail;
extern HoldingByUserNameMap_t g_map_holding_by_username;
extern std::mutex mtx_holding_map;

template <size_t N>
static void copy_field(char (&dst)[N], const char *src, size_t src_size)
{
    size_t len = strnlen(src, src_size);
    if (len >= N)
        len = N - 1;
    std::memcpy(dst, src, len);
    dst[len] = '\0';
}

static bool append_user_to_file(const std::string &username, const std::string &password)
{

    std::ofstream file(USERPASSFILENAME, std::ios::app);
    if (!file.is_open())
    {
        printf("%s", "could not open file for appending\n");
        return false;
    }

    file << username << ',' << password << '\n';
    file.flush();

    return static_cast<bool>(file);
}

Signup_res process_signup(const Signup_req &req)
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

    if (username[0] == '\0' || password[0] == '\0' || strpbrk(username, ",\r\n") || strpbrk(password, ",\r\n"))
    {
        res.login_status = LOGIN_STATUS::FAIL;
        copy_field(res.msg, "Invalid username or password", sizeof(res.msg));
        return res;
    }

    std::unique_lock<std::mutex> lck(mtx_user_detail);
    if (g_map_user_password.find(username) != g_map_user_password.end())
    {
        copy_field(res.msg, "User Already exist Please check username", sizeof(res.msg));
        res.login_status = LOGIN_STATUS::FAIL;
        return res;
    }

    if (!append_user_to_file(username, password))
    {
        res.login_status = LOGIN_STATUS::FAIL;
        copy_field(res.msg, "Signup Fail! Server could not save user", sizeof(res.msg));
        return res;
    }

    g_map_user_password[username] = password;
    ClientDetail clientdetail = {0};
    copy_field(clientdetail.username, username, sizeof(clientdetail.username));
    g_map_clients_detail[username] = clientdetail;

    res.login_status = LOGIN_STATUS::SUCCESS;
    copy_field(res.msg, "Signup Successful! You can login now.", sizeof(res.msg));

    return res;
}

Login_res process_login(Login_req &loginReq)
{
    Login_res objLoginRes = {0};

    objLoginRes.header.transcode = LOGIN_RES;
    objLoginRes.header.length =
        sizeof(Login_res) - sizeof(Header);

    char username[USERNAME]{};
    char password[PASSWORD]{};

    copy_field(username, loginReq.username, sizeof(username));
    copy_field(password, loginReq.password, sizeof(password));

    std::unique_lock<std::mutex> lck(mtx_user_detail);

    auto itr = g_map_user_password.find(username);

    if (itr == g_map_user_password.end())
    {
        objLoginRes.login_status = LOGIN_STATUS::USER_NOT_FOUND;

        strncpy(objLoginRes.msg, "User not found. Please signup.",
                sizeof(objLoginRes.msg) - 1);

        return objLoginRes;
    }

    if (strcmp(password, itr->second.c_str()) != 0)
    {
        objLoginRes.login_status = LOGIN_STATUS::FAIL;

        strncpy(objLoginRes.msg, "Wrong password.",
                sizeof(objLoginRes.msg) - 1);

        return objLoginRes;
    }

    auto itr_clientdetail = g_map_clients_detail.find(username);

    if (itr_clientdetail != g_map_clients_detail.end())
    {
        ClientDetail &client = itr_clientdetail->second;

        if (client.isLoggedIn)
        {
            objLoginRes.login_status = LOGIN_STATUS::FAIL;

            strncpy(objLoginRes.msg, "User already logged in.",
                    sizeof(objLoginRes.msg) - 1);

            return objLoginRes;
        }

        client.isLoggedIn = true;
    }

    objLoginRes.login_status = LOGIN_STATUS::SUCCESS;

    strncpy(objLoginRes.msg, "Login successful.",
            sizeof(objLoginRes.msg) - 1);

    return objLoginRes;
}

AddTokenResponse process_add_token(AddTokenRequest &addTokenReq)
{
    AddTokenResponse addtokenRes = {0};
    addtokenRes.header.transcode = ADDTOKEN_RES;
    addtokenRes.header.length = sizeof(AddTokenResponse) - sizeof(Header);

    char username[USERNAME] = {0};
    strncpy(username, addTokenReq.username, sizeof(username) - 1);
    username[USERNAME - 1] = '\0';

    {
        std::lock_guard<std::mutex> lck(mtx_user_detail);
        auto itr = g_map_clients_detail.find(username);
        if (itr == g_map_clients_detail.end())
        {
            // TODo for security check
        }
    }

    // if token already exist
    // TODO

    // add token
    TokenDetail temp_token_detail = {0};
    temp_token_detail.token = addTokenReq.token;
    strncpy(temp_token_detail.scrip, addTokenReq.scrip, sizeof(temp_token_detail.scrip) - 1);
    strncpy(temp_token_detail.remark, addTokenReq.remark, sizeof(temp_token_detail.remark) - 1);

    {
        std::lock_guard<std::mutex> lck(mtx_token);

        TokenDetailMap_t &map_token_detail = g_map_token_by_client[username];
        map_token_detail[addTokenReq.token] = temp_token_detail;
    }

    addtokenRes.isAddedflag = 1;
    strncpy(addtokenRes.msg, "Token Added sucessfully", MESSAGE - 1);
    addtokenRes.msg[MESSAGE - 1] = '\0';

    return addtokenRes;
}

int processRequest(const char *buffer, char *response)
{

    Header *header = (Header *)buffer;

    switch (header->transcode)
    {
    case SIGNUP_REQ:
    {
        Signup_req *psignup = (Signup_req *)buffer;

        Signup_res signup_res = process_signup(*psignup);

        std::memcpy(response, &signup_res, sizeof(Signup_res));

        return sizeof(signup_res);
    }
    break;
    case LOGIN_REQ:
    {
        Login_req *pLoginRequest = (Login_req *)buffer;

        Login_res loginResponse = process_login(*pLoginRequest);
        std::memcpy(response, &loginResponse, sizeof(Login_res));

        return sizeof(loginResponse);
    }
    break;
    case ADDTOKEN_REQ:
    {
        AddTokenRequest *pAddTokenReq = (AddTokenRequest *)buffer;

        AddTokenResponse addTokenRes = process_add_token(*pAddTokenReq);
        std::memcpy(response, &addTokenRes, sizeof(AddTokenResponse));

        return sizeof(addTokenRes);
    }
    break;
    case CHECK_HOLDING_REQ:
    {
    }
    break;
    case ADD_HOLDING_REQ:
    {
        AddHoldingRequest *pAddHoldingReq = (AddHoldingRequest *)buffer;
        AddHoldingResponse addholdingRes = {0};
        addholdingRes.header.transcode = ADD_HOLDING_RES;
        addholdingRes.header.length = sizeof(AddHoldingResponse) - sizeof(Header);
        char username[USERNAME] = {0};
        strncpy(username, pAddHoldingReq->username, USERNAME - 1);

        auto setError = [&](const char *msg)
        {
            addholdingRes.isAdded = 0;
            strncpy(addholdingRes.msg, msg, MESSAGE - 1);
            addholdingRes.msg[MESSAGE - 1] = '\0';
            
        };

        {
            std::lock_guard<std::mutex> lck(mtx_token);

            // if token exist
            auto itr = g_map_token_by_client.find(username);
            if (itr == g_map_token_by_client.end())
            {

                // return error
                setError("Client username does not exist in Mapping, Please Add Token before adding holding");
                std::memcpy(response, &addholdingRes, sizeof(addholdingRes));
                return sizeof(addholdingRes);

            }
            TokenDetailMap_t &tokendetailmap = itr->second;
            auto itr2 = tokendetailmap.find(pAddHoldingReq->token);

            if (itr2 == tokendetailmap.end())
            {
                // errror return
                setError("Please Add Token Before adding holding");
                std::memcpy(response, &addholdingRes, sizeof(addholdingRes));
                return sizeof(addholdingRes);
            }
        }

        uint64_t new_total_qty = 0;
        uint64_t new_avg_price = 0;

        {
            std::lock_guard<std::mutex> lck(mtx_holding_map);

            HoldingDetailMap_t &holdingMap = g_map_holding_by_username[username];

            auto itr = holdingMap.find(pAddHoldingReq->token);

            if (itr == holdingMap.end())
            {
                // First holding for this token
                new_total_qty = pAddHoldingReq->qty;
                new_avg_price = pAddHoldingReq->price;

                HoldingDetail holdingdetail = {0};
                holdingdetail.avg_price = new_avg_price;
                holdingdetail.qty = new_total_qty;

                holdingMap[pAddHoldingReq->token] = holdingdetail;
            }
            else
            {
                // Existing holding
                HoldingDetail &holding = itr->second;

                uint64_t old_qty = holding.qty;
                uint64_t old_avg_price = holding.avg_price;

                uint64_t new_qty = pAddHoldingReq->qty;

                new_total_qty = old_qty + new_qty;

                // Avoid division by zero
                if (new_total_qty == 0)
                {
                    addholdingRes.isAdded = 0;
                    strncpy(addholdingRes.msg, "Invalid quantity", MESSAGE - 1);

                    std::memcpy(response, &addholdingRes, sizeof(addholdingRes));
                    return sizeof(addholdingRes);
                }

                
                long double total_value =static_cast<long double>(old_qty) * old_avg_price + static_cast<long double>(new_qty) * pAddHoldingReq->price;

                new_avg_price = static_cast<uint64_t>(total_value / new_total_qty);

                // Update holding
                holding.qty = new_total_qty;
                holding.avg_price = new_avg_price;
            }
        }

        addholdingRes.isAdded = 1;
        strncpy(addholdingRes.msg, "Holding Added Successfully", MESSAGE - 1);

        std::memcpy(response, &addholdingRes, sizeof(addholdingRes));
        return sizeof(addholdingRes);
    }
    break;
    default:
        break;
    }

    return 0;
}
