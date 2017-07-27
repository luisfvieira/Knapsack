#include <stdio.h>

int main(int argc, char const *argv[])
{
    //  A argument is necessary to specify the file and time limit
    if (argc < 3) {
        printf("Error\nShould provide a file as argument and a time limit.\n");
        exit(1);
    }
    return 0;
}
