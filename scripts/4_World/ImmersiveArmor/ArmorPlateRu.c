class IA_ArmorPlateRU_Base : ItemBase 
{
    // Add armor class at the end of description.
    override string GetTooltip()
    {   
        string type = GetType();
		return super.GetTooltip() + " " + type.Substring(type.Length() - 1, 1) + ".";
    }
};