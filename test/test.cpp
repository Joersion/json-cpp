#include <iostream>

#include "../Json.h"
using namespace std;
void printError(const vector<string>& v) {
    for (int i = 0; i < v.size(); ++i) {
        std::cout << "err" << i << ":" << v.at(i) << std::endl;
    }
}

void testToString() {
    string str =
        R"({"name": "Alice","age": 30,"isStudent": false,"email": "alice@example.com","address": {"street": "123 Main St","city": "Wonderland","zipcode": "12345"},"phoneNumbers": [{"type": "home","number": "123-456-7890"},{"type": "work","number": "987-654-3210"}],"courses": ["Mathematics","Physics","Computer Science"],"graduationYear": null})";
    Json json(str);
    printError(json.getError());
    cout << "testToString:" << (json.toString() == str) << endl;
    Json json1("{}");
    printError(json1.getError());
    cout << "testToString1:" << (json1.toString() == "{}") << endl;
    Json json2("[]");
    printError(json2.getError());
    cout << "testToString2:" << (json2.toString() == "[]") << endl;
}

void testAdd() {
    Json json;
    Json sub(R"({"aaa":4}))");
    json.add("key1", 1);
    json.add("key2", "2");
    json.add("key3", 3.0);
    json.add("key4", sub);
    json.add("key5", std::to_string(5));
    json.add("key6", true);
    json.add("key7", "key7", "7");
    printError(json.getError());
    std::cout << "testAdd:" << json.toString() << std::endl;
}

int main() {
    testToString();
    testAdd();
    getchar();
}