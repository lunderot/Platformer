
local jumpVelocity = -300
local walkAcceleration = 500
local gravity = 500

function playerInput(key, state, repeating)
	local input = { x = 0, y = 0 }
	local jump = 0
	if not repeating then

		if key == GetKeyCodeFromName("W") then
			if state == 1 then
				jump = jumpVelocity
			end
		end


		if key == GetKeyCodeFromName("A") then
			if state == 1 then
				input.x = -walkAcceleration
			else
				input.x = 0
			end
		elseif key == GetKeyCodeFromName("D") then
			if state == 1 then
				input.x = walkAcceleration
			else
				input.x = 0
			end
		end
		SetEntityAcceleration(0, input.x, input.y+gravity)
		local xvel, yvel = GetEntityVelocity(0)
		SetEntityVelocity(0, xvel, yvel+jump)
	end
end
addEventHandler("keyboardEvent", playerInput)