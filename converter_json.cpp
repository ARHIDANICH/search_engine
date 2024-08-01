#include <vector>
#include <iostream>
#include <string>
#include <fstream>

#include "nlohmann/json.hpp"

/**
* Класс для работы с JSON-файлами
*/
class ConverterJSON {
    nlohmann::json config;
public:
    ConverterJSON() = default;

    /**
     * Инициализирует ConverterJSON
     * @return Возвращает false если произошла ошибка при открытии config.json /
     * true при успешном открытии config.json
     */
    bool openConfig() {
        std::ifstream configFile;
        configFile.open("config.json");
        if (!configFile.is_open()) {
            std::cerr << "config.json не найден!\n Завершение программы.";
            return false;
        }
        configFile >> config;
        configFile.close();
        return true;
    };

    /**
    * Метод получения содержимого файлов
    * @return Возвращает список с содержимым файлов перечисленных в config.json /
    * либо пустой std::vector<std::string> если поле files отсутствует в config.json
    */
    std::vector<std::string> getTextDocuments() {
        if (config.count("files") == 0) {
            std::cerr << "Поле files не найдено в config.json.";
            return {};
        }
        return config["files"];
    };

    /**
    * Метод считывает поле max_responses для определения предельного количества ответов на один запрос
    * @return Предельное количество ответов на один запрос /
    * -1 если не считаны поля config или max_responses
    */
    int getResponsesLimit() {
        if (config.count("config") == 0) {
            std::cerr << "Поле config не найдено в config.json.";
            return -1;
        }
        if (config["config"].count("max_responses") == 0) {
            std::cerr << "Поле max_responses не найдено в config.json.";
            return -1;
        }
        return config["config"]["max_responses"];
    };

    /**
    * Метод получения запросов из файла requests.json
    * @return Cписок запросов из файла requests.json /
    * либо пустой std::vector<std::string> если поле requests отсутствует в requests.json или сам файл отсутствует
    */
    std::vector<std::string> getRequests() {
        std::ifstream requestFile;
        requestFile.open("requests.json");
        if (!requestFile.is_open()) {
            std::cerr << "requests.json не найден!\n Завершение программы.";
            return {};
        };
        nlohmann::json requests;
        requestFile >> requests;
        requestFile.close();

        if (requests.count("requests") == 0) {
            std::cerr << "Поле requests не найдено в requests.json.";
            return {};
        }
        return requests["requests"];
    };


    /**
    * TODO:
    * Положить в файл answers.json результаты поисковых запросов
    */
    void putAnswers(std::vector<std::vector<std::pair<int, float>>>
        answers) {
        std::ofstream answersFile("answers.json");
        answersFile.clear();

        nlohmann::json payLoad;
        for (int i = 0; i < answers.size();i++) {
            nlohmann::json jsonOutput = {};
            if (answers[i].empty()) {
                jsonOutput["request" + (std::to_string(1000 + i)).substr(1, 3)] = {
            "result", false
                };
            }
            else if (answers[i].size() == 1) {
                jsonOutput["request" + (std::to_string(1000 + i)).substr(1, 3)] = {
                    "result", true,
                    "docid", answers[i][0].first,
                    "rank", answers[i][0].second
                };
            }
            else {
                nlohmann::json relevance = {};
                for (int j = 0; j < answers[i].size();j++) {
                    relevance += {
                        "docid", answers[i][j].first,
                            "rank", answers[i][j].second,
                    };
                }
                jsonOutput["request" + (std::to_string(1000 + i)).substr(1, 3)] = { "result", true, relevance };

            };

            payLoad["answers"]+=jsonOutput;
        }
        
        answersFile << payLoad;
        answersFile.close();
    };
};