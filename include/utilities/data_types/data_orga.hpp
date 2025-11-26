#pragma once

#include <stdexcept>

namespace mpml
{
	

	struct Option
	{
		enum Data_Placement
			: unsigned short
		{
			Column = 0,
			Row
		};

		constexpr Option(Data_Placement type)
			: dat_pla{type}
		{
			if (dat_pla != Column && dat_pla != Row)
				throw std::runtime_error("ERROR::BAD_TYPE: data placement must be either Row or Column major");
		}

		constexpr bool operator==(const Option::Data_Placement& data) const
		{
			return data == dat_pla;
		}

		Data_Placement dat_pla;
	};


}