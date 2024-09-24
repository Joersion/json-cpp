#include <iostream>

#include "../Json.h"
using namespace std;
#define FENGEFU "---------------------------"

string gJsonStr = R"({
    "name": "Alice",
    "age": 30,
    "isStudent": false,
    "email": "alice@example.com",
    "address": {
        "street": "123 Main St",
        "city": "深圳",
        "zipcode": "12345",
        "code": 1234
    },
    "phoneNumbers": [
        {
            "type": "home",
            "number": "123-456-7890"
        },
        {
            "type": "work",
            "number": "987-654-3210"
        }
    ],
    "courses": [
        "Mathematics",
        "Physics",
        "Computer Science"
    ],
    "graduationYear": null
})";

string gJsonArry = R"([
    {
        "id": 1,
        "name": "Alice",
        "age": 30,
        "email": "alice@example.com"
    },
    {
        "id": 2,
        "name": "Bob",
        "age": 25,
        "email": "bob@example.com"
    },
    {
        "id": 3,
        "name": "Charlie",
        "age": 35,
        "email": "charlie@example.com"
    }
])";

void printError(const vector<string>& v) {
    for (int i = 0; i < v.size(); ++i) {
        std::cout << "err" << i << ":" << v.at(i) << std::endl;
    }
}

void testCreate() {
    cout << FENGEFU << "testCreate" << FENGEFU << endl;
    Json json;
    printError(json.getError());
    std::cout << "testSize1:" << (json.toString() == "{}") << std::endl;

    Json json2(json);
    printError(json2.getError());
    std::cout << "testSize2:" << (json2.toString() == "{}") << std::endl;

    Json json3(gJsonStr);
    Json json4;
    json4 = json3;
    printError(json2.getError());
    std::cout << "testSize3:" << (json3.toString() == json4.toString()) << std::endl;
}

void testToString() {
    cout << FENGEFU << "testToString" << FENGEFU << endl;
    Json json(gJsonStr);
    printError(json.getError());
    cout
        << "testToString:"
        << (json.toString() ==
            R"({"address":{"city":"深圳","code":1234,"street":"123 Main St","zipcode":"12345"},"age":30,"courses":["Mathematics","Physics","Computer Science"],"email":"alice@example.com","graduationYear":null,"isStudent":false,"name":"Alice","phoneNumbers":[{"number":"123-456-7890","type":"home"},{"number":"987-654-3210","type":"work"}]})")
        << endl;
    Json json1("{}");
    printError(json1.getError());
    cout << "testToString1:" << (json1.toString() == "{}") << endl;
    Json json2("[]");
    printError(json2.getError());
    cout << "testToString2:" << (json2.toString() == "[]") << endl;
}

void testGetString() {
    cout << FENGEFU << "testGetString" << FENGEFU << endl;
    Json json(gJsonStr);
    cout << "testGetString:" << (json.getString("name") == "Alice") << endl;
    cout << "testGetString1:" << (json.getString("age") == "30") << endl;
    cout << "testGetString2:" << (json.getString("isStudent") == "false") << endl;
    cout << "testGetString3:" << (json.getString("SSS") == "") << endl;
    cout << "testGetString4:" << (json.getString("address", "city") == "深圳") << endl;
    cout << "testGetString5:" << (json.getString("address", "code") == "1234") << endl;
    printError(json.getError());
}

void testGetInt() {
    cout << FENGEFU << "testGetInt" << FENGEFU << endl;
    Json json(gJsonStr);
    cout << "testGetInt:" << (json.getInt("name") == 0) << endl;
    cout << "testGetInt1:" << (json.getInt("age") == 30) << endl;
    cout << "testGetInt2:" << (json.getInt("isStudent") == false) << endl;
    cout << "testGetInt3:" << (json.getInt("SSS") == 0) << endl;
    cout << "testGetInt4:" << (json.getInt("address", "zipcode") == 12345) << endl;
    cout << "testGetInt5:" << (json.getInt("address", "code") == 1234) << endl;
    printError(json.getError());
}

void testGetJson() {
    cout << FENGEFU << "testGetJson" << FENGEFU << endl;
    Json json(gJsonStr);
    std::shared_ptr<Json> j = json.getJson("address");
    printError(json.getError());
    std::cout << "testGetJson:" << (j->getString("zipcode") == "12345") << std::endl;

    std::shared_ptr<Json> j1 = json.getJson("courses");
    printError(json.getError());
    std::cout << "testGetJson1:" << (j1->toString() == R"(["Mathematics","Physics","Computer Science"])") << std::endl;
}

void testAdd() {
    cout << FENGEFU << "testAdd" << FENGEFU << endl;
    Json json;
    Json sub(R"({"aaa":4})");
    json.add("key1", 1);
    json.add("key2", "2");
    json.add("key3", 3.0);
    json.add("key4", true);
    json.add("key5", std::to_string(5));
    json.add("key6", sub);
    json.add("key6", "key7", "7");
    printError(json.getError());
    std::cout << "testAdd:"
              << (json.toString() ==
                  R"({"key1":1,"key2":"2","key3":3,"key4":true,"key5":"5","key6":{"aaa":4,"key7":"7"}})")
              << std::endl;
}

void testAppend() {
    cout << FENGEFU << "testAppend" << FENGEFU << endl;
    Json sub(R"({"test":3})");
    Json json("[]");
    json.append(0);
    json.append("1");
    json.append(sub);
    printError(json.getError());
    std::cout << "testAppend:" << (json.toString() == R"([0,"1",{"test":3}])") << std::endl;

    Json json2(gJsonStr);
    Json sub2(R"({"type": "test","number": "987-654-3210-test"})");
    json2.append("phoneNumbers", sub2);
    json2.append("courses", "courses-append1");
    json2.append("courses", 1000);
    printError(json2.getError());
    std::cout
        << "testAppend2:"
        << (json2.toString() ==
            R"({"address":{"city":"深圳","code":1234,"street":"123 Main St","zipcode":"12345"},"age":30,"courses":["Mathematics","Physics","Computer Science","courses-append1",1000],"email":"alice@example.com","graduationYear":null,"isStudent":false,"name":"Alice","phoneNumbers":[{"number":"123-456-7890","type":"home"},{"number":"987-654-3210","type":"work"},{"number":"987-654-3210-test","type":"test"}]})")
        << std::endl;
}

void testClear() {
    cout << FENGEFU << "testClear" << FENGEFU << endl;
    Json json(gJsonStr);
    json.clear("phoneNumbers");
    json.clear("address");
    std::cout
        << "testClear:"
        << (json.toString() ==
            R"({"address":{},"age":30,"courses":["Mathematics","Physics","Computer Science"],"email":"alice@example.com","graduationYear":null,"isStudent":false,"name":"Alice","phoneNumbers":[]})")
        << std::endl;

    json.clear();
    printError(json.getError());
    std::cout << "testClear1:" << (json.toString() == "{}") << std::endl;

    Json json2(gJsonArry);
    json2.clear();
    printError(json2.getError());
    std::cout << "testClear2:" << (json2.toString() == "[]") << std::endl;
}

void testSize() {
    cout << FENGEFU << "testSize" << FENGEFU << endl;
    Json json(gJsonStr);
    printError(json.getError());
    std::cout << "testSize:" << (json.size() == 8) << std::endl;
    std::cout << "testSize1:" << (json.size("address") == 4) << std::endl;
    std::cout << "testSize2:" << (json.size("phoneNumbers") == 2) << std::endl;

    Json json2(gJsonArry);
    printError(json2.getError());
    std::cout << "testSize3:" << (json2.size() == 3) << std::endl;
}

void testGetKeys() {
    cout << FENGEFU << "testGetKeys" << FENGEFU << endl;
    Json json(gJsonStr);
    vector<string> v;
    json.getKeys(v);
    vector<string> v1 = {"address", "age", "courses", "email", "graduationYear", "isStudent", "name", "phoneNumbers"};
    cout << "testGetKeys:" << (v1 == v) << endl;
}

void testElement() {
    cout << FENGEFU << "testElement" << FENGEFU << endl;
    Json json(gJsonStr);
    shared_ptr<Json> j1 = json.elementObj("phoneNumbers", 0);
    std::cout << "testElement:" << (json.element("courses", 0) == "Mathematics") << std::endl;
    std::cout << "testElement1:" << (j1->toString() == R"({"number":"123-456-7890","type":"home"})") << std::endl;

    Json json2(R"([0,1,2,3])");
    Json json3(gJsonArry);
    shared_ptr<Json> j3 = json3.elementObj(0);
    std::cout << "testElement2:" << (json2.element(1) == "1") << std::endl;
    std::cout << "testElement3:"
              << (j3->toString() == R"({"age":30,"email":"alice@example.com","id":1,"name":"Alice"})") << std::endl;
    printError(json.getError());
    printError(json2.getError());
    printError(json3.getError());
}

int main() {
    testCreate();
    testGetString();
    testToString();
    testGetJson();
    testAdd();
    testAppend();
    testClear();
    testSize();
    testGetKeys();
    testElement();
}