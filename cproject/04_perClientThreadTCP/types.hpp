#include<unordered_map>
#include<cinttypes>
#include<common_struct.hpp>
#include<string>


// Token Related DS type
using TokenDetailMap_t=std::unordered_map<uint32_t,TokenDetail>;
using TokenByUserNameMap_t=std::unordered_map<std::string,TokenDetailMap_t>;