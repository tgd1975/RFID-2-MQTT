#ifndef MQTTPUBLISHER_STATE_H
#define MQTTPUBLISHER_STATE_H


#include <string>


class State {
private:
    std::string last_uid;
    bool card_present;   
    std::string last_update;

public:
    State();
    State(std::string uid, bool present);
    State(const State& other);

    void setLAST_UID(std::string uid);
    void setCARD_PRESENT(bool present);
    void setValues(std::string uid, bool present);
    void updateTimestampTo(const State& other);

    std::string getJson();
    bool getCardPresent();

    bool operator==(State& other) const;
};

#endif //MQTTPUBLISHER_STATE_H
