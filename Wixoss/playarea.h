#ifndef PLAYAREA_H
#define PLAYAREA_H
#include <vector>
#include "card.h"

class PlayArea
{
public:
    PlayArea();
    ~PlayArea();
private:
    std::vector<Card> hand;
    std::vector<Card> mainDeck;
    std::vector<Card> lrigDeck;
    std::vector<Card> enerZone;
    std::vector<Card> lrigZone;
    std::vector<Card> signiZone;
    std::vector<Card> lrigTrash;
    std::vector<Card> trash;
    std::vector<Card> lifeCloth;
    std::vector<Card> checkZone;
};

#endif // PLAYAREA_H
