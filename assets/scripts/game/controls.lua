
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
		SetEntityAcceleration(GetFirstPlayerId(), input.x, input.y+gravity)
		local xvel, yvel = GetEntityVelocity(GetFirstPlayerId())
		SetEntityVelocity(GetFirstPlayerId(), xvel, yvel+jump)
	end
end
addEventHandler("keyboardEvent", playerInput)

function playerTeleport(button, clicks, state, x, y)
	if state == 1 and button == 3 then
		local wx, wy = GetWorldPositionFromScreenPosition(x, y)
		SetEntityPosition(GetFirstPlayerId(), wx, wy)
		SetEntityVelocity(GetFirstPlayerId(), 0, 0)
	end
end
addEventHandler("mouseButtonEvent", playerTeleport)