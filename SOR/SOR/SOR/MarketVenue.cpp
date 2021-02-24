#include "MarketVenue.h"

void SOR::MarketVenue::set(int venue_id)
{
    _venue_id = venue_id;
}

int SOR::MarketVenue::getVenue_id() const
{
    return _venue_id;
}

SOR::TYPE_MARKET_VENUE_SELL* SOR::MarketVenue::getSellSide()
{
    return &_sell;
}

SOR::TYPE_MARKET_VENUE_BUY* SOR::MarketVenue::getBuySide()
{
    return &_buy;
}
