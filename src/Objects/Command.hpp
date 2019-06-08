#ifndef COMMAND_HPP_INCLUDED
#define COMMAND_HPP_INCLUDED

struct Command {
    string type;
    vector<int> parameters;
    Command(string t, vector<int> p):type(t),parameters(p){}
};

#endif // COMMAND_HPP_INCLUDED
