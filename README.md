# Immersive Armor — Physical Armor Hitboxes for DayZ

Immersive Armor replaces DayZ's vanilla ballistic armor mechanics with **physical hitboxes attached to character skeletons**. Instead of applying protection based only on the body slot an armor item occupies, bullets must interact with the actual hitbox geometry.

The mod introduces configurable armor protection, penetration materials, armor plates, and blunt-force damage transfer while supporting players, infected, and animals.

## Features

- **Physical armor hitboxes:** Equipped armor creates hitbox entities attached to the appropriate character bones.
- **Hitbox-based protection:** Projectiles interact with armor geometry before reaching the character, allowing hit location and penetration to determine the outcome.
- **Configurable armor:** Define hitboxes, attachment slots, bone offsets, damage zones, and damage transfer coefficients through JSON configuration.
- **Armor plate system:** Supports configurable armor plates with different protection levels and dedicated plate-carrier slots.
- **Penetration materials:** Includes Steel, Kevlar, and Polycarbonate materials with different ballistic protection levels.
- **Blunt-force damage:** Armor impacts transfer configurable damage to the wearer, simulating the force transmitted through a plate even when a projectile does not penetrate.
- **Ballistic adjustments:** Includes penetration-related adjustments to better align supported ammunition with the intended protection levels.
- **Improved Weapon Lift:** Integrated into the mod.

## Showcase

### Immersive Armor

[![Watch Immersive Armor showcase](https://img.youtube.com/vi/qlqCG6EOmW4/hqdefault.jpg)](https://youtu.be/qlqCG6EOmW4)

### Custom Armor and Hitbox Tutorial

[![Watch the custom armor tutorial](https://img.youtube.com/vi/FoxGlHiWR5A/hqdefault.jpg)](https://youtu.be/FoxGlHiWR5A)

The tutorial covers the general workflow for creating custom hitboxes. It predates the current JSON configuration system, so some configuration steps are outdated.

## Armor and Penetration

The mod includes configurable armor protection levels and three penetration material types:

| Material | Intended use |
|---|---|
| Steel | Steel armor and helmets |
| Kevlar | Soft armor and ballistic plates |
| Polycarbonate | Lightweight protective components, such as visors |

Protection levels are calibrated against base-game projectile parameters and penetration tests conducted at 5 meters against armor plates positioned at 90 degrees.

The default configuration uses six armor protection levels, ranging from protection against small-caliber ammunition and shotgun pellets to higher-powered rifle ammunition.

**Compatibility note:** Protection behavior may change when other mods alter projectile speed, caliber, or related ammunition parameters.

## Damage Transfer

When a projectile hits an armor hitbox, damage transfer is controlled by the hitbox configuration.

- **Non-penetrating hit:** The armor can transfer blunt-force damage to the character and damage to the associated armor item.
- **Penetrating hit:** The projectile can continue through the hitbox and damage the character, in addition to the blunt-force impact.

Blunt damage is logged using the `IA_ArmorBlunt_` prefix followed by the ammunition type.

## Configuration

Immersive Armor uses JSON configuration to define armor items, their hitboxes, and the behavior of those hitboxes.

Item configuration supports:

- Permanent hitboxes created when an item is equipped.
- Attachment-slot overrides for armor components such as plates and visors.
- Hitbox types and the skeleton bones to which they attach.
- Position and rotation offsets relative to the selected bone.

Hitbox configuration supports:

- `DamageCoefEntity` — the fraction of hitbox damage transferred to the character.
- `DamageCoefItem` — the fraction of hitbox damage transferred to the associated item.
- `DamageZone` — the character damage zone affected by transferred damage.

For the complete configuration structure and implementation details, see the source files in this repository.

## For Modders

- **Workshop:** [Immersive Armor](https://steamcommunity.com/sharedfiles/filedetails/?id=3403371340)
- **Custom armor tutorial:** [Watch the tutorial](https://youtu.be/FoxGlHiWR5A)

Immersive Armor can be extended with custom armor items, hitbox models, attachment slots, and penetration materials.

Important considerations when creating custom content:

1. **Hitbox orientation:** After creating a custom hitbox, rotate it by `0 90 90` in Object Builder to align it with the bone dimensions.
2. **Coordinate order:** Position offsets use `Y, Z, X`; rotation offsets use `Z, Y, X`.
3. **Penetration material paths:** Verify material paths carefully. An invalid path can cause the game to use the default impenetrable material.
4. **Custom ammunition:** Modded ammunition will require corresponding blunt-damage definitions.
5. **Debugging:** Check the logs if a hitbox does not spawn. Warnings can identify misspelled class names or configuration entries.

The tutorial above demonstrates the general custom-hitbox workflow, but use the current JSON configuration as the reference for configuration-related steps.

## Known Issues and Limitations

- **Arrows and bolts:** Not currently supported correctly; they may penetrate hitboxes farther than intended.
- **Attachment scanning:** Items attached to players, infected, or animals are checked for hitbox creation, including their attachments. This can produce hitboxes in unexpected situations, such as when an item allows a helmet to be attached as an accessory.
- **Custom ammunition and weapon mods:** Mods that change projectile speed, caliber, or other ballistic parameters may produce unpredictable protection results.
- **Helmet brain hitbox:** Vanilla behavior disables the brain hitbox when a helmet is worn. This limitation remains, although it is generally noticeable only with low-penetration ammunition.
- **Network timing:** There may be a short delay between equipping armor and its hitboxes appearing, depending on the server's `networkObjectBatch` setting.
