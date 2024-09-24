#pragma once
#include <Poco/JSON/Object.h>

#include <string>
#include <vector>

using std::string;
using std::vector;

class Json {
public:
    Json(const string &str);
    Json(const Poco::Dynamic::Var &p);
    Json();
    Json(const char *p);
    Json(const Json &p);
    Json &operator=(const Json &p);
    ~Json();

    string toString();
    const vector<string> &getError();

    string getString(const string &name);
    int getInt(const string &name);
    string getString(const string &name, const string &name2);
    int getInt(const string &name, const string &name2);
    std::shared_ptr<Json> getJson(const string &name);

    void add(const string &name, const char *value);
    void add(const string &name, const string &value);
    void add(const string &name, const string &name2, const string &value);
    void add(const string &name, Json &v);
    void add(const string &name, bool v);
    void add(const string &name, int v);
    void add(const string &name, double v);

    void append(const string &name, Json &v);
    void append(const string &name, const string &value);
    void append(const string &name, int value);
    void append(Json &v);
    void append(const string &value);
    void append(int value);

    void clear();
    void clear(const string &name);
    int size();
    int size(const string &name);

    std::shared_ptr<Json> elementObj(int i);
    std::shared_ptr<Json> elementObj(const string &name, int i);
    int elementInt(int i);
    int elementInt(const string &name, int i);
    string element(int i);
    string element(const string &name, int i);

    void getKeys(vector<string> &keys);

private:
    Poco::Dynamic::Var json_;
    vector<string> errs_;
};