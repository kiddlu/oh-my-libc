#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#if 0 //for reverse
void memdump(void *addr, uint32_t size)
{
    int index;
    
    while (size > 0) {
        //fprintf(stdout, "%p: ", addr);
        index = 0;

        // 32 bytes in the line
        while (index < 32) {
            fprintf(stdout, "0x%02x,", *((unsigned char *)addr));
            
            index++;
            addr++;
            size--;
 
            if (size <= 0)
                break;
        }
        //fprintf(stdout, "\n");
    }
    fprintf(stdout, "\n");
    return;
}
#endif


void print_hex(unsigned char str[], unsigned int len)
{
    int idx;

    for(idx = 0; idx < len; idx++)
        printf("%02x", str[idx]);
}

void memdump(void *addr, uint32_t size)
{
    int index;
    
    while (size > 0) {
        fprintf(stdout, "%p: ", addr);
        index = 0;

        // 32 bytes in the line
        while (index < 32) {
            fprintf(stdout, "%02x ", *((unsigned char *)addr));
            
            index++;
            addr++;
            size--;
 
            if (size <= 0)
                break;
        }
        fprintf(stdout, "\n");
    }
    fprintf(stdout, "\n");
    return;
}

unsigned int get_file_size(FILE *fp)
{
    unsigned int length;

    fseek(fp, 0L, SEEK_END);
    length = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    return length;
}

void usage(void)
{
	printf("useage: file\n");
}

int main(int argc, char* argv[])
{
    if(argc != 2) {
        usage();
        return -1;
    } else if ( 0 != access(argv[1], F_OK)) {
		usage();
		return -1;
	}

	FILE *fp = fopen(argv[1], "rb");
    uint32_t len = get_file_size(fp);

    char *data = malloc(len);
    fread(data, len, 1, fp);
	
	printf("\n");
	printf("hexdump of file %s (%d bytes):\n", argv[1], len);

    memdump(data, len);
    return 0;
}
