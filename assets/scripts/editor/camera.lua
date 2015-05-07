local tileSize = 70

function cameraInput(key, state, repeating)
	local input = { x = 0, y = 0 }
	if not repeating then
		if key == GetKeyCodeFromName("A") then
			if state == 1 then
				input.x = -tileSize
			else
				input.x = 0
			end
		elseif key == GetKeyCodeFromName("D") then
			if state == 1 then
				input.x = tileSize
			else
				input.x = 0
			end
		end
		if key == GetKeyCodeFromName("W") then
			if state == 1 then
				input.y = -tileSize
			else
				input.y = 0
			end
		elseif key == GetKeyCodeFromName("S") then
			if state == 1 then
				input.y = tileSize
			else
				input.y = 0
			end
		end
		local camx, camy = GetEntityPosition(GetCameraId())
		SetEntityPosition(GetCameraId(), camx + input.x, camy + input.y)
	end
end
addEventHandler("keyboardEvent", cameraInput)