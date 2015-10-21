local controls =	{
						reset	= GetKeyCodeFromName("R")
					}
local force = 20

function playerInput(key, state, repeating)
	local id = GetFirstPlayerId()
	if not repeating then
		if key == controls.reset and state == 1 then
			SetPosition(GetFirstPlayerId(), 390.167, 400)
		end
	end
end
addEventHandler("keyboardEvent", playerInput)
