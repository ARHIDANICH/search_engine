#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "nlohmann/json.hpp"
#include "gtest/gtest.h"

#include "converter_json.cpp"
int main() {
    ConverterJSON interface;
    if (!interface.openConfig()) {
        return 0;
    };
    std::vector<std::string> docs;
    docs = interface.getTextDocuments();
    int test = interface.getResponsesLimit();
    interface.putAnswers(
        { {},
            {
                {1,12.3},
                {2,25.6}},
            {
                {2,34.5},
                {4,56.7}},
            {},
        });

    //testing::InitGoogleTest();
    //return RUN_ALL_TESTS();

}
/*
struct Entry {
    size_t doc_id, count;
};

class InvertedIndex {
    std::vector<std::string> docs = {};
    std::map<std::string, std::vector<Entry>> freq_dictionary = {};
    //Map<word, List<what document, how often>>
};


*/



/*
file001.txt:
milk sugar salt
file002.txt:
milk a milk b milk c milk d

docs[0] = “milk sugar salt”;
docs[1] = “milk a milk b milk c milk d”;

index[“a”] = {1, 1};
index[“b”] = {1, 1};
index[“c”] = {1, 1};
index[“d”] = {1, 1};
index[“milk”] = {0, 1}, {1, 4};
index[“salt”] = {0, 1};
index[“sugar”] = {0, 1};
*/