#include "players.hpp"

// return the cards of current player
std::vector<Card>& getCurrentPlayerCards(GameSystem& gameSys)
{
    switch(Player(gameSys.wichPlayerTurn))
    {
        case Player::P0:
            return gameSys.p0;
            break;
        case Player::P1:
            return gameSys.p1;
            break;
        case Player::P2:
            return gameSys.p2;
            break;
        case Player::P3:
            return gameSys.p3;
            break;
        case Player::P4:
            return gameSys.p4;
            break;
        default: // should not happen
            return gameSys.p0;
            break;
    }
}

// return all the stacks of played cards
std::array<CardAttribute, 5> getCurrentStackNeedingCard(GameSystem& gameSys)
{
    return std::array<CardAttribute, 5>{gameSys.whiteStack, gameSys.blueStack, gameSys.redStack, gameSys.greenStack};
}

// return if card is known with certain to be playable with the hints given
bool isPlayableFromHints(GameSystem& gameSys, Card card)
{
    switch(card.directAttributeHints[1])
    {
        case CardAttribute::White:
            if (int(card.directAttributeHints[0]) == int(gameSys.whiteStack)+1)
            {
                return true;
            }
            break;
        case CardAttribute::Blue:
            if (int(card.directAttributeHints[0]) == int(gameSys.blueStack)+1)
            {
                return true;
            }
            break;
        case CardAttribute::Yellow:
            if (int(card.directAttributeHints[0]) == int(gameSys.yellowStack)+1)
            {
                return true;
            }
            break;
        case CardAttribute::Red:
            if (int(card.directAttributeHints[0]) == int(gameSys.redStack)+1)
            {
                return true;
            }
            break;
        case CardAttribute::Green:
            if (int(card.directAttributeHints[0]) == int(gameSys.greenStack)+1)
            {
                return true;
            }
            break;
        default:
            break;
    }
    return false;
}

// return if card is known with certain to be playable knowing what card it is
bool isPlayableFromCard(GameSystem& gameSys, Card card)
{
    switch(card.color)
    {
        case CardAttribute::White:
            if (int(card.number) == int(gameSys.whiteStack)+1)
            {
                return true;
            }
            break;
        case CardAttribute::Blue:
            if (int(card.number) == int(gameSys.blueStack)+1)
            {
                return true;
            }
            break;
        case CardAttribute::Yellow:
            if (int(card.number) == int(gameSys.yellowStack)+1)
            {
                return true;
            }
            break;
        case CardAttribute::Red:
            if (int(card.number) == int(gameSys.redStack)+1)
            {
                return true;
            }
            break;
        case CardAttribute::Green:
            if (int(card.number) == int(gameSys.greenStack)+1)
            {
                return true;
            }
            break;
        default:
            break;
    }
    return false;
}

// check and play one of the current player's card if it is known to be playable
bool checkCertainMove(GameSystem& gameSys)
{
    std::vector<Card> pCards = getCurrentPlayerCards(gameSys);
    for (int i = 0; i < int(pCards.size()); i++)
    {
        if (isPlayableFromHints(gameSys, pCards[i]))
        {
            gameSys.playCard(i);
            return true;
        }
    }
    return false;
}

// give a hint that is coherent to the current state of the stacks
bool giveCoherentHint(GameSystem& gameSys)
{
    if (gameSys.wichPlayerTurn != 1)
    {
        for (int i = 0; i < int(gameSys.p0.size()); i++)
        {
            if (isPlayableFromCard(gameSys, gameSys.p0[i]))
            {
                if (gameSys.p0[i].directAttributeHints.front() == CardAttribute::null)
                {
                    gameSys.giveHint(gameSys.p0[i].number, Player::P0);
                    return true;
                }
                else if (gameSys.p0[i].directAttributeHints.back() == CardAttribute::null)
                {
                    gameSys.giveHint(gameSys.p0[i].color, Player::P0);
                    return true;
                }
            }
        }
    }
    if (gameSys.wichPlayerTurn != 2)
    {
        for (int i = 0; i < int(gameSys.p1.size()); i++)
        {
            if (isPlayableFromCard(gameSys, gameSys.p1[i]))
            {
                if (gameSys.p1[i].directAttributeHints.front() == CardAttribute::null)
                {
                    gameSys.giveHint(gameSys.p1[i].number, Player::P1);
                    return true;
                }
                else if (gameSys.p1[i].directAttributeHints.back() == CardAttribute::null)
                {
                    gameSys.giveHint(gameSys.p1[i].color, Player::P1);
                    return true;
                }
            }
        }
    }
    if (gameSys.wichPlayerTurn != 3)
    {
        for (int i = 0; i < int(gameSys.p2.size()); i++)
        {
            if (isPlayableFromCard(gameSys, gameSys.p2[i]))
            {
                if (gameSys.p2[i].directAttributeHints.front() == CardAttribute::null)
                {
                    gameSys.giveHint(gameSys.p2[i].number, Player::P2);
                    return true;
                }
                else if (gameSys.p2[i].directAttributeHints.back() == CardAttribute::null)
                {
                    gameSys.giveHint(gameSys.p2[i].color, Player::P2);
                    return true;
                }
            }
        }
    }
    if (gameSys.wichPlayerTurn != 4)
    {
        for (int i = 0; i < int(gameSys.p3.size()); i++)
        {
            if (isPlayableFromCard(gameSys, gameSys.p3[i]))
            {
                if (gameSys.p3[i].directAttributeHints.front() == CardAttribute::null)
                {
                    gameSys.giveHint(gameSys.p3[i].number, Player::P3);
                    return true;
                }
                else if (gameSys.p3[i].directAttributeHints.back() == CardAttribute::null)
                {
                    gameSys.giveHint(gameSys.p3[i].color, Player::P3);
                    return true;
                }
            }
        }
    }
    if (gameSys.wichPlayerTurn != 5)
    {
        for (int i = 0; i < int(gameSys.p4.size()); i++)
        {
            if (isPlayableFromCard(gameSys, gameSys.p4[i]))
            {
                if (gameSys.p4[i].directAttributeHints.front() == CardAttribute::null)
                {
                    gameSys.giveHint(gameSys.p4[i].number, Player::P4);
                    return true;
                }
                else if (gameSys.p4[i].directAttributeHints.back() == CardAttribute::null)
                {
                    gameSys.giveHint(gameSys.p4[i].color, Player::P4);
                    return true;
                }
            }
        }
    }
    return false;
}

// check if a card is disposable based on its number and the current stacks state
bool isDisposableNumberFromHints(Card card, CardAttribute min)
{
    if (card.directAttributeHints[0] <= min)
    {
        return true;
    }
    return false;
}

// check if a card is disposable based on its color and the current stacks state
bool isDisposableColorFromHints(GameSystem& gameSys, Card card)
{
    switch(card.directAttributeHints[1])
    {
        case CardAttribute::White:
            if (gameSys.whiteStack == CardAttribute::Five)
            {
                return true;
            }
            break;
        case CardAttribute::Blue:
            if (gameSys.blueStack == CardAttribute::Five)
            {
                return true;
            }
            break;
        case CardAttribute::Yellow:
            if (gameSys.yellowStack == CardAttribute::Five)
            {
                return true;
            }
            break;
        case CardAttribute::Red:
            if (gameSys.redStack == CardAttribute::Five)
            {
                return true;
            }
            break;
        case CardAttribute::Green:
            if (gameSys.greenStack == CardAttribute::Five)
            {
                return true;
            }
            break;
        default:
            break;
    }
    return false;
}

// check if a card is disposable based on its number and the current stacks state
bool isDisposableNumberFromCard(Card card, CardAttribute min)
{
    if (card.number <= min)
    {
        return true;
    }
    return false;
}

// check if a card is disposable based on its color and the current stacks state
bool isDisposableColorFromCard(GameSystem& gameSys, Card card)
{
    switch(card.color)
    {
        case CardAttribute::White:
            if (gameSys.whiteStack == CardAttribute::Five)
            {
                return true;
            }
            break;
        case CardAttribute::Blue:
            if (gameSys.blueStack == CardAttribute::Five)
            {
                return true;
            }
            break;
        case CardAttribute::Yellow:
            if (gameSys.yellowStack == CardAttribute::Five)
            {
                return true;
            }
            break;
        case CardAttribute::Red:
            if (gameSys.redStack == CardAttribute::Five)
            {
                return true;
            }
            break;
        case CardAttribute::Green:
            if (gameSys.greenStack == CardAttribute::Five)
            {
                return true;
            }
            break;
        default:
            break;
    }
    return false;
}

// give a hint with the intention to discard that card, that is coherent to the current state of the stacks
bool giveDisposableHint(GameSystem& gameSys)
{
    CardAttribute min = std::min({gameSys.whiteStack, gameSys.blueStack, gameSys.yellowStack, gameSys.redStack, gameSys.greenStack});
    if (gameSys.wichPlayerTurn != 1)
    {
        for (int i = 0; i < int(gameSys.p0.size()); i++)
        {
            if (isDisposableNumberFromCard(gameSys.p0[i], min) && gameSys.p0[i].directAttributeHints[0] == CardAttribute::null)
            {
                gameSys.giveHint(gameSys.p0[i].number, Player::P0);
                return true;
            }
            if (isDisposableColorFromCard(gameSys, gameSys.p0[i]) && gameSys.p0[i].directAttributeHints[1] == CardAttribute::null)
            {
                gameSys.giveHint(gameSys.p0[i].color, Player::P0);
                return true;
            }
        }
    }
    if (gameSys.wichPlayerTurn != 2)
    {
        for (int i = 0; i < int(gameSys.p1.size()); i++)
        {
            if (isDisposableNumberFromCard(gameSys.p1[i], min) && gameSys.p1[i].directAttributeHints[0] == CardAttribute::null)
            {
                gameSys.giveHint(gameSys.p1[i].number, Player::P0);
                return true;
            }
            if (isDisposableColorFromCard(gameSys, gameSys.p1[i]) && gameSys.p1[i].directAttributeHints[1] == CardAttribute::null)
            {
                gameSys.giveHint(gameSys.p1[i].color, Player::P0);
                return true;
            }
        }
    }
    if (gameSys.wichPlayerTurn != 3)
    {
        for (int i = 0; i < int(gameSys.p2.size()); i++)
        {
            if (isDisposableNumberFromCard(gameSys.p2[i], min) && gameSys.p2[i].directAttributeHints[0] == CardAttribute::null)
            {
                gameSys.giveHint(gameSys.p2[i].number, Player::P0);
                return true;
            }
            if (isDisposableColorFromCard(gameSys, gameSys.p2[i]) && gameSys.p2[i].directAttributeHints[1] == CardAttribute::null)
            {
                gameSys.giveHint(gameSys.p2[i].color, Player::P0);
                return true;
            }
        }
    }
    if (gameSys.wichPlayerTurn != 4)
    {
        for (int i = 0; i < int(gameSys.p3.size()); i++)
        {
            if (isDisposableNumberFromCard(gameSys.p3[i], min) && gameSys.p3[i].directAttributeHints[0] == CardAttribute::null)
            {
                gameSys.giveHint(gameSys.p3[i].number, Player::P0);
                return true;
            }
            if (isDisposableColorFromCard(gameSys, gameSys.p3[i]) && gameSys.p3[i].directAttributeHints[1] == CardAttribute::null)
            {
                gameSys.giveHint(gameSys.p3[i].color, Player::P0);
                return true;
            }
        }
    }
    if (gameSys.wichPlayerTurn != 5)
    {
        for (int i = 0; i < int(gameSys.p4.size()); i++)
        {
            if (isDisposableNumberFromCard(gameSys.p4[i], min) && gameSys.p4[i].directAttributeHints[0] == CardAttribute::null)
            {
                gameSys.giveHint(gameSys.p4[i].number, Player::P0);
                return true;
            }
            if (isDisposableColorFromCard(gameSys, gameSys.p4[i]) && gameSys.p4[i].directAttributeHints[1] == CardAttribute::null)
            {
                gameSys.giveHint(gameSys.p4[i].color, Player::P0);
                return true;
            }
        }
    }
    return false;
}

// discard a known disposable card
bool discardDisposableCard(GameSystem& gameSys)
{
    CardAttribute min = std::min({gameSys.whiteStack, gameSys.blueStack, gameSys.yellowStack, gameSys.redStack, gameSys.greenStack});
    std::vector<Card> pCards = getCurrentPlayerCards(gameSys);
    for (int i = 0; i < int(pCards.size()); i++)
    {
        if (isDisposableNumberFromHints(pCards[i], min))
        {
            gameSys.discardCard(i);
            return true;
        }
        if (isDisposableColorFromHints(gameSys, pCards[i]))
        {
            gameSys.discardCard(i);
            return true;
        }
    }
    return false;
}

// discard oldest card in hand that have none direct hint
bool discardOldestUnhintedCard(GameSystem& gameSys)
{
    std::vector<Card> pCards = getCurrentPlayerCards(gameSys);
    for (int i = 0; i < int(pCards.size()); i++)
    {
        if (pCards[i].directAttributeHints[0] == CardAttribute::null && pCards[i].directAttributeHints[1] == CardAttribute::null)
        {
            gameSys.discardCard(i);
            return true;
        }
    }
    return false;
}

// check and play one of the current player's card by looking at his own cards to know if its playable (cheating)
bool tryCheatMove(GameSystem& gameSys)
{
    std::vector<Card> pCards = getCurrentPlayerCards(gameSys);
    for (int i = 0; i < int(pCards.size()); i++)
    {
        if (isPlayableFromCard(gameSys, pCards[i]))
        {
            gameSys.playCard(i);
            return true;
        }
    }
    return false;
}

// chack and discard card by looking at his own cards to know if it's disposable (cheating)
bool tryCheatDiscardUseless(GameSystem& gameSys)
{
    CardAttribute min = std::min({gameSys.whiteStack, gameSys.blueStack, gameSys.yellowStack, gameSys.redStack, gameSys.greenStack});
    std::vector<Card> pCards = getCurrentPlayerCards(gameSys);
    for (int i = 0; i < int(pCards.size()); i++)
    {
        if (isDisposableNumberFromCard(pCards[i], min))
        {
            gameSys.discardCard(i);
            return true;
        }
        if (isDisposableColorFromCard(gameSys, pCards[i]))
        {
            gameSys.discardCard(i);
            return true;
        }
    }
    return false;
}

// give a random hint (especially to the player / p0)
bool giveRandomHint(GameSystem& gameSys)
{
    if (gameSys.wichPlayerTurn != 1)
    {
        for (int i = 0; i < int(gameSys.p0.size()); i++)
        {
            if (gameSys.p0[i].directAttributeHints[0] == CardAttribute::null)
            {
                gameSys.giveHint(gameSys.p0[i].number, Player::P0);
                return true;
            }
            if (gameSys.p0[i].directAttributeHints[1] == CardAttribute::null)
            {
                gameSys.giveHint(gameSys.p0[i].color, Player::P0);
                return true;
            }
        }
    }
    else
    {
        gameSys.giveHint(CardAttribute::One, Player::P1);
        return true;
    }
    return false;
}

// look if card is "unique" to know if it is an important card or not (look if one copy left in drawPile and players hands)
bool lookIfCardIsUnique(GameSystem& gameSys, Card card)
{
    bool foundOneInDiscardPile = false;
    if (card.number == CardAttribute::Five)
    {
        return true;
    }
    for (int i = 0; i < int(gameSys.discardPile.size()); i++)
    {
        if ((gameSys.discardPile[i].color == card.color) && (gameSys.discardPile[i].number == card.number))
        {
            if (card.number != CardAttribute::One)
            {
                return true;
            }
            else
            {
                if (foundOneInDiscardPile)
                {
                    return true;
                }
                else
                {
                    foundOneInDiscardPile = true;
                }
            }
        }
    }
    return false;
}

bool tryCheatSafeDiscard(GameSystem& gameSys)
{
    std::vector<Card> pCards = getCurrentPlayerCards(gameSys);
    for (int i = 0; i < int(pCards.size()); i++)
    {
        if (!lookIfCardIsUnique(gameSys, pCards[i]))
        {
            gameSys.discardCard(i);
            return true;
        }
    }
    return false;
}


/*
- Check and play move if certain
- If not try to give a hint thats correspond with current stack
- If not try to give a hint for discardable cards
- If not discard a known disposable card
- If not discard oldest card that do not have direct hint
*/
void Certainty::genMove(GameSystem& gameSys)
{
    if (checkCertainMove(gameSys))
    {
        return;
    }
    if (gameSys.hintTokens != 0)
    {
        if (giveCoherentHint(gameSys))
        {
            return;
        }
        if (giveDisposableHint(gameSys))
        {
            return;
        }
    }
    if (gameSys.hintTokens != 8)
    {
        if (discardDisposableCard(gameSys))
        {
            return;
        }
        if (discardOldestUnhintedCard(gameSys))
        {
            return;
        }
    }
    // default bad move if none of the above didn't checked (should not happen ?)
    gameSys.playCard(0);
}

/*
- Cheat and look into his cards, play if possible
- Otherwise if token != 8, discard useless card
- Otherwise give hint to player
- Otherwise if token != 8, discard safe card
*/
void Omniscient::genMove(GameSystem& gameSys)
{
    if (tryCheatMove(gameSys))
    {
        return;
    }
    if (gameSys.hintTokens != 8)
    {
        if (tryCheatDiscardUseless(gameSys))
        {
            return;
        }
    }
    if (gameSys.hintTokens != 0)
    {
        if (giveRandomHint(gameSys))
        {
            return;
        }
    }
    if (gameSys.hintTokens != 8)
    {
        if (tryCheatSafeDiscard(gameSys))
        {
            return;
        }
    }
    // default bad move if none of the above didn't checked (should not happen ?)
    gameSys.playCard(0);
}

bool tryHintIntentionAndPlay(GameSystem& gameSys)
{
    std::vector<Card> pCards = getCurrentPlayerCards(gameSys);
    return false;
}

bool tryGiveHintIntention(GameSystem& gameSys)
{
    std::vector<Card> pCards = getCurrentPlayerCards(gameSys);
    return false;
}

bool tryDiscardSafe(GameSystem& gameSys)
{
    std::vector<Card> pCards = getCurrentPlayerCards(gameSys);
    return false;
}

/*
- if indirect hint has be given, with intention to play, then play
- Otherwise if token != 0, and can give good hint
- Otherwise if token != 8, and can discard safe useless card
- Otherwise discard oldest unhinted card
*/
void RuleBased::genMove(GameSystem& gameSys)
{

}

/*
- HAT !
*/
void HatPrinciple::genMove(GameSystem& gameSys)
{

}


