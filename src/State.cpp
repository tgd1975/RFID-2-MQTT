#include "State.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>


std::string getISOCurrentTimestamp() {
  auto now = std::chrono::system_clock::now();
  auto itt = std::chrono::system_clock::to_time_t(now);
  std::ostringstream ss;
  ss << std::put_time(gmtime(&itt), "%FT%TZ");
  return ss.str();
}

State::State() {
    card_present = false;
    last_uid = "";
    last_update = getISOCurrentTimestamp();
}

State::State(std::string uid, bool present) {
    this->card_present = present;
    this->last_uid = uid;
    last_update = getISOCurrentTimestamp();
}

State::State(const State& other) {
    card_present = other.card_present;
    last_uid = other.last_uid;
    last_update = other.last_update;

}

void State::setLAST_UID(std::string uid) {
    this->last_uid = uid;
    last_update = getISOCurrentTimestamp();
}

void State::setCARD_PRESENT(bool present) {
    this->card_present = present;
    last_update = getISOCurrentTimestamp();
}

void State::setValues(std::string uid, bool present) {
    this->card_present = present;
    this->last_uid = uid;
    last_update = getISOCurrentTimestamp();
}

inline const std::string BoolToString(const bool b)
{
  return b ? "TRUE" : "FALSE";
}

std::string State::getJson() {
    // {"uid": "116:4:126:1", "present": "TRUE", "timestamp": "2009-11-10T23:00:00.0Z"}
    std::string json = "{";
    json += "\"uid\": \"" + last_uid + "\", ";
    json += "\"present\": \"" + BoolToString(card_present) + "\", ";
    json += "\"timestamp\": \"" + last_update + "\"";
    json += "}";
    return json;
}

bool State::operator==(State& other) const {
    return (card_present == other.card_present && last_uid == other.last_uid);
}

void State::updateTimestampTo(const State& other) {
    this->last_update = other.last_update;
}

bool State::getCardPresent() {
    return card_present;
}