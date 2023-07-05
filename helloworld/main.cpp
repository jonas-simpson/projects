#include <iostream>
#include <vector>
#include <string>

#include "funny.h"

using namespace std;

int main()
{
    vector<string> msg{"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};

    for (const string &word : msg)
    {
        cout << word << " ";
    }
    cout << endl;

    funny myFunny;
    myFunny.i = 2;
    myFunny.SetHidden(3);
    cout << myFunny.DoSomething() << endl;

    return 0;
}