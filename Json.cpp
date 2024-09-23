#include "Json.h"

#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSONException.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Query.h>
#include <Poco/JSON/Object.h>

Json::Json(const string &str) : json_() {
    string err = "Json::Json," + str + ",";
    try {
        Poco::JSON::Parser parser;
        json_ = parser.parse(str);
    } catch (const Poco::JSON::JSONException &e) {
        err += e.message();
        errs_.emplace_back(err);
    } catch (...) {
        err += "unknow error";
        errs_.emplace_back(err);
    }
}

Json::Json(const Poco::Dynamic::Var &v) : json_(v) {
}

Json::Json() : Json(string("{}")) {
}

Json::Json(const char *p) : Json(string(p)) {
}

Json::Json(const Json &p) : json_(p.json_) {
}

Json &Json::operator=(const Json &p) {
    if (this != &p) {
        json_ = p.json_;
    }
    return *this;
}

Json::~Json() {
}

string Json::toString() {
    string err = "Json::toString,";
    std::stringstream ss;
    std::string str;
    try {
        if (json_.type() == typeid(Poco::JSON::Object::Ptr)) {
            auto obj = json_.extract<Poco::JSON::Object::Ptr>();
            obj->stringify(ss);
            str = ss.str();
        } else if (json_.type() == typeid(Poco::JSON::Array::Ptr)) {
            auto jsonArray = json_.extract<Poco::JSON::Array::Ptr>();
            jsonArray->stringify(ss);
            str = ss.str();
        } else {
            err += "this json_ error";
            errs_.emplace_back(err);
        }
    } catch (const Poco::JSON::JSONException &e) {
        err += e.message();
        errs_.emplace_back(err);
    } catch (...) {
        err += "unknow error";
        errs_.emplace_back(err);
    }
    return str;
}

const vector<string> &Json::getError() {
    return errs_;
}

string Json::getString(const string &name) {
    string err = "Json::getString," + name + ",";
    try {
        if (json_.type() == typeid(Poco::JSON::Object::Ptr)) {
            Poco::JSON::Query q(json_);
            return q.findValue(name.data(), "");
        } else {
            err += "JSON is not an object";
            errs_.emplace_back(err);
        }
    } catch (const Poco::JSON::JSONException &e) {
        err += e.message();
        errs_.emplace_back(err);
    } catch (...) {
        err += "unknow error";
        errs_.emplace_back(err);
    }
    return "";
}

int Json::getInt(const string &name) {
    string err = "Json::getInt," + name + ",";
    try {
        if (json_.type() == typeid(Poco::JSON::Object::Ptr)) {
            Poco::JSON::Query q(json_);
            return q.findValue(name, 0);
        } else {
            err += "JSON is not an object";
            errs_.emplace_back(err);
        }
    } catch (const Poco::JSON::JSONException &e) {
        err += e.message();
        errs_.emplace_back(err);
    } catch (...) {
        err += "unknow error";
        errs_.emplace_back(err);
    }
    return 0;
}

string Json::getString(const string &name, const string &name2) {
    string err = "Json::getString," + name + "," + name2 + ",";
    try {
        if (json_.type() == typeid(Poco::JSON::Object::Ptr)) {
            char buf[128] = {0};
            sprintf(buf, "%s[%s]", name.data(), name2.data());
            Poco::JSON::Query q(json_);
            return q.findValue(buf, "");
        } else {
            err += "JSON is not an object";
            errs_.emplace_back(err);
        }
    } catch (const Poco::JSON::JSONException &e) {
        err += e.message();
        errs_.emplace_back(err);
    } catch (...) {
        err += "unknow error";
        errs_.emplace_back(err);
    }
    return "";
}

int Json::getInt(const string &name, const string &name2) {
    string err = "Json::getInt," + name + "," + name2 + ",";
    try {
        if (json_.type() == typeid(Poco::JSON::Object::Ptr)) {
            char buf[128] = {0};
            sprintf(buf, "%s[%s]", name.data(), name2.data());
            Poco::JSON::Query q(json_);
            return atoi(q.findValue(buf, "").data());
        } else {
            err += "JSON is not an object";
            errs_.emplace_back(err);
        }
    } catch (const Poco::JSON::JSONException &e) {
        err += e.message();
        errs_.emplace_back(err);
    } catch (...) {
        err += "unknow error";
        errs_.emplace_back(err);
    }
    return 0;
}

string Json::getString(const string &name, const string &name2, const string &name3) {
    string err = "Json::getString," + name + "," + name2 + "," + name3 + ",";
    try {
        if (json_.type() == typeid(Poco::JSON::Object::Ptr)) {
            char buf[128] = {0};
            sprintf(buf, "%s[%s][%s]", name.data(), name2.data(), name3.data());
            Poco::JSON::Query q(json_);
            return q.findValue(buf, "");
        } else {
            err += "JSON is not an object";
            errs_.emplace_back(err);
        }
    } catch (const Poco::JSON::JSONException &e) {
        err += e.message();
        errs_.emplace_back(err);
    } catch (...) {
        err += "unknow error";
        errs_.emplace_back(err);
    }
    return "";
}

int Json::getInt(const string &name, const string &name2, const string &name3) {
    string err = "Json::getInt," + name + "," + name2 + "," + name3 + ",";
    try {
        if (json_.type() == typeid(Poco::JSON::Object::Ptr)) {
            char buf[128] = {0};
            sprintf(buf, "%s[%s][%s]", name.data(), name2.data(), name3.data());
            Poco::JSON::Query q(json_);
            return atoi(q.findValue(buf, "").data());
        } else {
            err += "JSON is not an object";
            errs_.emplace_back(err);
        }
    } catch (const Poco::JSON::JSONException &e) {
        err += e.message();
        errs_.emplace_back(err);
    } catch (...) {
        err += "unknow error";
        errs_.emplace_back(err);
    }
    return 0;
}

std::shared_ptr<Json> Json::getJson(const string &name) {
    string err = "Json::getJson," + name + ",";
    std::shared_ptr<Json> ret = std::shared_ptr<Json>();
    try {
        if (json_.type() == typeid(Poco::JSON::Object::Ptr)) {
            Poco::JSON::Query q(json_);
            Poco::Dynamic::Var v = q.find(name);
            return std::make_shared<Json>(v);
        } else {
            err += "JSON is not an object";
            errs_.emplace_back(err);
        }
    } catch (const Poco::JSON::JSONException &e) {
        err += e.message();
        errs_.emplace_back(err);
    } catch (...) {
        err += "unknow error";
        errs_.emplace_back(err);
    }
    return ret;
}

// 添加数据
void Json::add(const string &name, const char *value) {
    string err = "Json::add," + name + "," + value + ",";
    try {
        if (json_.type() == typeid(Poco::JSON::Object::Ptr)) {
            auto obj = json_.extract<Poco::JSON::Object::Ptr>();
            obj->set(name, value);
        } else {
            err += "JSON is not an object";
            errs_.emplace_back(err);
        }
    } catch (const Poco::JSON::JSONException &e) {
        err += e.message();
        errs_.emplace_back(err);
    } catch (...) {
        err += "unknow error";
        errs_.emplace_back(err);
    }
}

void Json::add(const string &name, const string &value) {
    string err = "Json::add," + name + "," + value + ",";
    try {
        if (json_.type() == typeid(Poco::JSON::Object::Ptr)) {
            auto obj = json_.extract<Poco::JSON::Object::Ptr>();
            obj->set(name, value);
        } else {
            err += "JSON is not an object";
            errs_.emplace_back(err);
        }
    } catch (const Poco::JSON::JSONException &e) {
        err += e.message();
        errs_.emplace_back(err);
    } catch (...) {
        err += "unknow error";
        errs_.emplace_back(err);
    }
}

void Json::add(const string &name, const string &name2, const string &value) {
    string err = "Json::add," + name + "," + name2 + "," + value + ",";
    try {
        std::shared_ptr<Json> j = getJson(name);
        if (j.get() && j->json_.type() == typeid(Poco::JSON::Object::Ptr)) {
            auto obj = j->json_.extract<Poco::JSON::Object::Ptr>();
            obj->set(name2, value);
            add(name, *j);
        } else {
            err += "JSON is not an Object";
            errs_.emplace_back(err);
        }
    } catch (const Poco::JSON::JSONException &e) {
        err += e.message();
        errs_.emplace_back(err);
    } catch (...) {
        err += "unknow error";
        errs_.emplace_back(err);
    }
}

void Json::add(const string &name, Json &v) {
    string err = "Json::add," + name + "," + v.toString() + ",";
    try {
        if (json_.type() == typeid(Poco::JSON::Object::Ptr)) {
            auto obj = json_.extract<Poco::JSON::Object::Ptr>();
            obj->set(name, v.json_);
        } else {
            err += "JSON is not an object";
            errs_.emplace_back(err);
        }
    } catch (const Poco::JSON::JSONException &e) {
        err += e.message();
        errs_.emplace_back(err);
    } catch (...) {
        err += "unknow error";
        errs_.emplace_back(err);
    }
}

void Json::add(const string &name, bool v) {
    string err = "Json::add," + name + "," + (v ? "true" : "false") + ",";
    try {
        if (json_.type() == typeid(Poco::JSON::Object::Ptr)) {
            auto obj = json_.extract<Poco::JSON::Object::Ptr>();
            obj->set(name, v);
        } else {
            err += "JSON is not an object";
            errs_.emplace_back(err);
        }
    } catch (const Poco::JSON::JSONException &e) {
        err += e.message();
        errs_.emplace_back(err);
    } catch (...) {
        err += "unknow error";
        errs_.emplace_back(err);
    }
}

void Json::add(const string &name, int v) {
    string err = "Json::add," + name + "," + std::to_string(v) + ",";
    try {
        if (json_.type() == typeid(Poco::JSON::Object::Ptr)) {
            auto obj = json_.extract<Poco::JSON::Object::Ptr>();
            obj->set(name, v);
        } else {
            err += "JSON is not an object";
            errs_.emplace_back(err);
        }
    } catch (const Poco::JSON::JSONException &e) {
        err += e.message();
        errs_.emplace_back(err);
    } catch (...) {
        err += "unknow error";
        errs_.emplace_back(err);
    }
}

void Json::add(const string &name, double v) {
    string err = "Json::add," + name + "," + std::to_string(v) + ",";
    try {
        if (json_.type() == typeid(Poco::JSON::Object::Ptr)) {
            auto obj = json_.extract<Poco::JSON::Object::Ptr>();
            obj->set(name, v);
        } else {
            err += "JSON is not an object";
            errs_.emplace_back(err);
        }
    } catch (const Poco::JSON::JSONException &e) {
        err += e.message();
        errs_.emplace_back(err);
    } catch (...) {
        err += "unknow error";
        errs_.emplace_back(err);
    }
}

// 追加数据
void Json::append(const string &name, Json &v) {
    string err = "Json::append," + v.toString() + ",";
    try {
        std::shared_ptr<Json> j = getJson(name);
        if (j.get() && j->json_.type() == typeid(Poco::JSON::Array::Ptr)) {
            auto array = j->json_.extract<Poco::JSON::Array::Ptr>();
            Poco::Dynamic::Array dynArray = *array;
            array->set(dynArray.size(), v);
            add(name, *j);
        } else {
            err += "JSON is not an Array";
            errs_.emplace_back(err);
        }
    } catch (const Poco::JSON::JSONException &e) {
        err += e.message();
        errs_.emplace_back(err);
    } catch (...) {
        err += "unknow error";
        errs_.emplace_back(err);
    }
}

void Json::append(const string &name, const string &value) {
    string err = "Json::append," + value + ",";
    try {
        std::shared_ptr<Json> j = getJson(name);
        if (j.get() && j->json_.type() == typeid(Poco::JSON::Array::Ptr)) {
            auto array = j->json_.extract<Poco::JSON::Array::Ptr>();
            Poco::Dynamic::Array dynArray = *array;
            array->set(dynArray.size(), value);
            add(name, *j);
        } else {
            err += "JSON is not an Array";
            errs_.emplace_back(err);
        }
    } catch (const Poco::JSON::JSONException &e) {
        err += e.message();
        errs_.emplace_back(err);
    } catch (...) {
        err += "unknow error";
        errs_.emplace_back(err);
    }
}

void Json::append(const string &name, int value) {
    string err = "Json::append," + std::to_string(value) + ",";
    try {
        std::shared_ptr<Json> j = getJson(name);
        if (j.get() && j->json_.type() == typeid(Poco::JSON::Array::Ptr)) {
            auto array = j->json_.extract<Poco::JSON::Array::Ptr>();
            Poco::Dynamic::Array dynArray = *array;
            array->set(dynArray.size(), value);
            add(name, *j);
        } else {
            err += "JSON is not an Array";
            errs_.emplace_back(err);
        }
    } catch (const Poco::JSON::JSONException &e) {
        err += e.message();
        errs_.emplace_back(err);
    } catch (...) {
        err += "unknow error";
        errs_.emplace_back(err);
    }
}

void Json::append(Json &v) {
    string err = "Json::append," + v.toString() + ",";
    try {
        if (json_.type() == typeid(Poco::JSON::Array::Ptr)) {
            auto array = json_.extract<Poco::JSON::Array::Ptr>();
            Poco::Dynamic::Array dynArray = *array;
            array->set(dynArray.size(), v);
        } else {
            err += "JSON is not an Array";
            errs_.emplace_back(err);
        }
    } catch (const Poco::JSON::JSONException &e) {
        err += e.message();
        errs_.emplace_back(err);
    } catch (...) {
        err += "unknow error";
        errs_.emplace_back(err);
    }
}

void Json::append(const string &value) {
    string err = "Json::append," + value + ",";
    try {
        if (json_.type() == typeid(Poco::JSON::Array::Ptr)) {
            auto array = json_.extract<Poco::JSON::Array::Ptr>();
            Poco::Dynamic::Array dynArray = *array;
            array->set(dynArray.size(), value);
        } else {
            err += "JSON is not an Array";
            errs_.emplace_back(err);
        }
    } catch (const Poco::JSON::JSONException &e) {
        err += e.message();
        errs_.emplace_back(err);
    } catch (...) {
        err += "unknow error";
        errs_.emplace_back(err);
    }
}

void Json::append(int value) {
    string err = "Json::append," + std::to_string(value) + ",";
    try {
        if (json_.type() == typeid(Poco::JSON::Array::Ptr)) {
            auto array = json_.extract<Poco::JSON::Array::Ptr>();
            Poco::Dynamic::Array dynArray = *array;
            array->set(dynArray.size(), value);
        } else {
            err += "JSON is not an Array";
            errs_.emplace_back(err);
        }
    } catch (const Poco::JSON::JSONException &e) {
        err += e.message();
        errs_.emplace_back(err);
    } catch (...) {
        err += "unknow error";
        errs_.emplace_back(err);
    }
}

// 清空内容
void Json::clear() {
    string err = "Json::clear,";
    errs_.clear();
    try {
        if (json_.type() == typeid(Poco::JSON::Object::Ptr)) {
            Poco::JSON::Parser parser;
            json_ = parser.parse("{}");
        } else if (json_.type() == typeid(Poco::JSON::Array::Ptr)) {
            Poco::JSON::Parser parser;
            json_ = parser.parse("[]");
        } else {
            err += "neither an object nor an array";
            errs_.emplace_back(err);
        }
    } catch (const Poco::JSON::JSONException &e) {
        err += e.message();
        errs_.emplace_back(err);
    } catch (...) {
        err += "unknow error";
        errs_.emplace_back(err);
    }
}

void Json::clear(const string &name) {
    string err = "Json::clear," + name + ",";
    try {
        std::shared_ptr<Json> j = getJson(name);
        if (j.get() && j->json_.type() == typeid(Poco::JSON::Object::Ptr)) {
            add(name, "{}");

        } else if (j->json_.type() == typeid(Poco::JSON::Array::Ptr)) {
            add(name, "[]");
        } else {
            err += "neither an object nor an array";
            errs_.emplace_back(err);
        }
    } catch (const Poco::JSON::JSONException &e) {
        err += e.message();
        errs_.emplace_back(err);
    } catch (...) {
        err += "unknow error";
        errs_.emplace_back(err);
    }
}

// 获取大小
int Json::size() {
    string err = "Json::size,";
    try {
        if (json_.type() == typeid(Poco::JSON::Object::Ptr)) {
            auto obj = json_.extract<Poco::JSON::Object::Ptr>();
            return obj->getNames().size();
        } else if (json_.type() == typeid(Poco::JSON::Array::Ptr)) {
            auto array = json_.extract<Poco::JSON::Array::Ptr>();
            Poco::Dynamic::Array dynArray = *array;
            return dynArray.size();
        } else {
            err += "neither an object nor an array";
            errs_.emplace_back(err);
        }
    } catch (const Poco::JSON::JSONException &e) {
        err += e.message();
        errs_.emplace_back(err);
    } catch (...) {
        err += "unknow error";
        errs_.emplace_back(err);
    }
    return 0;
}

int Json::size(const string &name) {
    string err = "Json::size," + name + ",";
    try {
        std::shared_ptr<Json> j = getJson(name);
        if (j.get() && j->json_.type() == typeid(Poco::JSON::Object::Ptr)) {
            auto obj = j->json_.extract<Poco::JSON::Object::Ptr>();
            return obj->getNames().size();
        } else if (j->json_.type() == typeid(Poco::JSON::Array::Ptr)) {
            auto array = j->json_.extract<Poco::JSON::Array::Ptr>();
            Poco::Dynamic::Array dynArray = *array;
            return dynArray.size();
        } else {
            err += "neither an object nor an array";
            errs_.emplace_back(err);
        }
    } catch (const Poco::JSON::JSONException &e) {
        err += e.message();
        errs_.emplace_back(err);
    } catch (...) {
        err += "unknow error";
        errs_.emplace_back(err);
    }
    return 0;
}

std::shared_ptr<Json> Json::element(int i) {
    string err = "Json::element," + std::to_string(i) + ",";
    try {
        if (json_.type() == typeid(Poco::JSON::Array::Ptr)) {
            auto array = json_.extract<Poco::JSON::Array::Ptr>();
            Poco::Dynamic::Var v = array->get(i);
            return std::make_shared<Json>(v.toString());
        } else {
            err += "JSON is not an Array";
            errs_.emplace_back(err);
        }
    } catch (const Poco::JSON::JSONException &e) {
        err += e.message();
        errs_.emplace_back(err);
    } catch (...) {
        err += "unknow error";
        errs_.emplace_back(err);
    }
    return std::shared_ptr<Json>();
}

std::shared_ptr<Json> Json::element(const string &name, int i) {
    string err = "Json::element," + name + "," + std::to_string(i) + ",";
    try {
        std::shared_ptr<Json> j = getJson(name);
        if (j.get() && j->json_.type() == typeid(Poco::JSON::Array::Ptr)) {
            auto array = j->json_.extract<Poco::JSON::Array::Ptr>();
            Poco::Dynamic::Var v = array->get(i);
            return std::make_shared<Json>(v.toString());
        } else {
            err += "JSON is not an Array";
            errs_.emplace_back(err);
        }
    } catch (const Poco::JSON::JSONException &e) {
        err += e.message();
        errs_.emplace_back(err);
    } catch (...) {
        err += "unknow error";
        errs_.emplace_back(err);
    }
    return std::shared_ptr<Json>();
}

void Json::getKeys(vector<string> &keys) {
    string err = "Json::getKeys,";
    try {
        if (json_.type() == typeid(Poco::JSON::Object::Ptr)) {
            auto obj = json_.extract<Poco::JSON::Object::Ptr>();
            for (int i = 0; i < obj->getNames().size(); ++i) {
                keys.emplace_back(obj->getNames()[i]);
            }
        } else {
            err += "JSON is not an Object";
            errs_.emplace_back(err);
        }
    } catch (const Poco::JSON::JSONException &e) {
        err += e.message();
        errs_.emplace_back(err);
    } catch (...) {
        err += "unknow error";
        errs_.emplace_back(err);
    }
}