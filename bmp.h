#ifndef _BMP_H_
#define _BMP_H_
#include<string>

using namespace std;

// ==================================================================================================
// Constants
// ==================================================================================================
const int BITMAP_FILE_HEADER_SIZE = 14;
const int BITMAP_INFO_HEADER_SIZE = 40;
const int BITMAP_HEADER_SIZE = BITMAP_FILE_HEADER_SIZE + BITMAP_INFO_HEADER_SIZE;
const int COLOR_TABLE_SIZE = 1024;

// ==================================================================================================
// Enums
// ==================================================================================================
// 14 Bytes of File header
typedef enum en_bitmap_file_header_tag
{
    SIGNATURE = 0,
    FILE_SIZE = 2,
    FILE_HEADER_RESERVED = 6,
    DATA_OFFSET = 10
}en_bitmap_file_header_t;

// 40 Bytes of Info header
typedef enum en_bitmap_info_header_tag
{
    INFO_HEADER_SIZE = 14,
    WIDTH = 18,
    HEIGHT = 22,
    PLANES = 26,
    BITS_PER_PIXEL = 28,
    COMPRESSION_TYPE = 30,
    COMPRESSED_IMAGE_SIZE = 34,
    X_PIXELS_PER_METER = 38,
    Y_PIXELS_PER_METER = 42,
    COLORS_USED = 46,
    IMPORTANT_COLORS = 50,
    RED_INTENSITY = 51,
    GREEN_INTENSITY = 52,
    BLUE_INTENSITY = 53,
    INFO_HEADER_RESERVED = 54
}en_bitmap_info_header_t;

// Bits per Pixel used to store palette entry information. 
// This also identifies in an indirect way the number of possible colors. 
// Possible values are:
typedef enum bits_per_pixel_tag
{
    MONOCHROME = 1,
    BITS_4_PALLETIZED = 4,
    BITS_8_PALLETIZED = 8,
    BITS_16_RGB = 16,
    BITS_24_RGB = 24
}bits_per_pixel_t;

typedef enum compression_type_tag
{
    COMPRESSION_RGB = 0,
    COMPRESSION_RLE8 = 1,
    COMPRESSION_RLE4 = 2
}compression_type_t;

// ==================================================================================================
// Structures
// ==================================================================================================
typedef struct bitmap_file_header_tag
{
    short signature;                //specifies the file type. "BM" - for BitMap
    int fileSize;                   //specifies the size in bytes of the bitmap file
    int reserved;                   //reserved; must be 0
    int dataOffset;                 //species the offset in bytes from the bitmapfileheader to the bitmap bits
}bitmap_file_header_t;

typedef struct bitmap_info_header_tag
{
    int infoHeaderSize;             //specifies the number of bytes required by the struct
    int width;                      //specifies width in pixels
    int height;                     //species height in pixels
    short planes;                   //specifies the number of color planes, must be 1
    short bitsPerPixel;             //specifies the number of bit per pixel
    int compressionType;            //spcifies the type of compression
    int compressedImageSize;        //size of image in bytes
    int xPixelsPerMeter;            //number of pixels per meter in x axis
    int yPixelsPerMeter;            //number of pixels per meter in y axis
    int colorsUsed;                 //number of colors used by th ebitmap
    int importantColors;            //number of colors that are important
    char redIntensity;
    char greenIntensity;
    char blueIntensity;
}bitmap_info_header_t;


// ==================================================================================================
// BitmapImage class definition
// ==================================================================================================
class BitmapImage
{
private:
    FILE *m_inputFilePointer;                   // Image file pointer
    std::string m_imagePath;                    // Image path

    char *m_bitmapHeaderChar;                   // Character array of the entire bitmap header - 54 bytes
    unsigned char *m_bitmapImageChar;           // Character array of the entire bitmap image pixels

    char *m_modifiedBitmapHeaderChar;           // Modified Character array of the entire bitmap header - 54 bytes
    unsigned char *m_modifiedBitmapImageChar;   // Modified Character array of the entire bitmap image pixels

    bitmap_file_header_t *m_bitmapFileHeader;   // File header structure
    bitmap_info_header_t *m_bitmapInfoHeader;   // Info header structure

    int m_imageSize;                            // Size of image- (width x height)
    int m_modifiedImageSize;                    // Size of modified image


public:
    BitmapImage(const char *imagePath);
    ~BitmapImage();
    char * LoadBitmapHeader();
    bitmap_file_header_t* LoadBitmapFileImageHeader();
    bitmap_info_header_t* LoadBitmapInfoImageHeader();
    unsigned char *LoadBitmapImagePixels();
    char* getBitsPerPixelInfoFromNumber(short val);
    char* getBitsCompressionTypeFromNumber(int val);
    string getSignatureString();
    void displayImageDetails();
    void displayImagePixels();
    int writeModifiedImageDataToFile(const char *outputFilePath);
};


#endif