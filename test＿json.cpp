#include <iostream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

int main()
{
    json j;
    j["name"] = "Emilia";
    j["age"] = 0.5;
    j["cute"] = true;

    std::cout << j.dump(4) << std::endl;
}
