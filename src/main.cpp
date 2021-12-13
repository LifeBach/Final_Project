#include "headers.h"
#include "parser.h"

int main(int argc, char *argv[])
{
    char *input_file = argv[1];
    const GlobalVar kGlobalVar = parser(input_file);
}