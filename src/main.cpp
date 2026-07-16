#include <cstdio>
#include <cstdlib>
#include <format>
#include <string>
#include <time.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <cpr/cpr.h>
#include "cpr/api.h"
#include "cpr/body.h"
#include "cpr/cprtypes.h"
#include "cpr/response.h"
#include "include/third-party/json.hpp"
#include "include/third-party/whereami/whereami.h"

using json = nlohmann::json;
namespace fs = std::filesystem;

fs::path exe_dir() {
    int length = wai_getExecutablePath(nullptr, 0, nullptr);
    std::vector<char> path(length + 1);
    int dirname_length;
    wai_getExecutablePath(path.data(), length, &dirname_length);
    return fs::path(std::string(path.data(), dirname_length));
}

json getTodaysQuote(fs::path resource_path) {
    std::ifstream f { resource_path / "quotes.json" };
    json data = json::parse(f);

    int quoteCount = data["quotes"].size();

    time_t seconds { time(NULL) };
    int daysSinceEpoch = (seconds / 60 / 60 + 2) / 24;
    srand(daysSinceEpoch);

    int quoteNumber = rand() % quoteCount;

    json quoteData = data["quotes"][quoteNumber];

    std::string quoteText = std::format("“{}”", quoteData["text"].get<std::string>());
    auto pos = quoteText.find('\n');
    std::string firstLine  = (pos == std::string::npos) ? quoteText : quoteText.substr(0, pos);
    std::string secondLine = (pos == std::string::npos) ? " "       : quoteText.substr(pos + 1);

    json quote = {
        {"data", {
            {"dynamic", {
                {
                    {"type", 1},
                    {"name", "quote-text-1"},
                    {"value", firstLine},
                },
                {
                    {"type", 1},
                    {"name", "quote-text-2"},
                    {"value", secondLine},
                },
                {
                    {"type", 1},
                    {"name", "quote-author"},
                    {"value", std::format("- {}", quoteData["author"].get<std::string>())},
                },
                {
                    {"type", 3},
                    {"name", "quote-image"},
                    {"value", {
                        {"url", quoteData["image"].get<std::string>()},
                    }},
                },
                {
                    {"type", 1},
                    {"name", "image-credit-text"},
                    {"value", std::format("Image by: {}", quoteData["image-credit"].get<std::string>())},
                },
                {
                    {"type", 2},
                    {"name", "quote-number"},
                    {"value", quoteNumber + 1},
                },
                {
                    {"type", 2},
                    {"name", "quote-count"},
                    {"value", quoteCount},
                },
            }}
        }},
    };

    return quote;
}

json getConfig(fs::path resource_path) {
    std::ifstream f { resource_path / "config.json" };
    json data = json::parse(f);

    return data["discord"];
}

int main() {
    fs::path resource_path = exe_dir() / "resources";

    json config = getConfig(resource_path);
    json quote = getTodaysQuote(resource_path);

    std::string url = std::format("https://discord.com/api/v9/applications/{}/users/{}/identities/0/profile",
        std::getenv("APP_ID"),
        std::getenv("USER_ID")
    );
    std::string auth = std::format("Bot {}", std::getenv("BOT_TOKEN"));

    cpr::Response r = cpr::Patch(
        cpr::Url { url },
        cpr::Body { quote.dump() },
        cpr::Header {
            {"Content-Type", "application/json"},
            {"Authorization", auth},
            {"User-Agent", "DiscordBot (https://github.com/discord/discord-api-docs, 1.0.0)"}
        }
    );

    std::cout << r.text << "\n";
}
