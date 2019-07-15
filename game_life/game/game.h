#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <set>
#include <algorithm>

using i8 = int8_t;
using i32 = int32_t;

using ui8 = uint8_t;
using ui32 = uint32_t;

namespace NLifeGame {
	class IState {
	public:
		IState(ui32 sizeX, ui32 sizeY);

		virtual void  MakeStep() = 0;

		virtual void Set(ui32 x, ui32 y, bool value) = 0;
		virtual bool Get(ui32 x, ui32 y) const = 0;

		ui32 GetSizeX() const;
		ui32 GetSizeY() const;

	protected:
		ui32 SizeX;
		ui32 SizeY;
	};

	std::ostream& operator<< (std::ostream& out, const IState& state);

	class ISimpleState : public IState {
	public:
		using IState::IState;

		void MakeStep() override;

	private:
		ui8 GetNeighborCount(ui32 x, ui32 y) const;
	};

	class TVectorState : public ISimpleState {
	public:
		TVectorState(const std::vector<std::vector<bool>>& map);
		void Set(ui32 x, ui32 y, bool value) override;
		bool Get(ui32 x, ui32 y) const override;

		bool operator< (const TVectorState& other) const;
	private:
		std::vector<std::vector<bool>> Map;
	};

	template <class TState = TVectorState>
	class TGame {
	public:
		TGame(const std::vector<std::vector<bool>>& state)
			: State(state)
		{}

		void MakeStep() {
			if (GameFinishedFlag) {
				return;
			}
			PrevStates.insert(State);
			State.MakeStep();

			GameFinishedFlag = PrevStates.count(State);
		}

		void Run() {
			while (!Finished()) {
				MakeStep();
			}
		}

		const IState& GetState() const {
			return State;
		}

		bool Finished() const {
			return GameFinishedFlag;
		}

		ui32 GetStepNumber() const {
			return PrevStates.size();
		}

	private:
		TState State;
		std::set<TState> PrevStates;
		bool GameFinishedFlag = false;
	};
}
