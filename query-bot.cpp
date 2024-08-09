#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <random>
#include <ctime>
#include <fstream>
#include <sstream>
#include <map>
#include <windows.h>
#include <urlmon.h>

#pragma comment(lib, "urlmon.lib")

using namespace std;

class QueryBot {
private:
    mt19937 rng;
    uniform_int_distribution<int> dist;
    map<string, string> learnedResponses;

    void loadLearnedResponses() {
        ifstream infile("learned_responses.txt");
        string line;
        while (getline(infile, line)) {
            size_t delimiter = line.find("|||");
            if (delimiter != string::npos) {
                string query = line.substr(0, delimiter);
                string response = line.substr(delimiter + 3);
                learnedResponses[query] = response;
            }
        }
    }

    void saveLearnedResponse(const string& query, const string& response) {
        learnedResponses[query] = response;
        ofstream outfile("learned_responses.txt", ios::app);
        outfile << query << "|||" << response << endl;
    }

    string getLearnedResponse(const string& query) {
        auto it = learnedResponses.find(query);
        if (it != learnedResponses.end()) {
            return it->second;
        }
        return "";
    }

    void downloadWebPage(const string& url, const string& filename) {
        HRESULT hr = URLDownloadToFileA(NULL, url.c_str(), filename.c_str(), 0, NULL);
        if (hr != S_OK) {
            cout << "Failed to download file: " << url << endl;
        }
    }

    string parseHTML(const string& filename) {
        ifstream infile(filename);
        stringstream buffer;
        buffer << infile.rdbuf();
        string htmlContent = buffer.str();
        infile.close();

        // Improved parsing to get the main content
        size_t start = htmlContent.find("<p>");
        size_t end = htmlContent.find("</p>", start);
        if (start != string::npos && end != string::npos) {
            string summary = htmlContent.substr(start + 3, end - start - 3);
            return cleanHTML(summary);
        }
        return "No relevant information found.";
    }

    string cleanHTML(const string& html) {
        string text;
        bool inTag = false;
        for (char c : html) {
            if (c == '<') inTag = true;
            if (!inTag) text += c;
            if (c == '>') inTag = false;
        }
        // Replace HTML entities with their actual characters
        text = regex_replace(text, regex("&quot;"), "\"");
        text = regex_replace(text, regex("&amp;"), "&");
        text = regex_replace(text, regex("&lt;"), "<");
        text = regex_replace(text, regex("&gt;"), ">");
        text = regex_replace(text, regex("&#39;"), "'");
        text = regex_replace(text, regex("&#91;"), "[");
        text = regex_replace(text, regex("&#93;"), "]");
        text = regex_replace(text, regex("&#10;"), " ");
        text = regex_replace(text, regex("\\s+"), " "); // Remove extra spaces
        return text;
    }

    string getRandomResponse(const vector<string>& responses) {
        return responses[dist(rng) % responses.size()];
    }

    string getResponse(const string& input) {
        string learnedResponse = getLearnedResponse(input);
        if (!learnedResponse.empty()) {
            return learnedResponse;
        }

        if (regex_match(input, regex("(hello|hi|hey)"))) {
            vector<string> responses = {
                "Hi there! How can I assist you today?",
                "Hello! What's up?",
                "Hey! How can I help you?"
            };
            return getRandomResponse(responses);
        }
        else if (regex_match(input, regex("how are you\\??"))) {
            vector<string> responses = {
                "I'm just a bot, but I'm here to help you!",
                "I'm doing great, thanks for asking!",
                "I'm just a bunch of code, but I'm ready to chat!"
            };
            return getRandomResponse(responses);
        }
        else if (regex_match(input, regex("(bye|goodbye|see you)"))) {
            vector<string> responses = {
                "Goodbye! Have a nice day!",
                "See you later!",
                "Bye! Take care!"
            };
            return getRandomResponse(responses);
        }
        else if (regex_search(input, regex("how to .*"))) {
            string query = input.substr(7); // Remove "how to " from the input
            return handleCodingQuery(query);
        }
        else if (regex_search(input, regex("what is .*"))) {
            string query = input.substr(8); // Remove "what is " from the input
            return handleGeneralQuery(query);
        }
        else if (regex_search(input, regex(".*coding.*"))) {
            string query = input.substr(input.find("coding") + 7); // Extract the term after "coding"
            return handleCodingQuery(query);
        }
        else {
            vector<string> responses = {
                "I'm sorry, I don't understand that.",
                "Can you please rephrase?",
                "I'm not sure what you mean."
            };
            return getRandomResponse(responses);
        }
    }

    string handleGeneralQuery(const string& query) {
        string modifiedQuery = query;
        replace(modifiedQuery.begin(), modifiedQuery.end(), ' ', '_');
        string url = "https://en.wikipedia.org/wiki/" + modifiedQuery;
        downloadWebPage(url, "temp.html");
        string summary = parseHTML("temp.html");
        saveLearnedResponse("what is " + query, summary);
        return summary;
    }

    string handleCodingQuery(const string& query) {
        if (query == "python" || query == "java" || query == "javascript" || query == "csharp" || query == "cpp") {
            string url = "https://www.w3schools.com/" + query + "/";
            downloadWebPage(url, "temp.html");
            string summary = parseHTML("temp.html");
            saveLearnedResponse("how to code " + query, summary);
            return summary;
        }
        return "I'm sorry, I don't understand that coding language.";
    }

public:
    QueryBot() : rng(static_cast<unsigned int>(time(0))), dist(0, 1000) {
        loadLearnedResponses();
    }

    void start() {
        string userInput;
        cout << "Welcome to QueryBot! Type 'bye' to exit." << endl;

        while (true) {
            cout << "You: ";
            getline(cin, userInput);

            if (regex_match(userInput, regex("(bye|goodbye|see you)"))) {
                cout << "Bot: " << getResponse(userInput) << endl;
                break;
            }

            string response = getResponse(userInput);
            cout << "Bot: " << response << endl;
        }
    }
};

int main() {
    QueryBot queryBot;
    queryBot.start();
    return 0;
}
