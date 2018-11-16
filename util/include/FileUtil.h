//
// Created by Xu Yi on 2018/11/13.
//

#ifndef COMMON4CPP_FILEUTIL_H
#define COMMON4CPP_FILEUTIL_H

#include <stdio.h>

namespace com {
    namespace picperweek {
        class FileUtil {

        private:
        public:

            /**
             * 获得文件大小
             * @param file
             * @return
             */
            static int get_file_size(FILE* file);

        };
    }
}


#endif //COMMON4CPP_FILEUTIL_H
