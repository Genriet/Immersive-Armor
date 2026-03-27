#ifdef SERVER
modded class ItemBase
{
    protected ref array<ref IA_ArmorHitbox_Data> m_IA_PermanentArmorHitboxesData = {};
    protected ref map<string, ref array<ref IA_ArmorHitbox_Data>> m_IA_SlotOverrideArmorHitboxesData = new map<string, ref array<ref IA_ArmorHitbox_Data>>();
    protected ref array<IA_ArmorHitboxBase> m_IA_ArmorHitboxes = {};

    void ItemBase()
    {
        IA_SetArmorHitboxesData();
    }

    void IA_SetArmorHitboxesData()
    {
        ImmersiveArmor_Config cfg = GetDayZGame().GetImmersiveArmor_Config();
        if (!cfg || !cfg.Items)
            return;

        IA_ItemArmorProperties itemCfg = cfg.Items.Get(GetType());

        if (!itemCfg)
        {
            for (int i = 0; i < cfg.Items.Count(); i++)
            {
                string configKey = cfg.Items.GetKey(i);
                if (configKey == "") continue;

                typename configType = configKey.ToType();
                if (configType && IsInherited(configType))
                {
                    itemCfg = cfg.Items.Get(configKey);
                    break;
                }
            }
        }

        if (!itemCfg)
            return;

        m_IA_PermanentArmorHitboxesData.Clear();
        foreach (IA_ArmorHitbox_Data data : itemCfg.PermanentHitboxes)
        {
            m_IA_PermanentArmorHitboxesData.Insert(new IA_ArmorHitbox_Data(data.HitboxType, data.HitboxBone, data.PositionOffset, data.RotationOffset));
        }

        m_IA_SlotOverrideArmorHitboxesData.Clear();
        if (itemCfg.SlotOverrides)
        {
            for (int j = 0; j < itemCfg.SlotOverrides.Count(); j++)
            {
                string slotName = itemCfg.SlotOverrides.GetKey(j);
                array<ref IA_ArmorHitbox_Data> overrides = itemCfg.SlotOverrides.Get(slotName);

                array<ref IA_ArmorHitbox_Data> copiedList = new array<ref IA_ArmorHitbox_Data>();
                foreach (IA_ArmorHitbox_Data ov : overrides)
                {
                    copiedList.Insert(new IA_ArmorHitbox_Data(ov.HitboxType, ov.HitboxBone, ov.PositionOffset, ov.RotationOffset));
                }

                m_IA_SlotOverrideArmorHitboxesData.Insert(slotName, copiedList);
            }
        }
    }

    void IA_AddArmorHitboxesSlotOverride(string slotName, IA_ArmorHitbox_Data data)
    {
        array<ref IA_ArmorHitbox_Data> list = m_IA_SlotOverrideArmorHitboxesData[slotName];

        if (!list)
            list = new array<ref IA_ArmorHitbox_Data>;

        list.Insert(data);
        m_IA_SlotOverrideArmorHitboxesData.Insert(slotName, list);
    }

    map<string, ref array<ref IA_ArmorHitbox_Data>> IA_GetSlotOverrideArmorHitboxesData()
    {
        return m_IA_SlotOverrideArmorHitboxesData;
    }

    array<ref IA_ArmorHitbox_Data> IA_GetCorrectedArmorHitboxData(EntityAI parent, string slotName)
    {
        array<ref IA_ArmorHitbox_Data> permList = m_IA_PermanentArmorHitboxesData;

        ItemBase item = ItemBase.Cast(parent);
        if (!item) return permList;

        array<ref IA_ArmorHitbox_Data> overrideList = item.IA_GetSlotOverrideArmorHitboxesData().Get(slotName);

        array<ref IA_ArmorHitbox_Data> correctedList = {};

        for (int i = 0; i < permList.Count(); i++)
        {
            IA_ArmorHitbox_Data perm = permList.Get(i);
            IA_ArmorHitbox_Data copy = new IA_ArmorHitbox_Data(perm.HitboxType, perm.HitboxBone, perm.PositionOffset, perm.RotationOffset);

            if (overrideList && i < overrideList.Count())
            {
                IA_ArmorHitbox_Data over = overrideList.Get(i);

                // Only override non-defaults
                if (over.HitboxType != "") copy.HitboxType = over.HitboxType;
                if (over.HitboxBone != "") copy.HitboxBone = over.HitboxBone;
                if (over.PositionOffset != "0 0 0") copy.PositionOffset = over.PositionOffset;
                if (over.RotationOffset != "0 0 0") copy.RotationOffset = over.RotationOffset;
            }

            correctedList.Insert(copy);
        }

        return correctedList;
    }

    void IA_TryAttachAllArmorHitboxes(EntityAI parent)
    {
        string slotName = IA_GetAttachedToSlotName();
        if (slotName == "") return;

        array<ref IA_ArmorHitbox_Data> correctedHitboxData = IA_GetCorrectedArmorHitboxData(parent, slotName);
        if (correctedHitboxData.Count() == 0) return;

        EntityAI root = parent.GetHierarchyRoot();

        PlayerBase player = PlayerBase.Cast(root);
        ZombieBase zombie = ZombieBase.Cast(root);
        AnimalBase animal = AnimalBase.Cast(root);

        foreach (IA_ArmorHitbox_Data hitboxData : correctedHitboxData)
        {
            int boneIndex = -1;
            if (player) boneIndex = player.GetBoneIndexByName(hitboxData.HitboxBone);
            else if (zombie) boneIndex = zombie.GetBoneIndexByName(hitboxData.HitboxBone);
            else if (animal) boneIndex = animal.GetBoneIndexByName(hitboxData.HitboxBone);
            
            if (boneIndex == -1) continue;

            IA_TryAttachArmorHitbox(root, hitboxData, boneIndex);
        }

        IA_CheckAttachmentsForHitboxes(parent, true);
    }

    void IA_TryAttachArmorHitbox(EntityAI root, IA_ArmorHitbox_Data hitboxData, int boneIndex)
    {
		IA_ArmorHitboxBase hitbox = IA_ArmorHitboxBase.Cast(GetGame().CreateObject(hitboxData.HitboxType, GetPosition()));
		if (!hitbox) return;

		root.AddChild(hitbox, boneIndex);
		hitbox.SetPosition(hitboxData.PositionOffset);
		hitbox.SetOrientation(hitboxData.RotationOffset);

		hitbox.IA_ArmorHitbox_SetParentItem(this);
        hitbox.IA_ArmorHitbox_SetParentEntity(root);

		m_IA_ArmorHitboxes.Insert(hitbox);
    }

    void IA_CheckAttachmentsForHitboxes(EntityAI parent, bool attach)
	{
		for (int i = 0; i < GetInventory().AttachmentCount(); i++)
		{
			ItemBase attachment = ItemBase.Cast(GetInventory().GetAttachmentFromIndex(i));
			if (!attachment) continue;

            if (attach)
            {
                
                attachment.IA_TryAttachAllArmorHitboxes(this);
            }
            else
            {
                attachment.IA_TryDetachAllArmorHitboxes(this);
            }
		}
    }

    void IA_TryDetachAllArmorHitboxes(EntityAI parent)
	{
		foreach (IA_ArmorHitboxBase hitbox : m_IA_ArmorHitboxes)
		{
			if (parent)
            {
				parent.RemoveChild(hitbox);
            }
			hitbox.Delete();
		}
		m_IA_ArmorHitboxes.Clear();

        IA_CheckAttachmentsForHitboxes(parent, false);
	}

    override void OnWasAttached(EntityAI parent, int slot_id)
	{
		super.OnWasAttached(parent, slot_id);

		IA_TryAttachAllArmorHitboxes(parent);
	}

	override void OnWasDetached(EntityAI parent, int slot_id)
	{
		super.OnWasDetached(parent, slot_id);

		IA_TryDetachAllArmorHitboxes(parent);
	}

    override void EEKilled(Object killer)
	{
		if (m_IA_ArmorHitboxes.Count() > 0)
        {
			IA_TryDetachAllArmorHitboxes(this);
        }

		super.EEKilled(killer);
	}

	override void EEDelete(EntityAI parent)
	{
		if (m_IA_ArmorHitboxes.Count() > 0)
        {
			IA_TryDetachAllArmorHitboxes(parent);
        }

		super.EEDelete(parent);
	}
};
#endif