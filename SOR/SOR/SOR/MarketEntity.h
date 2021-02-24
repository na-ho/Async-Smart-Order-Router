#pragma

namespace SOR
{
	class MarketVenue;
	template <typename T, typename U>
	struct MarketEntity
	{
		T _price;
		U _qty;

		MarketVenue* _marketVenue;
	};

	template <typename T, typename U>
	struct MarketEntityCmpLessBegin {
		bool operator() (const MarketEntity<T,U>& a, const MarketEntity<T, U>& b) const
		{
			return a._price < b._price;
		}
	};

	template <typename T, typename U>
	struct MarketEntityCmpMoreBegin {
		bool operator() (const MarketEntity<T, U>& a, const MarketEntity<T, U>& b) const
		{
			return a._price > b._price;
		}
	};
}

