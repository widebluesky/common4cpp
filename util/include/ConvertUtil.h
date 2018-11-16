//
// Created by Xu Yi on 2018/11/13.
//

#ifndef COMMON4CPP_CONVERTUTIL_H
#define COMMON4CPP_CONVERTUTIL_H

#include <string>

namespace com {
    namespace picperweek {

        class ConvertUtil {
        private:
        public:

            /**
             * 二进制转数值
             * @param binary_str
             * @return
             */
            static unsigned int binary_to_decimal(std::string binary_str);

            /**
             * 数值转二进制
             * @param int_num
             * @return
             */
            static std::string decimal_to_binary(unsigned int int_num);

            /**
             * 获得中文字符的GBK编码值
             * @param s
             * @return
             */
            static std::vector<unsigned char> gbk_encode(const std::string s);

            /**
             * 将GBK编码值解码成中文字段
             * @param buff
             * @return
             */
            static std::string gbk_decode(std::vector<unsigned char> buff);

            /**
             * GBK转码Unicode
             * @param gbk_code
             * @return
             */
            static unsigned short int convert_gbk_to_unicode(unsigned short int gbk_code);

            /**
            * GBK转码为UTF8
            * @param gbk_str
            * @return
            */
            static std::string convert_gbk_to_utf8(std::string gbk_str);

        };
    }
}

#endif //COMMON4CPP_CONVERTUTIL_H
