/*get_number c file*/
#include "get_number-lib.h"


int main(int argc, char *argv[])
{
    if(argc == 1) {
      printf("usage: ./get_number [number]\nexample: ./get_number 24\n");
      return 0;
    }
    run_get_number(argv[1], "key.txt", stdout);
    return 0;
}
