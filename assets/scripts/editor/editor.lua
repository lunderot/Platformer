require "math"

local placeType = 1

local isPlacingLine = false
local line = {}

local tileSize = 70

function getNearestMultiple(number, multiple)
	return math.floor(number / multiple) * multiple
end

function placeTypeChange(key, state, repeating)
	if state == 1 and not repeating then
		if key == GetKeyCodeFromName("1") then
			placeType = 1
		elseif key == GetKeyCodeFromName("2") then
			isPlacingLine = false
			placeType = 2
		end
	end
end
addEventHandler("keyboardEvent", placeTypeChange)

function placeTypeChange(key, state, repeating)
	if state == 1 and not repeating then
		if key == GetKeyCodeFromName("F8") then
			SaveToFile("assets/maps/test.map")
		end
	end
end
addEventHandler("keyboardEvent", placeTypeChange)

function mouseButtonEventHandler(button, clicks, state, x, y)
	if state == 1 and clicks == 1 then
		if placeType == 1 then --Place collision line
			if isPlacingLine then
				line.x2, line.y2 = GetWorldPositionFromScreenPosition(x, y)
				print("2: " .. line.x2 .." " .. line.y2)
				line.x1 = getNearestMultiple(line.x1, tileSize) + tileSize / 2
				line.y1 = getNearestMultiple(line.y1, tileSize) + tileSize / 2
				line.x2 = getNearestMultiple(line.x2, tileSize) + tileSize / 2
				line.y2 = getNearestMultiple(line.y2, tileSize) + tileSize / 2
				AddCollisionLine(line.x1, line.y1, line.x2, line.y2)
				isPlacingLine = false
			else
				line.x1, line.y1 = GetWorldPositionFromScreenPosition(x, y)
				print("1: " .. line.x1 .." " .. line.y1)
				isPlacingLine = true
			end
		elseif placeType == 2 then --Place tile
			local tpx, tpy = GetWorldPositionFromScreenPosition(x, y)
			local tilePos = {
								x = getNearestMultiple(tpx + tileSize/2, tileSize),
								y = getNearestMultiple(tpy + tileSize/2, tileSize)
							}
			
			local id = AddEntity(1, "assets/textures/tiles/box.png", tileSize)
			SetEntityPosition(id, tilePos.x, tilePos.y)
		end
	end
end
addEventHandler("mouseButtonEvent", mouseButtonEventHandler)