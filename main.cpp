#include<iostream>
#include<stdio.h>
#include<assert.h>
#include "bmp.h"

using namespace std;

const char* INPUT_IMAGE_PATH = "C:\\Users\\m0pxnn\\Desktop\\ImageTestFiles\\img6.bmp";
const char* OUTPUT_IMAGE_PATH = "C:\\Users\\m0pxnn\\Desktop\\ImageTestFiles\\img6_modified.bmp";

//******************************************************************************************
// M A I N - for testing purpose.
//******************************************************************************************
int main()
{
    int retval = -1;
    
    {
        BitmapImage bmpImage(INPUT_IMAGE_PATH);

        bmpImage.displayImageDetails();
        bmpImage.displayImagePixels();
        //retval = bmpImage.modify1();
        if (retval != 0)
        {
            printf("\nERROR: Image modification failed!\n");
        }

        printf("\nWriting to file...\n");
        retval = bmpImage.writeModifiedImageDataToFile(OUTPUT_IMAGE_PATH);
        if (retval != 0)
        {
            printf("\n>> Failed to create %s\n", OUTPUT_IMAGE_PATH);
        }
        else
        {
            printf("\n>> Created %s\n", OUTPUT_IMAGE_PATH);
        }

    }//Scope of BitmapImage object ends here

    getchar();
    return 0;
}