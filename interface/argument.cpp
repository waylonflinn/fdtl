#include "argument.h"

argument::argument(string name, string description)
  : nm(name), desc(description),
    use("<" + name + "> is " + description)
{
}

argument::argument()
  : nm(), desc(), use()
{
}
