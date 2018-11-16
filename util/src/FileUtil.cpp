//
// Created by Xu Yi on 2018/11/13.
//

#include "FileUtil.h"

namespace com {
    namespace picperweek {



        /**
         * 获得文件大小
         * @param file
         * @return
         */
        int FileUtil::get_file_size(FILE* file) {
            int seekErr = fseek(file, 0, SEEK_END);
            if(seekErr == EOF){
                return -1;
            }
            return ftell(file);
        }
    }
}