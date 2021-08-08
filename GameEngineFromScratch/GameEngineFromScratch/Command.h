//
//  Command.h
//  GameEngineFromScratch
//
//  Created by Ka Cheong Li on 8/8/21.
//

#ifndef Command_h
#define Command_h

class Command {
public:
    virtual ~Command() = default;
    virtual void Execute() = 0;
    virtual void Undo() = 0;
};

#endif /* Command_h */
