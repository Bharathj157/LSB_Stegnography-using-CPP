#ifndef ENCODE_H
#define ENCODE_H
#include"common.h"
#include "types.h" // Contains user defined types

/* 
 * Structure to store information required for
 * encoding secret file to source Image
 * Info about output and intermediate data is
 * also stored
 */

#define MAX_SECRET_BUF_SIZE 1
#define MAX_IMAGE_BUF_SIZE (MAX_SECRET_BUF_SIZE * 8)
#define MAX_FILE_SUFFIX 5

class EncodeInfo
{
    private:
	char *src_image_fname;
	FILE * fptr_src_image;
	uint image_capacity;
	uint bits_per_pixel;
	char image_data[MAX_IMAGE_BUF_SIZE];


	char * secret_fname;
	FILE *fptr_secret;
	char extn_secret_file[MAX_FILE_SUFFIX];
	char secret_data[MAX_SECRET_BUF_SIZE];
	long size_secret_file;

	const char * stego_image_fname;
	FILE *fptr_stego_image;

	const char * password=MAGIC_STRING;

	/* Encoding function prototype */

	/* Get File pointers for i/p and o/p files */
	Status open_files();

	/* check capacity */
	Status check_capacity();

	/* Get image size */
	uint get_image_size_for_bmp(FILE *fptr_image);

	/* Get file size */
	uint get_file_size(FILE *fptr);

	/* Copy bmp image header */
	Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image);

	/* Store Magic String */
	Status encode_magic_string(const char * magic_string);

	/* Encode secret file extenstion */
	Status encode_secret_file_extn( char *file_extn);

	/* Encode secret file size */
	Status encode_secret_file_size(long file_size);

	/* Encode secret file data*/
	Status encode_secret_file_data();

	/* Encode function, which does the real encoding */
	Status encode_data_to_image(const char *data, int size, FILE *fptr_src_image, FILE *fptr_stego_image);

	/* Encode a byte into LSB of image data array */
	Status encode_byte_to_lsb(char data, char *image_buffer);


	Status encode_size_to_lsb(int data, char *image_buffer);

	/* Copy remaining image bytes from src to stego image after encoding */
	Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest);

    public:
	/* Perform the encoding */
	Status do_encoding();

	/* Check operation type */
        OperationType check_operation_type(char *argv[]);

        /* Read and validate Decode args from argv */
        Status read_and_validate_encode_args(char *argv[]);
};

#endif
