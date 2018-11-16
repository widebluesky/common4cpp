#include <iostream>
#include <string>

#include <common4cpp>

using namespace com::picperweek;

int main() {

    std::string binary_str = ConvertUtil::decimal_to_binary(200);
    unsigned int int_num = ConvertUtil::binary_to_decimal(binary_str);

    std::string gbk_str = "gbk_str";

    std::string utf8_str = ConvertUtil::convert_gbk_to_utf8(gbk_str);

    printf("binary_str: %s \n", binary_str.c_str());
    printf("int_num: %d \n", int_num);

    return 0;
}