class CfgMods
{
	class ImmersiveArmor
	{
		type = "mod";
		dependencies[] = { "Game", "World" };
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = { "ImmersiveArmor\scripts\3_Game" };
			};
			class worldScriptModule
			{
				value = "";
				files[] = { "ImmersiveArmor\scripts\4_World" };
			};
		};
	};
};
class CfgPatches
{
	class ImmersiveArmor
	{
		requiredVersion = 0.1;
		requiredAddons[] = { "DZ_Weapons_Projectiles" };
	};
};

class CfgVehicles
{
	class Inventory_Base;
	// Hitbox base
	class IA_ArmorHitbox_Base : Inventory_Base
	{
		scope = 0;
		class ImmersiveArmorHitbox
		{
			damageCoefPlayer = 0.05;// Percentage of damage received by the hitbox that transfers to the player  
			damageCoefItem = 0.3;// Percentage of damage received by the hitbox that transfers to the linked item  
			damageZone = "Torso";// DamageZone where the damage will be applied  
		};
	};
	class IA_HelmetBase : IA_ArmorHitbox_Base
	{
		scope = 0;
		class ImmersiveArmorHitbox
		{
			damageCoefPlayer = 0.1;
			damageCoefItem = 0.3;
			damageZone = "Head";
		};
	};
};
// Penetration doesn�t seem to factor in projectile weight(at least, my tests didn�t confirm it).
// Some calibers don�t penetrate as much as they should based on weight, so I had to modify the caliber parameter to compensate.
// This does not change damage or range � only penetration depth, so your custom weapon balancing should remain unaffected.
class CfgAmmo
{
	class DamageApplied;// ???
	class Bullet_Base;
	class Shotgun_Base;
	class Bullet_556x45 : Bullet_Base
	{
		caliber = 1.05;// 1
	};
	class Bullet_545x39 : Bullet_Base
	{
		caliber = 1.25;// 0.9
	};
	class Bullet_762x54 : Bullet_Base
	{
		caliber = 1.7;// 1
	};
	class Bullet_308Win : Bullet_Base
	{
		caliber = 1.7;// 1
	};
	class Bullet_762x39 : Bullet_Base
	{
		caliber = 1;// 1
	};
	class Bullet_45ACP : Bullet_Base
	{
		caliber = 1.2;// 0.8
	};
	class Bullet_357 : Bullet_Base
	{
		caliber = 1.1;// 1
	};
	class Bullet_9x19 : Bullet_Base
	{
		caliber = 1;// 0.8
	};
	class Bullet_380 : Bullet_Base
	{
		caliber = 1;// 0.8
	};
	class Bullet_22 : Bullet_Base
	{
		caliber = 0.5;// 0.7
	};
	class Bullet_9x39AP : Bullet_Base
	{
		caliber = 3;// 1.2
		class DamageApplied : DamageApplied
		{
			class Health
			{
				damage = 75;
				//armorDamage = 3; No need for that anymore
			};
		};
	};
	class Bullet_9x39 : Bullet_Base
	{
		caliber = 2;// 0.9
	};

	// Backface deformation MELEE blunt damage.  
	// If you haven't created a custom blunt damage type for your ammo, the hitbox will apply PROJECTILE damage to the player.
	// This is not ideal for medical mods.  
	class MeleeDamage;
	class IA_ArmorBlunt_Base : MeleeDamage
	{
		hitAnimation = 0;
		class DamageApplied
		{
			type = "Melee";
			bleedThreshold = 0;
		};
	};

	// Just add "IA_ArmorBlunt_" and copy DamageApplied.  
	// Don't forget "DamageApplied : DamageApplied", otherwise the hitbox won't do any damage when hit. 
	class IA_ArmorBlunt_Bullet_12GaugePellets : IA_ArmorBlunt_Base
	{
		class DamageApplied : DamageApplied
		{
			class Health
			{
				damage = 35;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 35;
			};
		};
	};
	class IA_ArmorBlunt_Bullet_12GaugeSlug : IA_ArmorBlunt_Base
	{
		class DamageApplied : DamageApplied
		{
			class Health
			{
				damage = 110;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 110;
			};
		};
	};
	class IA_ArmorBlunt_Bullet_12GaugeRubberSlug : IA_ArmorBlunt_Base
	{
		class DamageApplied : DamageApplied
		{
			class Health
			{
				damage = 0;
			};
			class Blood
			{
				damage = 0;
			};
			class Shock
			{
				damage = 150;
			};
		};
	};
	class IA_ArmorBlunt_Bullet_12GaugeBeanbag : IA_ArmorBlunt_Base
	{
		class DamageApplied : DamageApplied
		{
			class Health
			{
				damage = 0;
			};
			class Blood
			{
				damage = 0;
			};
			class Shock
			{
				damage = 100;
			};
		};
	};
	class IA_ArmorBlunt_Bullet_556x45 : IA_ArmorBlunt_Base
	{
		class DamageApplied : DamageApplied
		{
			class Health
			{
				damage = 110;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 110;
			};
		};
	};
	class IA_ArmorBlunt_Bullet_556x45Tracer : IA_ArmorBlunt_Bullet_556x45 {};
	class IA_ArmorBlunt_Bullet_545x39 : IA_ArmorBlunt_Base
	{
		class DamageApplied : DamageApplied
		{
			class Health
			{
				damage = 115;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 115;
				damageOverride[] = { {0.9,1.0} };
			};
		};
	};
	class IA_ArmorBlunt_Bullet_545x39Tracer : IA_ArmorBlunt_Bullet_545x39 {};
	class IA_ArmorBlunt_Bullet_762x54 : IA_ArmorBlunt_Base
	{
		class DamageApplied : DamageApplied
		{
			class Health
			{
				damage = 150;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 150;
				damageOverride[] = { {0.86,1.0} };
			};
		};
	};
	class IA_ArmorBlunt_Bullet_762x54Tracer : IA_ArmorBlunt_Bullet_762x54 {};
	class IA_ArmorBlunt_Bullet_308Win : IA_ArmorBlunt_Base
	{
		class DamageApplied : DamageApplied
		{
			class Health
			{
				damage = 150;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 150;
			};
		};
	};
	class IA_ArmorBlunt_Bullet_308WinTracer : IA_ArmorBlunt_Bullet_308Win {};
	class IA_ArmorBlunt_Bullet_762x39 : IA_ArmorBlunt_Base
	{
		class DamageApplied : DamageApplied
		{
			class Health
			{
				damage = 110;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 110;
				damageOverride[] = { {0.8,1.0} };
			};
		};
	};
	class IA_ArmorBlunt_Bullet_762x39Tracer : IA_ArmorBlunt_Bullet_762x39 {};
	class IA_ArmorBlunt_Bullet_45ACP : IA_ArmorBlunt_Base
	{
		class DamageApplied : DamageApplied
		{
			class Health
			{
				damage = 40;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 40;
				damageOverride[] = { {0.9,1.0} };
			};
		};
	};
	class IA_ArmorBlunt_Bullet_357 : IA_ArmorBlunt_Base
	{
		class DamageApplied : DamageApplied
		{
			class Health
			{
				damage = 65;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 90;
			};
		};
	};
	class IA_ArmorBlunt_Bullet_9x19 : IA_ArmorBlunt_Base
	{
		class DamageApplied : DamageApplied
		{
			class Health
			{
				damage = 40;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 40;
			};
		};
	};
	class IA_ArmorBlunt_Bullet_380 : IA_ArmorBlunt_Base
	{
		class DamageApplied : DamageApplied
		{
			class Health
			{
				damage = 35;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 35;
			};
		};
	};
	class IA_ArmorBlunt_Bullet_22 : IA_ArmorBlunt_Base
	{
		class DamageApplied : DamageApplied
		{
			class Health
			{
				damage = 20;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 20;
			};
		};
	};
	class IA_ArmorBlunt_Bullet_9x39 : IA_ArmorBlunt_Base
	{
		class DamageApplied : DamageApplied
		{
			class Health
			{
				damage = 75;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 75;
				damageOverride[] = { {0.9,1.0} };
			};
		};
	};
	class IA_ArmorBlunt_Bullet_9x39AP : IA_ArmorBlunt_Base
	{
		class DamageApplied : DamageApplied
		{
			class Health
			{
				damage = 75;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 75;
			};
		};
	};
};