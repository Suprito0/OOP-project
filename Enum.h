#ifndef ENUM_H
#define ENUM_H
// Enumarators for the properties of the cards
enum Color
{
    Red,
    Green,
    Blue,
    Yellow,
    None
};
enum CardType
{
    Number,
    Action,
    Special_Action
};
enum ActionType
{
    Skip,
    Reverse,
    Draw_Two,
    Wild,
    Wild_Draw_Four
};

#endif