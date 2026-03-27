class IA_ArmorHitboxBase extends ItemBase
{
#ifdef SERVER
    protected EntityAI IA_ArmorHitbox_ParentEntity;
	protected EntityAI IA_ArmorHitbox_ParentItem;

	protected float IA_ArmorHitbox_DamageCoefEntity;
	protected float IA_ArmorHitbox_DamageCoefItem;
	protected string IA_ArmorHitbox_DamageZone;

    override void EEInit()
	{
		super.EEInit();

		SetTakeable(false);
		IA_ArmorHitbox_SetProperties();
	}

	void IA_ArmorHitbox_SetProperties()
	{
		ImmersiveArmor_Config cfg = GetDayZGame().GetImmersiveArmor_Config();
        if (!cfg || !cfg.Hitboxes)
            return;

        IA_HitboxProperties hitboxCfg = cfg.Hitboxes.Get(GetType());

        if (!hitboxCfg)
        {
            for (int i = 0; i < cfg.Hitboxes.Count(); i++)
            {
                string configKey = cfg.Hitboxes.GetKey(i);
                if (configKey == "") continue;

                typename configType = configKey.ToType();
                if (configType && IsInherited(configType))
                {
                    hitboxCfg = cfg.Hitboxes.Get(configKey);
                    break;
                }
            }
        }

        if (!hitboxCfg)
            return;

		IA_ArmorHitbox_DamageCoefEntity = hitboxCfg.DamageCoefEntity;
		IA_ArmorHitbox_DamageCoefItem = hitboxCfg.DamageCoefItem;
		IA_ArmorHitbox_DamageZone = hitboxCfg.DamageZone;
	}

    // Transfer damage to linked entity and item.
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		if (IA_ArmorHitbox_ParentEntity)
		{
			IA_ArmorHitbox_ParentEntity.ProcessDirectDamage(DamageType.CLOSE_COMBAT, source, IA_ArmorHitbox_DamageZone, IA_ArmorHitbox_GetValidDamageType(ammo), modelPos, speedCoef * IA_ArmorHitbox_DamageCoefEntity);
		}
		if (IA_ArmorHitbox_ParentItem)
		{
			IA_ArmorHitbox_ParentItem.ProcessDirectDamage(DamageType.CLOSE_COMBAT, source, IA_ArmorHitbox_DamageZone, IA_ArmorHitbox_GetValidDamageType(ammo), modelPos, speedCoef * IA_ArmorHitbox_DamageCoefItem);
		}

		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
	};

    // Assigning linked item.
	void IA_ArmorHitbox_SetParentItem(EntityAI parent)
	{
		IA_ArmorHitbox_ParentItem = parent;
	}

	// Assigning linked entity.
	void IA_ArmorHitbox_SetParentEntity(EntityAI parent)
	{
		IA_ArmorHitbox_ParentEntity = parent;
	}

    protected string IA_ArmorHitbox_GetValidDamageType(string ammo)
	{
        string ammoType = "IA_ArmorBlunt_" + ammo;
		if (GetGame().ConfigIsExisting("CfgAmmo " + ammoType))
			return ammoType;
		return ammo; // If no valid melee damage type found, return original ammo type.
	}
#endif // SERVER

	// Adding hitbox to the weapon lift exclusions.
	override void EEParentedTo(EntityAI parent)
	{
		super.EEParentedTo(parent);

        PlayerBase player = PlayerBase.Cast(parent);
		if (player)
		{
			player.IWL_AddToExclusions(this);
		}
	}

    // Removing hitbox from the weapon lift exclusions.
	override void EEDelete(EntityAI parent)
	{
		super.EEDelete(parent);

		PlayerBase player = PlayerBase.Cast(parent);
		if (player)
		{
			player.IWL_RemoveFromExclusions(this);
		}
	}
};
class IA_HelmetHitboxBase extends IA_ArmorHitboxBase {};