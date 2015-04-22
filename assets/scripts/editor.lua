local placeType = 1

function placeTypeChange(key, state, repeating)
	if state == 1 and not repeating then
		if key == GetKeyCodeFromName("1") then
			placeType = 1
		elseif key == GetKeyCodeFromName("2") then
			placeType = 2
		end
	end
end
addEventHandler("keyboardEvent", placeTypeChange)

local isPlacingLine = false
local line = {}

function mouseButtonEventHandler(button, clicks, state, x, y)
	if placeType == 1 and state == 1 and clicks == 1 then
		if isPlacingLine then
			line.x2, line.y2 = GetWorldPositionFromScreenPosition(x, y)
			print("2: " .. line.x2 .." " .. line.y2)
			AddCollisionLine(line.x1, line.y1, line.x2, line.y2)
			isPlacingLine = false
		else
			line.x1, line.y1 = GetWorldPositionFromScreenPosition(x, y)
			print("1: " .. line.x1 .." " .. line.y1)
			isPlacingLine = true
		end
	end
end
addEventHandler("mouseButtonEvent", mouseButtonEventHandler)