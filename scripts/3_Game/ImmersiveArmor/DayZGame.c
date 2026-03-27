class ImmersiveArmor_Config
{
    ref map<string, ref IA_ItemArmorProperties> Items = new map<string, ref IA_ItemArmorProperties>();
    ref map<string, ref IA_HitboxProperties> Hitboxes = new map<string, ref IA_HitboxProperties>();
};
class IA_HitboxProperties
{
    float DamageCoefEntity;
	float DamageCoefItem;
	string DamageZone;
};
class IA_ItemArmorProperties
{
    ref array<ref IA_ArmorHitbox_Data> PermanentHitboxes = {};
    ref map<string, ref array<ref IA_ArmorHitbox_Data>> SlotOverrides = new map<string, ref array<ref IA_ArmorHitbox_Data>>();
};
class IA_ArmorHitbox_Data
{
    string HitboxType;
	string HitboxBone;
	vector PositionOffset;
	vector RotationOffset;

    void IA_ArmorHitbox_Data(string type, string bone, vector pos, vector rot)
	{
		HitboxType = type;
		HitboxBone = bone;
		PositionOffset = pos;
		RotationOffset = rot;
	}
};
modded class DayZGame
{
    protected ref ImmersiveArmor_Config m_ImmersiveArmor_Config;

	ImmersiveArmor_Config GetImmersiveArmor_Config()
	{
		if (!m_ImmersiveArmor_Config)
		{
			if (!FileExist("$profile:\\ImmersiveArmor"))
			{
				MakeDirectory("$profile:\\ImmersiveArmor");
			}
			if (!FileExist("$profile:\\ImmersiveArmor\\ImmersiveArmor.json"))
			{
				m_ImmersiveArmor_Config = IA_CreateDefaultConfig();

				JsonFileLoader<ImmersiveArmor_Config>.JsonSaveFile("$profile:\\ImmersiveArmor\\ImmersiveArmor.json", m_ImmersiveArmor_Config);
			}
			else
			{
				JsonFileLoader<ImmersiveArmor_Config>.JsonLoadFile("$profile:\\ImmersiveArmor\\ImmersiveArmor.json", m_ImmersiveArmor_Config);

				if (!m_ImmersiveArmor_Config)
				{
					m_ImmersiveArmor_Config = IA_CreateDefaultConfig();
					ErrorEx("IMMERSIVE ARMOR JSON IS INVALID, USING DEFAULT ONE. REGENERATE JSON");
				}
			}
		}
		return m_ImmersiveArmor_Config;
	}

	ImmersiveArmor_Config IA_CreateDefaultConfig()
    {
        ImmersiveArmor_Config config = new ImmersiveArmor_Config();

        // ==================== VESTS ====================

        // PlateCarrierVest
        IA_ItemArmorProperties plateCarrier = new IA_ItemArmorProperties();
        plateCarrier.PermanentHitboxes.Insert(new IA_ArmorHitbox_Data("IA_ArmorHitbox_PlateCarrier_Sides", "Spine2", "0 0.02 0", "0 0 -7"));
        array<ref IA_ArmorHitbox_Data> frontOverride = { new IA_ArmorHitbox_Data("", "Spine3", "0.05 0.16 0", "0 0 7.5") };
        plateCarrier.SlotOverrides.Insert("IA_ArmorPlateFront", frontOverride);
        array<ref IA_ArmorHitbox_Data> backOverride = { new IA_ArmorHitbox_Data("", "Spine3", "0.05 -0.1 0", "0 0 4") };
        plateCarrier.SlotOverrides.Insert("IA_ArmorPlateBack", backOverride);
        config.Items.Insert("PlateCarrierVest", plateCarrier);

        // PoliceVest
        IA_ItemArmorProperties policeVest = new IA_ItemArmorProperties();
        policeVest.PermanentHitboxes.Insert(new IA_ArmorHitbox_Data("IA_ArmorHitbox_PoliceVest_Sides", "Spine2", "0.02 0.02 0", "0 0 -7"));
        policeVest.PermanentHitboxes.Insert(new IA_ArmorHitbox_Data("IA_ArmorHitbox_PoliceVest_Top", "Spine3", "0.09 0.025 0", "0 0 0"));
        policeVest.PermanentHitboxes.Insert(new IA_ArmorHitbox_Data("IA_ArmorHitbox_PoliceVest_Low", "Spine2", "-0.01 0.01 0", "0 0 -7.5"));
        config.Items.Insert("PoliceVest", policeVest);

        // PressVest_ColorBase
        IA_ItemArmorProperties pressVest = new IA_ItemArmorProperties();
        pressVest.PermanentHitboxes.Insert(new IA_ArmorHitbox_Data("IA_ArmorHitbox_PressVest_Sides", "Spine2", "-0.035 0 0", "0 0 -5"));
        pressVest.PermanentHitboxes.Insert(new IA_ArmorHitbox_Data("IA_ArmorHitbox_PressVest_Top", "Spine3", "0.105 0.025 0", "0 0 0"));
        pressVest.PermanentHitboxes.Insert(new IA_ArmorHitbox_Data("IA_ArmorHitbox_PressVest_Low", "Spine2", "-0.01 0 0", "0 0 -6"));
        config.Items.Insert("PressVest_ColorBase", pressVest);

        // ==================== HELMETS ====================

        // BallisticHelmet_ColorBase
        IA_ItemArmorProperties ballisticHelmet = new IA_ItemArmorProperties();
        ballisticHelmet.PermanentHitboxes.Insert(new IA_ArmorHitbox_Data("IA_ArmorHitbox_BallisticHelmet", "Head", "0.08 0 0", "0 0 0"));
        config.Items.Insert("BallisticHelmet_ColorBase", ballisticHelmet);

        // BallisticHelmet_BDU
        IA_ItemArmorProperties bduHelmet = new IA_ItemArmorProperties();
        bduHelmet.PermanentHitboxes.Insert(new IA_ArmorHitbox_Data("IA_ArmorHitbox_BallisticHelmetCamo", "Head", "0.08 0 0", "0 0 0"));
        config.Items.Insert("BallisticHelmet_BDU", bduHelmet);

        // BallisticHelmet_Desert
        IA_ItemArmorProperties desertHelmet = new IA_ItemArmorProperties();
        desertHelmet.PermanentHitboxes.Insert(new IA_ArmorHitbox_Data("IA_ArmorHitbox_BallisticHelmetCamo", "Head", "0.08 0 0", "0 0 0"));
        config.Items.Insert("BallisticHelmet_Desert", desertHelmet);

        // BallisticHelmet_Woodland
        IA_ItemArmorProperties woodlandHelmet = new IA_ItemArmorProperties();
        woodlandHelmet.PermanentHitboxes.Insert(new IA_ArmorHitbox_Data("IA_ArmorHitbox_BallisticHelmetCamo", "Head", "0.08 0 0", "0 0 0"));
        config.Items.Insert("BallisticHelmet_Woodland", woodlandHelmet);

        // BallisticHelmet_Winter
        IA_ItemArmorProperties winterHelmet = new IA_ItemArmorProperties();
        winterHelmet.PermanentHitboxes.Insert(new IA_ArmorHitbox_Data("IA_ArmorHitbox_BallisticHelmetCamo", "Head", "0.08 0 0", "0 0 0"));
        config.Items.Insert("BallisticHelmet_Winter", winterHelmet);

        // BallisticHelmet_Navy
        IA_ItemArmorProperties navyHelmet = new IA_ItemArmorProperties();
        navyHelmet.PermanentHitboxes.Insert(new IA_ArmorHitbox_Data("IA_ArmorHitbox_BallisticHelmetCamo", "Head", "0.08 0 0", "0 0 0"));
        config.Items.Insert("BallisticHelmet_Navy", navyHelmet);

        // Ssh68Helmet
        IA_ItemArmorProperties ssh68 = new IA_ItemArmorProperties();
        ssh68.PermanentHitboxes.Insert(new IA_ArmorHitbox_Data("IA_ArmorHitbox_Ssh68Helmet", "Head", "0.07 0 0", "0 0 0"));
        config.Items.Insert("Ssh68Helmet", ssh68);

        // Mich2001Helmet
        IA_ItemArmorProperties mich2001 = new IA_ItemArmorProperties();
        mich2001.PermanentHitboxes.Insert(new IA_ArmorHitbox_Data("IA_ArmorHitbox_Mich2001Helmet", "Head", "0.07 -0.02 0", "0 0 0"));
        config.Items.Insert("Mich2001Helmet", mich2001);

        // GorkaHelmet
        IA_ItemArmorProperties gorkaHelmet = new IA_ItemArmorProperties();
        gorkaHelmet.PermanentHitboxes.Insert(new IA_ArmorHitbox_Data("IA_ArmorHitbox_GorkaHelmet", "Head", "0.08 0 0", "0 0 0"));
        array<ref IA_ArmorHitbox_Data> glassOverride = { new IA_ArmorHitbox_Data("", "Head", "0.07 0 0", "0 0 3") };
        gorkaHelmet.SlotOverrides.Insert("Glass", glassOverride);
        config.Items.Insert("GorkaHelmet", gorkaHelmet);

        // GorkaHelmetVisor
        IA_ItemArmorProperties gorkaVisor = new IA_ItemArmorProperties();
        gorkaVisor.PermanentHitboxes.Insert(new IA_ArmorHitbox_Data("IA_ArmorHitbox_GorkaVisor", "", "0 0 0", "0 0 0"));
        config.Items.Insert("GorkaHelmetVisor", gorkaVisor);

        // ==================== ARMOR PLATES ====================

        IA_ItemArmorProperties plateClass1 = new IA_ItemArmorProperties();
        plateClass1.PermanentHitboxes.Insert(new IA_ArmorHitbox_Data("IA_ArmorHitbox_ArmorPlate_Class_1", "", "0 0 0", "0 0 0"));
        config.Items.Insert("IA_ArmorPlateRU_Class_1", plateClass1);

        IA_ItemArmorProperties plateClass2 = new IA_ItemArmorProperties();
        plateClass2.PermanentHitboxes.Insert(new IA_ArmorHitbox_Data("IA_ArmorHitbox_ArmorPlate_Class_2", "", "0 0 0", "0 0 0"));
        config.Items.Insert("IA_ArmorPlateRU_Class_2", plateClass2);

        IA_ItemArmorProperties plateClass3 = new IA_ItemArmorProperties();
        plateClass3.PermanentHitboxes.Insert(new IA_ArmorHitbox_Data("IA_ArmorHitbox_ArmorPlate_Class_3", "", "0 0 0", "0 0 0"));
        config.Items.Insert("IA_ArmorPlateRU_Class_3", plateClass3);

        IA_ItemArmorProperties plateClass4 = new IA_ItemArmorProperties();
        plateClass4.PermanentHitboxes.Insert(new IA_ArmorHitbox_Data("IA_ArmorHitbox_ArmorPlate_Class_4", "", "0 0 0", "0 0 0"));
        config.Items.Insert("IA_ArmorPlateRU_Class_4", plateClass4);

        IA_ItemArmorProperties plateClass5 = new IA_ItemArmorProperties();
        plateClass5.PermanentHitboxes.Insert(new IA_ArmorHitbox_Data("IA_ArmorHitbox_ArmorPlate_Class_5", "", "0 0 0", "0 0 0"));
        config.Items.Insert("IA_ArmorPlateRU_Class_5", plateClass5);

        IA_ItemArmorProperties plateClass6 = new IA_ItemArmorProperties();
        plateClass6.PermanentHitboxes.Insert(new IA_ArmorHitbox_Data("IA_ArmorHitbox_ArmorPlate_Class_6", "", "0 0 0", "0 0 0"));
        config.Items.Insert("IA_ArmorPlateRU_Class_6", plateClass6);

        // ==================== HITBOX PROPERTIES ====================

        IA_HitboxProperties armorHitboxBase = new IA_HitboxProperties();
        armorHitboxBase.DamageCoefEntity = 0.5;
        armorHitboxBase.DamageCoefItem = 0.3;
        armorHitboxBase.DamageZone = "Torso";
        config.Hitboxes.Insert("IA_ArmorHitboxBase", armorHitboxBase);
    
        IA_HitboxProperties helmetHitboxBase = new IA_HitboxProperties();
        helmetHitboxBase.DamageCoefEntity = 0.1;
        helmetHitboxBase.DamageCoefItem = 0.3;
        helmetHitboxBase.DamageZone = "Head";
        config.Hitboxes.Insert("IA_HelmetHitboxBase", helmetHitboxBase);

        return config;
    }
};