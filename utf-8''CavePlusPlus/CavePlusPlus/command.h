#ifndef COMMAND_H
#define COMMAND_H

#include "cave.h"

#include <string>

using namespace std;

// superclass of all user commands.
class Command {

public:
    Command(string triggerWord) : trigger(triggerWord) {}

    virtual bool triggersOn (string userCommand) {

        string userTrigger = userCommand;
        int index = userCommand.find(' ');
        if (index > 0)
                userTrigger = userCommand.substr(0, userCommand.find(' '));
        return trigger.compare(userTrigger) == 0;
    }

    virtual void fire(Cave& c, string arguments) =0;

protected:
    string tail(string userCommand) {

        int pos = userCommand.find(' ');
        if (pos >= 0)
            return userCommand.substr(userCommand.find(' ')+1, userCommand.length());
        else
            return "";
    }

private:
    string trigger;
};

#endif // COMMAND_H
