#include "../include/magic.h"

#include <stdio.h>

using namespace magic;
int main(int argc, char *argv[])
{
    IMagic *mc = GetMagic();
    printf("Start initalize Engine ... \n");
    mc->InitEngine();
    printf("Finish initalize Engine.\n");
    printf("Start Application ... \n");
    mc->StartApplication();
    printf("Application end.\n");
    printf("Cleaning ... \n");
    Clean();
    printf("Finish clean.\n");
    return 0;
}