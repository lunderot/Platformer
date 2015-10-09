
local controls =	{
						up		= GetKeyCodeFromName("W"),
						down	= GetKeyCodeFromName("S"),
						left	= GetKeyCodeFromName("A"),
						right	= GetKeyCodeFromName("D"),
						spinr	= GetKeyCodeFromName("X"),
						spinl	= GetKeyCodeFromName("Z")
					}
local force = 20

function playerInput(key, state, repeating)
	local id = GetFirstPlayerId()
	if not repeating then
		if key == controls.up and state == 1 then
			ApplyImpulse(id, 0, -force, 1)
		elseif key == controls.down and state == 1 then
			ApplyImpulse(id, 0, force, 1)
		end

		if key == controls.left and state == 1 then
			ApplyImpulse(id, -force, 0, 1)
		elseif key == controls.right and state == 1 then
			ApplyImpulse(id, force, 0, 1)
		end

		if key == controls.spinl and state == 1 then
			ApplyImpulseOffset(id, 0, -force, 1, 1, 0)
		elseif key == controls.spinr and state == 1 then
			ApplyImpulseOffset(id, 0, force, 1, 1, 0)
		end
	end
end
addEventHandler("keyboardEvent", playerInput)
