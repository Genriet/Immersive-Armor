modded class PlayerBase
{
	protected ref array<Object> m_IWL_ExcludeFromRaycast = {};

	void IWL_AddToExclusions(Object obj)
	{
		m_IWL_ExcludeFromRaycast.Insert(obj);
	}

	void IWL_RemoveFromExclusions(Object obj)
	{
		m_IWL_ExcludeFromRaycast.RemoveItem(obj);
	}

	array<Object> IWL_GetExclusions()
	{
		return m_IWL_ExcludeFromRaycast;
	}
	
	void IWL_ClearExclusions()
	{
		m_IWL_ExcludeFromRaycast.Clear();
	}
};

modded class Weapon_Base
{
	override bool LiftWeaponCheckEx(PlayerBase player, out float outObstruction, out Object outHitObject)
	{
		bool wasLift = m_LiftWeapon;
		vector lastLiftPosition = m_LastLiftPosition;
		
		m_LiftWeapon = false;

		// [14.2.2025]
		// The following selection check should be *unused* for some time now.
		// Leaving commented out for future reference, should the removal have unforseen consequences.
		//	if ( HasSelection("Usti hlavne") )
		//		return false;

		if (!player)
		{
			#ifndef SERVER
			#ifdef DIAG_DEVELOPER
				PluginDiagMenuClient.GetWeaponLiftDiag().Reset();
			#endif
			#endif
			Print("Error: No weapon owner for LiftWeaponCheckEx, returning.");
			return false;
		}
		
		// Obstruction can only occur if the weapon is rasied
		HumanMovementState movementState = new HumanMovementState();
		player.GetMovementState(movementState);
		if (!movementState.IsRaised())
			return false;
		
		// Suppress weapon obstruction during melee attack preventing state inconsistency
		if (movementState.m_CommandTypeId == DayZPlayerConstants.COMMANDID_MELEE || movementState.m_CommandTypeId == DayZPlayerConstants.COMMANDID_MELEE2)
		{
			#ifndef SERVER
			#ifdef DIAG_DEVELOPER
				PluginDiagMenuClient.GetWeaponLiftDiag().Reset();
			#endif
			#endif
			return false;
		}
		
		
		// If possible use aiming angles instead as these will work consistently
		// and independently of any cameras, etc.
		vector direction;
		HumanInputController hic = player.GetInputController();
		HumanCommandWeapons hcw = player.GetCommandModifier_Weapons();
		HumanCommandMove hcm = player.GetCommand_Move();
		if (hcw)
		{
			vector yawPitchRoll = Vector(
				hcw.GetBaseAimingAngleLR() + player.GetOrientation()[0],
				hcw.GetBaseAimingAngleUD(),
				0.0);
			
			float xAimHandsOffset = hcw.GetAimingHandsOffsetLR();
			float yAimHandsOffset = hcw.GetAimingHandsOffsetUD();
			
			yawPitchRoll[0] = yawPitchRoll[0] + xAimHandsOffset;
			yawPitchRoll[1] = Math.Clamp( yawPitchRoll[1] + yAimHandsOffset, DayZPlayerCamera1stPerson.CONST_UD_MIN, DayZPlayerCamera1stPerson.CONST_UD_MAX );
			
			direction = yawPitchRoll.AnglesToVector();
		}
		else // Fallback to previously implemented logic
		{
			// freelook raycast
			if (hic.CameraIsFreeLook())
			{
				if (player.m_DirectionToCursor != vector.Zero)
				{
					direction = player.m_DirectionToCursor;
				}
				// if player raises weapon in freelook
				else
				{
					direction = MiscGameplayFunctions.GetHeadingVector(player);
				}
			}
			else
			{
				direction = GetGame().GetCurrentCameraDirection(); // exception for freelook. Much better this way!
			}
		}
		
		// Reference bone to perform checks from
		vector start;
		int boneIdx = player.GetBoneIndexByName("Neck");
		if (boneIdx == -1)
		{
			start = player.GetPosition()[1] + 1.5;
		}
		else
		{
			 start = player.GetBonePositionWS(boneIdx);
		}
		
		// Update the ray origin and direction with approximations of character state
		vector velocity = GetVelocity(player);
		velocity = player.VectorToLocal(velocity);
		ApproximateWeaponLiftTransform(start, direction, movementState, hic, hcw, hcm, velocity);
		
		float effectiveAttachmentLength = GetEffectiveAttachmentLength();

		// weapon length including effective attachments
		float weaponLength = m_WeaponLength + effectiveAttachmentLength;
		// distance of point from 'shoulder' (start) from which the weapon length should be computed,
		// pistols have the start point further, near the character wrist whereas longer rifles, typically
		// the ones with buttstocks have the start point at 0 distance, ie. directly at shoulder	
		float weaponStartDist = m_ShoulderDistance;
		float weaponEndDist = weaponStartDist + weaponLength;
		
		// Weapon start and end positions as an offset from the character shoulder
		vector weaponStart = start + (weaponStartDist * direction);
		vector weaponEnd = start + (weaponEndDist * direction);
		
		// distance of point from 'shoulder' (start) at which the weapon is "fully obstructed", i.e.
		// needs to be lifted to be able to be physically fit wherever it is. Shifted by effective
		// attachment length to account for e.g. suppressors that make the weapon "longer".
		// Defaults to FLT_MAX if no value is configured, effectivelly always lifting weapon instead of obstructing.
		float baseObstructionLength = m_ObstructionDistance;
		if (baseObstructionLength==0)
		{
			baseObstructionLength = ApproximateBaseObstructionLength();
		}
		
		float weaponObstructionDist = baseObstructionLength + effectiveAttachmentLength;
		float rayRadius = 0.02;
		
		#ifndef SERVER
		#ifdef DIAG_DEVELOPER // Retrieve possible override
		float overrideObstDist = PluginDiagMenuClient.GetWeaponLiftDiag().Data().m_ObstructionDistance;
		PluginDiagMenuClient.GetWeaponLiftDiag().Data().SetWeaponRayParams(start, direction, weaponStartDist, weaponEndDist, effectiveAttachmentLength, m_ObstructionDistance, weaponObstructionDist, rayRadius);
		weaponObstructionDist = overrideObstDist;
		rayRadius = PluginDiagMenuClient.GetWeaponLiftDiag().Data().m_RayRadiusOverride;
		#endif
		#endif

		// Extend the raycast range by 30 cm to allow checking for intersections even
		// under shallow angles and other odd cases
		float rayEndDist = weaponEndDist + 0.30;
		vector rayEnd = start + rayEndDist * direction;
		
		// Prepare raycast params and perform the cast in fire geo
		RaycastRVParams rayParm = new RaycastRVParams(start, rayEnd, player, rayRadius);
		rayParm.flags = CollisionFlags.ALLOBJECTS;
		rayParm.type = ObjIntersect.Fire;
		
		RaycastRVResult hitResult;
		float hitFraction;
		float hitDist;
		
		array<ref RaycastRVResult> results = {};
		if (!DayZPhysics.RaycastRVProxy(rayParm, results) || results.Count() == 0)
		{
			hitFraction = 0;
		}
		else
		{
			// In case of multiple results, find the best (nearest) match, RaycastRVProxy doesn't guarantee any sensible order
			int numRes = results.Count();
			if (numRes == 1)
			{
				if (IWL_ShouldExcludeFromRaycast(player, results[0].obj)) // [Improved Weapon Lift] No result when object is an exclusion
				{
					hitResult = null;
				}
				else
				{
					hitResult = results[0];
				}
			}
			else
			{
				int bi = -1;
				float maxDist = float.MAX;
				for (int i = 0, nr = results.Count(); i < nr; ++i)
				{
					if (!IWL_ShouldExcludeFromRaycast(player, results[i].obj)) // [Improved Weapon Lift] Only proceed when object is not an exclusion
					{
						float sqDist = vector.DistanceSq(results[i].pos, weaponStart);
						if (sqDist < maxDist)
						{
							maxDist = sqDist;
							bi = i;
						}
					}
				}

				// [Improved Weapon Lift] Failsafe just in case array doesn't handle -1 index internally
				if (bi != -1)
				{
					hitResult = results[bi];
				}
				else
				{
					hitResult = null;
				}
			}

			if (hitResult && LiftWeaponRaycastResultCheck(hitResult))
			{
				float len0 = (hitResult.pos - start).Length();
				float len1 = (weaponEnd - start).Length(); // Do not include 'rayEnd' - pretend as if the computation happened in <start, weaponEnd>
				
				if (len0 <= 0 || len1 <= 0)
				{
					hitFraction = 1;
				}
				else
				{
					hitFraction = len0 / len1;
				}
				hitDist = hitFraction * weaponEndDist;
			}
			else
			{
				hitFraction = 0;
				hitDist = 0;
			}
		}
			
		#ifndef SERVER
		#ifdef DIAG_DEVELOPER	// isect diag
		PluginDiagMenuClient.GetWeaponLiftDiag().Data().SetIntersectionParams(hitResult, hitFraction, hitDist);
		PluginDiagMenuClient.GetWeaponLiftDiag().Data().SetLastPosition(lastLiftPosition);
		#endif	// !isect diag
		#endif
		
		// Start by assuming that we want to retain state
		bool wantsLift = wasLift;
		
		// Sq. distance of weapon movement required to trigger lift (in)
		const float inThreshold = 0.002;
		// Sq. distance of weapon movement required to trigger lift (out)
		const float outThreshold = 0.003;
		const float noIsctOutThreshold = 0.01;
		// Max num of ticks with no hit for which hysteresis will persist
		// value chosen by iteration, should be approx 0.333s
		const int maxNumMissedTicks = 10;
		
		// Min angle in degrees change from last lift to stop lifting
		// Base threshold of 0.75 degrees + 0.6 degrees per meter of weapon length
		float angleThreshold = 0.75 + Math.Clamp( m_WeaponLength * 0.6, 0, 1.5 );
		
		// Update state when a hit is registered
		if (hitFraction != 0)
		{
			vector v1 = hitResult.pos - weaponEnd;
			vector v2 = hitResult.pos - rayEnd;
			float d = vector.Dot(v1, v2);
			// But leave some threshold where previous state is kept
			// to prevent excessive switches from occuring
			if (!wasLift && d > inThreshold)
			{
				wantsLift = true;
			}
			else if (wasLift && d < -outThreshold)
			{
				wantsLift = false;
			}
			
			m_LastLiftPosition = hitResult.pos;
			m_LastLiftHit = player.GetSimulationTimeStamp();
		}
		else
		{
			// With no hit and no previous lift
			if (lastLiftPosition == vector.Zero)
			{
				wantsLift = false;
				m_LastLiftPosition = vector.Zero;
			}
			// See if previous hit wasn't very close to our current position,
			// in which case simply don't lift the weapon
			else
			{
				vector v3 = (lastLiftPosition - start).Normalized();
				vector v4 = (weaponEnd-start).Normalized();
				float d2 = vector.Dot(v3, v4);
				// no isect, angle delta check
				if (Math.Acos(d2) > (angleThreshold * Math.DEG2RAD)) // if relative angle is > x degree, stop lifting
				{
					wantsLift = false;
					m_LastLiftPosition = vector.Zero;
				}
				// no isect, distance check
				else
				{
					float d3 = vector.Dot( lastLiftPosition - weaponEnd, (start-weaponEnd).Normalized() );
					if (d3 < -noIsctOutThreshold)
					{
						wantsLift = false;
						m_LastLiftPosition = vector.Zero;
					}
					float lastObstruction = hcw.GetWeaponObstruction();	
					// fallback in case offending object disappears or moves
					int timeSinceHit = player.GetSimulationTimeStamp() - m_LastLiftHit;
					if (timeSinceHit > maxNumMissedTicks)
					{
						wantsLift = false;
						m_LastLiftPosition = vector.Zero;
					}
					else if (wantsLift && m_LastLiftPosition != vector.Zero) // pretended hit to retain obstruction in this very tight edge case
					{
						float l0 = (m_LastLiftPosition - start).Length();
						float l1 = (weaponEnd - start).Length();
						if (l0 <= 0 || l1 <= 0)
						{
							hitFraction = 1;
						}
						else
						{
							hitFraction = l0 / l1;
						}
						hitDist = hitFraction * weaponEndDist;
					}
				}
			}
		}
		
		// lift is desired
		if (wantsLift)
		{
			// Remap the hit distance into the <obstruction, weaponWithAttachmentLength> range as 0..1 (and beyond)
			float begDist = weaponObstructionDist;
			float endDist = weaponStartDist + weaponLength;
			
			float obstFraction;
			if (begDist < endDist)
				obstFraction = Math.InverseLerp( begDist, endDist, hitDist );
			
			if (hitResult)
				outHitObject = hitResult.obj;
			
			outObstruction 	= 1.0 - obstFraction;
			m_LiftWeapon 	= true;
			return true;
		}

		return false;
	}

	bool IWL_ShouldExcludeFromRaycast(PlayerBase player, Object obj)
	{
		return (player.IWL_GetExclusions().Find(obj) != -1);
	}
};