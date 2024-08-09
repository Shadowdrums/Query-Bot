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

### QueryBot Class

The QueryBot class is the main part of the program. It manages everything the bot does, including responding to users, learning new information, and retrieving data from the web.

#### Private Members (Behind-the-Scenes Helpers)

- **Random Number Generator (`mt19937 rng`)**: This tool helps the bot pick random responses, making the conversation feel more natural.
- **Integer Distribution (`uniform_int_distribution<int> dist`)**: This helps the random number generator pick a number within a certain range.
- **Learned Responses (`map<string, string> learnedResponses`)**: This is a storage space where the bot saves answers to questions it has learned before, so it can reuse them later.

#### Private Methods (Behind-the-Scenes Tasks)

- **Loading Responses (`loadLearnedResponses()`)**: The bot reads any saved responses from a file, so it remembers what it has learned in the past.
- **Saving a Response (`saveLearnedResponse(const string& query, const string& response)`)**: Whenever the bot learns a new response, it saves it to a file so it can remember it next time.
- **Getting a Saved Response (`getLearnedResponse(const string& query)`)**: If a user asks a question the bot has heard before, it looks up the answer it has already learned and uses it.
- **Downloading Web Pages (`downloadWebPage(const string& url, const string& filename)`)**: If the bot doesn't know the answer to a question, it can download a web page from the internet to find out.
- **Parsing HTML (`parseHTML(const string& filename)`)**: After downloading a web page, the bot goes through the page to find and extract the important information.
- **Cleaning Up HTML (`cleanHTML(const string& html)`)**: This method removes all the unnecessary parts from the web page, like code and tags, leaving just the useful text.
- **Getting a Random Response (`getRandomResponse(const vector<string>& responses)`)**: When the bot has several possible answers, it picks one at random to keep things interesting.
- **Generating a Response (`getResponse(const string& input)`)**: This is where the bot figures out what to say based on what the user typed.
- **Handling General Questions (`handleGeneralQuery(const string& query)`)**: If the user asks a general question starting with "what is," the bot will try to find the answer online and learn it for future use.
- **Handling Coding Questions (`handleCodingQuery(const string& query)`)**: If the user asks about coding, the bot checks if it's a common programming language and tries to find the answer on the web.

#### Public Methods (What the User Interacts With)

- **QueryBot Constructor (`QueryBot()`)**: This is what gets the bot ready to start. It sets up the random number generator and loads any previously saved responses.
- **Starting the Bot (`start()`)**: This method kicks off the bot, allowing it to start interacting with the user. It keeps the conversation going until the user says goodbye.

### Main Function

The main function of the program is simple:

1. **Create a QueryBot**: This sets up the bot.
2. **Start the Bot**: This begins the interaction loop, where the bot listens to and responds to the user.

### File Structure

- **`query-bot.cpp`**: This is the main file containing all the code that makes QueryBot work.
- **`learned_responses.txt`**: This file stores any questions and answers that QueryBot has learned during past interactions.

# MIT License

Copyright (c) 2024 Shadowdrums

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

