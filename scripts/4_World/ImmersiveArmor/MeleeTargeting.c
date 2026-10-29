modded class MeleeTargeting
{
	protected EntityAI m_IA_Attacker;
	protected Object m_IA_Target;

	override MeleeTargetData GetMeleeTargetEx(MeleeTargetSettings settings, out array<Object> allTargets = null, array<string> blacklistedDamageZones = null)
	{
		m_IA_Attacker = settings.Attacker;
		MeleeTargetData ret = super.GetMeleeTargetEx(settings, allTargets, blacklistedDamageZones);
		m_IA_Attacker = null;
		m_IA_Target = null;
		return ret;
	}

	override bool EvaluateComponentEx(Object obj, ComponentInfo cInfo, MeleeTargetSettings settings, out ComponentResult result, array<string> blacklistedDamageZones)
	{
		m_IA_Target = obj;
		return super.EvaluateComponentEx(obj, cInfo, settings, result, blacklistedDamageZones);
	}

	override bool IsMeleeTargetObstructed(vector rayStart, vector rayEnd)
	{
		if (rayStart == rayEnd)
			return true;

        //New raycast only for players
		PlayerBase attacker = PlayerBase.Cast(m_IA_Attacker);
		if (!attacker)
			return super.IsMeleeTargetObstructed(rayStart, rayEnd);

        //Replacing bullet raycast with rv to pass array of objects to ignore
		RaycastRVParams params = new RaycastRVParams(rayStart, rayEnd, attacker);
		params.type = ObjIntersectView;
		params.sorted = true;

		array<ref RaycastRVResult> results = new array<ref RaycastRVResult>;
		bool hit = DayZPhysics.RaycastRVProxy(params, results, attacker.IWL_GetExclusions());

		if (!hit)
			return false;

		foreach (RaycastRVResult res : results)
		{
			if (m_IA_Target && (res.obj == m_IA_Target || res.parent == m_IA_Target))
				continue;

			return true;
		}

		return false;
	}
};