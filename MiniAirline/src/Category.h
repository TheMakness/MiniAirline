#pragma once

namespace Category
{
	enum Type
	{
		None = 0,
		Scene = 1 << 0,
		Aircraft = 1 << 1,
		Selected = 1 << 2,
	};
}