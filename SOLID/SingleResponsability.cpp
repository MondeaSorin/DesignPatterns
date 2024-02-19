#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <exception>

using namespace std;

class FileNotFoundException : public exception
{
public:
	virtual ~FileNotFoundException() = default;
	virtual char const* what() const override
	{
		return "File not found";
	}
};

class Journal
{
private:
	string title;
	vector<string> entries;
public:
	Journal(const string& title) : title(title) {}

	void add_entry(const string& entry)
	{
		static int count{ 1 };
		entries.push_back(to_string(count++) + ": " + entry);
	}

	vector<string> get_entries() const { return this->entries; }

	// if we made the save function here, we would break the Single Responsability principle

};

class PersistanceManager
{
public:
	void save(const Journal& j, const string& file_name)
	{
		ofstream ofs(file_name);
		if (ofs.is_open())
		{
			for (const auto& e : j.get_entries())
				ofs << e << endl;
			ofs.close();
		}
		else
		{
			throw FileNotFoundException();
		}
	}
};

int main()
{
	Journal j("My journal");
	PersistanceManager pm;
	try
	{
		pm.save(j, "journal.txt");
		pm.save(j, ""); // should throw exception
	}
	catch (const FileNotFoundException& ex)
	{
		cerr << ex.what() << endl;
	}
}