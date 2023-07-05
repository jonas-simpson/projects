#include "funny.h"

funny::funny()
{
    i = 0;
    j = 0;
}

funny::~funny() {}

void funny::SetHidden(int newValue)
{
    j = newValue;
}

int funny::GetSomething() const
{
    return j;
}

int funny::DoSomething() const
{
    return (j + 1) * i;
}