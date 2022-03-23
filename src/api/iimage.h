#ifndef P_IIMAGE
#define P_IIMAGE

namespace punkyoi_api {
    
    class IImage {
    public:
        virtual ~IImage() = default;

        virtual uint8_t* getBuffer() = 0;

        int width;
        int height;
    };
}

#endif
