#include <format>
#include <string>
#include <vector>
#include <any>

using namespace std;

constexpr void print(const std::string_view str_fmt, auto&&... args) 
{
    fputs(vformat(str_fmt, make_format_args(args...)).c_str(), stdout);
}

void print_any(const any& o)
{
    if (!o.has_value())
        print("None\n");
    else if (o.type() == typeid(int))
    {
        auto x = any_cast<int>(o);
        print("int {}\n", x);
    }
    else if (o.type() == typeid(string))
    {
        auto& x = any_cast<const string&>(o);
        print("string {}\n", x);
    }
    else if (o.type() == typeid(vector<int>))
    {
        auto& x = any_cast<const vector<int>&>(o);
        for (auto& e : x)
            print("{} ", e);
        print("\n");
    }
    else
        print("I don't handle this type string: {}\n", o.type().name());
}

int main() 
{
    print_any(47);
    print_any(std::string{ "47" });
    print_any(std::vector{ 1, 2, 3, 4, 5 });
    print_any(std::vector{ 1.0, 2.0, 3.0, 4.0, 5.0 });
    print("\n");
}