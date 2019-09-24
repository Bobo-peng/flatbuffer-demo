#include "city_generated.h"
#include <iostream>

int main()
{
    flatbuffers::FlatBufferBuilder build_data;

    // 序列化
    std::vector<flatbuffers::Offset<Location::City_Fb>> cityVector;
    auto city1 = Location::CreateCity_Fb(build_data, build_data.CreateString("Handan"), build_data.CreateString("0310"));
    auto city2 = Location::CreateCity_Fb(build_data, build_data.CreateString("Shijiazhuang"), build_data.CreateString("0311"));
    auto city3 = Location::CreateCity_Fb(build_data, build_data.CreateString("Baoding"), build_data.CreateString("0312"));
    auto city4 = Location::CreateCity_Fb(build_data, build_data.CreateString("Zhangjiakou"), build_data.CreateString("0313"));
    cityVector.push_back(city1);
    cityVector.push_back(city2);
    cityVector.push_back(city3);
    cityVector.push_back(city4);

    auto citys = build_data.CreateVector(cityVector);
    auto provice = Location::CreateProvice_Fb(build_data, citys);
    build_data.Finish(provice);
    std::cout<<"size:"<< build_data.GetSize() <<std::endl;
//=================================================================
    //保存起来(save)
    char buffer[1024] = {0};
    memcpy(buffer, build_data.GetBufferPointer(), build_data.GetSize());
    //modify some bytes
    memset(buffer+100, 0x00, sizeof(char)*50);
    //Verify
    flatbuffers::Verifier verifier = flatbuffers::Verifier((const uint8_t*)buffer, build_data.GetSize());
    if(!Location::VerifyProvice_FbBuffer(verifier))
    {
        std::cout<<"Verify failed!"<<std::endl;
        return -1;
    }
    std::cout<<"Verify success!"<<std::endl;
    //反序列化(parse)
    flatbuffers::FlatBufferBuilder builder_out;
    builder_out.PushBytes((const uint8_t*)buffer, 1024);
    auto city_out = Location::GetProvice_Fb(builder_out.GetCurrentBufferPointer());
    for (auto i = 0; i < city_out->city_list()->Length(); ++i)
    {
        std::string city_name = city_out->city_list()->Get(i)->city_name()->str();
        std::string area_code = city_out->city_list()->Get(i)->area_code()->str();
        std::cout << "city_name " << i << ":" + city_name << ",area_code " << i << ":" + area_code << std::endl;
    }
}
