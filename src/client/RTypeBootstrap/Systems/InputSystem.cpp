#include "../registry.h"
#include "../Components/ControllableComponent.h"

void input_system(registry& r, sparse_array<ControllableComponent> const& controllable)
{
	for (auto const& i : controllable) {
		if (i) {

		}
	}
}