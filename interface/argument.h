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
  string desc;		// description (should be a standard noun phrase)
  string use;		// usage statement
};
