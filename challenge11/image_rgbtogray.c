/* Created by: Nelson Cardona
 * Date/Time: 24-03-23/16:50
 */
/* For strcasestr() */
#define _GNU_SOURCE

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <stddef.h>
#include <inttypes.h>
#include <assert.h>
#include <errno.h>

/* .bmp/.dip value offsets */
#define FILE_SIZE				0x02U
#define DATA_OFFSET				0x0AU
#define DIB_SIZE				0x0EU
#define WIDTH					0x12U
#define HEIGHT					0x16U
#define BITDEPTH				0x1CU
#define COMPRESSION				0x1EU

#define BMP_HEADER_SIZE			0x0EU
#define GRAY_BITDEPTH			0x18U

enum {	BI_RGB = 0, BI_RLE8 = 1, BI_RLE4 = 2, BITFIELDS = 3, 	};

/* Information on .bmp/.dib compression values was found here:
 * https://www.fileformat.info/format/bmp/egff.htm
 */
static char const*const comprsn_type[] = {
	[BI_RGB] = "no compression",
	[BI_RLE8] = "8bit RLE encoding",
	[BI_RLE4] = "4bit RLE encoding",
	[BITFIELDS] = "bitfields encoding",
};
static char const bmp_str[] = ".bmp";
static char const new_extension[] = "_gray";

/* Adapted from image_rgbtpgray.c in Priya Shah's repo: https://github.com/abhijitnathwani/image-processing
 */
int rgb_to_gray(char const* img_name)
{
assert(img_name);
	FILE *fIn = fopen(img_name,"r");					//Input File name

	if (!fIn) {
		fprintf(stderr, "Can't open file \"%s\": ", img_name);
		perror(0);
		errno = 0;
		return EXIT_FAILURE;
	}

	int i,j,y;
	unsigned char header[BMP_HEADER_SIZE];
	ptrdiff_t img_name_len = strcasestr(img_name, bmp_str) - img_name;	// Length of img_name w/o extension

#ifndef NDEBUG
printf("Length of image file name w/o extension is: %td\n", img_name_len);
#endif

	char out_name[img_name_len+1];
	strncpy(out_name, img_name, img_name_len);				// Copy name w/o ".bmp" extension
	out_name[img_name_len] = '\0';
	strcat(out_name, new_extension);
	strcat(out_name, bmp_str);

#ifndef NDEBUG
printf("Output file name will be: %s\n", out_name);
#endif

	FILE *fOut = fopen(out_name,"w+");		    		//Output File name

	if (!fOut) {
		fprintf(stderr, "Can't open file \"%s\": ", out_name);
		perror(0);
		errno = 0;
		return EXIT_FAILURE;
	}

	if (fread(header, sizeof(unsigned char), BMP_HEADER_SIZE, fIn) < BMP_HEADER_SIZE) {
		fprintf(stderr, "Not enough bytes were read from bmp header...\n");
		perror(0);
		errno = 0;
		return EXIT_FAILURE;
	}

	fwrite(header,sizeof(unsigned char),BMP_HEADER_SIZE,fOut);					//write the header back

	// Inspect Data Offset
	uint16_t DataOffset = *(uint16_t*)&header[DATA_OFFSET];
	size_t DIBct_len = DataOffset - BMP_HEADER_SIZE;

#ifndef DEBUG
printf("DataOffset: %" PRIu16 "\n", DataOffset);
printf("So, length of DIB + Color Table is: %zu\n", DIBct_len);
#endif

	uint8_t DIBct[DIBct_len];

	if (fread(DIBct, sizeof(uint8_t), DIBct_len, fIn) < DIBct_len) {
		fprintf(stderr, "Not enough bytes were read from DIB and Color Table...\n");
		perror(0);
		errno = 0;
		return EXIT_FAILURE;
	}

	// Inspect DIB size
	uint32_t DIB_size = *(uint32_t*)&DIBct[DIB_SIZE-BMP_HEADER_SIZE];

#ifndef DEBUG
printf("DIB_size: %" PRIi32 "\n", DIB_size);
#endif

	// extract image height, width and bitDepth from imageHeader (+ Compression Type)
	int height = *(int*)&DIBct[HEIGHT-BMP_HEADER_SIZE];
	int width = *(int*)&DIBct[WIDTH-BMP_HEADER_SIZE];
	uint16_t bitDepth = *(uint16_t*)&DIBct[BITDEPTH-BMP_HEADER_SIZE];
	uint32_t compression = *(uint32_t*)&DIBct[COMPRESSION-BMP_HEADER_SIZE];

	printf("width: %d\n",width);
	printf("height: %d\n",height );
	printf("bitDepth (Bits Per Pixel): %" PRIu16 "\n", bitDepth);
	printf("compression: %s\n", comprsn_type[compression]);

assert(!(DIBct_len - DIB_size));								// I honestly do not have the capacity to
assert(compression == BI_RGB);					// deal with either of these, atm

	/* Ensures that output file is 24bit RGB */
	if (bitDepth != GRAY_BITDEPTH) {
		DIBct[BITDEPTH-BMP_HEADER_SIZE+1] = 0;							// It's Little Endian
		DIBct[BITDEPTH-BMP_HEADER_SIZE] = (uint8_t) GRAY_BITDEPTH;		// Trust me, bro...
#ifndef NDEBUG
printf("New bitDepth has been set to: %" PRIu16 "\n", *(uint16_t*)&DIBct[BITDEPTH-BMP_HEADER_SIZE]);
#endif
	}

assert(*(uint16_t*)&DIBct[BITDEPTH-BMP_HEADER_SIZE] == GRAY_BITDEPTH);

	fwrite(DIBct, sizeof(uint8_t), DIBct_len, fOut);

	int size = height*width;									//calculate image size

	size_t px_size = bitDepth < 8 ? 1 : bitDepth / 8;
	unsigned char buffer[size][px_size];						//to store the image data
	
	size_t red = px_size - 3;
	size_t green = px_size - 2;
	size_t blue = px_size - 1;
	/* Rows must be padded at the end to ensure their length is a multiple of 4 bytes */
	size_t padding = (4 - ((px_size*width)%4)) % 4;						// Number of bytes to pad img row

#ifndef NDEBUG
printf("Indices are: red = %zu, green = %zu, blue = %zu\n", red, green, blue);
printf("Padding is %zu bytes\n", padding);
#endif

assert(!((padding + px_size*width) % 4));
			
	for(i=0;i<size;i++)											//RGB to gray
	{
		y=0;
/*		buffer[i][2]=getc(fIn);									//blue
		buffer[i][1]=getc(fIn);									//green
		buffer[i][0]=getc(fIn);		*/							//red

		/* NOTE: From MSB->LSB, we have - blue, green, red, alpha */
		for (j = px_size-1; j >= 0 ; --j)
			buffer[i][j] = getc(fIn);
			
		y=(buffer[i][red]*0.3) + (buffer[i][green]*0.59)	+ (buffer[i][blue]*0.11);			//conversion formula of rgb to gray

		putc(y,fOut);
		putc(y,fOut);
		putc(y,fOut);

		/* Padding the rows */
		if (!((i+1) % width)) {
			uint8_t pad_buf[padding];
			if (fread(pad_buf, sizeof(uint8_t), padding, fIn) < padding) {
				fprintf(stderr, "Padding is too large...\n");
				perror(0);
				errno = 0;
				return EXIT_FAILURE;
			}
			for (size_t z = 0; z < padding; ++z)
				pad_buf[z] = 0;
			fwrite(pad_buf, sizeof(uint8_t), padding, fOut);
		}
	}
	
	fclose(fOut);
	fclose(fIn);

	return 0;
}

int main(int argc, char* argv[argc+1]) {
	int ret = EXIT_FAILURE;

	for (int i = 1; i < argc; ++i) {
		ret = rgb_to_gray(argv[i]);
	}
	
	return ret;
}
