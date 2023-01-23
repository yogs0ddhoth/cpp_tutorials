#include <iostream>
#include <vector>
#include <string>

using namespace std;

string cInput()
{
    string name;
    cout << "Hiya Chuck, what's your name? " << endl;
    cin >> name;
    return name;
}

vector<string> getMsg(string name = "Chuck")
{
    vector<string> msg {
        "Hiya",
        name + ",",
        "it's",
        "John.",
    };

    return msg;
}

void printMsg(vector<string> msg)
{
    for (const string& word : msg)
    {
        cout << word << " ";
    }
    cout << endl;
}

int main()
{
    string input = cInput();
    vector<string> message = getMsg(input);
    printMsg(message);

    return 0;
}