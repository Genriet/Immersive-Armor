class CfgPatches
{
	class ImmersiveArmor
	{
		requiredAddons[] = { "DZ_Data", "DZ_Scripts" };
	};
};
class CfgMods
{
	class ImmersiveArmor
	{
		type = "mod";
		dependencies[] = { "Game", "World", "Mission" };
		class defs
		{
			class imageSets
			{
				files[] = {"ImmersiveArmor\imagesets\IA_BodyArmorSlots.imageset"};
			};
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
class CfgSlots
{
	class Slot_IA_ArmorPlateFront
	{
		name = "IA_ArmorPlateFront";
		displayName = "$STR_Slot_IA_ArmorPlateFront";
		ghostIcon = "set:IA_BodyArmorSlots image:armor_plate";
	};
	class Slot_IA_ArmorPlateBack
	{
		name = "IA_ArmorPlateBack";
		displayName = "$STR_Slot_IA_ArmorPlateBack";
		ghostIcon = "set:IA_BodyArmorSlots image:armor_plate";
	};
};
class CfgVehicles
{
	class Inventory_Base;
	class IA_ArmorHitboxBase : Inventory_Base
	{
		scope = 0;
	};
	class IA_HelmetHitboxBase : IA_ArmorHitboxBase
	{
		scope = 0;
	};

	//Plates
	class IA_ArmorHitbox_ArmorPlate_Class_1 : IA_ArmorHitboxBase
	{
		scope = 1;
		model = "ImmersiveArmor\models\hitboxes\hitbox_armorplate_kevlar_class_1.p3d";
	};
	class IA_ArmorHitbox_ArmorPlate_Class_2 : IA_ArmorHitboxBase
	{
		scope = 1;
		model = "ImmersiveArmor\models\hitboxes\hitbox_armorplate_kevlar_class_2.p3d";
	};
	class IA_ArmorHitbox_ArmorPlate_Class_3 : IA_ArmorHitboxBase
	{
		scope = 1;
		model = "ImmersiveArmor\models\hitboxes\hitbox_armorplate_kevlar_class_3.p3d";
	};
	class IA_ArmorHitbox_ArmorPlate_Class_4 : IA_ArmorHitboxBase
	{
		scope = 1;
		model = "ImmersiveArmor\models\hitboxes\hitbox_armorplate_kevlar_class_4.p3d";
	};
	class IA_ArmorHitbox_ArmorPlate_Class_5 : IA_ArmorHitboxBase
	{
		scope = 1;
		model = "ImmersiveArmor\models\hitboxes\hitbox_armorplate_kevlar_class_5.p3d";
	};
	class IA_ArmorHitbox_ArmorPlate_Class_6 : IA_ArmorHitboxBase
	{
		scope = 1;
		model = "ImmersiveArmor\models\hitboxes\hitbox_armorplate_kevlar_class_6.p3d";
	};

	class  IA_ArmorHitbox_BallisticHelmet : IA_HelmetHitboxBase
	{
		scope = 1;
		model = "ImmersiveArmor\models\hitboxes\hitbox_ballistichelmet.p3d";
	};

	class  IA_ArmorHitbox_BallisticHelmetCamo : IA_HelmetHitboxBase
	{
		scope = 1;
		model = "ImmersiveArmor\models\hitboxes\hitbox_ballistichelmetcamo.p3d";
	};

	class  IA_ArmorHitbox_Ssh68Helmet : IA_HelmetHitboxBase
	{
		scope = 1;
		model = "ImmersiveArmor\models\hitboxes\hitbox_ssh68helmet.p3d";
	};

	class  IA_ArmorHitbox_Mich2001Helmet : IA_HelmetHitboxBase
	{
		scope = 1;
		model = "ImmersiveArmor\models\hitboxes\hitbox_mich2001helmet.p3d";
	};

	class  IA_ArmorHitbox_GorkaHelmet : IA_HelmetHitboxBase
	{
		scope = 1;
		model = "ImmersiveArmor\models\hitboxes\hitbox_gorkahelmet.p3d";
	};

	class  IA_ArmorHitbox_GorkaVisor : IA_HelmetHitboxBase
	{
		scope = 1;
		model = "ImmersiveArmor\models\hitboxes\hitbox_gorkahelmetvisor.p3d";
	};

	//PoliceVest
	class  IA_ArmorHitbox_PoliceVest_Top : IA_HelmetHitboxBase
	{
		scope = 1;
		model = "ImmersiveArmor\models\hitboxes\hitbox_policevest_top.p3d";
	};
	class  IA_ArmorHitbox_PoliceVest_Low : IA_HelmetHitboxBase
	{
		scope = 1;
		model = "ImmersiveArmor\models\hitboxes\hitbox_policevest_low.p3d";
	};
	class  IA_ArmorHitbox_PoliceVest_Sides : IA_HelmetHitboxBase
	{
		scope = 1;
		model = "ImmersiveArmor\models\hitboxes\hitbox_policevest_sides.p3d";
	};

	//PressVest
	class  IA_ArmorHitbox_PressVest_Top : IA_HelmetHitboxBase
	{
		scope = 1;
		model = "ImmersiveArmor\models\hitboxes\hitbox_pressvest_top.p3d";
	};
	class  IA_ArmorHitbox_PressVest_Low : IA_HelmetHitboxBase
	{
		scope = 1;
		model = "ImmersiveArmor\models\hitboxes\hitbox_pressvest_low.p3d";
	};
	class  IA_ArmorHitbox_PressVest_Sides : IA_HelmetHitboxBase
	{
		scope = 1;
		model = "ImmersiveArmor\models\hitboxes\hitbox_pressvest_sides.p3d";
	};

	//PlateCarrier
	class  IA_ArmorHitbox_PlateCarrier_Sides : IA_HelmetHitboxBase
	{
		scope = 1;
		model = "ImmersiveArmor\models\hitboxes\hitbox_platecarrier_sides.p3d";
	};

	class IA_ArmorPlateRU_Base: Inventory_Base
	{
		scope = 1;
		displayName = "$STR_IA_ArmorPlateRU0";
		descriptionShort = "$STR_IA_ArmorPlateRU1";
		model = "ImmersiveArmor\models\armorplate\armorplate.p3d";
		hiddenSelections[] = {"zbytek"};
		itemSize[] = {2,3};
		rotationFlags = 1;
		absorbency = 0;
		soundImpactType = "metal";
		inventorySlot[] = { "IA_ArmorPlateFront", "IA_ArmorPlateBack" };
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 225;
					healthLevels[] = {{1.0,{"ImmersiveArmor\models\armorplate\armorplate.rvmat"}},{0.7,{"ImmersiveArmor\models\armorplate\armorplate.rvmat"}},{0.5,{"ImmersiveArmor\models\armorplate\armorplate_damage.rvmat"}},{0.3,{"ImmersiveArmor\models\armorplate\armorplate_damage.rvmat"}},{0.0,{"ImmersiveArmor\models\armorplate\armorplate_destruct.rvmat"}}};
				};
			};
		};
	};
	class IA_ArmorPlateRU_Class_1: IA_ArmorPlateRU_Base
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"ImmersiveArmor\models\armorplate\armorplate_1_co.paa"};
		weight = 800;
	};
	class IA_ArmorPlateRU_Class_2: IA_ArmorPlateRU_Base
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"ImmersiveArmor\models\armorplate\armorplate_2_co.paa"};
		weight = 1600;
	};
	class IA_ArmorPlateRU_Class_3: IA_ArmorPlateRU_Base
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"ImmersiveArmor\models\armorplate\armorplate_3_co.paa"};
		weight = 2100;
	};
	class IA_ArmorPlateRU_Class_4: IA_ArmorPlateRU_Base
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"ImmersiveArmor\models\armorplate\armorplate_4_co.paa"};
		weight = 3700;
	};
	class IA_ArmorPlateRU_Class_5: IA_ArmorPlateRU_Base
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"ImmersiveArmor\models\armorplate\armorplate_5_co.paa"};
		weight = 4300;
	};
	class IA_ArmorPlateRU_Class_6: IA_ArmorPlateRU_Base
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"ImmersiveArmor\models\armorplate\armorplate_6_co.paa"};
		weight = 5100;
	};

	class Clothing;
	class PlateCarrierVest: Clothing
	{
		attachments[] += {"IA_ArmorPlateFront", "IA_ArmorPlateBack"};
		weight = 1500;
		class DamageSystem
		{
			class GlobalArmor
			{
				class Projectile
				{
					class Health
					{
						damage = 1;//0.3
					};
					class Blood
					{
						damage = 0;
					};
					class Shock
					{
						damage = 1;//0.6
					};
				};
			};
		};
	};
	class BallisticHelmet_ColorBase: Clothing
	{
		class DamageSystem
		{
			class GlobalArmor
			{
				class Projectile
				{
					class Health
					{
						damage = 1;//0.25
					};
					class Blood
					{
						damage = 0;
					};
					class Shock
					{
						damage = 1;//0.5
					};
				};
			};
		};
	};
	class GorkaHelmet: Clothing
	{
		class DamageSystem
		{
			class GlobalArmor
			{
				class Projectile
				{
					class Health
					{
						damage = 1;//0.25
					};
					class Blood
					{
						damage = 0;
					};
					class Shock
					{
						damage = 1;//0.5
					};
				};
			};
		};
	};
	class Mich2001Helmet: Clothing
	{
		class DamageSystem
		{
			class GlobalArmor
			{
				class Projectile
				{
					class Health
					{
						damage = 1;//0.25
					};
					class Blood
					{
						damage = 0;
					};
					class Shock
					{
						damage = 1;//0.5
					};
				};
			};
		};
	};
	class Ssh68Helmet: Clothing
	{
		class DamageSystem
		{
			class GlobalArmor
			{
				class Projectile
				{
					class Health
					{
						damage = 1;//0.25
					};
					class Blood
					{
						damage = 0;
					};
					class Shock
					{
						damage = 1;//0.5
					};
				};
			};
		};
	};
	class PoliceVest: Clothing
	{
		class DamageSystem
		{
			class GlobalArmor
			{
				class Projectile
				{
					class Health
					{
						damage = 1;//0.5
					};
					class Blood
					{
						damage = 0;
					};
					class Shock
					{
						damage = 1;//0.75
					};
				};
			};
		};
	};
	class PressVest_ColorBase: Clothing
	{
		class DamageSystem
		{
			class GlobalArmor
			{
				class Projectile
				{
					class Health
					{
						damage = 1;//0.5
					};
					class Blood
					{
						damage = 0;
					};
					class Shock
					{
						damage = 1;//0.75
					};
				};
			};
		};
	};
};
// Penetration doesn't seem to factor in projectile weight(at least, my tests didn't confirm it).
// Some calibers don't penetrate as much as they should based on weight, so I had to modify the caliber parameter to compensate.
// This does not change damage or range, only penetration depth, so your custom weapon balancing should remain unaffected.
class CfgAmmo
{
	class MeleeDamage;
	class DamageApplied;
	class Bullet_Base;
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
				//armorDamage = 3; No need for that anymore, it never worked properly anyway.
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
	class IA_Ammo_ArmorBlunt_Base : MeleeDamage
	{
		hitAnimation = 0;
		class DamageApplied
		{
			type = "Melee";
			bleedThreshold = 0;
		};
	};
	// For custom ammo just add "IA_ArmorBlunt_" and copy DamageApplied.  
	// Don't forget "DamageApplied : DamageApplied", otherwise the hitbox won't do any damage when hit. 
	class IA_ArmorBlunt_Bullet_12GaugePellets : IA_Ammo_ArmorBlunt_Base
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
	class IA_ArmorBlunt_Bullet_12GaugeSlug : IA_Ammo_ArmorBlunt_Base
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
	class IA_ArmorBlunt_Bullet_12GaugeRubberSlug : IA_Ammo_ArmorBlunt_Base
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
	class IA_ArmorBlunt_Bullet_12GaugeBeanbag : IA_Ammo_ArmorBlunt_Base
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
	class IA_ArmorBlunt_Bullet_556x45 : IA_Ammo_ArmorBlunt_Base
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
	class IA_ArmorBlunt_Bullet_545x39 : IA_Ammo_ArmorBlunt_Base
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
	class IA_ArmorBlunt_Bullet_762x54 : IA_Ammo_ArmorBlunt_Base
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
	class IA_ArmorBlunt_Bullet_308Win : IA_Ammo_ArmorBlunt_Base
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
	class IA_ArmorBlunt_Bullet_762x39 : IA_Ammo_ArmorBlunt_Base
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
	class IA_ArmorBlunt_Bullet_45ACP : IA_Ammo_ArmorBlunt_Base
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
	class IA_ArmorBlunt_Bullet_357 : IA_Ammo_ArmorBlunt_Base
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
	class IA_ArmorBlunt_Bullet_9x19 : IA_Ammo_ArmorBlunt_Base
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
	class IA_ArmorBlunt_Bullet_380 : IA_Ammo_ArmorBlunt_Base
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
	class IA_ArmorBlunt_Bullet_22 : IA_Ammo_ArmorBlunt_Base
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
	class IA_ArmorBlunt_Bullet_9x39 : IA_Ammo_ArmorBlunt_Base
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
	class IA_ArmorBlunt_Bullet_9x39AP : IA_Ammo_ArmorBlunt_Base
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