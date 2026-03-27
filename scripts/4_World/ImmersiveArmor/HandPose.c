modded class ModItemRegisterCallbacks
{
    override void RegisterOneHanded(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
    {
        super.RegisterOneHanded(pType, pBehavior);

        pType.AddItemInHandsProfileIK("IA_ArmorPlateRU_Base", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "IA_ImmersiveArmor/models/armorplate/armorplate.anm");
    }
};