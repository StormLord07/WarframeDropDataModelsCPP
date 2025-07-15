#ifndef STARCHART_MODEL_H
#define STARCHART_MODEL_H

#include "RewardModel.h"
#include <string>
#include <variant>
#include <vector>

namespace planet {
struct Mission {
  std::string gameMode;
  bool isEvent;
  std::variant<Rewards, std::vector<RewardItem>> rewards;
};
} // namespace planet

using Planet = std::map<std::string_view, planet::Mission>;

struct Planets {
  Planet Mercury;
  Planet Venus;
  Planet Earth;
  Planet Mars;
  Planet Jupiter;
  Planet Saturn;
  Planet Uranus;
  Planet Neptune;
  Planet Pluto;
  Planet Ceres;
  Planet Eris;
  Planet Sedna;
  Planet Europa;
  Planet Void;
  Planet Phobos;
  Planet Deimos;
  Planet Lua;
  Planet KuvaFortress;
  Planet Sanctuary;
  Planet Veil;
  Planet Zariman;
  Planet Hyollvania;
  Planet Duviri;
};

template <> struct glz::meta<Planets> {
  using T = Planets;
  static constexpr auto value = glz::object(
      "Mercury", &T::Mercury, "Venus", &T::Venus, "Earth", &T::Earth, "Mars",
      &T::Mars, "Jupiter", &T::Jupiter, "Saturn", &T::Saturn, "Uranus",
      &T::Uranus, "Neptune", &T::Neptune, "Pluto", &T::Pluto, "Ceres",
      &T::Ceres, "Eris", &T::Eris, "Sedna", &T::Sedna, "Europa", &T::Europa,
      "Void", &T::Void, "Phobos", &T::Phobos, "Deimos", &T::Deimos, "Lua",
      &T::Lua, "Kuva Fortress", &T::KuvaFortress, "Sanctuary", &T::Sanctuary,
      "Veil", &T::Veil, "Zariman", &T::Zariman, "Höllvania", &T::Hyollvania,
      "Duviri", &T::Duviri);
};

#endif // STARCHART_MODEL_H