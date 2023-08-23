
typedef enum sur_compression{ /// an identifier for image compression algorithm
	SUR_COMPRESSION_NOT_SPECIFIED, /// no specified compression algorithm
	SUR_NO_COMPRESSION,///no compression algorithm used
	SUR_COMPRESSION_RLE8,/// 8-bit RLE encoding
	SUR_COMPRESSION_RLE4,/// 4-bit RLE encoding
}sur_compression_t;

typedef enum sur_file_format{
	SUR_FILE_FORMAT_BMP,
	SUR_FILE_FORMAT_JPG,
	SUR_FILE_FORMAT_JPEG,
	SUR_FILE_FORMAT_PNG,// add more file formats as neccessary
}sur_file_format_t;
