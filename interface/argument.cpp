#include <string>

using std::string;

class argument{
public:
  // constructors
  argument(string name, string description);
  argument();

  // methods
  const string& name() const { return nm; }
  const string& description() const { return desc; }
  const string& usage() const { return use; }

private:
  string nm;		// name
  string desc;		// description
  string use;		// usage statement
};

argument::argument(string name, string description)
  : nm(name), desc(description),
    use("where <" + name + "> is " + description)
{
}

argument::argument()
  : nm(), desc(), use()
{
}
