#include "MarketsData.h"

SOR::MarketsData* SOR::MarketsData::s_instance = 0;

SOR::MarketSymbolData* SOR::MarketsData::getSymbolData(const std::string& symbol)
{
	MarketSymbolData* symbolData = NULL;
	_symbols.find(symbol, symbolData);
	return symbolData;
}
