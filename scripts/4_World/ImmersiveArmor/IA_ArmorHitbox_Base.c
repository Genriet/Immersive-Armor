class IA_ArmorHitbox_Base extends ItemBase
{
#ifdef SERVER
	// Variables to transfer damage
	protected EntityAI ImmersiveArmor_ParentPlayer;
	protected EntityAI ImmersiveArmor_ParentItem;
	protected float ImmersiveArmor_DamageCoefPlayer;
	protected float ImmersiveArmor_DamageCoefItem;
	protected string ImmersiveArmor_DamageZone;

	override void EEInit()
	{
		super.EEInit();
		ImmersiveArmor_InitHitbox();

		// We don't want this hitbox to be takeable, don't we?
		SetTakeable(false);
	}

	// Check if config exists for hitbox.
	protected void ImmersiveArmor_InitHitbox()
	{
		if (ConfigIsExisting("ImmersiveArmorHitbox"))
		{
			string IA_Path = "CfgVehicles " + GetType() + " ImmersiveArmorHitbox ";
			ImmersiveArmor_DamageCoefPlayer = GetGame().ConfigGetFloat(IA_Path + "damageCoefPlayer");
			ImmersiveArmor_DamageCoefItem = GetGame().ConfigGetFloat(IA_Path + "damageCoefItem");
			GetGame().ConfigGetText(IA_Path + "damageZone", ImmersiveArmor_DamageZone);
		}
		else
			ErrorEx("ImmersiveArmor: " + GetType() + " does not have ImmersiveArmorHitbox config defined.", ErrorExSeverity.WARNING);
	}

	// Transfer damage to linked player and item.
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		if (ImmersiveArmor_ParentPlayer)
		{
			ImmersiveArmor_ParentPlayer.ProcessDirectDamage(DamageType.CLOSE_COMBAT, source, ImmersiveArmor_DamageZone, ImmersiveArmor_GetValidDamageType(ammo), modelPos, speedCoef * ImmersiveArmor_DamageCoefPlayer);
		}
		if (ImmersiveArmor_ParentItem)
		{
			ImmersiveArmor_ParentItem.ProcessDirectDamage(DamageType.CLOSE_COMBAT, source, ImmersiveArmor_DamageZone, ImmersiveArmor_GetValidDamageType(ammo), modelPos, speedCoef * ImmersiveArmor_DamageCoefItem);
		}

		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
	};

	protected string ImmersiveArmor_GetValidDamageType(string ammo)
	{
		if (GetGame().ConfigIsExisting("CfgAmmo IA_ArmorBlunt_" + ammo))
			return "IA_ArmorBlunt_" + ammo;
		ErrorEx("ImmersiveArmor: " + ammo + " does not have melee damage defined, using projectile damage.", ErrorExSeverity.WARNING);
		return ammo; // If no valid melee damage type found, return original ammo type.
	}

	// Assigning linked item.
	void ImmersiveArmor_SetParentItem(EntityAI parent)
	{
		ImmersiveArmor_ParentItem = parent;
	}

	// Assigning linked player.
	override void EEParentedTo(EntityAI parent)
	{
		super.EEParentedTo(parent);
		ImmersiveArmor_ParentPlayer = parent;
	}

#else
#ifdef ImprovedWeaponLift

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

#endif
#endif
};