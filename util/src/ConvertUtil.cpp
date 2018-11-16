//
// Created by Xu Yi on 2018/11/13.
//

#include <string>
#include <vector>
#include <math.h>

#include <UnicodeGBKMap.h>
#include "../include/ConvertUtil.h"

namespace com {
    namespace picperweek {

        /**
         * 二进制转换为数值
         * @param binary_str
         * @return
         */
        unsigned int ConvertUtil::binary_to_decimal(std::string binary_str) {
            const char *binary_char = binary_str.c_str();
            int i = 0, k = 0, sum = 0;
            while (binary_char[i++] != '\0') {
                i++;
            }
            i--;

            for (int j = i; j > 0; j--) {
                if (binary_char[k++] == '1')
                    sum += (unsigned int) pow(2, j - 1);
            }
            return sum;
        }

        /**
         * 数值转换为二进制
         * @param int_num
         * @return
         */
        std::string ConvertUtil::decimal_to_binary(unsigned int int_num) {

            std::string binary_str; //转换后的二进制存储为字符串，调用了默认构造函数初试化为空串

            while (int_num) {
                if (int_num & 0x01) {
                    binary_str += '1';
                } else {
                    binary_str += '0';
                }
                int_num >>= 1;//对正数右移，高位补0
            }

            reverse(binary_str.begin(), binary_str.end());

            std::string append_str = "";
            for (int j = 0; j < 8 - binary_str.length(); j++) {
                append_str += "0";
            }
            binary_str = append_str + binary_str;

            return binary_str;
        }

        /**
         * 获得中文字符的GBK编码值
         * @param s
         * @return
         */
        std::vector<unsigned char> ConvertUtil::gbk_encode(const std::string s) {
            std::string str = s;
            std::vector<unsigned char> buff;
            int len = str.length();
            buff.resize(len);
            memcpy(&buff[0], str.c_str(), len);
            return buff;
        }

        /**
         * 将GBK编码值解码成中文字段
         * @param buff
         * @return
         */
        std::string ConvertUtil::gbk_decode(std::vector<unsigned char> buff) {
            std::vector<unsigned char>debuf = buff;
            debuf.resize(buff.size() + 1);
            char* res = (char*) &debuf[0];
            std::string str = res;
            return str;
        }

        /**
         * GBK转码Unicode
         * @param gbk_code
         * @return
         */
        unsigned short int ConvertUtil::convert_gbk_to_unicode(unsigned short int gbk_code) {
            int i;
            for (i = 0; i < sizeof(unicode_to_gbk); ++i) {
                if (unicode_to_gbk[i].gbkcode == gbk_code) {
                    break;
                }
            }
            return unicode_to_gbk[i].unicode;
        }

        /**
         * GBK转码为UTF8
         * @param gbk_str
         * @return
         */
        std::string ConvertUtil::convert_gbk_to_utf8(std::string gbk_str) {
            std::string utf8_word = "";
            // 编码转换 输出原始数据编码 GBK
            int mo_size = 2;
            int unicode_index = 0;
            unsigned short int unicode_buffer[mo_size];
            for (int i = 0; i < gbk_str.length(); i++) {
                unsigned char item_c = gbk_str[i];
                unsigned int item_i = (unsigned int) item_c;
                unsigned short int item_i_s = (unsigned short int) item_c;

                if (item_i == 0x0000) {
                    // 判断是否是 //字符串结束符
                    break;
                }

                if (item_i < 0x80) {
                    // 判断是否小于 0x80
                    // 如果小于代表是 /*ASCII不用查表*/
                    utf8_word += item_c;
                    continue;
                } else {
                    int mo_index = unicode_index % mo_size;
                    unicode_buffer[mo_index] = item_i_s;

                    // 如果大于等于，则代表需要两个字符，进行转换
                    if (unicode_index != 0 && mo_index == 1) {
                        // 满足两个字符，将中文字符转换位二进制

                        unsigned short int high_num = unicode_buffer[0];
                        unsigned short int low_num = unicode_buffer[1];
                        unsigned short int gbk_code = high_num * 16 * 16 + low_num;

                        unsigned short int unicode = convert_gbk_to_unicode(gbk_code);

                        unsigned short int high_num_unicode = unicode / 16 / 16;
                        unsigned short int low_num_unicode = unicode % 256;

                        // 取高八位、低八位分别替代，三字节模板 1110yyyy 10yyyyxx 10xxxxxx
                        std::string high_binary_str = decimal_to_binary((unsigned int) high_num_unicode); // 需要补位
                        std::string low_binary_str = decimal_to_binary((unsigned int) low_num_unicode);   // 需要补位

                        std::string first_char = "1110" + high_binary_str.substr(0, 4);
                        std::string second_char = "10" + high_binary_str.substr(4, 7) + low_binary_str.substr(0, 2);
                        std::string thid_char = "10" + low_binary_str.substr(2, 7);

                        // 每四位转换为十六进制，然后再decode
                        unsigned int first_num = binary_to_decimal(first_char);
                        unsigned int second_num = binary_to_decimal(second_char);
                        unsigned int third_num = binary_to_decimal(thid_char);

                        std::vector<unsigned char> test_v;
                        test_v.push_back(first_num);
                        test_v.push_back(second_num);
                        test_v.push_back(third_num);

                        std::string utf8_str = gbk_decode(test_v);
                        utf8_word += utf8_str.c_str();
                        memset(unicode_buffer, 0, sizeof(unicode_buffer));
                    }
                    unicode_index++;
                }
            }
            return utf8_word;
        }

    }
}