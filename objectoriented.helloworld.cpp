#include <iostream>
#include <memory>
#include <string>

using namespace std;

class StreamInput {
    public:
        StreamInput(string prompt = "Hiya Chuck, what's your name?") {
            this->prompt = prompt;
        };
        string getInput() {
            return this->input;
        }
        void setInput() {
            cout << this->prompt << endl;
            cin >> input;
        };
    private:
        string input;
        string prompt;
};

class Message {
    public:
        Message(string name = "Chuck") {
            this->msg = "Hiya " + name + ", it's John.";
        };
        void printMsg() {
            cout << msg << endl;
        };
    private:
        string msg;
};

int main()
{
    StreamInput input;
    input.setInput();
    Message message(input.getInput());
    message.printMsg();

    return 0;
}