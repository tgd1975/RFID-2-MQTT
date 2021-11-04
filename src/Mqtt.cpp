#include "Mqtt.h"
#include <algorithm>

Mqtt::Mqtt(string id, string publish_topic, string subscription_topic, string host, int port, string username, string password){

    mosqpp::lib_init();
    this->id = id;
    this->keepalive = 60;
    this->port = port;
    this->host = host;
    this->publish_topic = publish_topic;
    this->subscription_topic = subscription_topic;
    this->last_rfid_state = State();

    mosquittopp::username_pw_set(username.c_str(), password.c_str());


    /*
     * Connect to an MQTT broker. This is a non-blocking call. If you use mosquitto_connect_async your client must use
     * the threaded interface mosquitto_loop_start.
     */
    connect_async(this->host.c_str(), this->port, this->keepalive);
    loop_start();
    subscribe();
}



Mqtt::Mqtt(string id, string publish_topic, string subscription_topic, string host, int port) : mosquittopp(id.c_str())
{
    mosqpp::lib_init();
    this->id = id;
    this->keepalive = 60;
    this->port = port;
    this->host = host;
    this->publish_topic = publish_topic;
    this->subscription_topic = subscription_topic;
    this->last_rfid_state = State();    


    /*
     * Connect to an MQTT broker. This is a non-blocking call. If you use mosquitto_connect_async your client must use
     * the threaded interface mosquitto_loop_start.
     */
    connect_async(this->host.c_str(), this->port, this->keepalive);
    loop_start();
    subscribe();
};

Mqtt::~Mqtt() {
    disconnect();
    loop_stop();
    mosqpp::lib_cleanup();
}

bool Mqtt::publish()
{
    /*
     * NULL: pointer to an int.  If not NULL, the function will set this to the message id of this particular message.
     * This can be then used with the publish callback to determine when the message has been sent.
     * Note that although the MQTT protocol doesn’t use message ids for messages with QoS=0, libmosquitto assigns them
     * message ids so they can be tracked with this parameter.
     *
     * publish_topic.c_str(): null terminated string of the topic to publish to.
     *
     * message.length(): the size of the payload (bytes). Valid values are between 0 and 268,435,455.
     *
     * message.c_str(): pointer to the data to send.  If message.length() > 0 this must be a valid memory location.
     *
     * 1: integer value 0, 1 or 2 indicating the Quality of Service to be used for the message.
     *
     * false: set to true to make the message retained.
     *
     */

    string message = last_rfid_state.getJson();

    cout << TAG << "publishing message \"" << message << "\"" << endl;

    int answer = mosqpp::mosquittopp::publish(nullptr, publish_topic.c_str(), message.length(), message.c_str(), 1, false);
    return (answer == MOSQ_ERR_SUCCESS);
}

bool Mqtt::subscribe() {
    bool success = true;
    int answer = mosquittopp::subscribe(nullptr, subscription_topic.c_str());
    if(answer != MOSQ_ERR_SUCCESS){
        success = false;
    }
    return success;
}

void Mqtt::on_subscribe(int, int, const int *) {
    cout << TAG <<"Subscription succeeded." << endl;
}

inline void toUpperCase(std::string& str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
}

void Mqtt::on_message(const struct mosquitto_message *message) {

    string payload = string(static_cast<char *>(message->payload));
    string topic = string(message->topic);

    cout<< TAG << "topic: " << topic << " payload: " << payload << endl;

    toUpperCase(payload);

    if (payload == "TRUE") publish();
}

void Mqtt::on_disconnect(int rc) {
    cout << TAG << "disconnection(" << rc << ")" << endl;
}

void Mqtt::on_connect(int rc)
{
    if ( rc == 0 ) {
        cout << TAG << "connected with server" << endl;
    } else {
        cout << TAG << "impossible to connect with server(" << rc << ")" << endl;
    }
}

void Mqtt::on_publish(int mid)
{
    cout << TAG << "Message (" << mid << ") succeed to be published " << endl;
}

bool Mqtt::publishRfidState(const State& currentRfidState) {
    if (currentRfidState == this->last_rfid_state) {
        this->last_rfid_state.updateTimestampTo(currentRfidState);
        return true;
    } else {
        this->last_rfid_state = State(currentRfidState);
        return publish();
    }
}