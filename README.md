# Query-Bot
a simple query bot in C++ 

# QueryBot

QueryBot is a simple C++ console application designed to interact with users by answering general questions and coding-related queries. The bot uses a combination of predefined responses and web scraping to provide relevant information to the user.

## Features

- **Predefined Responses**: QueryBot responds to common greetings and questions with predefined answers.
- **Learning Capability**: The bot saves responses to previously asked questions and can recall them in future interactions.
- **Web Scraping**: For more complex queries, QueryBot can download and parse web pages to provide detailed information.
- **HTML Parsing**: QueryBot extracts meaningful content from HTML files and cleans the text for better readability.
- **Randomized Responses**: To make interactions feel more natural, QueryBot provides randomized responses for certain queries.

## Requirements

- **C++ Compiler**: Ensure you have a C++ compiler installed that supports the C++11 standard or later.
- **Windows Environment**: The application relies on the Windows-specific `urlmon` library for downloading web pages.

## Setup

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/your-username/query-bot.git
   cd query-bot ```

## Compile the Program:
Use a C++ compiler to compile the source code. Here's an example using g++:
```bash
g++ query-bot.cpp -o query-bot -lurlmon
```
## Run the Application:

```bash
./query-bot
```

## How It Works
QueryBot Class
Private Members:

- mt19937 rng: Random number generator for selecting random responses.
uniform_int_distribution<int> dist: Distribution used for generating random integers.
map<string, string> learnedResponses: Stores learned queries and their corresponding responses.
Private Methods:

- loadLearnedResponses(): Loads responses from a file into memory.
saveLearnedResponse(const string& query, const string& response): Saves a new query-response pair to the file.
getLearnedResponse(const string& query): Retrieves a previously learned response.
downloadWebPage(const string& url, const string& filename): Downloads a web page and saves it locally.
parseHTML(const string& filename): Extracts meaningful content from an HTML file.
cleanHTML(const string& html): Cleans and processes HTML content to plain text.
getRandomResponse(const vector<string>& responses): Returns a random response from a list.
getResponse(const string& input): Determines the appropriate response based on user input.
handleGeneralQuery(const string& query): Handles queries starting with "what is" by downloading and parsing web pages.
handleCodingQuery(const string& query): Handles queries related to coding languages and provides relevant information.
Public Methods:

- QueryBot(): Constructor that initializes the random number generator and loads learned responses.
start(): Starts the bot and handles the user interaction loop.
Main Function
Instantiates the QueryBot object and starts the interaction loop.
File Structure
query-bot.cpp: The main source code file containing the QueryBot class and program logic.
learned_responses.txt: A file where QueryBot stores learned query-response pairs.
