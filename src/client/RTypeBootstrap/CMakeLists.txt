# CMakeList.txt : projet CMake pour RTypeBootstrap, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

# Ajoutez une source à l'exécutable de ce projet.
add_executable (RTypeBootstrap "RTypeBootstrap.cpp" "RTypeBootstrap.h" "Entity.h" "sparse_array.h"  "registry.h"  "Components/PositionComponent.h" "Components/VelocityComponent.h" "Components/DrawableComponent.h" "Components/ControllableComponent.h" "Components/HealthComponent.h" "Components/HitBoxComponent.h" "Components/WeaponComponent.h" "Components/AccelerationComponent.h"   "Components/MaximumVelocityComponent.h" "Systems/InputSystem.cpp" "Systems/ShootingSystem.cpp"  )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RTypeBootstrap PROPERTY CXX_STANDARD 20)
endif()

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
