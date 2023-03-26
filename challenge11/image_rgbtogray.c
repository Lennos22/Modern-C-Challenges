/* Created by: Nelson Cardona
 * Date/Time: 24-03-23/16:50
 * 
 * It turns out, Windows' Win32 API ALREADY contains functionality for processing and developing
 * graphics and formatted text called the Microsoft Windows graphics device interface (GDI):
 * 
 * https://learn.microsoft.com/en-us/windows/win32/api/_gdi/
 *
 * This also includes bitmaps, and most of this functionality for bitmaps is contained in the
 * wingdi.h header. The information of which can be found here:
 *
 * https://learn.microsoft.com/en-us/windows/win32/api/wingdi/
 *
 * A lot of the identifiers you see in this code have come about from studying this API.
 */
/* For strcasestr() */
#define _GNU_SOURCE
//#define NDEBUG

#include <tgmath.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <stddef.h>
#include <inttypes.h>
#include <assert.h>
#include <errno.h>
#include <stdbool.h>

#ifndef NDEBUG
#include <limits.h>
#endif

/* .bmp/.dip value offsets */
#define FILE_SIZE				0x02U
#define DATA_OFFSET				0x0AU
#define DIB_SIZE				0x0EU
#define WIDTH					0x12U
#define HEIGHT					0x16U
#define BITDEPTH				0x1CU
#define COMPRESSION				0x1EU

#define FILE_HEADER_SIZE		0x0EU
#define GRAY_BITDEPTH			0x18U

/* In the interest of time and effieciency, I chucked all Union-Find functionality below main.
 * Don't worry, this will be the last time I live without function prototypes and headers. I
 * did this out of principle, because we hadn't reached the point of headers and API. The book
 * doesn't even use function prototypes in this Level, it's so annoying.
 */
void init(size_t parent[], size_t size);
size_t Find(size_t parent[], size_t element);
size_t FindReplace(size_t parent[], size_t element, size_t new_parent);
size_t FindCompress(size_t parent[], size_t element);
void Union(size_t parent[], size_t parent_tree, size_t child_tree);

typedef struct PixelRegion {
	size_t nPixels;
	size_t sum;
} PixelRegion;

enum {	buf_max = 0x80000U,	/* 131,072 Bytes! */	};
/* Information on .bmp/.dib compression values was found here:
 * https://www.fileformat.info/format/bmp/egff.htm
 * Contains the compression type encoded by value of compression field in bitmap header
 */
enum {	BI_RGB = 0, BI_RLE8 = 1, BI_RLE4 = 2, BI_BITFIELDS = 3, BI_JPEG = 4, BI_PNG = 5, 	};
static char const*const comprsn_type[] = {
	[BI_RGB] = "no compression",
	[BI_RLE8] = "8bit RLE encoding",
	[BI_RLE4] = "4bit RLE encoding",
	[BI_BITFIELDS] = "bitfields encoding",
	[BI_JPEG] = "JPEG encoding",
	[BI_PNG] = "PNG encoding",
};
/* Information on bitmap header types can be found here:
 * https://learn.microsoft.com/en-us/windows/win32/gdi/bitmap-header-types
 * Contains the length in bytes of each header type as of BMP Version 5
 */
enum {	COREHEADER = 12, INFOHEADER = 40, V4HEADER = 108, V5HEADER = 124,	};
static char const*const header_type_str[] = {
	[COREHEADER] = "BITMAPCOREHEADER",
	[INFOHEADER] = "BITMAPINFOHEADER",
	[V4HEADER] = "BITMAPV4HEADER",
	[V5HEADER] = "BITMAPV5HEADER",
};
static char const bmp_str[] = ".bmp";
static char const gray_ext_str[] = "_gray";
static char const avg_ext_str[] = "_avg";

/* I consider 15-25 to be the sweet-stop b/w detail identification and form identification.
 * It also creates a really nice effect!
 */
static int const merge_threshold = 25;

/* Adapted from image_rgbtpgray.c in Priya Shah's repo: https://github.com/abhijitnathwani/image-processing
 */
int rgb_to_gray(char const* img_name, size_t buf_len, unsigned char px_buf[buf_len], int img_dim[static 2])
{
assert(img_name);
	FILE *fIn = fopen(img_name,"r");					//Input File name

	if (!fIn) {
		fprintf(stderr, "Can't open file \"%s\": ", img_name);
		perror(0);
		errno = 0;
		fclose(fIn);
		return EXIT_FAILURE;
	}

	int i,j,y;
	unsigned char file_header[FILE_HEADER_SIZE];
	ptrdiff_t img_name_len = strcasestr(img_name, bmp_str) - img_name;	// Length of img_name w/o extension

	char out_name[img_name_len+strlen(gray_ext_str)+strlen(bmp_str)+1];
	strncpy(out_name, img_name, img_name_len);				// Copy name w/o ".bmp" extension
	out_name[img_name_len] = '\0';
	strcat(out_name, gray_ext_str);
	strcat(out_name, bmp_str);

	FILE *fOut = fopen(out_name,"w+");		    		//Output File name

	if (!fOut) {
		fprintf(stderr, "Can't open file \"%s\": ", out_name);
		perror(0);
		errno = 0;
		fclose(fOut);
		fclose(fIn);
		return EXIT_FAILURE;
	}

	if (fread(file_header, sizeof(unsigned char), FILE_HEADER_SIZE, fIn) < FILE_HEADER_SIZE) {
		fprintf(stderr, "Not enough bytes were read from bmp file_header...\n");
		perror(0);
		errno = 0;
		fclose(fOut);
		fclose(fIn);
		return EXIT_FAILURE;
	}

	fwrite(file_header,sizeof(unsigned char),FILE_HEADER_SIZE,fOut);					//write the file_header back

	// Inspect Data Offset
	uint32_t DataOffset = *(uint32_t*)&file_header[DATA_OFFSET];
	size_t bmp_header_len = DataOffset - FILE_HEADER_SIZE;

	uint8_t bmp_header[bmp_header_len];				// Grabs the bmp header (and color table, if applicable)

	if (fread(bmp_header, sizeof(uint8_t), bmp_header_len, fIn) < bmp_header_len) {
		fprintf(stderr, "Not enough bytes were read from DIB and Color Table...\n");
		perror(0);
		errno = 0;
		fclose(fOut);
		fclose(fIn);
		return EXIT_FAILURE;
	}

	// Inspect DIB size
	uint32_t DIB_size = *(uint32_t*)&bmp_header[DIB_SIZE-FILE_HEADER_SIZE];
assert(header_type_str[DIB_size]);
	printf("DIB header type is: %s\n", header_type_str[DIB_size]);

	// extract image height, width and bitDepth from imageHeader (+ Compression Type)
	int height = *(int*)&bmp_header[HEIGHT-FILE_HEADER_SIZE];
	int width = *(int*)&bmp_header[WIDTH-FILE_HEADER_SIZE];
	uint16_t bitDepth = *(uint16_t*)&bmp_header[BITDEPTH-FILE_HEADER_SIZE];
	uint32_t compression = *(uint32_t*)&bmp_header[COMPRESSION-FILE_HEADER_SIZE];

	printf("width: %d\n",width);
	printf("height: %d\n",height );
	printf("bitDepth (Bits Per Pixel): %" PRIu16 "\n", bitDepth);
	printf("compression: %s\n", comprsn_type[compression]);

assert(!(bmp_header_len - DIB_size));								// I honestly do not have the capacity to
assert(compression == BI_RGB);									// deal with either of these, atm

	/* Ensures that output file is 24bit RGB */
	if (bitDepth != GRAY_BITDEPTH) {
		bmp_header[BITDEPTH-FILE_HEADER_SIZE+1] = 0;							// It's Little Endian
		bmp_header[BITDEPTH-FILE_HEADER_SIZE] = (uint8_t) GRAY_BITDEPTH;		// Trust me, bro...
	}

	fwrite(bmp_header, sizeof(uint8_t), bmp_header_len, fOut);

	int size = height*width;									//calculate image size

	/* Determine if size is within buf_max */
	if (size > buf_max) {
		fprintf(stderr, "Image size is too large to store atm...\n");
		fclose(fIn);
		fclose(fOut);
		return EXIT_FAILURE;
	}

	img_dim[0] = width;
	img_dim[1] = height;

	size_t px_size = bitDepth < 8 ? 1 : bitDepth / 8;
	unsigned char buffer[px_size];						//to store the image data
	
	size_t red = px_size - 3;
	size_t green = px_size - 2;
	size_t blue = px_size - 1;
	/* Rows must be padded at the end to ensure their length is a multiple of 4 bytes */
	size_t padding = (4 - ((px_size*width)%4)) % 4;				// Number of bytes to pad img row

assert(!((padding + px_size*width) % 4));
			
	printf("Drawing grayscaled image into file: \"%s\"\n", out_name);
	for(i=0;i<size;i++)											//RGB to gray
	{
		y=0;
/*		buffer[i][2]=getc(fIn);									//blue
		buffer[i][1]=getc(fIn);									//green
		buffer[i][0]=getc(fIn);		*/							//red

		/* NOTE: From MSB->LSB, we have - blue, green, red, alpha */
		for (j = px_size-1; j >= 0 ; --j)
			buffer[j] = getc(fIn);
			
		y=(buffer[red]*0.3) + (buffer[green]*0.59)	+ (buffer[blue]*0.11);			//conversion formula of rgb to gray
		px_buf[i] = y;

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
				fclose(fOut);
				fclose(fIn);
				return EXIT_FAILURE;
			}
			fwrite(pad_buf, sizeof(uint8_t), padding, fOut);
		}
	}
	
	fclose(fOut);
	fclose(fIn);

	return EXIT_SUCCESS;
}

void calcStatistic(PixelRegion segments[], size_t dest_root, size_t src_root) {
	segments[dest_root].nPixels += segments[src_root].nPixels;
	segments[dest_root].sum += segments[src_root].sum;
}

bool canMerge(size_t parent[], size_t elem1, size_t elem2, PixelRegion segments[], size_t merge_threshold) {
	size_t root1 = Find(parent, elem1);
	size_t root2 = Find(parent, elem2);
	if (root1 == root2) return false;

	double reg1_mean = ((double) segments[root1].sum) / ((double) segments[root1].nPixels);
	double reg2_mean = ((double) segments[root2].sum) / ((double) segments[root2].nPixels);

	return fabs(reg1_mean - reg2_mean) <= merge_threshold;
}

void mergeSegments(size_t parent[], size_t dest, size_t src, PixelRegion segments[]) { assert(Find(parent, dest) != Find(parent, src));
	size_t old_root = Find(parent, src);
	Union(parent, dest, src);
	calcStatistic(segments, Find(parent, dest), old_root);
}

bool passThrough(size_t nElem, size_t parent[nElem], PixelRegion segments[nElem], int img_dim[static 2], size_t merge_threshold) {
	bool hasMerged = false;

	for (size_t i = 0; i < nElem; ++i) {
		if ((i % img_dim[0]) && canMerge(parent, i-1, i, segments, merge_threshold)) {
			mergeSegments(parent, i-1, i, segments);
			hasMerged = true;
		}
		if ((i < img_dim[0]*(img_dim[1]-1)) && canMerge(parent, i+img_dim[0], i, segments, merge_threshold)) {
			mergeSegments(parent, i+img_dim[0], i, segments);
			hasMerged = true;
		}
	}

	return hasMerged;
}

unsigned char getSegmentAvg(size_t parent[], size_t pixel, PixelRegion segments[]) {
	size_t root = Find(parent, pixel);
	double avg = ((double) segments[root].sum) / ((double) segments[root].nPixels);

	assert((unsigned char) avg <= UCHAR_MAX);

	return (unsigned char) avg;
}

void generateAvgImg(char const* img_name, size_t nElem, size_t parent[nElem], PixelRegion segments[nElem]) {
	FILE* instream = fopen(img_name, "r");
	unsigned char file_header[FILE_HEADER_SIZE] = {0};
	
	fread(file_header, sizeof(unsigned char), FILE_HEADER_SIZE, instream);

	uint32_t DataOffset = *(uint32_t*)&file_header[DATA_OFFSET];
	size_t bmp_header_size = DataOffset - FILE_HEADER_SIZE;
	
	unsigned char bmp_header[bmp_header_size];

	fread(bmp_header, sizeof(unsigned char), bmp_header_size, instream);

	uint32_t width = *(uint32_t*)&bmp_header[WIDTH - FILE_HEADER_SIZE];
	uint16_t bitDepth = *(uint16_t*)&bmp_header[BITDEPTH - FILE_HEADER_SIZE];
	
	if (bitDepth != GRAY_BITDEPTH) {
		bmp_header[BITDEPTH-FILE_HEADER_SIZE+1] = 0;							// It's Little Endian
		bmp_header[BITDEPTH-FILE_HEADER_SIZE] = (unsigned char) GRAY_BITDEPTH;		// Trust me, bro...
	}

	ptrdiff_t img_name_len = strcasestr(img_name, bmp_str) - img_name;	// Length of img_name w/o extension
	/* The absolute physical max merge_threshold could be is 256, but even anything close to 100 is
	 * already ridiculous!
	 */
	char thresh_str[4] = {0};
	snprintf(thresh_str, 4, "%d", merge_threshold);
	/* This variable was generated RIGHT NEXT to bmp_header so MAKE SURE YOU ALLOCATE CORRECT MEMORY!!! */
	char out_name[img_name_len+strlen(avg_ext_str)+strlen(thresh_str)+strlen(bmp_str)+1];

	strncpy(out_name, img_name, img_name_len);				// Copy name w/o ".bmp" extension
	out_name[img_name_len] = '\0';
	strcat(out_name, avg_ext_str);
	strcat(out_name, thresh_str);
	strcat(out_name, bmp_str);


	printf("Drawing grayscale AVERAGE into file: \"%s\"\n", out_name);
	FILE* outstream = fopen(out_name, "w");

	assert((FILE_HEADER_SIZE + bmp_header_size) == DataOffset);

	fwrite(file_header, sizeof(unsigned char), FILE_HEADER_SIZE, outstream);
	fwrite(bmp_header, sizeof(unsigned char), bmp_header_size, outstream);

#ifndef NDEBUG
uint32_t height = *(uint32_t*)&bmp_header[HEIGHT - FILE_HEADER_SIZE];
size_t image_size = width*height;
#endif
	size_t px_size = GRAY_BITDEPTH/8;
	size_t padding = (4 - ((px_size*width)%4)) % 4;				// Number of bytes to pad img row

	assert(nElem == image_size);
	assert(!((px_size*width + padding) % 4));

	for (size_t i = 0; i < nElem; ++i) {
		unsigned char pixel_data = getSegmentAvg(parent, i, segments);

		putc(pixel_data,outstream);
		putc(pixel_data,outstream);
		putc(pixel_data,outstream);

		/* Padding the rows */
		if (!((i+1) % width)) {
			unsigned char pad_buf[padding];
			fwrite(pad_buf, sizeof(unsigned char), padding, outstream);
		}
	}

	fclose(instream);
	fclose(outstream);
}

int main(int argc, char* argv[argc+1]) {
	int ret = EXIT_FAILURE;
	unsigned char px_buf[buf_max] = {0};

	for (int i = 1; i < argc; ++i) {
		printf("Processing image file: \"%s\"\n", argv[i]);
		int img_dim[2] = {0};
		int result = rgb_to_gray(argv[i], buf_max, px_buf, img_dim);
		if (result == EXIT_SUCCESS) {
			printf("Grayscaling complete! Moving on to image segmentation...\n");
			printf("Averaging image segments using a threshold value of %d\n", merge_threshold);
			size_t nPixels = img_dim[0] * img_dim[1];
			size_t parent[nPixels];
			init(parent, nPixels);
			PixelRegion segments[nPixels];
			for (size_t j = 0; j < nPixels && j < nPixels; ++j) {
				segments[j].nPixels = 1;
				segments[j].sum = px_buf[j];
			}
			size_t num_passes = 1;
			while (passThrough(nPixels, parent, segments, img_dim, merge_threshold)) {
				printf("Completed pass through #%zu\n", num_passes);
				++num_passes;
			}
			printf("Averaging completed after %zu passes!\n", num_passes);
			generateAvgImg(argv[i], nPixels, parent, segments);
			printf("Image processing of file \"%s\"  complete!\n\n", argv[i]);
			ret = EXIT_SUCCESS;
		}
	}
	
	return ret;
}

/* The below functions were taken from Challenge 4 which are for Union-Find */
/* Initialization of index table */
void init(size_t parent[], size_t parent_size) {
		/* Set all elements as singletons */
		for (size_t i = 0; i < parent_size; ++i)
				parent[i] = SIZE_MAX;
}

size_t Find(size_t parent[], size_t element) {
		if (parent[element] != SIZE_MAX)
				return Find(parent, parent[element]);
		return element;
}

size_t FindReplace(size_t parent[], size_t element, size_t new_parent) {
		size_t old_parent = parent[element];
		parent[element] = new_parent;
		if (old_parent != SIZE_MAX) {
				return FindReplace(parent, old_parent, new_parent);
		}
		return element;
}

size_t FindCompress(size_t parent[], size_t element) {
		if (parent[element] != SIZE_MAX) {
				parent[element] = FindCompress(parent, parent[element]);
				return parent[element];
		}
		return element;
}

void Union(size_t parent[], size_t parent_tree, size_t child_tree) {
		if (Find(parent, parent_tree) == Find(parent, child_tree)) {
				printf("Invalid union: Both elements are in the same set.\n");
				return;
		}

		FindReplace(parent, child_tree, FindCompress(parent, parent_tree));
}
