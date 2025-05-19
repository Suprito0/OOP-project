
#include "Enum.h"
#include "Card.h"
std::string colorToString(Color color) {
    switch (color) {
        case Red: return "Red";
        case Green: return "Green";
        case Blue: return "Blue";
        case Yellow: return "Yellow";
        case None: return "Wild";
        default: return "Unknown";
    }
}

std::string cardTypeToString(CardType type) {
    switch (type) {
        case Number: return "Number";
        case Action: return "Action";
        case Special_Action: return "Special Action";
        default: return "Unknown";
    }
}

std::string actionTypeToString(ActionType action) {
    switch (action) {
        case Skip: return "Skip";
        case Reverse: return "Reverse";
        case Draw_Two: return "Draw Two";
        case Wild: return "Wild";
        case Wild_Draw_Four: return "Wild Draw Four";
        default: return "Unknown";
    }
}
        