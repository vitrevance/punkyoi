#ifndef P_IIMAGE
#define P_IIMAGE

namespace punkyoi_api {
    
    class IImage {
    public:
        virtual ~IImage() = default;

        virtual uint8_t* getBuffer() = 0;
        virtual int getWidth() = 0;
        virtual int getHeight() = 0;
    };
}

#endif
