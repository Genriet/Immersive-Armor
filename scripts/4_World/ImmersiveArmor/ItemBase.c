#ifdef SERVER
modded class ItemBase
{
	bool IA_IsArmorPiece = false;
	ref array<string> IA_ArmorTypes = {};
	ref array<string> IA_ArmorBones = {};
	ref array<string> IA_ArmorPosOffset = {};
	ref array<string> IA_ArmorRotOffset = {};
	ref array<string> IA_ArmorSpecialSlots = {};
	ref array<int> IA_ArmorSpecialSlotsId = {};

	ref array<string> IA_DamageZoneOverrides = {};
	ref array<float> IA_DamageCoefPlayerOverrides = {};
	ref array<float> IA_DamageCoefItemOverrides = {};

	ref array<IA_ArmorHitbox_Base> IA_ArmorPieces = {};

	// ConfigGetChildrenCount reads everything, not just subclasses, so this is needed to exclude arrays.  
	ref array<string> IA_DayzIsRetarded = {"armorTypes","armorBones","armorPosOffset","armorRotOffset","damageZone","damageCoefPlayer","damageCoefItem"};

	// For some reason, only calling it in the constructor works properly, not in init or deferredInit.  
	void ItemBase()
	{
		IA_SetupArmor();
	}

	//Just reading config
	void IA_SetupArmor()
	{
		if (ConfigIsExisting("ImmersiveArmor"))
		{
			IA_IsArmorPiece = true;

			string IA_Path = "CfgVehicles " + GetType() + " ImmersiveArmor";
			GetGame().ConfigGetTextArray(IA_Path + " armorTypes", IA_ArmorTypes);
			GetGame().ConfigGetTextArray(IA_Path + " armorBones", IA_ArmorBones);
			GetGame().ConfigGetTextArray(IA_Path + " armorPosOffset", IA_ArmorPosOffset);
			GetGame().ConfigGetTextArray(IA_Path + " armorRotOffset", IA_ArmorRotOffset);

			int children = GetGame().ConfigGetChildrenCount(IA_Path);
			if (children > 0)
			{
				IA_ArmorSpecialSlotsId.Clear();
				IA_ArmorSpecialSlots.Clear();
				for (int i = 0; i < children; i++)
				{
					string child;
					GetGame().ConfigGetChildName(IA_Path, i, child);

					int slot = InventorySlots.GetSlotIdFromString(child);
					if (slot != InventorySlots.INVALID)
					{
						IA_ArmorSpecialSlotsId.Insert(slot);
						IA_ArmorSpecialSlots.Insert(child);
					}
					else
					{
						if (IA_DayzIsRetarded.Find(child) == -1)
						{
							ErrorEx("ImmersiveArmor: Slot override " + child + " is not in attachments or is misspelled", ErrorExSeverity.WARNING);
						}
					}
				}
			}

			GetGame().ConfigGetTextArray(IA_Path + " damageZone", IA_DamageZoneOverrides);
			GetGame().ConfigGetFloatArray(IA_Path + " damageCoefPlayer", IA_DamageCoefPlayerOverrides);
			GetGame().ConfigGetFloatArray(IA_Path + " damageCoefItem", IA_DamageCoefItemOverrides);
		}
		else
		{
			IA_IsArmorPiece = false;
		}
	}

	// Check parent's config for overrides for my slot.  
	void IA_TryApplyOverridesFromParent(EntityAI parent, int slot_id)
	{
		ItemBase item = ItemBase.Cast(parent);
		if (!item || !item.IA_IsArmorPiece)
		{
			return;
		}

		int arrayIndex = item.IA_ArmorSpecialSlotsId.Find(slot_id);
		if (arrayIndex > -1)
		{
			string IA_Path = "CfgVehicles " + item.GetType() + " ImmersiveArmor " + item.IA_ArmorSpecialSlots[arrayIndex];

			if (GetGame().ConfigIsExisting(IA_Path))
			{
				GetGame().ConfigGetTextArray(IA_Path + " armorBones", IA_ArmorBones);
				GetGame().ConfigGetTextArray(IA_Path + " armorPosOffset", IA_ArmorPosOffset);
				GetGame().ConfigGetTextArray(IA_Path + " armorRotOffset", IA_ArmorRotOffset);

				GetGame().ConfigGetTextArray(IA_Path + " damageZone", IA_DamageZoneOverrides);
				GetGame().ConfigGetFloatArray(IA_Path + " damageCoefPlayer", IA_DamageCoefPlayerOverrides);
				GetGame().ConfigGetFloatArray(IA_Path + " damageCoefItem", IA_DamageCoefItemOverrides);
			}
		}
	}

	// Check that the bone index is valid and spawn the hitbox with all properties applied.  
	void IA_CheckValidBoneAndAddChild(int id, EntityAI parent, IA_ArmorHitbox_Base armorPiece, int i)
	{
		if (id > -1)
		{
			armorPiece.SetPosition(IA_ArmorPosOffset[i].ToVector());
			armorPiece.SetOrientation(IA_ArmorRotOffset[i].ToVector());
			IA_FuckDayZItIsRetardedAndDontLetMeDoThingsTheEasyWay_CheckValidOverridesForHitbox(armorPiece, i);
			parent.AddChild(armorPiece, id);
			IA_ArmorPieces.Insert(armorPiece);
		}
		else
		{
			ErrorEx("ImmersiveArmor: Bone " + IA_ArmorBones[i] + " is misspelled or doesn't exist", ErrorExSeverity.WARNING);
		}
	}

	//Don't ask
	void IA_FuckDayZItIsRetardedAndDontLetMeDoThingsTheEasyWay_CheckValidOverridesForHitbox(IA_ArmorHitbox_Base armorPiece, int i)
	{
		string tempZone = "no";
		float tempCoefItem = -1;
		float tempCoefPlayer = -1;

		if (IA_DamageZoneOverrides.IsValidIndex(i))
		{
			tempZone = IA_DamageZoneOverrides[i];
		}
		if (IA_DamageCoefPlayerOverrides.IsValidIndex(i))
		{
			tempCoefPlayer = IA_DamageCoefPlayerOverrides[i];
		}
		if (IA_DamageCoefItemOverrides.IsValidIndex(i))
		{
			tempCoefItem = IA_DamageCoefItemOverrides[i];
		}

		armorPiece.IA_SetupParentItemAndOverrides(this, tempZone, tempCoefPlayer, tempCoefItem);
	}

	// Check all attachments of this item to see if they need to spawn or despawn their own hitboxes.  
	void IA_CheckAttachments(EntityAI parent, bool attach)
	{
		for (int i = 0; i < GetInventory().AttachmentCount(); i++)
		{
			ItemBase attachment = ItemBase.Cast(GetInventory().GetAttachmentFromIndex(i));
			if (attachment)
			{
				if (attach)
				{
					attachment.IA_TryAttachArmorPieces(parent);
				}
				else
				{
					attachment.IA_TryDetachArmorPieces(parent);
				}
			}
		}
	}

	// Trying to spawn hitboxes.
	void IA_TryAttachArmorPieces(EntityAI parent)
	{
		if (!IA_IsArmorPiece || IA_ArmorPieces.Count() > 0)
		{
			IA_CheckAttachments(parent, true);
			return;
		}

		// There is no common hierarchy root for these classes that has GetBoneIndexByName(), so each one has to be checked individually.  
		PlayerBase player = PlayerBase.Cast(parent);
		ZombieBase zombie = ZombieBase.Cast(parent);
		AnimalBase animal = AnimalBase.Cast(parent);
		if (parent.GetHierarchyRoot())
		{
			player = PlayerBase.Cast(parent.GetHierarchyRoot());
			zombie = ZombieBase.Cast(parent.GetHierarchyRoot());
			animal = AnimalBase.Cast(parent.GetHierarchyRoot());
		}
		if (player || zombie || animal)
		{
			for (int i = 0; i < IA_ArmorTypes.Count(); i++)
			{
				IA_ArmorHitbox_Base armorPiece = IA_ArmorHitbox_Base.Cast(GetGame().CreateObject(IA_ArmorTypes[i], GetPosition()));
				if (armorPiece)
				{
					if (player)
					{
						IA_CheckValidBoneAndAddChild(player.GetBoneIndexByName(IA_ArmorBones[i]), player, armorPiece, i);
					}
					else if (zombie)
					{
						IA_CheckValidBoneAndAddChild(zombie.GetBoneIndexByName(IA_ArmorBones[i]), zombie, armorPiece, i);
					}
					else if (animal)
					{
						IA_CheckValidBoneAndAddChild(animal.GetBoneIndexByName(IA_ArmorBones[i]), animal, armorPiece, i);
					}
				}
				else
				{
					ErrorEx("ImmersiveArmor: " + IA_ArmorTypes[i] + " misspelled classname or is not inherited from IA_ArmorHitbox_Base", ErrorExSeverity.WARNING);
				}
			}
			// After spawning its own, check attachments.  
			IA_CheckAttachments(parent, true);
		}
	}
	// Trying to despawn hitboxes, same logic as spawn.
	void IA_TryDetachArmorPieces(EntityAI parent)
	{
		if (!IA_IsArmorPiece || IA_ArmorPieces.Count() == 0)
		{
			IA_CheckAttachments(parent, false);
			return;
		}

		PlayerBase player = PlayerBase.Cast(parent);
		ZombieBase zombie = ZombieBase.Cast(parent);
		AnimalBase animal = AnimalBase.Cast(parent);
		if (parent.GetHierarchyRoot())
		{
			player = PlayerBase.Cast(parent.GetHierarchyRoot());
			zombie = ZombieBase.Cast(parent.GetHierarchyRoot());
			animal = AnimalBase.Cast(parent.GetHierarchyRoot());
		}
		if (player || zombie || animal)
		{
			for (int i = 0; i < IA_ArmorPieces.Count(); i++)
			{

				if (player)
				{
					player.RemoveChild(IA_ArmorPieces[i]);
				}
				else if (zombie)
				{
					zombie.RemoveChild(IA_ArmorPieces[i]);
				}
				else if (animal)
				{
					animal.RemoveChild(IA_ArmorPieces[i]);
				}

				GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Call(GetGame().ObjectDelete, IA_ArmorPieces[i]);
			}
			IA_ArmorPieces.Clear();
			IA_CheckAttachments(parent, false);
		}
	}

	override void OnWasAttached(EntityAI parent, int slot_id)
	{
		super.OnWasAttached(parent, slot_id);

		// Applying overrides before spawning hitboxes.
		IA_TryApplyOverridesFromParent(parent, slot_id);
		IA_TryAttachArmorPieces(parent);
	}

	override void OnWasDetached(EntityAI parent, int slot_id)
	{
		super.OnWasDetached(parent, slot_id);

		IA_TryDetachArmorPieces(parent);
		// Resetting overrides as the item is no longer in the slot.  
		IA_SetupArmor();
	}

	// Called when the item is ruined.
	override void EEKilled(Object killer)
	{
		if (IA_IsArmorPiece)
		{
			IA_TryDetachArmorPieces(this);
		}

		super.EEKilled(killer);
	}

	override void EEDelete(EntityAI parent)
	{
		if (IA_IsArmorPiece)
		{
			IA_TryDetachArmorPieces(parent);
		}

		super.EEDelete(parent);
	}
};
#endif