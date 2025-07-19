#ifndef WARFRAME_MANIFESTS_H
#define WARFRAME_MANIFESTS_H

#include "Warframe/Manifest/Export/Customs.h"
#include "Warframe/Manifest/Export/Drones.h"
#include "Warframe/Manifest/Export/Flavour.h"
#include "Warframe/Manifest/Export/FusionBundles.h"
#include "Warframe/Manifest/Export/Gear.h"
#include "Warframe/Manifest/Export/Generic.h"
#include "Warframe/Manifest/Export/Keys.h"
#include "Warframe/Manifest/Export/Manifest.h"
#include "Warframe/Manifest/Export/Recipes.h"
#include "Warframe/Manifest/Export/Regions.h"
#include "Warframe/Manifest/Export/RelicArcane.h"
#include "Warframe/Manifest/Export/Resources.h"
#include "Warframe/Manifest/Export/Sentinels.h"
#include "Warframe/Manifest/Export/SortieRewards.h"
#include "Warframe/Manifest/Export/Upgrades.h"
#include "Warframe/Manifest/Export/Warframes.h"
#include "Warframe/Manifest/Export/Weapons.h"

struct Exports {
  Warframe::Manifest::Export::Customs customs;
  Warframe::Manifest::Export::Drones drones;
  Warframe::Manifest::Export::Flavour flavour;
  Warframe::Manifest::Export::FusionBundles fusion_bundle;
  Warframe::Manifest::Export::Gear gear;
  Warframe::Manifest::Export::Keys keys;
  Warframe::Manifest::Export::Recipes recipes;
  Warframe::Manifest::Export::Regions regions;
  Warframe::Manifest::Export::RelicArcane relic_acrane;
  Warframe::Manifest::Export::Resources resources;
  Warframe::Manifest::Export::Sentinels sentinels;
  Warframe::Manifest::Export::SortieRewards sortie_rewards;
  Warframe::Manifest::Export::Upgrades upgrades;
  Warframe::Manifest::Export::Warframes warframes;
  Warframe::Manifest::Export::Weapons weapons;
  Warframe::Manifest::ExportManifest manifest;
};

#endif // WARFRAME_MANIFESTS_H