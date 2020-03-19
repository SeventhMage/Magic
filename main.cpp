#include "include/magic.h"

#include <iostream>

using namespace std;
using namespace magic;
int main(int argc, char *argv[])
{
    IMagic *mc = GetMagic();
    cout << "Start initalize Engine ... " << endl;
    mc->InitEngine();
    cout << "Finish initalize Engine." << endl;
    cout << "Start Application ... " << endl;
    mc->StartApplication();
    cout << "Application end." << endl;
    cout << "Cleaning ... " << endl;
    Clean();
    cout << "Finish clean." << endl;
    return 0;
}