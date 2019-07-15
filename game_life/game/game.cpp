#include "game.h"

namespace {
	const std::list<std::pair<i8, i8>> NeighborShifts = {
		{-1, -1}, {-1,0}, {-1,1},
		{0, -1}, {0,1},
		{1, -1}, {1,0}, {1,1}
	};
};

namespace NLifeGame {
	IState::IState(ui32 sizeX, ui32 sizeY)
		: SizeX(sizeX)
		, SizeY(sizeY)
	{}

	ui32 IState::GetSizeX() const {
		return SizeX;
	}
	ui32 IState::GetSizeY() const {
		return SizeY;
	}

	void ISimpleState::MakeStep() {
		std::list<std::pair<ui32, ui32>> willDie;
		std::list<std::pair<ui32, ui32>> willBorn;
		for (ui32 x = 0; x < SizeX; ++x) {
			for (ui32 y = 0; y < SizeY; ++y) {
				bool alive = Get(x, y);
				ui8 neighborCount = GetNeighborCount(x, y);
				if (!alive && neighborCount == 3) {
					willBorn.push_back({ x, y });
				}
				if (alive && (neighborCount < 2 || neighborCount > 3)) {
					willDie.push_back({ x, y });
				}
			}
		}
		for (auto&& entity : willBorn) {
			Set(entity.first, entity.second, true);
		}
		for (auto&& entity : willDie) {
			Set(entity.first, entity.second, false);
		}
	}

	ui8 ISimpleState::GetNeighborCount(ui32 x, ui32 y) const {
		ui8 count = 0;
		for (auto&& shift : NeighborShifts) {
			if (x + shift.first >= 0 && y + shift.second >= 0) {
				ui32 nx = x + shift.first;
				ui32 ny = y + shift.second;
				if (0 <= nx && nx < GetSizeX() && 0 <= ny && ny < GetSizeY()) {
					count += Get(nx, ny) ? 1 : 0;
				}
			}
		}
		return count;
	}

	TVectorState::TVectorState(const std::vector<std::vector<bool>>& map)
		: ISimpleState(map.size(), map.front().size())
		, Map(map)
	{}

	void TVectorState::Set(ui32 x, ui32 y, bool value) {
		Map[x][y] = value;
	}

	bool TVectorState::Get(ui32 x, ui32 y) const {
		return Map[x][y];
	}

	bool TVectorState::operator< (const TVectorState& other) const {
		return Map < other.Map;
	}

	std::ostream& operator<< (std::ostream& out, const IState& state) {
		for (ui32 x = 0; x < state.GetSizeX(); ++x) {
			for (ui32 y = 0; y < state.GetSizeY(); ++y) {
				out << (state.Get(x, y) ? '*' : '0');
			}
			out << std::endl;
		}
		return out;
	}
}