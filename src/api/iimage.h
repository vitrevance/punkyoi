#pragma once

namespace punkyoi_api {
    
    class IImage {
    public:
        virtual ~IImage() = 0;

        virtual char* getBuffer();

        int width;
        int height;
    };
}