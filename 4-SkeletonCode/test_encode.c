#include <stdio.h>
#include "encode.h"
#include "decode.h"
#include "types.h"


// gcc *.c
// ./a.out -e beautiful.bmp secret.txt output.bmp \0
// ./a.out -e beautiful.bmp secret.txt \0

int main(int argc,char *argv[])
{
    EncodeInfo encInfo;
    DecodeInfo decInfo;

    if(argc == 1){
        printf("./a.out -e source_file.bmp secret_file.txt [output_file.bmp]\n");
        printf("./a.out -d stego.bmp [decoded.txt]\n");
        return 1;
    }
    
    OperationType op = check_operation_type(argv[1][1]);

    if(op == e_encode){
        
        if(read_and_validate_encode_args(argv,&encInfo) == e_failure)
            return e_failure;
        else{
            if(do_encoding(&encInfo) == e_success)
                printf("Encoding is success\n");
        }
    }

    else if(op == e_decode){
        if(read_and_validate_decode_args(argv,&decInfo) == e_failure)
            return e_failure;
        else{
            if(do_decoding(&decInfo) == e_success)
                printf("Decoding is success\n");
        }
    }

    return 0;
}


OperationType check_operation_type(char opt)
{
    if(opt == 'e')
        return e_encode;
    else if(opt == 'd')
        return e_decode;
    else{
        printf("Invalid option\n");
        printf("./a.out -e source_file.bmp secret_file.txt [output_file.bmp]\n");
        printf("./a.out -d stego.bmp [decoded.txt]\n");
        return e_unsupported;
    }
}