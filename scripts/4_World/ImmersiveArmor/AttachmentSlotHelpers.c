modded class ItemBase
{
    protected string m_IA_CurrentlyAttachedToSlotName;
    protected int m_IA_CurrentlyAttachedToSlotId;
    protected bool m_IA_CurrentlyAttachedToSlot;

    protected void IA_SetAttachedToSlot(int slotId)
    {
        m_IA_CurrentlyAttachedToSlot = true;
        m_IA_CurrentlyAttachedToSlotId = slotId;
        m_IA_CurrentlyAttachedToSlotName = InventorySlots.GetSlotName(slotId);
    }

    protected void IA_SetDetachedToSlot(int slotId)
    {
        m_IA_CurrentlyAttachedToSlot = false;
        m_IA_CurrentlyAttachedToSlotId = -1;
        m_IA_CurrentlyAttachedToSlotName = "";
    }

    string IA_GetAttachedToSlotName()
    {
        return m_IA_CurrentlyAttachedToSlotName;
    }

    int IA_GetAttachedToSlotId()
    {
        return m_IA_CurrentlyAttachedToSlotId;
    }

    bool IA_IsAttachedToSlot()
    {
        return m_IA_CurrentlyAttachedToSlot;
    }

    override void OnWasAttached(EntityAI parent, int slot_id)
	{
		IA_SetAttachedToSlot(slot_id);

		super.OnWasAttached(parent, slot_id);
	}

	override void OnWasDetached(EntityAI parent, int slot_id)
	{
		IA_SetDetachedToSlot(slot_id);

		super.OnWasDetached(parent, slot_id);
	}
};